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

#include "CameraC.h"
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

using namespace std;
using namespace higgs;

#define _GNU_SOURCE
#include <getopt.h>
#define __STDC_CONSTANT_MACROS
#include <stdint.h>
#include <inttypes.h>

#include <X11/Xlib.h>   // Header File For X11R6 library
#include <X11/Xutil.h>
#include <X11/extensions/Xvlib.h>
#include <X11/keysym.h>

#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>      // Header File For The OpenGL32 Library
#include <GL/glu.h>     // Header File For The GLu32 Library
#include <GL/glext.h>   // Header File For The GLext Library
#include <GL/glx.h>     // Header file fot the GLx libraries.

#include <IL/il.h>
#include <IL/ilu.h>

#if defined(__linux__)
#define GLvoid void
#include <GL/glui.h>    // Header file fot the GLui libraries.
#else
#define GLvoid void
#include <glui.h>    // Header file fot the GLui libraries.
#endif

//define PANEL_SIZE 0
#define PANEL_SIZE 160

extern "C" {
    #include "initGL.h"
}
#include "dc1394/dc1394.h"
#include "encode.h"

/* ASCII code for the escape key. */
#define ESCAPE 27

/* The number of our GLUT window */
int window;
GLUI* glui;

/* uncomment the following to drop frames to prevent delays */
#define MAX_PORTS   4
#define MAX_CAMERAS 8
#define NUM_BUFFERS 8

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
bool videreStereo = false;
short camera = 1;
bool update = true;
bool cubo = false;
bool full_screen = false;
bool stop = true;
bool record = false;
static GLfloat spin = 0.0;

long device_width,device_height;
//long width,height;
//int videoImageWidth, videoImageHeight;
int connection=-1;
long format=0;

/* Other declarations */
long frame_length;
long frame_free;
int frame=0;
int adaptor=-1;
int freeze=0;
int average=0;
int fps;
higgs::CameraResolution res;


// create texture
char *videoTexture=NULL;
char *frame_buffer5=NULL; //Bayer
char *frame_buffer6=NULL; //YUV
char *frame_buffer7=NULL; //Camera decompresion 1
char *frame_buffer8=NULL; //Camera decompresion 2

CORBA::ORB_var orb;
//CORBA::Object_ptr obj;
CORBA::Object_var obj;
higgs::Camera_var im;
char *data=NULL;
char *str;

/* image saving variables */
static ILuint image_id = 0;
static GLubyte* image_data = 0;
ILuint image_size1 = 0;

static struct option long_options[]={
    {"device",1,NULL,0},
    {"fps",1,NULL,0},
    {"res",1,NULL,0},
    {"help",0,NULL,0},
    {NULL,0,0,0}
};


GLuint base;            // base display list for the font set.
GLuint texture[2];      /* storage for our two textures */
GLuint loop;            /* generic loop variable */
GLfloat cnt1;           // 1st counter used to move text & for coloring.
GLfloat cnt2;           // 2nd counter used to move text & for coloring.

GLvoid BuildFont(GLvoid)
{
    Display *dpy;
    XFontStruct *fontInfo;  // storage for our font.

    base = glGenLists(96);                      // storage for 96 characters.

    // load the font.  what fonts any of you have is going
    // to be system dependent, but on my system they are
    // in /usr/X11R6/lib/X11/fonts/*, with fonts.alias and
    // fonts.dir explaining what fonts the .pcf.gz files
    // are.  in any case, one of these 2 fonts should be
    // on your system...or you won't see any text.

    // get the current display.  This opens a second
    // connection to the display in the DISPLAY environment
    // value, and will be around only long enough to load
    // the font.
    dpy = XOpenDisplay(NULL); // default to DISPLAY env.

    fontInfo = XLoadQueryFont(dpy, "-adobe-helvetica-medium-r-normal--18-*-*-*-p-*-iso8859-1");
    if (fontInfo == NULL) {
		fontInfo = XLoadQueryFont(dpy, "fixed");
		if (fontInfo == NULL) {
			printf("no X font available?\n");
		}
    }

    // after loading this font info, this would probably be the time
    // to rotate, scale, or otherwise twink your fonts.

    // start at character 32 (space), get 96 characters (a few characters past z), and
    // store them starting at base.
    glXUseXFont(fontInfo->fid, 32, 96, base);

    // free that font's info now that we've got the
    // display lists.
    XFreeFont(dpy, fontInfo);

    // close down the 2nd display connection.
    XCloseDisplay(dpy);
}

GLvoid KillFont(GLvoid)                         // delete the font.
{
    glDeleteLists(base, 96);                    // delete all 96 characters.
}

GLvoid glPrint(char *text)                      // custom gl print routine.
{
    if (text == NULL) {                         // if there's no text, do nothing.
		return;
    }

    glPushAttrib(GL_LIST_BIT);                  // alert that we're about to offset the display lists with glListBase
    glListBase(base - 32);                      // sets the base character to 32.

    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); // draws the display list text.
    glPopAttrib();                              // undoes the glPushAttrib(GL_LIST_BIT);
}

