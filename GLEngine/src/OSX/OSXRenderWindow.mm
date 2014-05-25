//
//  OSXRenderWindow.mm
//  QtGLEngine
//
//  Created by Rob Rau on 12/14/10.
//  Copyright 2010 Robert F. Rau II. All rights reserved.
//
#include "Cocoa/Cocoa.h"
#include "OpenGLView.h"
#include "OSXRenderWindow.h"



static GLfloat lightPosition[4] = { 0.0, 0.0, 15.0, 1.0 };
static GLfloat lightDiffuse[4] = {2, 2, 2, 1};
static GLfloat lightSpecular[4] = {-.2, -.2, -.2, 1};
static GLfloat lightAmbient[4] = {-.5, -.5, -.5, 1};

static GLfloat lightPosition2[4] = { -15.0, 0.0, 0.0, 1.0 };
static GLfloat lightDiffuse2[4] = {2, 2, 2, 1};
static GLfloat lightSpecular2[4] = {-.2, -.2, -.2, 1};
static GLfloat lightAmbient2[4] = {-.2, -.2, -.2, 1};

OSXRenderWindow::OSXRenderWindow()
{
	int retVal;
	mPool = [[NSAutoreleasePool alloc] init];
	
	retVal = NSApplicationLoad();
	
	setupRenderWindow();
	
	mTimer = [NSTimer timerWithTimeInterval:(0.0f) target:(OpenGLView*)mView 
								  selector:@selector(drawRect:) userInfo:nil repeats:YES];
	[[NSRunLoop currentRunLoop]addTimer:(NSTimer*)mTimer forMode:NSDefaultRunLoopMode];
	[[NSRunLoop currentRunLoop]addTimer:(NSTimer*)mTimer forMode:NSEventTrackingRunLoopMode];


	mObjects = 0;
	mNumObjects = 0;
}

OSXRenderWindow::OSXRenderWindow(string _name, int _w, int _h, bool _fullScreen)
{
	mName =			_name;
	mWidth =		_w;
	mHeight =		_h;
	mFullScreen =	_fullScreen;
	
	int retVal;
	mPool = [[NSAutoreleasePool alloc] init];
	
	retVal = NSApplicationLoad();
	
	setupRenderWindow();
	
	mTimer = [NSTimer timerWithTimeInterval:(0.01f) target:(OpenGLView*)mView 
								  selector:@selector(drawRect:) userInfo:nil repeats:YES];
	[[NSRunLoop currentRunLoop]addTimer:(NSTimer*)mTimer forMode:NSDefaultRunLoopMode];
	[[NSRunLoop currentRunLoop]addTimer:(NSTimer*)mTimer forMode:NSEventTrackingRunLoopMode];
	
		
	mObjects = 0;
	mNumObjects = 0;
}

OSXRenderWindow::~OSXRenderWindow()
{
	[(NSAutoreleasePool*)mPool release];
}

void OSXRenderWindow::_start()
{
	[NSApp run];
}

void OSXRenderWindow::update()
{
	render();
	[(NSOpenGLContext*)mGLContext flushBuffer];
}

void OSXRenderWindow::setupRenderWindow()
{	
	NSOpenGLPixelFormat* openglFormat = nil;
	NSOpenGLPixelFormatAttribute attribs[30];
	int i = 0;
	
	// Specifying "NoRecovery" gives us a context that cannot fall back to the software renderer.  This makes the mView-based context a compatible with the mFullScreen context, enabling us to use the "shareContext" feature to share textures, display lists, and other OpenGL objects between the two.
	attribs[i++] = NSOpenGLPFAOpenGLProfile;
	attribs[i++] = NSOpenGLProfileVersion3_2Core;
	
	attribs[i++] = NSOpenGLPFANoRecovery;
	
	attribs[i++] = NSOpenGLPFAAccelerated;
	attribs[i++] = NSOpenGLPFADoubleBuffer;
	
	attribs[i++] = NSOpenGLPFAAlphaSize;
	attribs[i++] = (NSOpenGLPixelFormatAttribute) 8;
	
	attribs[i++] = NSOpenGLPFAStencilSize;
	attribs[i++] = (NSOpenGLPixelFormatAttribute) 8;
	
	attribs[i++] = NSOpenGLPFAAccumSize;
	attribs[i++] = (NSOpenGLPixelFormatAttribute) 0;
	
	attribs[i++] = NSOpenGLPFADepthSize;
	attribs[i++] = (NSOpenGLPixelFormatAttribute) 32;
	
	attribs[i++] = (NSOpenGLPixelFormatAttribute) 0;
	
	//attribs[i++] = NSOpenGLPFAMultisample;
	attribs[i++] = NSOpenGLPFASupersample;
	
	attribs[i++] = NSOpenGLPFASampleBuffers;
	attribs[i++] = (NSOpenGLPixelFormatAttribute) 1;
	
	attribs[i++] = NSOpenGLPFASamples;
	attribs[i++] = (NSOpenGLPixelFormatAttribute) 8;
	
	openglFormat = [[[NSOpenGLPixelFormat alloc] initWithAttributes: attribs] autorelease];
	
	mGLContext = [[NSOpenGLContext alloc] initWithFormat:openglFormat shareContext:NULL];


	NSRect frame = NSMakeRect(0, 0, mWidth, mHeight);
	mRenderWindow = [[NSWindow alloc] initWithContentRect:frame
											    styleMask:NSTitledWindowMask | NSResizableWindowMask
												  backing:NSBackingStoreBuffered 
												    defer:NO];
	
	[(NSWindow*)mRenderWindow setAcceptsMouseMovedEvents:YES];
	
	static NSOpenGLPixelFormatAttribute	attributes[] =	// OpenGL context attributes
	{
		NSOpenGLPFAWindow,
		NSOpenGLPFADoubleBuffer,
		NSOpenGLPFADepthSize, (NSOpenGLPixelFormatAttribute)16,
		(NSOpenGLPixelFormatAttribute)nil
	};
	
	mView = [[OpenGLView alloc] initWithOSXWindow:this];
	
	[[(NSWindow*)mRenderWindow contentView] addSubview:(OpenGLView*)mView];
	[(NSWindow*)mRenderWindow setContentView:(OpenGLView*)mView];
	[(NSWindow*)mRenderWindow makeFirstResponder:(OpenGLView*)mView];
	
	[(NSOpenGLContext*)mGLContext setView:(OpenGLView*)mView];
	[(NSOpenGLContext*)mGLContext makeCurrentContext];
	
	//[mRenderWindow setTitle:[[NSString alloc] stringWithUTF8String: mName.c_str()]];
	
	[(NSWindow*)mRenderWindow makeKeyAndOrderFront:nil];
	
	setupOpenGL();
	
	//[mView drawRect:NSMakeRect(0, 0, 200, 200)];
}

void OSXRenderWindow::setInputHandler(InputHandler *inputHandler)
{
	[(OpenGLView*)mView setInputHandler:inputHandler];
}