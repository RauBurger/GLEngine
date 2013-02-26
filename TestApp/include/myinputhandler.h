//
//  myinputhandler.h
//  QtGLEngine
//
//  Created by Rob Rau on 6/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef QtGLEngine_myinputhandler_h
#define QtGLEngine_myinputhandler_h

#include "InputHandler.h"
#include "EventListener.h"

class Node;

class MyInputHandler : InputHandler, EventListener
{
public:
	MyInputHandler();
	~MyInputHandler();
	
	void setWidth(int width);
	void setHeight(int height);
	virtual void keyDown(KeyCode key);
	virtual void keyUp(KeyCode key);
	virtual void mouseDown(MouseButton button, float x, float y);
	virtual void mouseUp(MouseButton button, float x, float y);
	virtual void mouseMoved(float posx, float posy);
	virtual void scrollWheel(float delta);
	
	virtual void FrameStart();
	virtual void FrameFinished();
	
	void setCamNodes(Node* camPitchNode,Node* camRotNode);
	
private:
	bool mRightMouseDown;
	bool mLeftMouseDown;
	bool mWDown;
	bool mADown;
	bool mSDown;
	bool mDDown;
	bool mQDown;
	bool mEDown;
	
	int mWidth;
	int mHeight;
	
	float mMousePressPos[2];
	
	Node* mCamNodePitch;
	Node* mCamNodeRot;
};

#endif
