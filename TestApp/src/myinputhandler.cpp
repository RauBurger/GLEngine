//
//  myinputhandler.cpp
//  QtGLEngine
//
//  Created by Rob Rau on 6/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

//#include <iostream>
#include "myinputhandler.h"
#include "Node.h"
#include "Matrix3.h"

MyInputHandler::MyInputHandler()
{
	mRightMouseDown = false;
	mLeftMouseDown = false;
	mWDown = false;
	mADown = false;
	mSDown = false;
	mDDown = false;
	mQDown = false;
	mEDown = false;
}

MyInputHandler::~MyInputHandler()
{
	
}

void MyInputHandler::keyDown(KeyCode key)
{
	switch (key)
	{
		case InputHandler::KEY_w:
		case InputHandler::KEY_W:
			mWDown = true;
			break;
			
		case InputHandler::KEY_a:
		case InputHandler::KEY_A:
			mADown = true;
			break;
			
		case InputHandler::KEY_s:
		case InputHandler::KEY_S:
			mSDown = true;
			break;
			
		case InputHandler::KEY_d:
		case InputHandler::KEY_D:
			mDDown = true;
			break;
			
		case InputHandler::KEY_q:
		case InputHandler::KEY_Q:
			mQDown = true;
			break;
			
		case InputHandler::KEY_e:
		case InputHandler::KEY_E:
			mEDown = true;
			break;
			
		default:
			break;
	}
}

void MyInputHandler::keyUp(KeyCode key)
{
	switch (key)
	{
		case InputHandler::KEY_w:
		case InputHandler::KEY_W:
			mWDown = false;
			break;
			
		case InputHandler::KEY_a:
		case InputHandler::KEY_A:
			mADown = false;
			break;
			
		case InputHandler::KEY_s:
		case InputHandler::KEY_S:
			mSDown = false;
			break;
			
		case InputHandler::KEY_d:
		case InputHandler::KEY_D:
			mDDown = false;
			break;
			
		case InputHandler::KEY_q:
		case InputHandler::KEY_Q:
			mQDown = false;
			break;
			
		case InputHandler::KEY_e:
		case InputHandler::KEY_E:
			mEDown = false;
			break;
			
		default:
			break;
	}	
}

void MyInputHandler::mouseDown(MouseButton button, float x, float y)
{
	if(button == LEFT_MOUSE_BUTTON)
		mLeftMouseDown = true;
	else if(button == RIGHT_MOUSE_BUTTON)
		mRightMouseDown = true;
}

void MyInputHandler::mouseUp(MouseButton button, float x, float y)
{
	if(button == LEFT_MOUSE_BUTTON)
		mLeftMouseDown = false;
	else if(button == RIGHT_MOUSE_BUTTON)
		mRightMouseDown = false;
}

void MyInputHandler::mouseMoved(float xMag, float yMag)
{
	if(mLeftMouseDown)
	{
		mCamNodePitch->rotateNodeLocal(2.0f*yMag, 1.0f, 0.0f, 0.0f);
		mCamNodeRot->rotateNodeLocal(2.0f*xMag, 0.0f, 1.0f, 0.0f);
	}
}

void MyInputHandler::scrollWheel(float delta)
{
	
}

void MyInputHandler::setCamNodes(Node* camPitchNode, Node* camRotNode)
{
	mCamNodePitch = camPitchNode;
	mCamNodeRot = camRotNode;
}

void MyInputHandler::FrameStart()
{
	if(mDDown)
		//mCamNodePitch->translateNodeLocal(5.0f, 0.0f, 0.0f);
		mCamNodeRot->translateNodeLocal(5.0f, 0.0f, 0.0f);
	if(mWDown)
		//mCamNodePitch->translateNodeLocal(0.0f, 0.0f, -5.0f);
		mCamNodeRot->translateNodeLocal(0.0f, 0.0f, -5.0f);
	if(mADown)
		//mCamNodePitch->translateNodeLocal(-5.0f, 0.0f, 0.0f);
		mCamNodeRot->translateNodeLocal(-5.0f, 0.0f, 0.0f);
	if(mSDown)
		//mCamNodePitch->translateNodeLocal(0.0f, 0.0f, 5.0f);
		mCamNodeRot->translateNodeLocal(0.0f, 0.0f, 5.0f);
	if(mQDown)
		//mCamNodePitch->translateNodeLocal(0.0f, 5.0f, 0.0f);
		mCamNodeRot->translateNodeLocal(0.0f, 5.0f, 0.0f);
	if(mEDown)
		//mCamNodePitch->translateNodeLocal(0.0f, -5.0f, 0.0f);
		mCamNodeRot->translateNodeLocal(0.0f, -5.0f, 0.0f);
}

void MyInputHandler::FrameFinished()
{
	
}