/*
void get_options(int argc,char *argv[])
{
    int option_index=0;
    fps=7;
    res=0;

    while(getopt_long(argc,argv,"",long_options,&option_index)>=0){
        if(optarg){
            switch(option_index){
                // case values must match long_options
            case 0:
                device_name=strdup(optarg);
                break;
            case 1:
                fps=atoi(optarg);
                break;
            case 2:
                res=atoi(optarg);
                break;
            }
        }
        if(option_index==3){
            printf( "\n"
                    "        %s - multi-cam monitor for libdc1394 and XVideo\n\n"
                    "Usage:\n"
                    "        %s [--fps=[1,3,7,15,30]] [--res=[0,1,2]] [--device=/dev/video1394/x]\n"
                    "             --fps    - frames per second. default=7,\n"
                    "                        30 not compatible with --res=2\n"
                    "             --res    - resolution. 0 = 320x240 (default),\n"
                    "                        1 = 640x480 YUV4:1:1, 2 = 640x480 RGB8\n"
                    "             --device - specifies video1394 device to use (optional)\n"
                    "                        default = automatic\n"
                    "             --help   - prints this message\n\n"
                    "Keyboard Commands:\n"
                    "        q = quit\n"
                    "        < -or- , = scale -50%%\n"
                    "        > -or- . = scale +50%%\n"
                    "        0 = pause\n"
                    "        1 = set framerate to 1.875 fps\n"
                    "        2 = set framerate tp 3.75 fps\n"
                    "        3 = set framerate to 7.5 fps\n"
                    "        4 = set framerate to 15 fps\n"
                    "        5 = set framerate to 30 fps\n"
                    ,argv[0],argv[0]);
            exit(0);
        }
    }

}
*/

/* image format conversion functions */
/*
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
}*/

/*static inline
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
}*/

void yuv422_2vuy422(const unsigned char *theYUVFrame, unsigned char *the422Frame, const unsigned int width, const unsigned int height)
{
    int i =0, j=0;
    unsigned int numPixels = width * height;
    unsigned int totalNumberOfPasses = numPixels * 2;
    register unsigned int y0, y1, y2, y3, u0, u2, v0, v2;

    while (i < (totalNumberOfPasses) )
    {
        u0 = theYUVFrame[i++]-128;
        y0 = theYUVFrame[i++];
        v0 = theYUVFrame[i++]-128;
        y1 = theYUVFrame[i++];
        u2 = theYUVFrame[i++]-128;
        y2 = theYUVFrame[i++];
        v2 = theYUVFrame[i++]-128;
        y3 = theYUVFrame[i++];

        // U0 Y0 V0 Y1 U2 Y2 V2 Y3

        // Remap the values to 2VUY (YUYS?) (Y422) colorspace for OpenGL
        // Y0 U Y1 V Y2 U Y3 V

        // IIDC cameras are full-range y=[0..255], u,v=[-127..+127], where display is "video range" (y=[16..240], u,v=[16..236])

        the422Frame[j++] = ((y0 * 240) / 255 + 16);
        the422Frame[j++] = ((u0 * 236) / 255 + 128);
        the422Frame[j++] = ((y1 * 240) / 255 + 16);
        the422Frame[j++] = ((v0 * 236) / 255 + 128);
        the422Frame[j++] = ((y2 * 240) / 255 + 16);
        the422Frame[j++] = ((u2 * 236) / 255 + 128);
        the422Frame[j++] = ((y3 * 240) / 255 + 16);
        the422Frame[j++] = ((v2 * 236) / 255 + 128);
    }
}

/* helper functions */
void set_frame_length(long size, int numCameras)
{
    frame_length=size;
    frame_free=0;
    printf("Tamaño: %ld \n", size);
    frame_buffer5 = (char*) malloc( size * numCameras * 3); // Bayer
    frame_buffer6 = (char*) malloc( size * numCameras * 3); // YUV
    frame_buffer7 = (char*) malloc( size * numCameras * 4); // JPEG Compressed 1
    frame_buffer8 = (char*) malloc( size * numCameras * 4); // JPEG Compressed 2
    videoTexture  = (char*) malloc( size * numCameras * 4);
}

static double current_time(void)
{
    struct timeval tv;
    struct timezone tz;
    (void) gettimeofday(&tv, &tz);
    return (double) tv.tv_sec + tv.tv_usec / 1000000.0;
}

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
/*
void InitGL(int Width, int Height)              // We call this right after our OpenGL window is created.
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);         // This Will Clear The Background Color To Black
  glClearDepth(1.0);                            // Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);                         // The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);                      // Enables Depth Testing
  glShadeModel(GL_SMOOTH);                      // Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();                             // Reset The Projection Matrix

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);     // Calculate The Aspect Ratio Of The Window

  glMatrixMode(GL_MODELVIEW);


  // Initialize texture
  glEnable(GL_TEXTURE_RECTANGLE_ARB);
  glBindTexture(GL_TEXTURE_RECTANGLE_ARB, 1);

//  glTextureRangeAPPLE(GL_TEXTURE_RECTANGLE_ARB, videoImageWidth * videoImageHeight * 2, videoTexture);
  //glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_STORAGE_HINT_APPLE , GL_STORAGE_SHARED_APPLE);
  glPixelStorei(GL_UNPACK_CLIENT_STORAGE_APPLE, GL_TRUE);

  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

  glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, videoImageWidth,
        videoImageHeight, 0, GL_YCBCR_422_APPLE, GL_UNSIGNED_SHORT_8_8_REV_APPLE, videoTexture);
}
*/

