/*
 * 1394-Based Digital Camera Control Library
 *
 * Written by Damien Douxchamps <ddouxchamps@users.sf.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <iostream>

#include "CameraS.h"
#include "orbsvcs/CosNamingC.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xvlib.h>
#include <X11/keysym.h>
#define _GNU_SOURCE
#include <getopt.h>
#include <stdint.h>
#include <inttypes.h>

#include <GL/glx.h>
#include <IL/il.h>
#include <IL/ilu.h>

using namespace std;

#include "dc1394/dc1394.h"
//
// Stereo when Higgs cameras. Mono when Adolfo's cameras.
#if defined(__linux__)
//define CAMARA_STEREO 1
#endif

/* uncomment the following to drop frames to prevent delays */
#define MAX_PORTS   4
#define MAX_CAMERAS 8
#define NUM_BUFFERS 6

/* ok the following constant should be by right included thru in Xvlib.h */
#ifndef XV_YV12
#define XV_YV12 0x32315659
#endif

#ifndef XV_YUY2
#define XV_YUY2 0x32595559
#endif

#ifndef XV_UYVY
#define XV_UYVY 0x59565955
#endif


/* declarations for libdc1394 */
int numCameras = 0;
bool capture = 0;
bool capture_start = 0;
bool capture_finish = 0;
bool capture_init = 0;
bool videreStereo = false;
dc1394camera_t *cameras[MAX_CAMERAS];
dc1394featureset_t features;
dc1394video_frame_t * frames[MAX_CAMERAS];
//dc1394video_frame_t * frames2[MAX_CAMERAS];

/* declarations for video1394 */
char *device_name=NULL;

/* declarations for image */
long device_width,device_height;
long format=0;

/* Other declarations */
long frame_length;
short frame=0;
int adaptor=-1;

int freeze=0;
int average=0;
int fps;
int res;

/* image saving variables */
static ILuint image_id = 0;
static GLubyte* image_data = 0;
ILuint image_size1 = 0;

char *frame_buffer1=NULL; // Bayer/YUV
char *frame_buffer2=NULL; // RGB
char *frame_buffer3=NULL; // JPEG
char *frame_buffer4=NULL; // JPEG2

pthread_mutex_t global_jpeg_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t global_dc1394_mutex = PTHREAD_MUTEX_INITIALIZER;

extern FILE *stdout;

static struct option long_options[]={
    {"device",1,NULL,0},
    {"fps",1,NULL,0},
    {"res",1,NULL,0},
    {"help",0,NULL,0},
    {NULL,0,0,0}
};

/* image format conversion functions */

static inline
void iyu12yuy2 (char *src, char *dest, int NumPixels) {
    int i=0,j=0;
    register int y0, y1, y2, y3, u, v;
    while (i < NumPixels*3/2) {
        u = src[i++];
        y0 = src[i++];
        y1 = src[i++];
        v = src[i++];
        y2 = src[i++];
        y3 = src[i++];

        dest[j++] = y0;
        dest[j++] = u;
        dest[j++] = y1;
        dest[j++] = v;

        dest[j++] = y2;
        dest[j++] = u;
        dest[j++] = y3;
        dest[j++] = v;
    }
}

static inline
void rgb2yuy2 (char *RGB,char *YUV, int NumPixels) {
    int i, j;
    register int y0, y1, u0, u1, v0, v1 ;
    register int r, g, b;

    for (i = 0, j = 0; i < 3 * NumPixels; i += 6, j += 4) {
        r = RGB[i + 0];
        g = RGB[i + 1];
        b = RGB[i + 2];
        RGB2YUV (r, g, b, y0, u0 , v0);
        r = RGB[i + 3];
        g = RGB[i + 4];
        b = RGB[i + 5];
        RGB2YUV (r, g, b, y1, u1 , v1);
        YUV[j + 0] = y0;
        YUV[j + 1] = (u0+u1)/2;
        YUV[j + 2] = y1;
        YUV[j + 3] = (v0+v1)/2;
    }
}

/* helper functions */

