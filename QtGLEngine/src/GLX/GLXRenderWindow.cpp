/*
 *  GLXRenderWindow.cpp
 *
 *  Created by Rob Rau on 2/20/13.
 *  Copyright 2013 Rob Rau. All rights reserved.
 *
 */
#include <stdlib.h>

#include "GLXRenderWindow.h"


GLXRenderWindow::GLXRenderWindow()
{

}

GLXRenderWindow::GLXRenderWindow(string _name, int _w, int _h, bool _fullScreen)
{
	mName =			_name;
	mWidth =		_w;
	mHeight =		_h;
	mFullScreen =	_fullScreen;

	mAttrib[0] = GLX_RGBA;
	mAttrib[1] = GLX_DEPTH_SIZE;
	mAttrib[2] = 24;
	mAttrib[3] = GLX_DOUBLEBUFFER;
	mAttrib[4] = None;

	mDisplay = XOpenDisplay(NULL);

	if(mDisplay == NULL)
	{
		cout << "Cannot connect to XServer" << endl;
		exit(0);
	}

	mRoot = DefaultRootWindow(mDisplay);

	mVisualInfo = glXChooseVisual(mDisplay, 0, mAttrib);

	if(mVisualInfo == NULL)
	{
		cout << "No appropriate visual found." << endl;
		exit(0);
	}

	mColorMap = XCreateColormap(mDisplay, mRoot, mVisualInfo->visual, AllocNone);

	mSetWinAttrib.colormap = mColorMap;
	mSetWinAttrib.event_mask = ExposureMask | KeyPressMask;

	mWindow = XCreateWindow(mDisplay, mRoot, 0, 0, _w, _h, 0, mVisualInfo->depth, InputOutput, 
							mVisualInfo->visual, CWColormap | CWEventMask, &mSetWinAttrib);

	XMapWindow(mDisplay, mWindow);

	XStoreName(mDisplay, mWindow, _name.c_str());

	mGLXContext = glXCreateContext(mDisplay, mVisualInfo, NULL, GL_TRUE);
	glXMakeCurrent(mDisplay, mWindow, mGLXContext);

	setupOpenGL();
	cout << "Passed setupOpenGL()" << endl;
}

GLXRenderWindow::~GLXRenderWindow()
{

}

void GLXRenderWindow::_start()
{
	cout << "Start rendering" << endl;
	while(1)
	{
		XNextEvent(mDisplay, &mXEvent);
		
		cout << "Render loop " << mXEvent.type << endl;
		if(mXEvent.type == Expose)
		{
			cout << "Rendering" << endl;
			XGetWindowAttributes(mDisplay, mWindow, &mWindowAttrib);
			render();
			glXSwapBuffers(mDisplay, mWindow);
//			cout << "Rendering" << endl;
		}
		else if(mXEvent.type == KeyPress)
		{
			cout << "Exiting " << mXEvent.type << endl;
			glXMakeCurrent(mDisplay, None, NULL);
			glXDestroyContext(mDisplay, mGLXContext);
			XDestroyWindow(mDisplay, mWindow);
			XCloseDisplay(mDisplay);
			exit(0);
		}
	}
}

void GLXRenderWindow::setInputHandler(InputHandler* inputHandler)
{

}
