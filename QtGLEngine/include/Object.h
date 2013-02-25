/*
 *  Object.h
 *  QtGLEngine
 *
 *  Created by Rob Rau on 12/14/10.
 *  Copyright 2010 Robert F. Rau II. All rights reserved.
 *
 */
#ifndef OBJECT_H
#define OBJECT_H

#ifndef GL3_PROTOTYPES
	#define GL3_PROTOTYPES 1
#endif

#ifndef GL_GLEXT_PROTOTYPES
# define GL_GLEXT_PROTOTYPES 1
#endif

#ifndef kCGLOGLPVersion_3_2_Core
	#define kCGLOGLPVersion_3_2_Core 1
#endif

#ifdef __APPLE__
# include <OpenGL/gl3.h>
# include <OpenGL/gl3ext.h>
//#include "OpenGL/glu.h"
#elif __linux__
# include <GL/gl.h>
# include <GL/glx.h>
# include <GL/glext.h>
#elif __WIN32__
# include <windows.h>
# include "gl/glew.h"
# include "gl/gl.h"
# include "gl/glu.h"
#endif

#include "Matrix4.h"
#include "Matrix3.h"
#include <string>
//#include "SceneTree.h"
class Node;

class Object
{
public:
	Object();
	~Object();

	virtual void loadModel();
	void loadModelx3d();
	void loadModelPly();
	//virtual void draw(Matrix4* viewMat);
	virtual void draw(Matrix4* viewMat, Matrix4* projMat);
	
	void setProgram(GLuint i);
	void setupShaders();
protected:
	friend class Node;
	
	
	std::string readShaderFile(std::string fileName);
	
	void setParentNode(Node* node);
	//void setWorldViewMatrixPtr(Matrix4* viewMat);
	Matrix4* mWorldViewMatrixPtr;
	Matrix4 mModelMat;
	Matrix3 mNormalMat;
	Node* mParentNode;
	
	GLfloat* mVerticies;
	GLfloat* mNormals;
	GLuint* mIndicies;
	
	GLuint ids[3];
	GLuint mVertArrayObj;
	
	GLuint p;
	
	GLuint mVpLight1;
	GLuint mVpLight2;
	
	GLuint mNumLights;
	GLuint mFpNumLights;
	GLuint mFpLightNum;
	
	GLuint mMVPMptr;
	GLuint mNMptr;
	GLuint mMVMptr;
	GLuint mMMat;
	
	GLuint mLight1Ptr;
	GLuint mWorldRotPtr;
	GLuint mWMatrixPtr;
	GLuint mCamPosPtr;
	GLuint mMVMatPtr;
	
	int mNumVerts;
	int mNumNormals;
	int mNumFaces;
};

#endif // OBJECT_H
