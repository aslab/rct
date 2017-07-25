#include "encode.h"

int i,j,k;
AVCodec *codec=NULL;
AVCodecContext *c=NULL;
int u, out_size, size, x, y, video_outbuf_size;
FILE *f;
AVFrame *picture, *tmp_picture;
uint8_t *video_outbuf, *picture_buf;

#if defined(__linux__)
AVStream *video_st=NULL;
AVFormatContext *oc=NULL;
#endif

/* add a video output stream */
static AVStream *add_video_stream(AVFormatContext *oc, CodecID codec_id)
{
    AVCodecContext *c;
    AVStream *st;

    st = av_new_stream(oc, 0);
    if (!st) {
        fprintf(stderr, "Could not alloc stream\n");
        exit(1);
    }

    c = st->codec;
    c->codec_id = codec_id;
    c->codec_type = CODEC_TYPE_VIDEO;

    /* put sample parameters */
    c->bit_rate = 2000000;
    /* resolution must be a multiple of two */
    c->width = 640;
    c->height = 480;
    /* time base: this is the fundamental unit of time (in seconds) in terms
      of which frame timestamps are represented. for fixed-fps content,
      timebase should be 1/framerate and timestamp increments should be
      identically 1. */
    c->time_base.den = STREAM_FRAME_RATE;
    c->time_base.num = 1;
    c->gop_size = 12; /* emit one intra frame every twelve frames at most */
    c->pix_fmt = STREAM_PIX_FMT;
    //c->pix_fmt = PIX_FMT_YUYV422;
    if (c->codec_id == CODEC_ID_MPEG2VIDEO) {
        /* just for testing, we also add B frames */
        c->max_b_frames = 2;
    }
    if (c->codec_id == CODEC_ID_MPEG1VIDEO){
        /* Needed to avoid using macroblocks in which some coeffs overflow.
           This does not happen with normal video, it just happens here as
           the motion of the chroma plane does not match the luma plane. */
        c->mb_decision=2;
    }
    // some formats want stream headers to be separate
    if(oc->oformat->flags & AVFMT_GLOBALHEADER)
        c->flags |= CODEC_FLAG_GLOBAL_HEADER;

    return st;
}

static AVFrame *alloc_picture(PixelFormat pix_fmt, int width, int height)
{
    AVFrame *picture;
    uint8_t *picture_buf;
    int size;

    picture = avcodec_alloc_frame();
    if (!picture)
        return NULL;
    size = avpicture_get_size(pix_fmt, width, height);
    picture_buf = (uint8_t*) av_malloc(size);
    if (!picture_buf) {
        av_free(picture);
        return NULL;
    }
    avpicture_fill((AVPicture *)picture, picture_buf,
                   pix_fmt, width, height);
    return picture;
}

static void open_video(AVFormatContext *oc, AVStream *st)
{
    AVCodec *codec;
    AVCodecContext *c;

    c = st->codec;

    /* find the video encoder */
    codec = avcodec_find_encoder(c->codec_id);
    if (!codec) {
        fprintf(stderr, "codec not found\n");
        exit(1);
    }

    /* open the codec */
    if (avcodec_open(c, codec) < 0) {
        fprintf(stderr, "could not open codec\n");
        exit(1);
    }

    video_outbuf = NULL;
    if (!(oc->oformat->flags & AVFMT_RAWPICTURE)) {
        /* allocate output buffer */
        /* XXX: API change will be done */
        /* buffers passed into lav* can be allocated any way you prefer,
           as long as they're aligned enough for the architecture, and
           they're freed appropriately (such as using av_free for buffers
           allocated with av_malloc) */
        video_outbuf_size = 5000000;
        video_outbuf = (uint8_t*) av_malloc(video_outbuf_size);
    }

    /* allocate the encoded raw picture */
    picture = alloc_picture(c->pix_fmt, c->width, c->height);
    picture = alloc_picture(c->pix_fmt, c->width, c->height);
    if (!picture) {
        fprintf(stderr, "Could not allocate picture\n");
        exit(1);
    }

    /* if the output format is not YUV420P, then a temporary YUV420P
       picture is needed too. It is then converted to the required
       output format */
    tmp_picture = NULL;
    if (c->pix_fmt != PIX_FMT_YUV420P) {
        tmp_picture = alloc_picture(PIX_FMT_YUV420P, c->width, c->height);
        if (!tmp_picture) {
            fprintf(stderr, "Could not allocate temporary picture\n");
            exit(1);
        }
    }
}


static void close_video(AVFormatContext *oc, AVStream *st)
{
    avcodec_close(st->codec);
    av_free(picture->data[0]);
    av_free(picture);

    if (tmp_picture) {
        av_free(tmp_picture->data[0]);
        av_free(tmp_picture);
    }

    av_free(video_outbuf);
}