/* The function called when our window is resized
   (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
  int Position=0;
  if (Height==0)                      // Prevent A Divide By Zero If The Window Is Too Small
    Height=1;

  Width=Width+PANEL_SIZE;
  GLUI_Master.get_viewport_area( &Position, &Position, &Width, &Height );
  glViewport(0, 0, Width, Height);    // Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,-1.0f,1200.0f);
  glMatrixMode(GL_MODELVIEW);

  glTexImage2D (GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, device_width,
    device_height, 0, GL_RGB, GL_UNSIGNED_BYTE, videoTexture);
}

/* The main drawing function. */
void DrawGLScene()
{
  static int frames = 0;
  static ::CORBA::UShort frame1, frame2;
  static double dt, fps1;
  static double t1=-1.0, t2=-1.0;
  static higgs::ImagenData_var datos;
  static higgs::ImagenData_var datosc;
  static char filename[512];
  static double sleep_usecs = 0.0;

  glutSetWindow(window);

  if(!freeze){
    t2 = current_time();
    if(t1 < 0.0)
      t1 = t2;
    if(im==NULL)
      return;
	//usleep(sleep_usecs);
    while (frame1==frame2) {
    	usleep(15000);
    	frame1 = im->getFrame();
    }
    frame2=frame1;

	if (res == Res_640x480_rgb) {
		datos = new higgs::ImagenData;
		//cout << "im->getImagen1 " << endl;
		datos = im->getImagen(camera, update);
		//cout << "im->getImagen2 " << endl;
		//printf("Length: %ld\n", datos->length());
	} else {
		datosc = new higgs::ImagenData;
		datos  = new higgs::ImagenData(frame_length*4, (CORBA::Octet*) &frame_buffer8[0], 0);

		//printf("getJPEGImagen: %d\n", update);
		datosc = im->getJPEGImagen(camera, update);

		/*
			static char filename[512];
			sprintf(filename, "/tmp/image0_%.10u.jpg", frames);
			FILE* File = fopen(filename, "wb");
			printf("F:%ld \n", fwrite(&datosc[0], 1, datosc->length(), File));
			fclose(File);
		*/

		//printf(" w: %d h: %d \n", device_width, device_height);
		//printf("Length: %ld\n", datosc->length());
		//fflush(stdout);
		//ilTexImage(device_width, device_height, 1, 4, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		ilTexImage(device_width, device_height, 1, 3, GL_RGB, GL_UNSIGNED_BYTE, image_data);
		//ilLoadL(IL_TYPE_UNKNOWN, (void *) &datosc[0], datosc->length());
		if ( !ilLoadL(IL_JPG, (void *) &datosc[0], datosc->length() ) )
		{
			printf("ERROR1: %d\n", ilGetError() );
			printf("ERROR2: %s\n", iluErrorString( ilGetError() ) );
		}

		//ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
		//ilGetData();
		//glDrawPixels(1280, 960, GL_RGB, GL_UNSIGNED_BYTE, frame_buffer8);
		//ilSetPixels(0, 0, 0, device_width, device_height, 1, IL_RGB, IL_UNSIGNED_BYTE, (ILubyte*) datosc[0]);

		/*
			sprintf(filename, "/tmp/image1_%.10u.jpg", frames);
			ilEnable(IL_FILE_OVERWRITE);
			ilSave(IL_JPG, filename);
		*/

		//printf("ilCopyPixels\n");
		ilCopyPixels(0, 0, 0, device_width, device_height, 1, IL_RGB, IL_UNSIGNED_BYTE, (ILubyte*) &frame_buffer8[0]);
		//memcpy(frame_buffer8, ilGetData(), device_width*device_height*3);
		//ilSaveL(IL_RAW, (void*) &frame_buffer8[0], device_width*device_height*3);
		datos->length(device_width*device_height*3);
	}
    frames++;
/*
    printf("Length: %ld --- ", datos->length());
    printf("Width: %ld Height: %ld \n", device_width, device_height);
    fflush(stdout);
*/
    // Draw texture
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_TEXTURE_2D);
    //glViewport(0, 0, 640, 480);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho( (GLfloat)0, (GLfloat)device_width, (GLfloat)0, (GLfloat)device_height, -1.0, 640.0);
    gluPerspective(45.0f,(GLfloat)device_width/(GLfloat)device_height,1.0f,1200.0f);

    float viewerPosition[3];

    if (device_width==640)
    {
	//viewerPosition = { -320.0, -240.0, -600.0 };
	viewerPosition[0] = -320.0;
	viewerPosition[1] = -240.0;
	viewerPosition[2] = -600.0;
    } else if (device_width==1280)
    {
	//viewerPosition = { -640.0, -480.0, -1200.0 };
	viewerPosition[0] = -640.0;
	viewerPosition[1] = -480.0;
	viewerPosition[2] = -1200.0;
    } else if (device_width==320)
    {
	//viewerPosition = { -640.0, -480.0, -1200.0 };
	viewerPosition[0] = -160.0;
	viewerPosition[1] = -120.0;
	viewerPosition[2] = -300.0;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef( viewerPosition[0], viewerPosition[1], viewerPosition[2]);
#if defined (__APPLE2__)
    glEnable(GL_TEXTURE_RECTANGLE_ARB);
    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture[0]);
    if (videreStereo==true)
    {
    	//Formato RGB - frame_buffer5
    	dc1394_bayer_decoding_8bit((uint8_t*)&datos[0] + (0 * frame_length),
                (uint8_t*)frame_buffer5 + (0 * frame_length),
                device_width, device_height,
                DC1394_COLOR_FILTER_GRBG, DC1394_BAYER_METHOD_SIMPLE);
    	dc1394_convert_to_YUV422((uint8_t*)frame_buffer5,
    			(uint8_t*)frame_buffer6,
    			device_width, device_height,
    			DC1394_BYTE_ORDER_UYVY,
    			DC1394_COLOR_CODING_RGB8,
    			8);
    } else {
    	//Formato YUV422 - frame_buffer6
    	yuv422_2vuy422((unsigned char*)&datos[0], (unsigned char*)frame_buffer6, 640, 480);
    	//memcpy(frame_buffer6, &(datos.contenido), 640*480*2);
    	//memcpy(frame_buffer6, &datos[0], device_width*device_height*480*3);
    }

    // upload texture data
    glTexSubImage2D (GL_TEXTURE_RECTANGLE_ARB, 0, 0, 0, device_width, device_height,
        GL_YCBCR_422_APPLE, GL_UNSIGNED_SHORT_8_8_REV_APPLE, frame_buffer6);
#elif !defined(TEXTURE2D)
    glEnable(GL_TEXTURE_RECTANGLE_ARB);
    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture[0]);
    if (videreStereo==true)
    {
    	if (res == Res_640x480_rgb) {
    		// Videre - Bayer
        	dc1394_bayer_decoding_8bit((uint8_t*)&datos[0] + (0 * frame_length),
                    (uint8_t*)videoTexture + (0 * frame_length),
                    device_width, device_height,
                    DC1394_COLOR_FILTER_GRBG, DC1394_BAYER_METHOD_SIMPLE);
    	} else {
    		// Videre - JPEG Compressed
    		memcpy(videoTexture, &datos[0], device_width*device_height*3);
    	}
    	if (record==true)
    		dc1394_convert_to_YUV422((uint8_t*)videoTexture,
    				(uint8_t*)frame_buffer6,
    				device_width, device_height,
    				DC1394_BYTE_ORDER_UYVY,
    				DC1394_COLOR_CODING_RGB8,
    				8);
	} else {
	   	if (res == Res_640x480_rgb) {
	   		dc1394_convert_to_RGB8((uint8_t*)&datos[0],
	   				(uint8_t*)videoTexture,
	   				device_width, device_height,
	   				DC1394_BYTE_ORDER_UYVY,DC1394_COLOR_CODING_YUV411,16);
	   				//DC1394_BYTE_ORDER_YUYV,DC1394_COLOR_CODING_YUV411,16);
					//DC1394_BYTE_ORDER_YUYV,DC1394_COLOR_CODING_YUV422,16);
	   		//printf("|");
	   		fflush(stdout);
    	} else {
			memcpy(videoTexture, &datos[0], device_width*device_height*3);
			//printf("�");
    	}
			if (record==true)
				memcpy(frame_buffer6, &datos[0], device_width*device_height*2);
	}
    // upload texture data
    glTexSubImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, 0, 0, device_width, device_height,
    	GL_RGB, GL_UNSIGNED_BYTE, videoTexture);
