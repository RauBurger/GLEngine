//
//  Frustrum.h
//  QtGLEngine
//
//  Created by Rob Rau on 3/3/12.
//  Copyright (c) 2012 Robert F. Rau II. All rights reserved.
//

#ifndef QtGLEngine_Frustrum_h
#define QtGLEngine_Frustrum_h

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
#else
#include <windows.h>
#include "gl/glew.h"
#include "gl/gl.h"
#include "gl/glu.h"
#endif

#include "Matrix4.h"

class Frustrum
{
public:
	Frustrum(float fovY, float aspect, float clipNear, float clipFar);
	~Frustrum();
	
	
	void setPerspective(float fovY, float aspect, float clipNear, float clipFar);
	
	Matrix4* getProjectionMatrix();
	
	
private:
	
	Matrix4 mProjectionMatrix;
	
	GLfloat mFovY;
	GLfloat mAspectRatio;
	GLfloat mClipNear, mClipFar;
	
	
};

#endif
