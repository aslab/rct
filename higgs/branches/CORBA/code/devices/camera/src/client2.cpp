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
#include "CameraC.cpp"
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
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xvlib.h>
#include <X11/keysym.h>
#define _GNU_SOURCE
#include <getopt.h>
#include <stdint.h>
#include <inttypes.h>

#include "dc1394/dc1394.h"


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

#if defined(__linux__)
#define CAMARA_STEREO 1
#define GLvoid void
#endif

/* declarations for libdc1394 */
/*
    dc1394camera_t *cameras[MAX_CAMERAS];
    dc1394featureset_t features;
    dc1394video_frame_t * frames[MAX_CAMERAS];
*/
int numCameras = 0;
short camera = 1;
bool  update = true;

/* declarations for video1394 
char *device_name=NULL;

/* declarations for Xwindows */
Display *display=NULL;
Window window=(Window)NULL;
long width,height;
long device_width,device_height;
int connection=-1;
XvImage *xv_image=NULL;
XvAdaptorInfo *info;
long format=0;
GC gc;

XImage *x_image=NULL;
int screen;
int depth;
Visual *visual=NULL;

/* Other declarations */
long frame_length;
long frame_free;
int frame=0;
int adaptor=-1;
int f;

int freeze=0;
int average=0;
int fps;
int res;

unsigned char *yuv;
char *frame_buffer5=NULL;
char *frame_buffer6=NULL;
char *frame_buffer7=NULL;
char *frame_buffer8=NULL;
char *frame_buffer9=NULL;

higgs::Camera_var im;
char *data=NULL;
char *str;
    
/*static struct option long_options[]={
    {"device",1,NULL,0},
    {"fps",1,NULL,0},
    {"res",1,NULL,0},
    {"help",0,NULL,0},
    {NULL,0,0,0}
};*/
/* image format conversion functions */

/*static inline
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

/* helper functions */

void set_frame_length(long size, int numCameras)
{
    frame_length=size;
    //dc1394_log_debug("Setting frame size to %ld kb",size/1024);
    frame_free=0;
    printf("tamaño %d \n", size);
    frame_buffer5 = (char*) malloc( 614400 * 2);
    frame_buffer6 = (char*) malloc( 614400 * 2);
    frame_buffer7 = (char*) malloc( 614400 * 2);
    frame_buffer8 = (char*) malloc( 614400 * 2);
    frame_buffer9 = (char*) malloc( 614400 * 2);
}

static double current_time(void)
{
    struct timeval tv;
    struct timezone tz;
    (void) gettimeofday(&tv, &tz);
    return (double) tv.tv_sec + tv.tv_usec / 1000000.0;
}

//Adolfo
 /*void display_frames() {
	int i=0;
		// Camara derecha
        	dc1394_deinterlace_stereo(frames[i]->image,
        		(uint8_t*)frame_buffer6 + (i * frame_length),
        		device_width, device_height*2);
        	dc1394_bayer_decoding_8bit((uint8_t*)frame_buffer6 + (i * frame_length),
        		(uint8_t*)frame_buffer7 + (i * frame_length),
        		device_width, device_height,
        		DC1394_COLOR_FILTER_GRBG,DC1394_BAYER_METHOD_SIMPLE);
        	dc1394_convert_to_YUV422((uint8_t*)frame_buffer7 + (i * frame_length),
        		(uint8_t*)frame_buffer8 + (i * frame_length),
        		device_width, device_height,
        		DC1394_BYTE_ORDER_UYVY,
        		DC1394_COLOR_CODING_RGB8,
        		8);
        	// Camara Izquierda
        	dc1394_deinterlace_stereo(frames[i]->image+1,
        		(uint8_t*)frame_buffer6 + ((i+1) * frame_length),
        		device_width, device_height*2);
        	dc1394_bayer_decoding_8bit((uint8_t*)frame_buffer6 + ((i+1) * frame_length),
        		(uint8_t*)frame_buffer6 + ((i+1) * frame_length),
        		device_width, device_height,
        		DC1394_COLOR_FILTER_GRBG,DC1394_BAYER_METHOD_SIMPLE);
        	dc1394_convert_to_YUV422((uint8_t*)frame_buffer7 + ((i+1) * frame_length),
        		(uint8_t*)frame_buffer5 + ((i+1) * frame_length),
        		device_width, device_height,
        		DC1394_BYTE_ORDER_UYVY,
        		DC1394_COLOR_CODING_RGB8,
        		8);
                //memcpy( frame_buffer + (i * frame_length),
                //        frames[i]->image, device_width*device_height*2);
                //memcpy( frame_buffer + (i * frame_length),
                //        frame_buffer2 + (i * frame_length), device_width*device_height*1);
    }*/

