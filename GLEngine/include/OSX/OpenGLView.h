/*
 *  OpenGLView.h
 *  QtGLEngine
 *
 *  Created by Rob Rau on 12/14/10.
 *  Copyright 2010 Robert F. Rau II. All rights reserved.
 *
 */

#ifndef OPENGLVIEW_H_
#define OPENGLVIEW_H_


//#include "OSXRenderWindow.h"
class InputHandler;
class OSXRenderWindow;

@interface OpenGLView : NSView
{
	OSXRenderWindow* mWindow;
	InputHandler* mInputHandler;
}

- (id)initWithFrame:(NSRect)frame;
- (id)initWithOSXWindow:(OSXRenderWindow*)win;

- (void)keyDown:(NSEvent *)theEvent;
- (void)keyUp:(NSEvent *)theEvent;

- (void)mouseDown:(NSEvent *)theEvent;
- (void)mouseUp:(NSEvent *)theEvent;

- (void)rightMouseDown:(NSEvent *)theEvent;
- (void)rightMouseUp:(NSEvent *)theEvent;

- (void)middleMouseDown:(NSEvent *)theEvent;
- (void)middleMouseUp:(NSEvent *)theEvent;

- (void)mouseDragged:(NSEvent *)theEvent;
- (void)mouseMoved:(NSEvent *)theEvent;

- (void)scrollWheel:(NSEvent *)theEvent;

- (void)setInputHandler:(InputHandler*) input;


@end

#endif //OPENGLVIEW_H_