void set_frame_length(long size, int numCameras)
{
    frame_length=size;
    dc1394_log_debug("Setting frame size to %ld kb",size/1024);
    printf("Tamaño: %ld \n", size);
    frame_buffer1 = (char*) malloc(device_width*device_height*2);   // Bayer/YUV422
    frame_buffer2 = (char*) malloc(device_width*device_height*4*2); // RGB
    frame_buffer3 = (char*) malloc(device_width*device_height*4*2); // JPEG
    frame_buffer4 = (char*) malloc(device_width*device_height*4*2); // JPEG2
}

void cleanup(void) {
    int i;
    for (i=0; i < numCameras; i++) {
        dc1394_video_set_transmission(cameras[i], DC1394_OFF);
        dc1394_capture_stop(cameras[i]);
    }
	pthread_mutex_unlock(&global_dc1394_mutex);

    if (frame_buffer1 != NULL)
        free( frame_buffer1 );
}

static void* camera_loop(void* pthis)
{
    dc1394error_t err;
    int i=0;
	int j=0;
	int k=0;
	capture_start = 1;
    while(true)
    {
		if (capture_finish==1)
		{
			printf("F\n");
			fflush(stdout);
			return 0;
		}

		if (capture_start==1)
		{
			pthread_mutex_lock(&global_dc1394_mutex);
			err = dc1394_capture_dequeue(cameras[0], DC1394_CAPTURE_POLICY_POLL, &frames[0]);
			//err = dc1394_capture_dequeue(cameras[0], DC1394_CAPTURE_POLICY_WAIT, &frames[0]);
			if (err==DC1394_SUCCESS && (frames[0]!=NULL) && (frames[0]->image!=NULL) )
			{
				printf("S");
				fflush(stdout);
				dc1394_capture_enqueue (cameras[0], frames[0]);
				capture_start=0;
			}
			pthread_mutex_unlock(&global_dc1394_mutex);
#if defined(__linux__)
			//pthread_yield();
#endif
			continue;
		}

		pthread_mutex_lock(&global_dc1394_mutex);
		err = dc1394_capture_dequeue(cameras[0], DC1394_CAPTURE_POLICY_POLL, &frames[0]);
		if (err==DC1394_SUCCESS && (frames[0]!=NULL) && (frames[0]->image!=NULL) )
		{
			frame++;
			if (frame>100) frame=0;
			printf("X");
			if (videreStereo==true)
			{
				dc1394_deinterlace_stereo(frames[i]->image,
								(uint8_t*)frame_buffer1 + (i * frame_length),
								device_width, device_height*2);
			} else {
				memcpy(&frame_buffer1[0], frames[i]->image, device_width*device_height*3/2);
			}
			dc1394_capture_enqueue (cameras[0], frames[0]);
		} else if (frames[0]==NULL || frames[0]->image==NULL) {
			k++;
			usleep(100);
			if (k>1000) {
				printf("$");
				k=0;
			}
		} else {
			printf("Error: %d\n", err);
		}
		pthread_mutex_unlock(&global_dc1394_mutex);
		fflush(stdout);
#if defined(__linux__)
		pthread_yield();
		//usleep(15000);
#endif
	}
    //return NULL;
}

