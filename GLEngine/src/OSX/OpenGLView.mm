//
//  OpenGLView.m
//  QtGLEngine
//
//  Created by Rob Rau on 12/14/10.
//  Copyright 2010 Robert F. Rau II. All rights reserved.
//

#include "Cocoa/Cocoa.h"
#include "OpenGLView.h"
#include "OSXRenderWindow.h"
#include "InputHandler.h"
#include <iostream>

@implementation OpenGLView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
	{
		mInputHandler = 0;
		mWindow = 0;
    }
    return self;
}

-(id)initWithOSXWindow:(OSXRenderWindow*)win
{
	if((self = [super initWithFrame:NSMakeRect(win->getWindowX(), win->getWindowY(), win->getWidth(), win->getHeight())]))
    {
        mWindow = win;
		mInputHandler = 0;
    }
	return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
	if(mWindow)
		mWindow->update();
}

- (BOOL)acceptsFirstResponder
{
    return YES;
}

- (BOOL)canBecomeKeyView
{
    return YES;
}

- (void)keyDown:(NSEvent *)theEvent
{
	int keyCode = 0;
	NSString *theKey = [theEvent charactersIgnoringModifiers];
	keyCode = [theKey characterAtIndex:0];
	if(mInputHandler)
		mInputHandler->keyDown((InputHandler::KeyCode)keyCode);
}

- (void)keyUp:(NSEvent *)theEvent
{
	int keyCode = 0;
	NSString *theKey = [theEvent charactersIgnoringModifiers];
	keyCode = [theKey characterAtIndex:0];
	if(mInputHandler)
		mInputHandler->keyUp((InputHandler::KeyCode)keyCode);
}

- (void)mouseDown:(NSEvent *)theEvent
{
	NSPoint pos = [self convertPoint:[theEvent locationInWindow] fromView:nil];

	if(mInputHandler)
		mInputHandler->mouseDown(InputHandler::LEFT_MOUSE_BUTTON, pos.x, pos.y);
	
}

- (void)mouseUp:(NSEvent *)theEvent
{
	NSPoint pos = [self convertPoint:[theEvent locationInWindow] fromView:nil];
	if(mInputHandler)
		mInputHandler->mouseUp(InputHandler::LEFT_MOUSE_BUTTON, pos.x, pos.y);
}

- (void)mouseDragged:(NSEvent *)theEvent
{
	NSPoint pos = [self convertPoint:[theEvent locationInWindow] fromView:nil];
	
	if(mInputHandler)
		mInputHandler->mouseMoved(pos.x, pos.y);
}

- (void)mouseMoved:(NSEvent *)theEvent
{
	NSPoint pos = [self convertPoint:[theEvent locationInWindow] fromView:nil];
	
	if(mInputHandler)
		mInputHandler->mouseMoved(pos.x, pos.y);
}

- (void)rightMouseDown:(NSEvent *)theEvent
{
	NSPoint pos = [self convertPoint:[theEvent locationInWindow] fromView:nil];
	if(mInputHandler)
		mInputHandler->mouseDown(InputHandler::RIGHT_MOUSE_BUTTON, pos.x, pos.y);
}

- (void)rightMouseUp:(NSEvent *)theEvent
{
	NSPoint pos = [self convertPoint:[theEvent locationInWindow] fromView:nil];
	if(mInputHandler)
		mInputHandler->mouseUp(InputHandler::RIGHT_MOUSE_BUTTON, pos.x, pos.y);
}

- (void)middleMouseDown:(NSEvent *)theEvent
{
	NSPoint pos = [self convertPoint:[theEvent locationInWindow] fromView:nil];
	if(mInputHandler)
		mInputHandler->mouseDown(InputHandler::MIDDLE_MOUSE_BUTTON, pos.x, pos.y);
}

- (void)middleMouseUp:(NSEvent *)theEvent
{
	NSPoint pos = [self convertPoint:[theEvent locationInWindow] fromView:nil];
	if(mInputHandler)
		mInputHandler->mouseUp(InputHandler::MIDDLE_MOUSE_BUTTON, pos.x, pos.y);
}

- (void)scrollWheel:(NSEvent *)theEvent
{
	float scrollDelta = [theEvent scrollingDeltaY];
	if(mInputHandler)
		mInputHandler->scrollWheel(scrollDelta);
}

- (void)setInputHandler:(InputHandler *)input
{
	mInputHandler = input;
}

@end