void yuv420_encode_start(void)
{
    k=0;
    printf("Video encoding\n");
    //const char *filename = "/tmp/test.avi";     // AVI
    //const char *filename = "/tmp/test.mpg"; // MPEG1
    const char *filename = "/tmp/test.dvd"; // MPEG2
    //const char *filename = "/tmp/test.mp4"; // MPEG4
    //const char *filename = "/tmp/test.wmv"; // WMV

    /* must be called before using avcodec lib */
    //avcodec_init();

    /* register all the codecs */
    //avcodec_register_all();

    /* initialize libavcodec, and register all codecs and formats */
    av_register_all();

    // allocate the output media context 
    oc = avformat_alloc_context();
    if (!oc) {
	fprintf(stderr, "Memory error\n");
    }
	
    oc->oformat = guess_format(NULL, filename, NULL);
    if (!oc->oformat) {
	printf("Could not deduce output format from file extension: \n");
	printf("Using MPEG.\n");
	oc->oformat = guess_format("mpeg", NULL, NULL);
    }
    if (!oc->oformat) {
    	fprintf(stderr, "Could not find suitable output format\n");
	exit(1);
    }

    video_st = add_video_stream(oc, oc->oformat->video_codec);
    if (!video_st) {
	fprintf(stderr, "Could not alloc stream\n");
	exit(1);
    }

    /* set the output parameters (must be done even if no
       parameters). */
    if (av_set_parameters(oc, NULL) < 0) {
	fprintf(stderr, "Invalid output format parameters\n");
	exit(1);
    }

    dump_format(oc, 0, filename, 1);

    /* now that all the parameters are set, we can open the audio and
       video codecs and allocate the necessary encode buffers */
    if (video_st)
        open_video(oc, video_st);

    // open the output file, if needed
    if (!(oc->oformat->flags & AVFMT_NOFILE)) {
        if (url_fopen(&oc->pb, filename, URL_WRONLY) < 0) {
            fprintf(stderr, "Could not open '%s'\n", filename);
            exit(1);
        }
    }

    // write the stream header, if any
    av_write_header(oc);

    c=video_st->codec;
    size = c->width * c->height;
}

void yuv420_encode_image(uint8_t* data)
{
    static struct SwsContext *img_convert_ctx;
    static int linesize[4]={640*2,0,0,0};
    int ret;

    fflush(stdout);
    c=video_st->codec;
/*
#if defined(__linux__)
    for(i=0;i<size;i++)
    {
	    picture->data[0][i] = data[i*2+1];
    }
    for(i=0;i<c->height/1;i=i+2)
	{
	    for(j=0;j<c->width/1;j=j+2)
	    {
	        picture->data[1][i/2*c->width/2+j/2] = data[(i*c->width+j)*2+0];
	        picture->data[2][i/2*c->width/2+j/2] = data[(i*c->width+j)*2+2];
	    }
    }
#elif defined(__APPLE__)
    for(i=0;i<size;i++)
    {
		picture->data[0][i] = data[i*2+0];
    }
    for(i=0;i<c->height*1;i=i+2)
    {
	    for(j=0;j<c->width/1;j=j+2)
	    {
	        picture->data[1][i/2*c->width/2+j/2] = data[(i*c->width+j)*2+1];
	        picture->data[2][i/2*c->width/2+j/2] = data[(i*c->width+j)*2+3];
	    }
    }
#endif
*/

    // Convert UYVY422 to YUV420P
    if (img_convert_ctx == NULL) {
        img_convert_ctx = sws_getContext(c->width, c->height,
                                             PIX_FMT_UYVY422,
                                             c->width, c->height,
                                             c->pix_fmt,
                                             sws_flags, NULL, NULL, NULL);
        if (img_convert_ctx == NULL) {
            fprintf(stderr, "Cannot initialize the conversion context\n");
            exit(1);
        }
    }
    sws_scale(img_convert_ctx, &data, linesize,
                  0, c->height, picture->data, picture->linesize);
	
    /* encode the image */
    out_size = avcodec_encode_video(c, video_outbuf, video_outbuf_size, picture);
    printf("encoding frame %3d (size=%5d)\n", k, out_size);
    /* if zero size, it means the image was buffered */
    if (out_size > 0) {
        AVPacket pkt;
        av_init_packet(&pkt);

        if (c->coded_frame->pts != AV_NOPTS_VALUE)
            pkt.pts= av_rescale_q(c->coded_frame->pts, c->time_base, video_st->time_base);
        if(c->coded_frame->key_frame)
            pkt.flags |= PKT_FLAG_KEY;
        pkt.stream_index= video_st->index;
        pkt.data= video_outbuf;
        pkt.size= out_size;

        /* write the compressed frame in the media file */
        ret = av_interleaved_write_frame(oc, &pkt);
    } else {
	ret = 0;
    }

    if (ret != 0) {
        fprintf(stderr, "Error while writing video frame\n");
        exit(1);
    }
    //frame_count++;

    k++;
    if(k>25) 
	k=0;
}