static void* camera_loop2(void* pthis)
{
    //dc1394error_t err;
	static short frame2;
    while(true)
    {
		if (frame2==frame) continue;
		frame2=frame;
		if (videreStereo==true)
		{
			dc1394_bayer_decoding_8bit((uint8_t*)&frame_buffer1[0] + (0 * frame_length),
							(uint8_t*)frame_buffer2 + (0 * frame_length),
							device_width, device_height,
							DC1394_COLOR_FILTER_GRBG, DC1394_BAYER_METHOD_SIMPLE);
		} else {
			dc1394_convert_to_RGB8((uint8_t*)&frame_buffer1[0],
							(uint8_t*)&frame_buffer2[0],
							device_width, device_height,
							DC1394_BYTE_ORDER_UYVY,DC1394_COLOR_CODING_YUV411,16);
		}

		pthread_mutex_lock(&global_jpeg_mutex);
		//ilTexImage(device_width, device_height, 1, 4, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		ilTexImage(device_width, device_height, 1, 3, GL_RGB, GL_UNSIGNED_BYTE, image_data);
		ilSetPixels(0, 0, 0, device_width, device_height, 1, IL_RGB, IL_UNSIGNED_BYTE, (ILubyte*) &frame_buffer2[0]);
		image_size1=ilSaveL(IL_JPG, NULL, 0);
		if ( !ilSaveL(IL_JPG, (void *) &frame_buffer3[0], device_width*device_height*3) )
		{
			printf("ERROR1: %d\n", ilGetError() );
			printf("ERROR2: %s\n", iluErrorString( ilGetError() ) );
		}
		pthread_mutex_unlock(&global_jpeg_mutex);
/*
		ilTexImage(device_width, device_height, 1, 4, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		ilSetPixels(0, 0, 0, device_width, device_height, 1, IL_RGB, IL_UNSIGNED_BYTE, (ILubyte*) &frame_buffer2[0]);
		image_size1=ilSaveL(IL_JPG, NULL, 0);
		if ( !ilSaveL(IL_JPG, (void *) &frame_buffer3[0], device_width*device_height*3) )
		{
			printf("ERROR: %d\n", ilGetError() );
		}
*/
#if defined(__linux__)
		pthread_yield();
		//usleep(15000);
#endif

    }
    //return NULL;
}


class Camera_impl : public virtual POA_higgs::Camera {

    void init() {
    	dc1394error_t err;
		printf("\n");

		if (capture_init==0)
		{
			capture_finish = 1;

			pthread_mutex_lock(&global_dc1394_mutex);
			err=dc1394_camera_print_info(cameras[0], stdout);
			DC1394_ERR_CLN(err,cleanup(),"Could not get camera info");

			dc1394featureset_t features;
			err=dc1394_feature_get_all(cameras[0], &features);
			DC1394_ERR_CLN(err,cleanup(),"Could not get camera feature set");

			err=dc1394_feature_print_all(&features, stdout);
			DC1394_ERR_CLN(err,cleanup(),"Could not print camera feature set");
			pthread_mutex_unlock(&global_dc1394_mutex);

			pthread_mutex_lock(&global_jpeg_mutex);
			ilInit();
			ilEnable(IL_NVIDIA_COMPRESS);
			ilGenImages(1, &image_id);
			ilBindImage(image_id);
			//image_data = (GLubyte*)malloc(device_width * device_height * 4 * sizeof(GLubyte));
			image_data = (GLubyte*)malloc(1280 * 960 * 4 * sizeof(GLubyte));
			//ilTexImage(device_width, device_height, 1, 4, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
			ilTexImage(device_width, device_height, 1, 3, GL_RGB, GL_UNSIGNED_BYTE, image_data);
			printf("JPEG Quality: %d", ilGetInteger(IL_JPG_QUALITY));
			ilSetInteger(IL_JPG_QUALITY,70);
			printf("JPEG Quality: %d", ilGetInteger(IL_JPG_QUALITY));
			pthread_mutex_unlock(&global_jpeg_mutex);
			changeRes(getRes());

			pthread_mutex_lock(&global_dc1394_mutex);
			// Perder 1 frames
			int i=0;
			while( i<1 ){
				err = dc1394_capture_dequeue(cameras[0], DC1394_CAPTURE_POLICY_POLL, &frames[0]);
				//printf("o");
				if (err==DC1394_SUCCESS && frames[0]!=NULL) {
					dc1394_capture_enqueue (cameras[0], frames[0]);
					printf("O");
					i++;
				}
				fflush(stdout);
			}
			pthread_mutex_unlock(&global_dc1394_mutex);

			capture_finish = 0;

			pthread_attr_t pt_attr;
			pthread_t      pt_t1, pt_t2;
			pthread_attr_init(&pt_attr);
			pthread_attr_setdetachstate(&pt_attr, PTHREAD_CREATE_DETACHED);
			int code1=pthread_create(&pt_t1, &pt_attr, camera_loop, NULL);
			int code2=pthread_create(&pt_t2, &pt_attr, camera_loop2, NULL);

			capture_init=1;
		}
    }