// Adolfo acaba aqui

void display_frames()
{
      static int frames = 0;
      static double dt, fps1;
      static double t1=-1.0, t2=-1.0;
      static higgs::ImagenData_var datos;

      int j,k;

      if(!freeze){	
    	t2 = current_time();
        if(t1 < 0.0)
    	    t1 = t2;
    	datos = new higgs::ImagenData;
	datos=im->getImagen(camera, update);
/*
        for (int g = 0; g < 1228800/2; g++){
	  frame_buffer5[g]=datos[g];
        }
*/
#ifdef CAMARA_STEREO
	dc1394_bayer_decoding_8bit((uint8_t*)&datos[0], (uint8_t*)frame_buffer6,
			device_width, device_height,
			DC1394_COLOR_FILTER_GRBG, DC1394_BAYER_METHOD_SIMPLE);
#else
	dc1394_convert_to_RGB8((uint8_t*)&datos[0], (uint8_t*)frame_buffer6,
                        device_width, device_height,
                        DC1394_BYTE_ORDER_UYVY,DC1394_COLOR_CODING_YUV422,16);
#endif
	frames++;

/*
     	xv_image=XvCreateImage(display,info[adaptor].base_id,format,frame_buffer8,
                               device_width,device_height * 1);
*/

        for(k=0;k<device_height;k++) {
            for(j=0;j<device_width;j++) {
                data[(k*device_width+j)*4+2]=frame_buffer6[(k*device_width+j)*3+0];
                data[(k*device_width+j)*4+1]=frame_buffer6[(k*device_width+j)*3+1];
                data[(k*device_width+j)*4+0]=frame_buffer6[(k*device_width+j)*3+2];
            }
        }
/*

	if(device_height>300)
	{
     	  XvPutImage(display,info[adaptor].base_id,window,gc,xv_image,
                   0,0,device_width,device_height*1/10,
                   0,0,width,height*1/10);
    	  sprintf(str, "HIGGS - %6.3f FPS", fps1);

	  XSetForeground(display, gc, 0xFF0000);
          //XDrawImageString(display,window,gc,30,30,str, strlen(str));
          XDrawString(display,window,gc,30,30,str, strlen(str));
	  XDrawLine(display,window,gc,28,6,270,6);
	  XDrawLine(display,window,gc,28,32,270,32);
	  XDrawLine(display,window,gc,28,6,28,32);
	  XDrawLine(display,window,gc,270,6,270,32);

     	  XvPutImage(display,info[adaptor].base_id,window,gc,xv_image,
                   0,device_height*1/10,device_width,device_height*9/10,
                   0,height*1/10,width,height*9/10);
     	  xv_image=NULL;
          XDrawString(display,window,gc,30,30,str, strlen(str));
	} else {
     	  XvPutImage(display,info[adaptor].base_id,window,gc,xv_image,
                   0,0,device_width,device_height * 1,
                   0,0,width,height);
     	  xv_image=NULL;

    	  sprintf(str, "HIGGS - %6.3f FPS", fps1);
	  XSetForeground(display, gc, 0xFF0000);
          //XDrawImageString(display,window,gc,30,30,str, strlen(str));
          XDrawString(display,window,gc,30,30,str, strlen(str));
	  XDrawLine(display,window,gc,28,6,270,6);
	  XDrawLine(display,window,gc,28,32,270,32);
	  XDrawLine(display,window,gc,28,6,28,32);
	  XDrawLine(display,window,gc,270,6,270,32);
	}
*/
	//XSetForeground(display, gc, 0xFF0000);

        XPutImage(display,window,gc,x_image,
                   0,0,0,0,width,100);

        sprintf(str, "HIGGS - %6.3f FPS", fps1);
        XDrawString(display,window,gc,30,30,str, strlen(str));

        XDrawLine(display,window,gc,28,6,270,6);
        XDrawLine(display,window,gc,28,32,270,32);
        XDrawLine(display,window,gc,28,6,28,32);
        XDrawLine(display,window,gc,270,6,270,32);

        XPutImage(display,window,gc,x_image,
                   0,100,0,100,width,height-100);

        if(t2 - t1 >= 1.0) {
    	    dt = t2 - t1;
    	    fps1 = frames / dt;
    	    printf("%d frames in %3.1f seconds = %6.3f FPS\n", frames, dt, fps1);
    	    t1 = t2;
    	    frames = 0;
        }
      }
      XFlush(display);
}

