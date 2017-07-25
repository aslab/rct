#include <iostream>

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

using namespace std;

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

void set_frame_length(long size, int numCameras)
{
    frame_length=size;
    //dc1394_log_debug("Setting frame size to %ld kb",size/1024);
    frame_free=0;
    printf("tama<F1>o %d \n", size);
    frame_buffer5 = (char*) malloc( 614400 *  2);
    frame_buffer6 = (char*) malloc( 614400 * 2);
    frame_buffer7 = (char*) malloc( 614400 * 2);
    frame_buffer8 = (char*) malloc( 614400 * 2);
}


static double current_time(void)
{
    struct timeval tv;
    struct timezone tz;
    (void) gettimeofday(&tv, &tz);
    return (double) tv.tv_sec + tv.tv_usec / 1000000.0;
}

void display_frames()
{
      static int frames = 0;
      static double dt, fps1;
      static double t1=-1.0, t2=-1.0;
      char *str;

      if(!freeze){      
        str=(char*)malloc(30);
        t2 = current_time();
        if(t1 < 0.0)
            t1 = t2;
        frames++;

        //xv_image=XvCreateImage(display,info[adaptor].base_id,format,frame_buffer8,
        //                       device_width,device_height * 1);

        sprintf(str, "HIGGS - %6.3f FPS", fps1);

        XSetForeground(display, gc, 0xFF0000);
        XDrawImageString(display,window,gc,30,30,str, strlen(str));

	XDrawLine(display,window,gc,28,6,270,6);
	XDrawLine(display,window,gc,28,32,270,32);
	XDrawLine(display,window,gc,28,6,28,32);
	XDrawLine(display,window,gc,270,6,270,32);

        //XDrawString(display,window,gc,30,30,str, strlen(str));
	xv_image=NULL;
        if(t2 - t1 >= 5.0) {
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
    //if(adaptor<0)
        //dc1394_log_error("No suitable Xv adaptor found");

}

void cleanup(void) {
    if ((void *)window != NULL)
        XUnmapWindow(display,window);
    if (display != NULL)
        XFlush(display);
}

int main(int argc,char* argv[])
{

    if (argc < 1) {
      cerr << "Usage: " << argv[0] << " IOR" << endl;
      return 1;
    }

    XEvent xev;
    XGCValues xgcv;
    long background=0x010203;


    device_width=640;
    device_height=480;
    format=XV_UYVY;
    width=device_width;
    height=device_height * 2;

    /* make the window */
    display=XOpenDisplay(getenv("DISPLAY"));

    //QueryXv();

    width=device_width;
    height=device_height * 1;
    

    window=XCreateSimpleWindow(display,DefaultRootWindow(display),0,0,width,height,0,
                               WhitePixel(display,DefaultScreen(display)),
                               background);

    XSelectInput(display,window,StructureNotifyMask|KeyPressMask);
    XMapWindow(display,window);
    connection=ConnectionNumber(display);

    gc=XCreateGC(display,window,0,&xgcv);

    //Datos0=(char*)malloc(614400);
    //Datos1=(char*)malloc(614400);

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
                }
                break;
         }
      } /* XPending */

    } /* while not interrupted */
    exit(0);
  //}
  return 0;
}
                                    
