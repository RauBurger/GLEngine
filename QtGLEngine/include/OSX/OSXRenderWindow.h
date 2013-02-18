/*
 *  OSXRenderWindow.h
 *  QtGLEngine
 *
 *  Created by Rob Rau on 12/14/10.
 *  Copyright 2010 Robert F. Rau II. All rights reserved.
 *
 */
#ifndef OSXRENDERWINDOW_H_
#define OSXRENDERWINDOW_H_
//#include "Cocoa/Cocoa.h"

#include "RenderWindow.h"
//#include <string>
//#include <NSTimer>
//#import <Cocoa/NSTimer.h>
//#include <Foundation/NSTimer.h>

//#ifdef __cplusplus
//class NSTimer;
//class NSWindow;
//class NSOpenGLContext;
//class NSView;
//class NSOpenGLView;
//class OpenGLView;
//class NSAutoreleasePool;
//#endif
using namespace std;

class OSXRenderWindow : public RenderWindow
{
public:
	OSXRenderWindow();
	OSXRenderWindow(string _name, int _w, int _h, bool _fullScreen);
	~OSXRenderWindow();
	
	void setInputHandler(InputHandler* inputHandler);
	
	void update();
	
	void _start();
	
private:
	void setupRenderWindow();
	
    bool				mInitialized;
    void*				mTimer;
	void*				mRenderWindow;
	//NSOpenGLContext*	mGLContext;
	void*				mGLContext;
	//OpenGLView*			mView;
	void*				mView;
	
	//NSAutoreleasePool * mPool;
	void*				mPool;
};


#endif //OSXRENDERWINDOW_H_