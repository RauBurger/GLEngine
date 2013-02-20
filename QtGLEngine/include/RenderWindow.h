/*
 *  RenderWindow.h
 *  QtGLEngine
 *
 *  Created by Rob Rau on 12/14/10.
 *  Copyright 2010 Robert F. Rau II. All rights reserved.
 *
 */
#ifndef RENDERWINDOW_H_
#define RENDERWINDOW_H_

#ifndef GL3_PROTOTYPES
	#define GL3_PROTOTYPES 1
#endif
#ifndef kCGLOGLPVersion_3_2_Core
	#define kCGLOGLPVersion_3_2_Core 1
#endif

#ifdef __APPLE__
#include "OpenGL/gl3.h"
#include <OpenGL/gl3ext.h>
//#include "OpenGL/glu.h"
#elif __linux
# include "GL/gl.h"
# include "GL/glx.h"
# include "GL/glext.h"
#elif __WIN32__
# include <windows.h>
# include "gl/glew.h"
# include "gl/gl.h"
# include "gl/glu.h"
#endif

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <math.h>
#include "Object.h"
#include "Camera.h"
#include "EventListener.h"
#include "Frustrum.h"

using namespace std;

class Matrix4;
class InputHandler;

class RenderWindow
{
public:
	RenderWindow();
	RenderWindow(string _name, int _w, int _h, bool _fullScreen);
	~RenderWindow();
	
	virtual void setupOpenGL();
	
	void setWindow(int _w, int _h);
	void setWidth(int _w);
	void setHeight(int _h);
	
	void setWindowPosition(int _x, int _y);
	void setWindowX(int _x);
	void setWindowY(int _y);
	
	void getWindow(int* _w, int* _h);
	int getWidth();
	int getHeight();
	
	void getWindowPosition(int* _x, int* _y);
	int getWindowX();
	int getWindowY();
	
	Camera* createCamera();
	
	//not recomended for outside use
	virtual void _start() {}
	virtual Object* _newObject(string _name);
	virtual void _registerObject(string _name, Object* obj);
	virtual Object* _getObject(string _name);
	virtual void _registerListener(EventListener* _listener);
	//virtual SceneTree* _createSceneTree();
	//virtual Light* _newLight() {}
	virtual void _setWorldViewMatrixPtr(Matrix4* viewMatPtr);
	virtual void _setSceneTree(SceneTree* sceneTree);
	
	virtual void setInputHandler(InputHandler* inputHandler) = 0;
	virtual void setEventListener(EventListener* eventListener);
	
	void getGlError(std::string errTxt);
	
	GLuint getProgram();

private:
	
protected:
	//======Window Properties======//
	int mWidth;
	int mHeight;
	
	int mX;
	int mY;
	
	bool mFullScreen;
	
	string mName;
	
	//======Renderables=======//
	int mNumObjects;
	map<string, int> mObjectNames;
	Object** mObjects;
	//Light** lights;
	Camera* mCamera;
	
	//======Rendering======//
	void render();
	//======shaders======//
	GLuint mShaderProgram;
	
	void setupShaders();
	string readShaderFile(string fileName);
	
	//======utilities======//
	EventListener* mFrameListener;
	Matrix4* mWorldViewMatrix;
	SceneTree* mSceneTree;
	Frustrum* mFrustrum;
	
};

#endif //RENDERWINDOW_H_
