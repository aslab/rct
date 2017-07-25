#ifndef __initGL__H_
#define __initGL__H_

#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>      // Header File For The OpenGL32 Library
#include <GL/glu.h>     // Header File For The GLu32 Library
#include <GL/glext.h>     // Header File For The GLext Library

extern long device_width, device_height;
extern char *videoTexture;
extern GLuint texture[2];

void InitGL(int, int);

//define TEXTURE2D=1

#endif // __initGL__H_