#else // TEXTURE2D
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    if (videreStereo==true)
    {
    	if (res == Res_640x480_rgb) {
    		// Videre - Bayer
        	dc1394_bayer_decoding_8bit((uint8_t*)&datos[0] + (0 * frame_length),
                    (uint8_t*)videoTexture + (0 * frame_length),
                    device_width, device_height,
                    DC1394_COLOR_FILTER_GRBG, DC1394_BAYER_METHOD_SIMPLE);
    	} else {
    		// Videre - JPEG Compressed
    		memcpy(videoTexture, &datos[0], device_width*device_height*3);
    	}
    	if (record==true)
    		dc1394_convert_to_YUV422((uint8_t*)videoTexture,
    				(uint8_t*)frame_buffer6,
    				device_width, device_height,
    				DC1394_BYTE_ORDER_UYVY,
    				DC1394_COLOR_CODING_RGB8,
    				8);
    } else {
    	//dc1394_convert_to_RGB8((uint8_t*)&datos[0], (uint8_t*)videoTexture,
    	//	videoImageWidth, videoImageHeight,
    	//	DC1394_BYTE_ORDER_UYVY,DC1394_COLOR_CODING_YUV422,16);
    	memcpy(videoTexture, &datos[0], device_width*device_height*3);
    	if (record==true)
    		memcpy(frame_buffer6, &datos[0], device_width*device_height*2);
    }
    // upload texture data
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, device_width, device_height,
    	GL_RGB, GL_UNSIGNED_BYTE, videoTexture);
#endif // __APPLE__

	  glMatrixMode(GL_TEXTURE);
	  glLoadIdentity();