void QueryXv()
{
    int num_adaptors;
    int num_formats;
    XvImageFormatValues *formats=NULL;
    int i,j;
    char xv_name[5];
    XvQueryAdaptors(display,DefaultRootWindow(display),(unsigned int*)&num_adaptors,&info);
    printf("num_adaptors %d \n",num_adaptors);
    for(i=0;i<num_adaptors;i++) {
        formats=XvListImageFormats(display,info[i].base_id,&num_formats);
        printf("num_formats %d \n", num_formats);
        for(j=0;j<num_formats;j++) {
            xv_name[4]=0;
            memcpy(xv_name,&formats[j].id,4);
            printf("detected Xv format 0x%x %s %s \n",formats[j].id,xv_name,(formats[j].format==XvPacked)?"packed":"planar");
            if(formats[j].id==format) {
                printf("using Xv format 0x%x %s %s \n",formats[j].id,xv_name,(formats[j].format==XvPacked)?"packed":"planar");
                if(adaptor<0)adaptor=i;
		//printf("vamos %d \n",j);
            }
        }
    }
    
    XFree(formats);
    if(adaptor<0)
    {
	adaptor=1;
        printf("No suitable Xv adaptor found\n");
        //dc1394_log_error("No suitable Xv adaptor found");
    }
}

void cleanup(void) {
/*
    // Clean dc1394
    int i;
    for (i=0; i < numCameras; i++) {
        dc1394_video_set_transmission(cameras[i], DC1394_OFF);
        dc1394_capture_stop(cameras[i]);
    }
*/
    if ((void *)window != NULL)
        XUnmapWindow(display,window);
    if (display != NULL)
        XFlush(display);

    if (frame_buffer5 != NULL)
        free(frame_buffer5);
    if (frame_buffer6 != NULL)
        free(frame_buffer6);
    if (frame_buffer7 != NULL)
        free(frame_buffer7);
    if (frame_buffer8 != NULL)
        free(frame_buffer8);
}


