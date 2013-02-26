/*
 *  GLXRenderWindow.cpp
 *
 *  Created by Rob Rau on 2/20/13.
 *  Copyright 2013 Rob Rau. All rights reserved.
 *
 */
#include <stdlib.h>

#include "GLXRenderWindow.h"
#include "InputHandler.h"

GLXRenderWindow::GLXRenderWindow()
{
	mInputHandler = 0;
}

void GLXRenderWindow::setInputHandler(InputHandler* inputHandler)
{
	mInputHandler = inputHandler;
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
	mSetWinAttrib.event_mask = ExposureMask | KeyPressMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask;

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
		if(XPending(mDisplay))
			XNextEvent(mDisplay, &mXEvent);
		
		XGetWindowAttributes(mDisplay, mWindow, &mWindowAttrib);
		render();
		glXSwapBuffers(mDisplay, mWindow);

		if(mXEvent.type == KeyPress)
		{
			cout << "Exiting " << mXEvent.type << endl;
			glXMakeCurrent(mDisplay, None, NULL);
			glXDestroyContext(mDisplay, mGLXContext);
			XDestroyWindow(mDisplay, mWindow);
			XCloseDisplay(mDisplay);
	   		exit(0);
		}
		else if(mXEvent.type == MotionNotify)
		{
			if(mInputHandler)
				mInputHandler->mouseMoved(mXEvent.xmotion.x, mXEvent.xmotion.y);
		}
		else if(mXEvent.type == ButtonPress)
		{
			//std::cout << "Button Press" << mXEvent.type << std::endl;
			if(mInputHandler)
				mInputHandler->mouseDown(InputHandler::LEFT_MOUSE_BUTTON, mXEvent.xbutton.x, mXEvent.xbutton.y);
		}
		else if(mXEvent.type == ButtonRelease)
		{
			//std::cout << "Button Released" << std::endl;
			if(mInputHandler)
				mInputHandler->mouseUp(InputHandler::LEFT_MOUSE_BUTTON, mXEvent.xbutton.x, mXEvent.xbutton.y);
		}
	}
}