#if defined(__APPLE__) || !defined (TEXTURE2D)
	    if (cubo==false)
	    {
	      glBegin(GL_QUADS);
	    	if (res == Res_640x480_rgb) {
	    		glTexCoord2f(0.0f, 0.0f);
	    		glVertex2f(0.0f, device_height);

	    		glTexCoord2f(0.0f, device_height);
	    		glVertex2f(0.0f, 0.0f);

	    		glTexCoord2f(device_width, device_height);
	    		glVertex2f(device_width, 0.0f);

	    		glTexCoord2f(device_width, 0.0f);
	    		glVertex2f(device_width, device_height);
	    	} else {
	    		glTexCoord2f(0.0f, 0.0f);
	    		glVertex2f(0.0f, 0.0f);

	    		glTexCoord2f(0.0f, device_height);
	    		glVertex2f(0.0f, device_height);

	    		glTexCoord2f(device_width, device_height);
	    		glVertex2f(device_width, device_height);

	    		glTexCoord2f(device_width, 0.0f);
	    		glVertex2f(device_width, 0.0f);
	    	}
	      glEnd();
	    }
	    if (cubo==true)
		{
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			//glTranslatef(viewerPosition[0], viewerPosition[1], viewerPosition[2]);
			//glTranslatef(320.0f, viewerPosition[1], +160.0f);
			glTranslatef(0.0f, 0.0f, -760.0f);

			if (stop==false)
				spin = spin + 0.5;
			if (spin > 360.0)
				spin = spin - 360.0;
			glRotatef(spin, 0.0f, 1.0f, 0.0f);
			glTranslatef(-320.0f, -240.0f, +160.0f);

			glMatrixMode(GL_TEXTURE);
			glLoadIdentity();
			glBegin(GL_QUADS);
			  glTexCoord2f(0.0f, 0.0f);
			  glVertex3f(0.25f*device_width, 0.75f*device_height, -0.5f*device_width);

			  glTexCoord2f(0.0f, device_height);
			  glVertex3f(0.25f*device_width, 0.25f*device_height, -0.5f*device_width);

			  glTexCoord2f(device_width, device_height);
			  glVertex3f(0.75f*device_width, 0.25f*device_height, -0.5f*device_width);

			  glTexCoord2f(device_width, 0.0f);
			  glVertex3f(0.75f*device_width, 0.75f*device_height, -0.5f*device_width);
			glEnd();
			glBegin(GL_QUADS);
			  glTexCoord2f(0.0f, 0.0f);
			  glVertex3f(0.75f*device_width, 0.75f*device_height, -0.5f*device_width);

			  glTexCoord2f(0.0f, device_height);
			  glVertex3f(0.75f*device_width, 0.25f*device_height, -0.5f*device_width);

			  glTexCoord2f(device_width, device_height);
			  glVertex3f(0.75f*device_width, 0.25f*device_height, 0.0f*device_width);

			  glTexCoord2f(device_width, 0.25f);
			  glVertex3f(0.75f*device_width, 0.75f*device_height, 0.0f*device_width);
			glEnd();
			glBegin(GL_QUADS);
			  glTexCoord2f(0.0f, 0.0f);
			  glVertex3f(0.75f*device_width, 0.75f*device_height, 0.0f*device_width);

			  glTexCoord2f(0.0f, device_height);
			  glVertex3f(0.75f*device_width, 0.25f*device_height, 0.0f*device_width);

			  glTexCoord2f(device_width, device_height);
			  glVertex3f(0.25f*device_width, 0.25f*device_height, 0.0f*device_width);

			  glTexCoord2f(device_width, 0.25f);
			  glVertex3f(0.25f*device_width, 0.75f*device_height, 0.0f*device_width);
			glEnd();
			glBegin(GL_QUADS);
			  glTexCoord2f(0.0f, 0.0f);
			  glVertex3f(0.25f*device_width, 0.75f*device_height, 0.0f*device_width);

			  glTexCoord2f(0.0f, device_height);
			  glVertex3f(0.25f*device_width, 0.25f*device_height, 0.0f*device_width);

			  glTexCoord2f(device_width, device_height);
			  glVertex3f(0.25f*device_width, 0.25f*device_height, -0.5f*device_width);

			  glTexCoord2f(device_width, 0.25f);
			  glVertex3f(0.25f*device_width, 0.75f*device_height, -0.5f*device_width);
			glEnd();
		}

	glDisable(GL_TEXTURE_RECTANGLE_ARB);
#else
	  glBegin(GL_QUADS);
	    glTexCoord2f(0.0f, 0.0f);
	    glVertex2f(0.0f, device_height);

	    glTexCoord2f(0.0f, 1.0f);
	    glVertex2f(0.0f, 0.0f);

	    glTexCoord2f(1.0f, 1.0f);
	    glVertex2f(device_width, 0.0f);

	    glTexCoord2f(1.0f, 0.0f);
	    glVertex2f(device_width, device_height);
	  glEnd();
	glDisable(GL_TEXTURE_2D);
#endif // __APPLE__

	glMatrixMode(GL_MODELVIEW);
	  //glLoadIdentity();				// Reset The View
	  //glDisable(GL_LIGHTING);
	  //glDisable(GL_DEPTH_TEST);
	  //glEnable(GL_BLEND);
	  //glTranslatef(0.0f, 0.0f, 0.2f);              // move 1 unit out of the screen.

	  if(t2 - t1 >= 1.0) {
		  dt = t2 - t1;
		  fps1 = frames / dt;
		  printf("%d frames in %3.1f seconds = %6.3f FPS\n", frames, dt, fps1);
		  sprintf(str, "HIGGS - %6.3f FPS", fps1);
		  t1 = t2;
		  frames = 0;
/*
		  if (fps1<=27.0) {
			  sleep_usecs = 0.7 * sleep_usecs;
		  } if (fps1>33.0) {
			  sleep_usecs = sleep_usecs+(1/30)*1000000;
		  } else {
			  sleep_usecs = fmax(0.0,((0.64/fps1)-(1/30))*1000000);
		  }
*/
/*
		  if (fps1 < 30.0) {
			  sleep_usecs = 0;
		  } else {
			  sleep_usecs = (1-(30.0/fps1))/30.0;
		  }
*/
		  //printf("FT: %f \n", sleep_usecs);
	  }

	  if (device_width==320) {
		  // Print string
		  glColor3f(1.0f, 0.0f, 0.0f);
		  glRasterPos2f(200.0f, 220.0f);
		  glPrint(str);
		  glColor3f(1.0f, 1.0f, 1.0f);
		  glRasterPos2f(200.0f, 200.0f);
		  glPrint("ASLab - AHM");                  // print gl text to the screen.
	  } else {
		  // Print string
		  glColor3f(1.0f, 0.0f, 0.0f);
		  glRasterPos2f(400.0f, 440.0f);
		  glPrint(str);
		  glColor3f(1.0f, 1.0f, 1.0f);
		  glRasterPos2f(400.0f, 400.0f);
		  glPrint("ASLab - AHM");                  // print gl text to the screen.
	  }

	  //glTranslatef(0.0f, 0.0f, -0.2f);              // move 1 unit into the screen.
	  glColor3f(1.0f, 1.0f, 1.0f);

#if defined(__APPLE__) || !defined(TEXTURE2D)
	  glEnable(GL_TEXTURE_RECTANGLE_ARB);
#else
	  glEnable(GL_TEXTURE_2D);
