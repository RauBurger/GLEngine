//
//  app.cpp
//  QtGLEngine
//
//  Created by Rob Rau on 6/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#ifdef __APPLE__
#include "mach-o/dyld.h"
#endif
#include "app.h"
#include "Core.h"
#include "SceneTree.h"
#include "Node.h"
#include "myinputhandler.h"

App::App(int argc, char** argv)
{
	mArgc = argc;
	mArgv = argv;
	
#ifdef __APPLE__
	char buf[256];
	uint32_t bufSize = sizeof(buf);
	_NSGetExecutablePath(buf, &bufSize);
	std::cout << buf << std::endl;
#endif
	
	mCore = new Core();
	mInputHandler = new MyInputHandler;
	mSceneTree = 0;
	mCamera = 0;
	mMainNode = 0;
	mCamPitchNode = 0;
	mCamRotNode = 0;
}

void App::init()
{
	mCore->createRenderWindow("Test App", 1280.0f, 720.0f, false);
	mInputHandler->setWidth(1280);
	mInputHandler->setHeight(720);
	mSceneTree = mCore->createSceneTree();
	mCamera = mCore->createCamera();
	
	/*mMainNode = mSceneTree->createNode("MainNode");
	mCamPitchNode = mSceneTree->createNode("CamPitchNode");
	mCamRotNode = mSceneTree->createNode("CamRotNode");*/
	mMainNode = mSceneTree->getRootNode();
	mCamRotNode = mSceneTree->getRootNode()->createNode("CamRotNode");
	mCamPitchNode = mCamRotNode->createNode("CamPitchNode");

	cout << "Mid init" << endl;

	Object* obj = new Object();
	//obj->setupShaders();
	obj->loadModelPly();
	cout << "Passed loadModelPly" << endl;
	obj->setupShaders();

	mSceneTree->getRootNode()->attachObject(obj);
	//mMainNode->rotateNodeLocal(-3.141592f/2.0f, 1, 0, 0);
	
	mCore->registerObject("TestObject", obj);
	mCamPitchNode->attachCamera(mCamera);
	//mCamNode->translateNodeLocal(0.0f, 0.0f, -55.0f);
	mCamera->translate(0.0f, 0.0f, 55.0f);
	//mCamera->translate(-55.0f, 0.0f, 0.0f);
	//mCamPitchNode->rotateNodeLocal(-3.141592f/2.0f, 0.0f, 1.0f, 0.0f);
	//mCamRotNode->attachObject(mCamPitchNode);
	//mMainNode->attachObject(mCamRotNode);
	
	mInputHandler->setCamNodes(mCamPitchNode, mCamRotNode);
	mCore->setInputHandler((InputHandler*)mInputHandler);
	mCore->setEventListener((EventListener*)mInputHandler);
	cout << "End init" << endl;
}

int App::Run()
{
	mCore->startRendering();
	return 0;
}