	char* vendor() {
		return CORBA::string_dup(cameras[0]->vendor);
	}

	char* model() {
		return CORBA::string_dup(cameras[0]->model);
	}

	::CORBA::UShort getFrame () {
		return frame;
	}

	// For Higgs' camera, both images are interlaced with a RGB format, behind the YUV422 specification.
    higgs::ImagenData* getImagen(::CORBA::UShort camera, ::CORBA::Boolean update) throw(CORBA::SystemException) {

		static higgs::ImagenData* datos[2];
		int k = frame_length/2;
		//datos[0]->length(k);
		//datos[1]->length(k);
		if (videreStereo==true)
		{
			datos[0]= new higgs::ImagenData(frame_length/2, (CORBA::Octet*) &frame_buffer1[0], 0);
			datos[1]= new higgs::ImagenData(frame_length/2, (CORBA::Octet*) &frame_buffer1[k], 0);
		} else {
			//datos[0]= new higgs::ImagenData(frame_length, (CORBA::Octet*) &frame_buffer1[0], 0);
			datos[0]= new higgs::ImagenData(frame_length*3/4, (CORBA::Octet*) &frame_buffer1[0], 0);
			datos[1]= new higgs::ImagenData(frame_length/2, (CORBA::Octet*) &frame_buffer1[k], 0);
		}
		int i=0;
		dc1394error_t err;

		if (update==0)
		{
		    	printf("-");
		    	fflush(stdout);
			return datos[camera-1];
		}

		printf("+");
		fflush(stdout);

		return datos[camera-1];
    }


	// For Higgs' camera, both images are interlaced with a RGB format, behind the YUV422 specification.
    higgs::ImagenData* getJPEGImagen(::CORBA::UShort camera, ::CORBA::Boolean update) throw(CORBA::SystemException) {

		static higgs::ImagenData* datos[2];
		static higgs::ImagenData* datosc[2];
		int k = frame_length/2;
		static int l;
		//datos[0]->length(k);
		static bool no_first_run;
		if (videreStereo==true)
		{
			datos[0]= new higgs::ImagenData(frame_length/2, (CORBA::Octet*) &frame_buffer1[0], 0);
			datos[1]= new higgs::ImagenData(frame_length/2, (CORBA::Octet*) &frame_buffer1[k], 0);
			datosc[0]= new higgs::ImagenData(frame_length/2*3, (CORBA::Octet*) &frame_buffer4[0], 0);
			//datosc[1]= new higgs::ImagenData(frame_length/2*3, (CORBA::Octet*) &frame_buffer3[k], 0);
		} else {
			datos[0]= new higgs::ImagenData(frame_length/2*4, (CORBA::Octet*) &frame_buffer1[0], 0);
			datos[1]= new higgs::ImagenData(frame_length/2*4, (CORBA::Octet*) &frame_buffer1[k], 0);
			datosc[0]= new higgs::ImagenData(frame_length/2*3, (CORBA::Octet*) &frame_buffer4[0], 0);
			//datosc[1]= new higgs::ImagenData(frame_length/2*3, (CORBA::Octet*) &frame_buffer3[k], 0);
		}
		if (no_first_run==false)
		{
		    l=0;
		    no_first_run=true;
		}

		if ( update==0 )
		{
		    printf("-");
		    fflush(stdout);
			datosc[0]->length(l);
			return datosc[0];
		}

/*
		// Perder frames si hay mas de 1 frame en el ring buffer
		while( (frames[0]!=NULL) && (frames[0]->frames_behind) > 1 ){
			printf(",[%ld]", frames[0]->frames_behind);
			fflush(stdout);
			err = dc1394_capture_dequeue(cameras[0], DC1394_CAPTURE_POLICY_POLL, &frames[0]);
		    if (err==DC1394_SUCCESS && frames[0]!=NULL) {
				printf(".[%ld]", frames[0]->frames_behind);
				dc1394_capture_enqueue (cameras[0], frames[0]);
				fflush(stdout);
			}
		}
*/

			pthread_mutex_lock(&global_jpeg_mutex);
			memcpy(&frame_buffer4[0], &frame_buffer3[0], image_size1);
			datosc[0]->length(image_size1);
			l=image_size1;
			pthread_mutex_unlock(&global_jpeg_mutex);

/*
			static char filename[512];
			static int frames2;
			sprintf(filename, "/tmp/image2_%.10u.jpg", frames2);
			ilEnable(IL_FILE_OVERWRITE);
			ilSave(IL_JPG, filename);

			sprintf(filename, "/tmp/image3_%.10u.jpg", frames2);
			FILE* File = fopen(filename, "wb");
			//fseek(File, 0, SEEK_SET);
			printf("F:%ld \n", fwrite(frame_buffer3, 1, image_size1, File));
			fclose(File);

			frames2++;
*/

		printf("+");
		fflush(stdout);
		//return datosc[camera-1];
		return datosc[0];
    }