#endif

    // swap buffers to display, since we're double buffered.
    glutSwapBuffers();

    if (record==true)
    {
    	if (videreStereo==true)
    	{
            //dc1394_convert_to_YUV422((uint8_t*)frame_buffer5,
            //	(uint8_t*)frame_buffer7,
            //	device_width, device_height,
            //	DC1394_BYTE_ORDER_UYVY,
            //	DC1394_COLOR_CODING_RGB8,
            //	8);
    		//yuv422p_encode_image((uint8_t*)frame_buffer6);
    		yuv420_encode_image((uint8_t*)frame_buffer6);
    		//yuv422_encode_image((uint8_t*)frame_buffer6);
    	} else {
    		//yuv422p_encode_image((uint8_t*)frame_buffer6);
    		yuv420_encode_image((uint8_t*)frame_buffer6);
    		//yuv422_encode_image((uint8_t*)frame_buffer6);
    	}
    }
  } // freeze
}

void cleanup(void) {
	//CORBA::release(im);
	//CORBA::release(obj);
	im=NULL;
	orb->shutdown();
}

void GLUI_exit(void) {
	/* get rid of font display lists */
	KillFont();

        /* shut down our window */
        glutDestroyWindow(window);
	cleanup();

        /* exit the program...normal termination. */
	exit(0);
}

void GLUI_finish(void) {
	/* get rid of font display lists */
	KillFont();

	/* shut down our window */
	glutDestroyWindow(window);

	// Terminar servidor
	im->finish();
	cleanup();

	/* exit the program...normal termination. */
	exit(0);
}

void GLUI_restart(void) {
	im->restart();
	glutSetWindow(window);
	//glutReshapeWindow(width, height);
	//im->changeRes(res);
	glutPostRedisplay();
}

void GLUI_update(void) {
	if (update==true)
	{
		update=false;
		printf("u");
	} else {
		update=true;
		printf("U");
	}
	fflush(stdout);
	glutPostRedisplay();
}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y)
{
    /* avoid thrashing this procedure */
    usleep(100);

    /* If escape is pressed, kill everything. */
    if (key == ESCAPE)
    {
		/* get rid of font display lists */
		KillFont();

		/* shut down our window */
		glutDestroyWindow(window);
		cleanup();

		/* exit the program...normal termination. */
		exit(0);
    } else if (key == 'q')
	{
		/* get rid of font display lists */
		KillFont();

		/* shut down our window */
		glutDestroyWindow(window);
		cleanup();

		/* exit the program...normal termination. */
		exit(0);
	} else if (key == 'x' || key == 'X')
	{
		/* get rid of font display lists */
		KillFont();

		/* shut down our window */
		glutDestroyWindow(window);

		// Terminar servidor
		im->finish();
		cleanup();

		/* exit the program...normal termination. */
		exit(0);
	} else if (key == 'u' || key == 'U')
	{
		GLUI_update();
	} else if (key == 'a' || key == 'A')
	{
		glutSetWindow(window);
		glutReshapeWindow(320+PANEL_SIZE, 240);
		glutPostRedisplay();
	} else if (key == 's' || key == 'S')
	{
		glutSetWindow(window);
		glutReshapeWindow(640+PANEL_SIZE, 480);
		glutPostRedisplay();
	} else if (key == 'd' || key == 'D')
	{
		glutSetWindow(window);
		glutReshapeWindow(1280+PANEL_SIZE, 960);
		glutPostRedisplay();
	} else if (key == 'h' || key == 'h')
	{
		device_width=320;
		device_height=240;
		glutSetWindow(window);
		glutReshapeWindow(320+PANEL_SIZE, 240);
		res = Res_320x240;
		im->changeRes(res);
		glutPostRedisplay();
	} else if (key == 'j' || key == 'J')
	{
		device_width=640;
		device_height=480;
		glutSetWindow(window);
		glutReshapeWindow(640+PANEL_SIZE, 480);
		res = Res_640x480_rgb;
		im->changeRes(res);
		glutPostRedisplay();
	} else if (key == 'k' || key == 'K')
	{
		device_width=640;
		device_height=480;
		glutSetWindow(window);
		glutReshapeWindow(640+PANEL_SIZE, 480);
		res = Res_640x480;
		im->changeRes(res);
		glutPostRedisplay();
	} else if (key == 'l' || key == 'L')
	{
		device_width=1280;
		device_height=960;
		glutSetWindow(window);
		glutReshapeWindow(1280+PANEL_SIZE, 960);
		res = Res_1280x960;
		im->changeRes(res);
		glutPostRedisplay();
	} else if (key == '1' || key == '!')
	{
		camera=1;
	} else if (key == '2' || key == '"')
	{
		camera=2;
	} else if (key == '9' || key == ')')
	{
		if (cubo==false)
			cubo=true;
		else
			cubo=false;
	} else if (key == ' ')
	{
		if (stop==false)
			stop=true;
		else
			stop=false;
	} else if (key == 'r' || key == 'R')
	{
		if (record==false)
		{
			record = true;
			yuv420_encode_start(); // Funciona Linux y Mac
			//yuv422_encode_start(); // No funciona Linux
			//yuv422p_encode_start(); // Funciona Linux
		} else {
			record = false;
			video_encode_stop();
		}
	} else if (key == 'p' || key == 'P')
	{
		im->restart();
		glutSetWindow(window);
		//glutReshapeWindow(width, height);
		//im->changeRes(res);
		glutPostRedisplay();
	} else if (key == 'n')
	{
		im->setBright(im->getBright()-5);
	} else if (key == 'm')
	{
		im->setBright(im->getBright()+5);
	} else if (key == ',')
	{
		im->setGain(im->getGain()-5);
	} else if (key == '.')
	{
		im->setGain(im->getGain()+5);
	}
}