int main(int argc,char* argv[])
{

  try {
    if (argc < 2) {
      cerr << "Usage: " << argv[0] << " IOR" << endl;
      return 1;
    }

    // Initialize ORB
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
    cout << "Init !\n";

    // Read object reference
    /*
    CORBA::Object_var obj = orb->string_to_object (argv[1]);
    if (CORBA::is_nil(obj)) {
       cerr << "NIL Reference obtained from string" << endl;
       throw 0;
    }
    */

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
    CORBA::Object_var obj;
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
                                                                                                                                                                                                                
    //cout << "String to Object !\n";

    // Narrow the reference
    //Imagen_var im = Imagen::_narrow (obj);
    im = higgs::Camera::_narrow (obj);

    cout << "Narrow !\n";
    if (CORBA::is_nil(im)) {
       cerr << "NIL Reference obtained from _narrow()" << endl;
       throw 0;
    }


    XEvent xev;
    XGCValues xgcv;
    long background=0x010203;
    //unsigned char *yuv;
    int i, j, k;
    
    j=0;
    i=0;
    k=0;
    //dc1394_t * d;
    //dc1394camera_list_t * list;
    
    fps = 2;
    printf("valor de framerate %d \n", fps);
    printf("valor de res %d \n", res);
    //res = DC1394_VIDEO_MODE_640x480_YUV422;
    device_width=640;
    device_height=480;
    format=XV_UYVY;

    /*dc1394error_t err;
    
    d = dc1394_new ();
    err=dc1394_camera_enumerate (d, &list);
    DC1394_ERR_RTN(err,"Failed to enumerate cameras");*/
    //cameras[0] = dc1394_camera_new (d, list->ids[0].guid);
    //cameras[1] = dc1394_camera_new (d, list->ids[0].guid);
    numCameras = 1;
    printf("numero de camaras %d \n", numCameras);
    //dc1394_camera_free_list (list);


    fflush(stdout);
    
    set_frame_length(1228800,0);
    /* make the window */
    display=XOpenDisplay(getenv("DISPLAY"));

    QueryXv();

    width=device_width;
    height=device_height * 1;
    

    window=XCreateSimpleWindow(display,DefaultRootWindow(display),0,0,width,height,0,
                               WhitePixel(display,DefaultScreen(display)),
                               background);

    XSelectInput(display,window,StructureNotifyMask|KeyPressMask);
    XMapWindow(display,window);
    connection=ConnectionNumber(display);

    gc=XCreateGC(display,window,0,&xgcv);
    data = (char*) malloc(device_width*device_height*4);
    str=(char*)malloc(30);

    screen = DefaultScreen(display);
    depth = DefaultDepth(display,screen);
    visual = DefaultVisual(display, screen);

    x_image=XCreateImage(display,visual,depth,ZPixmap,0,data,
                device_width,device_height,32,0);

    XSetForeground(display, gc, 0xFF0000);
    //static  char *fontname="-adobe-helvetica-bold-r-normal--34-240-100-100-p-182-iso8859-1";
    static  char *fontname="12x24";
    XSetFont(display, gc, XLoadFont(display,fontname));

    /* main event loop !*/
    while(1){
	
     display_frames();
 
     while(XPending(display)>0){
	    XNextEvent(display,&xev);
	    switch(xev.type){
            case ConfigureNotify:
            	width=xev.xconfigure.width;
            	height=xev.xconfigure.height;
		display_frames();
		break;
	    case KeyPress:
                switch(XKeycodeToKeysym(display,xev.xkey.keycode,0)){
                case XK_q:
                case XK_Q:
                    cleanup();
                    exit(0);
                    break;
                case XK_u:
                case XK_U:
		    if (update==1)
			update=0;
		    else
			update=1;
                    break;
                case XK_x:
                case XK_X:
					im->finish();
                    cleanup();
                    exit(0);
                    break;
                case XK_comma:
                case XK_less:
                    width=width/2;
                    height=height/2;
                    XResizeWindow(display,window,width,height);
                    display_frames();
                    break;
                case XK_period:
                case XK_greater:
                    width=2*width;
                    height=2*height;
                    XResizeWindow(display,window,width,height);
                    display_frames();
                    break;
                case XK_0:
                    freeze = !freeze;
                    break;
                case XK_1:
                    camera=1;
                    display_frames();
                    break;
                case XK_2:
                    camera=2;
                    display_frames();
                    break;
/*
                case XK_1:
                    fps =        DC1394_FRAMERATE_1_875;
                    for (i = 0; i < numCameras; i++)
                        dc1394_video_set_framerate(cameras[i], fps);
                    break;
                case XK_2:
                    fps =        DC1394_FRAMERATE_3_75;
                    for (i = 0; i < numCameras; i++)
                        dc1394_video_set_framerate(cameras[i], fps);
                    break;
                case XK_4:
                    fps = DC1394_FRAMERATE_15;
                    for (i = 0; i < numCameras; i++)
                        dc1394_video_set_framerate(cameras[i], fps);
                    break;
                case XK_5:
                    fps = DC1394_FRAMERATE_30;
                    for (i = 0; i < numCameras; i++)
                        dc1394_video_set_framerate(cameras[i], fps);
                    break;
                case XK_3:
                    fps = DC1394_FRAMERATE_7_5;
                    for (i = 0; i < numCameras; i++)
                        dc1394_video_set_framerate(cameras[i], fps);
                    break;
*/
                }
                break;
	}
     } /* XPending */

        //for (i = 0; i < 1; i++) {
          //      dc1394_capture_enqueue (cameras[i], frames[i]);
	//}
    } /* while not interrupted */
    exit(0);
  }
    catch (CORBA::Exception &) {
    cerr << "CORBA exception raised!" << endl;
  }
  return 0;
}