    void changeRes(higgs::CameraResolution res) {
		pthread_mutex_lock(&global_dc1394_mutex);
	    switch (res)
	    {
			case higgs::Res_1280x960:
				::res = DC1394_VIDEO_MODE_1280x960_YUV422;
				break;
			case higgs::Res_1280x960_rgb:
				::res = DC1394_VIDEO_MODE_1280x960_YUV422;
				break;
			case higgs::Res_640x480:
			case higgs::Res_640x480_rgb:
				if ( strcmp("iSight", cameras[0]->model)==0 ) {
					::res = DC1394_VIDEO_MODE_640x480_YUV411;
				} else {
					::res = DC1394_VIDEO_MODE_640x480_YUV422;
				}
				break;
			case higgs::Res_320x240:
				::res = DC1394_VIDEO_MODE_320x240_YUV422;
				break;
			default:
				throw 0;
	    }

	    dc1394error_t err;
	    if(::res== DC1394_VIDEO_MODE_1280x960_YUV422)
	    {
	    	fps = DC1394_FRAMERATE_7_5;
	    	//fps = DC1394_FRAMERATE_3_75;
	    	device_width=1280;
	    	device_height=960;
	    	format=XV_UYVY;
	    }

	    if(::res== DC1394_VIDEO_MODE_640x480_YUV422)
	    {
	    	if (videreStereo==true)
	    	{
	    		fps = DC1394_FRAMERATE_30;
	    		//fps = DC1394_FRAMERATE_15;
	    	} else {
	    		fps = DC1394_FRAMERATE_15;
	    	}
	    	device_width=640;
	    	device_height=480;
	    	format=XV_UYVY;
	    }

		if(::res== DC1394_VIDEO_MODE_640x480_YUV411)
		{
			if (videreStereo==true)
			{
				fps = DC1394_FRAMERATE_30;
				//fps = DC1394_FRAMERATE_15;
			} else {
				fps = DC1394_FRAMERATE_30;
			}
			device_width=640;
			device_height=480;
			format=XV_UYVY;
		}

		printf("\nVideo stop\n");
        err=dc1394_video_set_transmission(cameras[0], DC1394_OFF);
		printf("Capture stop\n");
        err=dc1394_capture_stop(cameras[0]);

		printf("ISO channels release\n");
        //err=dc1394_cleanup_iso_channels_and_bandwidth(cameras[0]);
		err=dc1394_iso_release_all(cameras[0]);

        //err=dc1394_camera_reset(cameras[0]);
        //DC1394_ERR_CLN(err,cleanup(),"Could not reset camera");

		printf("Set video mode\n");
		err=dc1394_video_set_mode(cameras[0], (dc1394video_mode_t)::res);
        DC1394_ERR_CLN(err,cleanup(),"Could not set video mode");

		printf("Set framerate\n");
        err=dc1394_video_set_framerate(cameras[0], (dc1394framerate_t)fps);
        DC1394_ERR_CLN(err,cleanup(),"Could not set framerate");

		printf("Capture Setup\n");
        err=dc1394_capture_setup(cameras[0], NUM_BUFFERS, DC1394_CAPTURE_FLAGS_DEFAULT);
        DC1394_ERR_CLN(err,cleanup(),"Could not setup camera-\nmake sure that the video mode and framerate are\nsupported by your camera");

		printf("Camera ISO transmission\n");
        err=dc1394_video_set_transmission(cameras[0], DC1394_ON);
        DC1394_ERR_CLN(err,cleanup(),"Could not start camera iso transmission");

	    frame_length=device_width*device_height*2;

/*
	    // Perder 1 frames
	    int i=0;
	    while( i<1 ){
    	    err = dc1394_capture_dequeue(cameras[0], DC1394_CAPTURE_POLICY_POLL, &frames[0]);
	        if (err==DC1394_SUCCESS && frames[0]!=NULL) {
	        	dc1394_capture_enqueue (cameras[0], frames[0]);
	    	    printf("O");
	    	    i++;
	        }
    	    fflush(stdout);
	    }
*/
		pthread_mutex_unlock(&global_dc1394_mutex);

	    return;
    }