void GLUI_bright_minus(void) {
		im->setBright(im->getBright()-5);
		printf("Bright: %ld \n", im->getBright());
}

void GLUI_bright_plus(void) {
		im->setBright(im->getBright()+5);
		printf("Bright: %ld \n", im->getBright());
}

void GLUI_gain_minus(void) {
		im->setGain(im->getGain()-5);
		printf("Gain: %ld \n", im->getGain());
}

void GLUI_gain_plus(void) {
		im->setGain(im->getGain()+5);
		printf("Gain: %ld \n", im->getGain());
}

void GLUI_expo_minus(void) {
		im->setExpo(im->getExpo()-5);
		printf("Expo: %ld \n", im->getExpo());
}

void GLUI_expo_plus(void) {
		im->setExpo(im->getExpo()+5);
		printf("Expo: %ld \n", im->getExpo());
}

void GLUI_size_small(void) {
		glutSetWindow(window);
		glutReshapeWindow(320+PANEL_SIZE, 240);
		glutPostRedisplay();
		//GLUI_Master.set_glutKeyboardFunc(keyPressed);
}

void GLUI_full_screen(void) {
	if (full_screen==false) {
		glutSetWindow(window);
		glutReshapeWindow(1280+PANEL_SIZE, 960);
		glutFullScreen();
		glutPostRedisplay();
		full_screen=true;
		//GLUI_Master.set_glutKeyboardFunc(keyPressed);
	} else {
		glutSetWindow(window);
		glutReshapeWindow(640+PANEL_SIZE, 480);
		glutPostRedisplay();
		full_screen=false;
	}
}

void GLUI_size_medium(void) {
		glutSetWindow(window);
		glutReshapeWindow(640+PANEL_SIZE, 480);
		glutPostRedisplay();
		//GLUI_Master.set_glutKeyboardFunc(keyPressed);
}

void GLUI_size_big(void) {
		glutSetWindow(window);
		glutReshapeWindow(1280+PANEL_SIZE, 960);
		glutPostRedisplay();
		//GLUI_Master.set_glutKeyboardFunc(keyPressed);
}

void GLUI_640_RGB(void) {
		device_width=640;
		device_height=480;
		glutSetWindow(window);
		glutReshapeWindow(640+PANEL_SIZE, 480);
		res = Res_640x480_rgb;
		im->changeRes(res);
		//GLUI_Master.set_glutKeyboardFunc(keyPressed);
		update=true;
		glutPostRedisplay();
}
void GLUI_320_YUV(void) {
		device_width=320;
		device_height=240;
		glutSetWindow(window);
		glutReshapeWindow(320+PANEL_SIZE, 240);
		res = Res_320x240;
		im->changeRes(res);
		//GLUI_Master.set_glutKeyboardFunc(keyPressed);
		update=true;
		glutPostRedisplay();
}

void GLUI_640_YUV(void) {
		device_width=640;
		device_height=480;
		glutSetWindow(window);
		glutReshapeWindow(640+PANEL_SIZE, 480);
		res = Res_640x480;
		im->changeRes(res);
		//GLUI_Master.set_glutKeyboardFunc(keyPressed);
		update=true;
		glutPostRedisplay();
}

void GLUI_1280_YUV(void) {
		device_width=1280;
		device_height=960;
		glutSetWindow(window);
		glutReshapeWindow(1280+PANEL_SIZE, 960);
		res = Res_1280x960;
		im->changeRes(res);
		//GLUI_Master.set_glutKeyboardFunc(keyPressed);
		update=true;
		glutPostRedisplay();
}