void yuv422p_encode_start(void)
{
    k=0;
    printf("Video encoding\n");
    const char *filename = "/tmp/test.mpg";

    /* must be called before using avcodec lib */
    avcodec_init();

    /* register all the codecs */
    avcodec_register_all();

    // Find de mpeg1 vido encoder
    codec = avcodec_find_encoder(CODEC_ID_MPEG2VIDEO);
    //codec = avcodec_find_encoder(CODEC_ID_H264);
    //codec = avcodec_find_encoder(CODEC_ID_MPEG4);
    if (!codec) {
	fprintf(stderr, "codec not found\n");
	exit(1);
    }

    c = avcodec_alloc_context();
    picture = avcodec_alloc_frame();

    /* put sample parameters */
    c->bit_rate = 3000000;
    /* resolution must be a multiple of two */
    c->width = 640;
    c->height = 480;
#if defined(__linux__)
    /* frames per second */
    c->time_base= (AVRational){1,25};
	//c->time_base.den=25;
	//c->time_base.num=1;
#endif
    c->gop_size = 10; /* emit one intra frame every ten frames */
    c->max_b_frames=1;
    c->pix_fmt = PIX_FMT_YUV422P;
    //c->pix_fmt = PIX_FMT_UYVY422;

    /* open it */
    if (avcodec_open(c, codec) < 0) {
        fprintf(stderr, "could not open codec\n");
        exit(1);
    }

    f = fopen(filename, "wb");
    if (!f) {
        fprintf(stderr, "could not open %s\n", filename);
        exit(1);
    }

    /* alloc image and output buffer */
    video_outbuf_size = 2000000;
    video_outbuf = (uint8_t*) malloc(video_outbuf_size);
    size = c->width * c->height;
    picture_buf = (uint8_t*) malloc((size * 2)); /* size for YUV 422 */

    picture->data[0] = picture_buf;
    picture->data[1] = picture->data[0] + size;
	picture->data[2] = picture->data[1] + size/2;
    picture->linesize[0] = c->width;
    picture->linesize[1] = c->width/2;
    picture->linesize[2] = c->width/2;

}

void yuv422p_encode_image(uint8_t* data)
{
    fflush(stdout);

	#if defined(__linux__)
    for(i=0;i<size/2;i++)
    {
		picture->data[0][i*2] = data[i*4+1];
		picture->data[0][i*2+1] = data[i*4+3];
		picture->data[1][i] = data[i*4+0];
		picture->data[2][i] = data[i*4+2];
    }
	#elif defined(__APPLE__2)
    for(i=0;i<size/2;i++)
    {
		picture->data[0][i*2] = data[i*4+0];
		picture->data[0][i*2+1] = data[i*4+2];
		picture->data[1][i] = data[i*4+1];
		picture->data[2][i] = data[i*4+3];
    }
	#elif defined(__APPLE__)
    for(i=0;i<size;i++)
    {
		picture->data[0][i] = data[i*2+0];
    }
    for(i=0;i<c->height*1;i=i+2)
    {
		for(j=0;j<c->width/1;j=j+1)
		{
			picture->data[1][i/2*c->width+j] = data[(i*c->width+j)*4+1];
			picture->data[2][i/2*c->width+j] = data[(i*c->width+j)*4+3];
		}
    }
	#endif
	
    //picture->data[0]=data;

    /* encode the image */
    out_size = avcodec_encode_video(c, video_outbuf, video_outbuf_size, picture);
    printf("encoding frame %3d (size=%5d)\n", k, out_size);
    fwrite(video_outbuf, 1, out_size, f);

    k++;
    if (k>25)
	k=0;
}