    higgs::CameraResolution getRes () {
		switch (res)
		{
			case DC1394_VIDEO_MODE_1280x960_YUV422:
				return higgs::Res_1280x960;
			case DC1394_VIDEO_MODE_640x480_YUV422:
				return higgs::Res_640x480;
			case DC1394_VIDEO_MODE_640x480_YUV411:
				return higgs::Res_640x480;
			case DC1394_VIDEO_MODE_320x240_YUV422:
				return higgs::Res_320x240;
			default:
				throw 0;
		}
    }


    ::CORBA::ULong getDeviceWidth () {
		return device_width;
    }

    ::CORBA::ULong getDeviceHeight () {
		return device_height;
    }


    ::CORBA::UShort getGain () {
		uint32_t value;
		dc1394error_t err;
		//pthread_mutex_lock(&global_dc1394_mutex);
		err=dc1394_feature_get_value(cameras[0], DC1394_FEATURE_GAIN, &value);
		//pthread_mutex_unlock(&global_dc1394_mutex);
        DC1394_ERR_CLN_RTN(err,cleanup(),"Could not get camera feature gain");
        return value;
    }

    void setGain (::CORBA::UShort gain) {
		dc1394error_t err;
		//pthread_mutex_lock(&global_dc1394_mutex);
		err=dc1394_feature_set_power(cameras[0], DC1394_FEATURE_GAIN, DC1394_ON);
		err=dc1394_feature_set_value(cameras[0], DC1394_FEATURE_GAIN, gain);
		//pthread_mutex_unlock(&global_dc1394_mutex);
        DC1394_ERR_CLN(err,cleanup(),"Could not set camera feature gain");
    }


    ::CORBA::UShort getBright () {
		uint32_t value;
		dc1394error_t err;
		//pthread_mutex_lock(&global_dc1394_mutex);
		err=dc1394_feature_get_value(cameras[0], DC1394_FEATURE_BRIGHTNESS, &value);
		//pthread_mutex_unlock(&global_dc1394_mutex);
        DC1394_ERR_CLN_RTN(err,cleanup(),"Could not get camera feature brightness");
        return value;
    }

    void setBright (::CORBA::UShort bright) {
    	dc1394error_t err;
		//pthread_mutex_lock(&global_dc1394_mutex);
    	err=dc1394_feature_set_value(cameras[0], DC1394_FEATURE_BRIGHTNESS, bright);
		//pthread_mutex_unlock(&global_dc1394_mutex);
        DC1394_ERR_CLN(err,cleanup(),"Could not set camera feature brightness");
    }

    ::CORBA::UShort getExpo () {
		uint32_t value;
		dc1394error_t err;
		//pthread_mutex_lock(&global_dc1394_mutex);
		err=dc1394_feature_get_value(cameras[0], DC1394_FEATURE_EXPOSURE, &value);
		//pthread_mutex_unlock(&global_dc1394_mutex);
        DC1394_ERR_CLN_RTN(err,cleanup(),"Could not get camera feature brightness");
        return value;
    }