int main(int argc,char* argv[])
{

  try {
    if (argc < 2) {
      cerr << "Usage: " << argv[0] << " IOR" << endl;
      return 1;
    }

    // Initialize ORB
    orb = CORBA::ORB_init(argc, argv);
    cout << "Init !\n";

    cout << "Obteniendo servicio de nombres...";
    CORBA::Object_var nameService =
		orb->resolve_initial_references("NameService");
    cout << "(2)...";
    CosNaming::NamingContext_var namingContext =
		CosNaming::NamingContext::_narrow( nameService );
    cout << "hecho." << endl;
	if (CORBA::is_nil (namingContext)) {
            cerr << "oops, I cannot access the Naming Service!" << endl;
            exit (1);
        }

    cout << "Construyendo nombre para invocar al servant...";
    CosNaming::Name name;
    name.length(1);
    name[0].id = CORBA::string_dup( "Camera" );
    name[0].kind = CORBA::string_dup( "" );
    cout << "hecho." << endl;

    cout << "Resolviendo nombre...";
    #ifdef HAVE_EXCEPTIONS
        try {
              obj = namingContext->resolve (name);
        }
        catch (CosNaming::NamingContext::NotFound &exc) {
              cout << "NotFound exception." << endl;
              exit (1);
        }
        catch (CosNaming::NamingContext::CannotProceed &exc) {
              cout << "CannotProceed exception." << endl;
              exit (1);
        }
        catch (CosNaming::NamingContext::InvalidName &exc) {
              cout << "InvalidName exception." << endl;
              exit (1);
        }
    #else
              obj = namingContext->resolve (name);
    #endif
    cout << "hecho." << endl;

    // Narrow the reference
    im = higgs::Camera::_narrow (obj);

    cout << "Narrow !\n";
    if (CORBA::is_nil(im)) {
       cerr << "NIL Reference obtained from _narrow()" << endl;
       throw 0;
    }

    long background=0x010203;
    int i, j, k;

    i=0;
    j=0;
    k=0;
    fps = 2;

    im->init();
	if ( strcmp((const char*)im->model(), "iSight")==0) {
		videreStereo=false;
	} else if ( strcmp((const char*)im->model(), "MDS-STH")==0) {
		videreStereo=true;
	}

    if (im->getDeviceWidth()==640) {
    	device_width=640;
    	device_height=480;
    	format=XV_UYVY;
    	if (im->getRes()==Res_640x480_rgb) {
    		res = Res_640x480_rgb;
    	} else if (im->getRes()==Res_640x480) {
    		res = Res_640x480;
    	}
    }
    if (im->getDeviceWidth()==1280) {
    	device_width=1280;
    	device_height=960;
    	format=XV_UYVY;
    	res = Res_1280x960;
    }

    printf("Valor de framerate: %d \n", fps);
    printf("Valor de res: %d \n", res);
    numCameras = 1;
    printf("Número de camaras: %d \n", numCameras);
    fflush(stdout);
    set_frame_length(1280*960,numCameras);

    str=(char*)malloc(30);
    sprintf(str, "HIGGS - calibrando FPS");

  /* Initialize GLUT state - glut will take any command line arguments that pertain to it or
     X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */
  glutInit(&argc, argv);

  /* Select type of Display mode:
     Double buffer
     RGBA color
     Alpha components supported
     Depth buffer */
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

  /* get a width x height window */
  glutInitWindowSize(device_width+PANEL_SIZE, device_height);

  /* the window starts at the upper left corner of the screen */
  glutInitWindowPosition(0, 0);

  /* Open a window */
  window = glutCreateWindow("HIGGS ... AHM'09");

  /* Register the function to do all our OpenGL drawing. */
  glutDisplayFunc(&DrawGLScene);

  /* Go fullscreen.  This is the soonest we could possibly go fullscreen. */
  //glutFullScreen();
  glutSetWindow(window);

  glui = GLUI_Master.create_glui_subwindow(window, GLUI_SUBWINDOW_RIGHT);
  glui->set_main_gfx_window(window);

  char camera_vendor[300]="";
  strncat(camera_vendor, im->vendor(), 14);
  printf("%s\n", camera_vendor);
  char camera_model[300]="Camera: ";
  strncat(camera_model, im->model(), 10);
  printf("%s\n", camera_model);
  glui->add_statictext(camera_vendor);
  glui->add_statictext(camera_model);
  glui->add_separator();
  glui->add_button("Quit", 0, (GLUI_Update_CB) GLUI_exit);
  glui->add_button("Finish", 0, (GLUI_Update_CB) GLUI_finish);
  glui->add_separator();
  glui->add_button("A-320x40", 0, (GLUI_Update_CB) GLUI_size_small);
  glui->add_button("S-640x480", 0, (GLUI_Update_CB) GLUI_size_medium);
  glui->add_button("D-1280x960", 0, (GLUI_Update_CB) GLUI_size_big);
  glui->add_separator();
  glui->add_button("H-YUV320", 0, (GLUI_Update_CB) GLUI_320_YUV);
  glui->add_button("J-RGB640", 0, (GLUI_Update_CB) GLUI_640_RGB);
  glui->add_button("K-YUV640", 0, (GLUI_Update_CB) GLUI_640_YUV);
  glui->add_button("L-YUV1280", 0, (GLUI_Update_CB) GLUI_1280_YUV);
  glui->add_separator();
  glui->add_button("P-Restart", 0, (GLUI_Update_CB) GLUI_restart);
  glui->add_button("U-Update", 0, (GLUI_Update_CB) GLUI_update);
  glui->add_button("Full Screen", 0, (GLUI_Update_CB) GLUI_full_screen);
  glui->add_separator();
  glui->add_button("N-Bright-", 0, (GLUI_Update_CB) GLUI_bright_minus);
  glui->add_button("M-Bright+", 0, (GLUI_Update_CB) GLUI_bright_plus);
  glui->add_button(",-Gain-", 0, (GLUI_Update_CB) GLUI_gain_minus);
  glui->add_button(".-Gain+", 0, (GLUI_Update_CB) GLUI_gain_plus);
  glui->add_button(" -Expo-", 0, (GLUI_Update_CB) GLUI_expo_minus);
  glui->add_button(" -Expo+", 0, (GLUI_Update_CB) GLUI_expo_plus);
  glui->add_separator();

  /* Even if there are no events, redraw our gl scene. */
  //glutIdleFunc(&DrawGLScene);
  GLUI_Master.set_glutIdleFunc(DrawGLScene);

  /* Register the function called when our window is resized. */
  //glutReshapeFunc(&ReSizeGLScene);
  GLUI_Master.set_glutReshapeFunc(ReSizeGLScene);

  /* Register the function called when the keyboard is pressed. */
  //glutKeyboardFunc(&keyPressed);
  GLUI_Master.set_glutKeyboardFunc(keyPressed);

  /* Initialize our window. */
  printf("GLUT Init --- ");
  InitGL(device_width, device_height);
  BuildFont();
  //im->restart();

  //DevIL
  ilInit();
  ilEnable(IL_NVIDIA_COMPRESS);
  ilGenImages(1, &image_id);
  ilBindImage(image_id);
  //image_data = (GLubyte*)malloc(device_width * device_height * 4 * sizeof(GLubyte));
  image_data = (GLubyte*)malloc(1280 * 960 * 4 * sizeof(GLubyte));
  ilTexImage(device_width, device_height, 1, 3, GL_RGB, GL_UNSIGNED_BYTE, image_data);

  update=true;

  /* Start Event Processing Engine */
  printf("GLUT Main Loop\n");
  glutMainLoop();

  } catch (CORBA::Exception &) {
    cerr << "CORBA exception raised!" << endl;
  }
  return 0;
}