void yuv422_encode_start(void)
{
    k=0;
    printf("Video encoding\n");
    const char *filename = "/tmp/test.mpg";
	
    /* must be called before using avcodec lib */
    avcodec_init();
	
    /* register all the codecs */
    avcodec_register_all();
	
    // Find de mpeg1 vido encoder
    codec = avcodec_find_encoder(CODEC_ID_MPEG2VIDEO);
    //codec = avcodec_find_encoder(CODEC_ID_H264);
    //codec = avcodec_find_encoder(CODEC_ID_MPEG4);
    if (!codec) {
		fprintf(stderr, "codec not found\n");
		exit(1);
    }
	
    c = avcodec_alloc_context();
    picture = avcodec_alloc_frame();
	
    /* put sample parameters */
    c->bit_rate = 3000000;
    /* resolution must be a multiple of two */
    c->width = 640;
    c->height = 480;
#if defined(__linux__)
    /* frames per second */
    //c->time_base= (AVRational){1,25};
	//c->time_base.den=25;
	//c->time_base.num=1;
#endif
	c->gop_size = 10; /* emit one intra frame every ten frames */
    c->max_b_frames=1;
    //c->pix_fmt = PIX_FMT_YUV422;
    c->pix_fmt = PIX_FMT_YUYV422;
    //c->pix_fmt = PIX_FMT_UYVY422;
	
    /* open it */
    if (avcodec_open(c, codec) < 0) {
        fprintf(stderr, "could not open codec\n");
        exit(1);
    }
	
    f = fopen(filename, "wb");
    if (!f) {
        fprintf(stderr, "could not open %s\n", filename);
        exit(1);
    }
	
    /* alloc image and output buffer */
    video_outbuf_size = 2000000;
    video_outbuf = (uint8_t*) malloc(video_outbuf_size);
    size = c->width * c->height;
    picture_buf = (uint8_t*) malloc((size * 2)); /* size for YUV 422 */
	
    picture->data[0] = picture_buf;
    picture->data[1] = picture->data[0] + size;
	picture->data[2] = picture->data[1] + size*1/2;
    picture->linesize[0] = c->width;
    picture->linesize[1] = c->width/2;
    picture->linesize[2] = c->width/2;
	
}

void yuv422_encode_image(uint8_t* data)
{
    fflush(stdout);
	
#if defined(__linux__)
    for(i=0;i<size/2;i++)
    {
		picture->data[0][i*2] = data[i*4+1];
		picture->data[0][i*2+1] = data[i*4+3];
		picture->data[1][i] = data[i*4+0];
		picture->data[2][i] = data[i*4+2];
    }
/*	
    for(i=0;i<size;i++)
    {
		picture->data[0][i] = data[i*2+0];
    }
	for(i=0;i<c->height*1;i=i+2)
    {
		for(j=0;j<c->width/1;j=j+1)
		{
			picture->data[1][i/2*c->width+j] = data[(i*c->width+j)*4+1];
			picture->data[2][i/2*c->width+j] = data[(i*c->width+j)*4+3];
		}
    }
*/
#elif defined(__APPLE__2)
    for(i=0;i<size/2;i++)
    {
		picture->data[0][i*2] = data[i*4+0];
		picture->data[0][i*2+1] = data[i*4+2];
		picture->data[1][i] = data[i*4+1];
		picture->data[2][i] = data[i*4+3];
    }
#elif defined(__APPLE__)
	//memcpy(picture->data[0], data, c->width*c->height*2);
/*
    for(i=0;i<size/2;i++)
    {
		picture->data[0][i*2+0] = data[i*4+0];
		picture->data[0][i*2+1] = data[i*4+2];
		picture->data[1][i] = data[i*4+1];
		picture->data[2][i] = data[i*4+3];
	}
*/
    for(i=0;i<size;i++)
    {
		picture->data[0][i] = data[i*2+0];
    }

	for(i=0;i<c->height*1;i=i+2)
	{
		for(j=0;j<c->width/1;j=j+2)
		{
			picture->data[1][i/2*c->width/2+j/2] = data[(i*c->width/2+j/2)*4+1];
			picture->data[2][i/2*c->width/2+j/2] = data[(i*c->width/2+j/2)*4+3];
		}
	 }

/*
	for(i=0;i<c->height*1;i=i+1)
    {
		for(j=0;j<c->width/1;j=j+2)
		{
			picture->data[1][i*c->width/2+j/2] = data[(i*c->width/2+j/2)*4+1];
			picture->data[2][i*c->width/2+j/2] = data[(i*c->width/2+j/2)*4+3];
		}
    }
*/
#endif
	
    //picture->data[0]=data;
	
    /* encode the image */
    out_size = avcodec_encode_video(c, video_outbuf, video_outbuf_size, picture);
    printf("encoding frame %3d (size=%5d)\n", k, out_size);
    fwrite(video_outbuf, 1, out_size, f);
	
    k++;
    if (k>25)
		k=0;
}

void video_encode_stop()
{
    int i;

    /* write the trailer, if any.  the trailer must be written
     * before you close the CodecContexts open when you wrote the
     * header; otherwise write_trailer may try to use memory that
     * was freed on av_codec_close() */
    av_write_trailer(oc);

    /* close each codec */
    if (video_st)
        close_video(oc, video_st);

    /* free the streams */
    for(i = 0; i < oc->nb_streams; i++) {
        av_freep(&oc->streams[i]->codec);
        av_freep(&oc->streams[i]);
    }

    if (!(oc->oformat->flags & AVFMT_NOFILE)) {
        // close the output file
        url_fclose(oc->pb);
    }

    // free the stream
    av_free(oc);

    printf("\n");
}


