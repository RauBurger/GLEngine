//
//  app.h
//  QtGLEngine
//
//  Created by Rob Rau on 6/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef QtGLEngine_app_h
#define QtGLEngine_app_h

class Core;
class SceneTree;
class Node;
class Camera;
class MyInputHandler;

class App
{
public:
	App(int argc, char** argv);
	
	void init();
	
	int Run();
	
private:
	int mArgc;
	char** mArgv;
	
	Camera* mCamera;
	SceneTree* mSceneTree;
	Node* mMainNode;
	Node* mCamPitchNode;
	Node* mCamRotNode;
	Core* mCore;
	MyInputHandler* mInputHandler;
};

#endif