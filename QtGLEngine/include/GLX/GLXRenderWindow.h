#ifndef GLXRENDERWINDOW_H_
#define GLXRENDERWINDOW_H_
/*
 *  GLXRenderWindow.h
 *
 *  Created by Rob Rau on 2/19/13.
 *  Copyright 2013 Rob Rau. All rights reserved.
 *
 */

#include <X11/X.h>
#include <X11/Xlib.h>

#include "RenderWindow.h"

class GLXRenderWindow : public RenderWindow
{
public:
	GLXRenderWindow();
	GLXRenderWindow(string _name, int _w, int _h, bool _fullScreen);
	~GLXRenderWindow();

	void _start();

        void setInputHandler(InputHandler* inputHandler);
private:
	void setupRenderWindow();

	//=====Window Params=====//
	Display* mDisplay;
	Window mRoot;
	GLint mAttrib[5];
	XVisualInfo* mVisualInfo;
	Colormap mColorMap;
	XSetWindowAttributes mSetWinAttrib;
	Window mWindow;
	GLXContext mGLXContext;
	XWindowAttributes mWindowAttrib;
	XEvent mXEvent;
};

#endif //GLXRENDERWINDOW_H_
