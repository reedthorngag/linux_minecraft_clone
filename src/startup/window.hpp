#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/extensions/xfixesproto.h>
#include <GL/glew.h>
#include <GL/glx.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>
#include <unistd.h>

#include "../util/shader_loader.hpp"
#include "../globals.hpp"

#ifndef _WINDOW_SETUP
#define _WINDOW_SETUP

extern Display                 *dpy;
extern Window                  root;
extern GLint                   att[];
extern XVisualInfo             *vi;
extern Colormap                cmap;
extern XSetWindowAttributes    swa;
extern Window                  win;
extern GLXContext              glc;
extern XWindowAttributes       gwa;
extern XEvent                  xev;

const long mask = KeyPressMask
        | KeyReleaseMask
        | ButtonPressMask
        | ButtonReleaseMask
        | PointerMotionMask;

void createWindow();

#endif
