#ifndef __encode__H_
#define __encode__H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <sys/types.h>

#ifdef HAVE_AV_CONFIG_H
#undef HAVE_AV_CONFIG_H
#endif

#if defined(__linux__)
extern "C" {
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
    #include <libavcodec/avcodec.h>
    #include <libavutil/mathematics.h>
    #include <libavutil/pixfmt.h>
}
#elif defined(__APPLE__)
extern "C" {
	//include <ffmpeg/avutil.h>
	//include <ffmpeg/avformat.h>
        //include <ffmpeg/swscale.h>
	#include <ffmpeg/avcodec.h>
	#include <ffmpeg/mathematics.h>
}
#endif

#define STREAM_FRAME_RATE 25 /* 25 images/s */
#define STREAM_PIX_FMT PIX_FMT_YUV420P /* default pix_fmt */

static int sws_flags = SWS_BICUBIC;
//define INT64_C

#define INBUF_SIZE 4096



//extern AVCodec *codec;
//extern AVCodecContext *c;
//extern int u, out_size, size, x, y, outbuf_size;
//extern FILE *f;
//extern AVFrame *picture;
//extern uint8_t *outbuf, *picture_buf;

void yuv420_encode_start(void);
void yuv420_encode_image(uint8_t*);
void yuv422p_encode_start(void);
void yuv422p_encode_image(uint8_t*);
void yuv422_encode_start(void);
void yuv422_encode_image(uint8_t*);
void video_encode_stop(void);

#endif // __encode__H_