    void setExpo (::CORBA::UShort expo) {
    	dc1394error_t err;
		//pthread_mutex_lock(&global_dc1394_mutex);
    	err=dc1394_feature_set_value(cameras[0], DC1394_FEATURE_EXPOSURE, expo);
		//pthread_mutex_unlock(&global_dc1394_mutex);
        DC1394_ERR_CLN(err,cleanup(),"Could not set camera feature brightness");
    }

    void restart(void) {
    	dc1394error_t err;
		pthread_mutex_lock(&global_dc1394_mutex);
#if defined(__amd64__)
		printf("\nUsing camera with GUID %lx\n", cameras[0]->guid);
#else
        printf("\nUsing camera with GUID %llx\n", cameras[0]->guid);
#endif
        printf("Reseting bus...\n");
        if (dc1394_reset_bus (cameras[0]) != DC1394_SUCCESS)
                printf ("Warning: reset reported error\n");
		pthread_mutex_unlock(&global_dc1394_mutex);

        changeRes(getRes());
    }

    void finish(void) {
    	//dc1394error_t err;
    	cleanup();
    	dc1394_camera_free(cameras[0]);
        printf("\nServer finished\n\n");
        fflush(stdout);
        exit(0);
    }

};

int main(int argc,char *argv[])
{


try{ // All the sever is put into a try-catch contruction

  // Initialize ORB
  CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
  // Get reference to Root POA
  CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");

  PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

  // Activate POA Manager
  PortableServer::POAManager_var mgr = poa->the_POAManager();
  mgr->activate();

  // Create an object
  Camera_impl CameraData_servant;

  // Write stringfied IOR to stodut
  higgs::Camera_var im = CameraData_servant._this();
  CORBA::String_var str = orb->object_to_string(im);
  cout << str << endl;

  // CORBA Name Server
  cout << "Obteniendo servicio de nombres...";
  CORBA::Object_var nameService =
	orb->resolve_initial_references("NameService");
  CosNaming::NamingContext_var namingContext =
	CosNaming::NamingContext::_narrow(nameService);
  if (CORBA::is_nil (namingContext)) {
	cerr << "oops, I cannot access the Naming Service!" << endl;
	exit (1);
  }
  cout << "hecho." << endl;

  cout << "Creando un nombre para registrarse en el NS...";
  CosNaming::Name name;
  name.length(1);
  name[0].id = CORBA::string_dup("Camera");
  name[0].kind = CORBA::string_dup("");
  cout << "hecho." << endl;

  cout << "Registrándose en el NS...";
  namingContext->rebind(name, im.in());
  cout << "hecho." << endl;

    int i, j, k;
    j=0;
    i=0;
    k=0;
    dc1394_t * d;
    dc1394camera_list_t * list;

    // Obtain camera list & first camera
    dc1394error_t err;
    d = dc1394_new ();
    err=dc1394_camera_enumerate (d, &list);
    DC1394_ERR_RTN(err,"Failed to enumerate cameras");
    numCameras = list->num;
    printf("Numero de camaras: %d \n", numCameras);
    if (numCameras==0) {
		printf("oops, No camera available!\n");
		exit(1);
    }
    cameras[0] = dc1394_camera_new (d, list->ids[0].guid);
    if(cameras[0]->one_shot_capable > 0)
		printf("Camera one-shot capable\n");
    else
    	printf("Camera not one-shot capable\n");
    dc1394_camera_free_list (list);

    /* setup cameras for capture */
    for (i = 0; i < 1; i++) {
		pthread_mutex_lock(&global_dc1394_mutex);
    	err=dc1394_camera_print_info(cameras[0], stdout);
    	DC1394_ERR_CLN_RTN(err,cleanup(),"Could not get camera info");

    	printf("Vendor: %s\n",cameras[0]->vendor);
    	printf("Model:  %s\n",cameras[0]->model);

    	if ( strcmp("iSight", cameras[0]->model)==0 )
            err=dc1394_video_set_iso_speed(cameras[0], DC1394_ISO_SPEED_200);
    	else
            err=dc1394_video_set_iso_speed(cameras[0], DC1394_ISO_SPEED_400);
		DC1394_ERR_CLN_RTN(err,cleanup(),"Could not set ISO speed");

		if ( strcmp("MDS-STH", cameras[0]->model)==0 )
		{
			videreStereo=true;
			fps = DC1394_FRAMERATE_7_5;
			res = DC1394_VIDEO_MODE_1280x960_YUV422;
			device_width=1280;
			device_height=960;
			format=XV_UYVY;
		} else if ( strcmp("iSight", cameras[0]->model)==0 ) {
			videreStereo=false;
			fps = DC1394_FRAMERATE_15;
			res = DC1394_VIDEO_MODE_640x480_YUV422;
			device_width=640;
			device_height=480;
			format=XV_UYVY;
		} else {
			printf("Camera not recognized\n");
		}

		//res = DC1394_VIDEO_MODE_640x480_YUV411;
		printf("Valor de res: %d \n", res);
		printf("Valor de fps: %d \n", fps);

		err=dc1394_video_set_mode(cameras[0], (dc1394video_mode_t)res);
		DC1394_ERR_CLN_RTN(err,cleanup(),"Could not set video mode");

		err=dc1394_video_set_framerate(cameras[0], (dc1394framerate_t)fps);
		DC1394_ERR_CLN_RTN(err,cleanup(),"Could not set framerate");

		err=dc1394_capture_setup(cameras[0], NUM_BUFFERS, DC1394_CAPTURE_FLAGS_DEFAULT);
		DC1394_ERR_CLN_RTN(err,cleanup(),"Could not setup camera-\nmake sure that the video mode and framerate are\nsupported by your camera");

		err=dc1394_feature_set_value(cameras[0], DC1394_FEATURE_BRIGHTNESS, 64);
		DC1394_ERR_CLN_RTN(err,cleanup(),"Could not set camera feature brightness");

		err=dc1394_feature_set_value(cameras[0], DC1394_FEATURE_EXPOSURE, 600);
		DC1394_ERR_CLN_RTN(err,cleanup(),"Could not set camera feature exposure");

		//pthread_mutex_lock(&global_dc1394_mutex);
		err=dc1394_feature_set_mode(cameras[0], DC1394_FEATURE_GAIN, DC1394_FEATURE_MODE_AUTO);
		err=dc1394_feature_set_value(cameras[0], DC1394_FEATURE_GAIN, 100);
		pthread_mutex_unlock(&global_dc1394_mutex);
		DC1394_ERR_CLN_RTN(err,cleanup(),"Could not set camera feature gain");

		for (j=0; j<1;) {
			err=dc1394_video_set_transmission(cameras[0], DC1394_ON);
			//DC1394_ERR_CLN_RTN(err,cleanup(),"Could not start camera iso transmission");
			if (err!=DC1394_SUCCESS) {
				printf("iSight: Iris closed...\n");
				fflush(stdout);
				usleep(1000000);
			} else {
				j++;
				break;
			}
		}

		//err=dc1394_feature_set_value(cameras[0], DC1394_FEATURE_HUE, 25);
		//DC1394_ERR_CLN_RTN(err,cleanup(),"Could not set camera feature hue");

		//err=dc1394_feature_set_value(cameras[0], DC1394_FEATURE_SHARPNESS, 25);
		//DC1394_ERR_CLN_RTN(err,cleanup(),"Could not set camera feature hue");
    }

    fflush(stdout);
    switch(format){
      case XV_YV12:
        set_frame_length(device_width*device_height*3/2, 1);
        break;
      case XV_YUY2:
      case XV_UYVY:
        set_frame_length(device_width*device_height*2, 1);
        break;
      default:
        dc1394_log_error("Unknown format set (internal error)");
        exit(255);
    }

    /* main event loop !*/
    cout << "Server running..." << endl;
    orb->run();
  }

  catch(const CORBA::Exception &){
    cout << ".fail." << endl;
    cerr << "Uncaught CORBA Exception" << endl;
    return 1;
  }
}
