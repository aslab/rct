#include "initGL.h"

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
void InitGL(int Width, int Height)              // We call this right after our OpenGL window is created.
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);         // This Will Clear The Background Color To Black
  glClearDepth(1.0);                            // Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);                         // The Type Of Depth Test To Do
  //glEnable(GL_DEPTH_TEST);                      // Enables Depth Testing
  glShadeModel(GL_SMOOTH);                      // Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();                             // Reset The Projection Matrix

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);     // Calculate The Aspect Ratio Of The Window

  glMatrixMode(GL_MODELVIEW);

#if defined (__APPLE__)
  printf("APPLE optimized\n");

  // Initialize texture
  glEnable(GL_TEXTURE_RECTANGLE_ARB);
  //glEnable(GL_TEXTURE_2D);

  glGenTextures(2, texture);
  glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture[0]);

  glTextureRangeAPPLE(GL_TEXTURE_RECTANGLE_ARB, videoImageWidth * videoImageHeight * 2, videoTexture);
  //glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_STORAGE_HINT_APPLE , GL_STORAGE_SHARED_APPLE);
  glPixelStorei(GL_UNPACK_CLIENT_STORAGE_APPLE, GL_TRUE);

  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

  glTexImage2D(GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGB, device_width,
        device_height, 0, GL_YCBCR_422_APPLE, GL_UNSIGNED_SHORT_8_8_REV_APPLE, videoTexture);

#elif !defined (TEXTURE2D)
  printf("No APPLE optimized RECTANGLE_ARB\n");

  // Initialize texture
  glEnable(GL_TEXTURE_RECTANGLE_ARB);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glGenTextures(2, texture);
  glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture[0]);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

// don't use mipmapping (since we're not creating any mipmaps); the default
// minification filter uses mipmapping.  Use linear filtering for minification
// and magnification.
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_RECTANGLE_ARB, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D (GL_TEXTURE_RECTANGLE_ARB, 0, GL_RGBA, device_width, 
	device_height, 0, GL_RGB, GL_UNSIGNED_BYTE, videoTexture);
#else
  printf("No APPLE optimized TEXTURE_2D\n");

  // Initialize texture
  glEnable(GL_TEXTURE_2D);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glGenTextures(2, texture);
  glBindTexture(GL_TEXTURE_2D, texture[0]);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

// don't use mipmapping (since we're not creating any mipmaps); the default
// minification filter uses mipmapping.  Use linear filtering for minification
// and magnification.
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, device_width, 
	device_height, 0, GL_RGB, GL_UNSIGNED_BYTE, videoTexture);
#endif
  //glEnable(GL_TEXTURE_2D);

}

