/*
 *  RenderWindow.cpp
 *  QtGLEngine
 *
 *  Created by Rob Rau on 12/14/10.
 *  Copyright 2010 Robert F. Rau II. All rights reserved.
 *
 */

#include "RenderWindow.h"

static GLfloat lightPosition[4] = { 30.0, 0.0, 0.0, 1.0 };
static GLfloat lightDiffuse[4] = {1, 1, 1, 1};
static GLfloat lightSpecular[4] = {-.7, -.7, -.7, 1};
static GLfloat lightAmbient[4] = {-.5, -.5, -.5, 1};

static GLfloat lightPosition2[4] = { -50.0, 0.0, -350.0, 1.0 };
static GLfloat lightDiffuse2[4] = {0, 0, 0, 1};
static GLfloat lightSpecular2[4] = {-.7, -.7, -.7, 1};
static GLfloat lightAmbient2[4] = {-.5, -.5, -.5, 1};



RenderWindow::RenderWindow()
{
	mObjects = NULL;
	mNumObjects = 0;
	mFrameListener = 0;
	mWorldViewMatrix = 0;
	mSceneTree = 0;
	mCamera = 0;
}

RenderWindow::~RenderWindow()
{

}

Object* RenderWindow::_newObject(string _name)
{
	if(mObjects != NULL)
	{
		Object** tmpObj;
		tmpObj = new Object*[mNumObjects + 1];
		for(int i = 0; i < mNumObjects; i++)
		{
			tmpObj[i] = mObjects[i];
		}
		mNumObjects++;
		delete [] mObjects;
		mObjects = tmpObj;
		mObjects[mNumObjects - 1] = new Object();
		mObjectNames[_name] = mNumObjects - 1;
		return mObjects[mNumObjects - 1];
	}
	else
	{
		mNumObjects++;
		mObjects = new Object*[mNumObjects];
		mObjects[mNumObjects - 1] = new Object();
		mObjectNames[_name] = mNumObjects - 1;
		return mObjects[mNumObjects - 1];
	}	
}

void RenderWindow::_registerObject(string _name, Object* obj)
{
	
	if(mObjects != NULL)
	{
		Object** tmpObj;
		tmpObj = new Object*[mNumObjects + 1];
		for(int i = 0; i < mNumObjects; i++)
		{
			tmpObj[i] = mObjects[i];
		}
		mNumObjects++;
		delete [] mObjects;
		mObjects = tmpObj;
		mObjects[mNumObjects - 1] = obj;
		mObjectNames[_name] = mNumObjects - 1;
	}
	else
	{
		mNumObjects++;
		mObjects = new Object*[mNumObjects];
		mObjects[mNumObjects - 1] = obj;
		mObjectNames[_name] = mNumObjects - 1;
	}
}

Object* RenderWindow::_getObject(string _name)
{
	return mObjects[mObjectNames[_name]];
}

void RenderWindow::_setWorldViewMatrixPtr(Matrix4 *viewMatPtr)
{
	mWorldViewMatrix = viewMatPtr;
}

void RenderWindow::_setSceneTree(SceneTree *sceneTree)
{
	mSceneTree = sceneTree;
}

Camera* RenderWindow::createCamera()
{
	mCamera = new Camera();
	return mCamera;
}

/*SceneTree* RenderWindow::_createSceneTree()
{
	mSceneTree = new SceneTree();
	mWorldViewMatrix = mSceneTree->_getWorldViewMatrixPtr();
	return mSceneTree;
}*/

void RenderWindow::setEventListener(EventListener *eventListener)
{
	mFrameListener = eventListener;
}

void RenderWindow::setupOpenGL()
{
	glEnable(GL_DEPTH_TEST);
	getGlError("RenderWindow::setupOpenGL() line:96, glEnable(GL_DEPTH_TEST);");
	glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CW);
	getGlError("RenderWindow::setupOpenGL() line:98, glEnable(GL_CULL_FACE);");
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_LINE_SMOOTH);

	//setupShaders();
	
	//mCamera.setPosition(30, -40, 0);
	//mCamera.setRotation(90, 0, 40);
	glViewport(0, 0, mWidth, mHeight);
	mFrustrum = new Frustrum(45, ((float)mWidth/(float)mHeight), 1.0, 1000.0);
	
	int vM, vMi;
	glGetIntegerv(GL_MAJOR_VERSION, &vM);
	glGetIntegerv(GL_MINOR_VERSION, &vMi);
	
	std::cout << "OpenGL version: " << vM << "." << vMi << std::endl;
	
	
}

void RenderWindow::render()
{
	if(mFrameListener)
		mFrameListener->FrameStart();

	if(mSceneTree)
		mSceneTree->update();
	
	static GLfloat xpos = 0;
	static int ypos = 0;
	static double cnt = 0;
	static double cnt2 = 0;
	
	GLfloat** lights = new GLfloat*[2];
	
	lights[0] = lightPosition;
	lights[1] = lightPosition2;
	
	/*GLuint vpLight1 = glGetUniformLocation(mShaderProgram, "light1");
	getGlError("RenderWindow::render() line:201, Uniform Error");
	GLuint vpLight2 = glGetUniformLocation(mShaderProgram, "light2");
	getGlError("RenderWindow::render() line:203, Uniform Error");
	
	GLuint numLights = glGetUniformLocation(mShaderProgram, "numLights");
	getGlError("RenderWindow::render() line:206, Uniform Error");
	GLuint fpNumLights = glGetUniformLocation(mShaderProgram, "fpNumLights");
	getGlError("RenderWindow::render() line:208, Uniform Error");
	GLuint fpLightNum = glGetUniformLocation(mShaderProgram, "numLight");
	getGlError("RenderWindow::render() line:210, Uniform Error");*/
	
	GLfloat fLargest;
	//xrot += .6;
	xpos = 4*sin((cnt += .05));
	ypos = 15*sin((cnt2 += .2));
	//std::cout << xpos << std::endl;
	//lightPosition[0] = xpos;
	//lightPosition2[0] = xpos;
	//lightPosition2[1] = ypos;
	//glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	//glLightfv(GL_LIGHT1, GL_POSITION, lightPosition2);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glClearColor(0, 0, 0, 1);
	
	//glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
	//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
	
	//cube->setRot(xrot, 0, 0);
	//glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glEnable(GL_DEPTH_TEST);
	
	for(int i = 0; i < 1; i++)
	{
		if(i == 0)
		{
			glDepthFunc(GL_LESS);
			//glBlendFunc(GL_ONE, GL_ONE);
		}
		else if(i == 1)
		{
			glEnable(GL_BLEND);
			glDepthFunc(GL_LEQUAL);
			glBlendFunc(GL_ONE, GL_ONE);
		}
		
		if(mCamera)
			mCamera->draw(mWorldViewMatrix);

		glUseProgram(mShaderProgram);

		/*if(mWorldViewMatrix)
		{
			(*mWorldViewMatrix)[14] = -55;
			//(*mWorldViewMatrix)[12] = -20;
		}*/
		for(int k = 0; k < mNumObjects; k++)
		{
			mObjects[k]->draw(mWorldViewMatrix, mFrustrum->getProjectionMatrix());
		}


	}
	
	//glPushMatrix();
	/*glBegin(GL_LINE_STRIP);
	//mX Axis
	glColor3f(1,0,0);
	glVertex3f(0,0,0);
	glVertex3f(70,0,0);
	
	//mY Axis
	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(0,70,0);
	
	//z Axis
	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,0,70);
	
	glEnd();
	//glPopMatrix();*/
	
	if(mFrameListener)
		mFrameListener->FrameFinished();
}


void RenderWindow::setupShaders()
{
	string fragSrc;
	string vertSrc;
	GLint testVal;

	GLuint v = glCreateShader(GL_VERTEX_SHADER);
	GLuint f = glCreateShader(GL_FRAGMENT_SHADER);
	
	vertSrc = readShaderFile("QtGLEngine.app/Contents/Resources/vertexMP.vs");
	fragSrc = readShaderFile("QtGLEngine.app/Contents/Resources/fragmentMP.fs");
	
	const char* vv = vertSrc.c_str();
	const char* ff = fragSrc.c_str();
	
	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);
	
	//free(vs);free(fs);
	glCompileShader(v);
	glCompileShader(f);
	
	glGetShaderiv(v, GL_COMPILE_STATUS, &testVal);
	if(testVal == GL_FALSE)
	{
		char infoLog[1024];
		glGetShaderInfoLog((GLint)v, 1024, NULL, infoLog);
		cout << "Vertex shader compile failed! Error: " << infoLog << endl;
	}
	
	glGetShaderiv(f, GL_COMPILE_STATUS, &testVal);
	if(testVal == GL_FALSE)
	{
		char infoLog[1024];
		glGetShaderInfoLog((GLint)f, 1024, NULL, infoLog);
		cout << "Fragment shader compile failed! Error: " << infoLog << endl;
	}
	
	mShaderProgram = glCreateProgram();
	
	glAttachShader(mShaderProgram, v);
	glAttachShader(mShaderProgram, f);
	
	glBindAttribLocation(mShaderProgram, 0, "vVert");
	getGlError("RenderWindow::setupShaders() line:333, glBindAttribLocation");
	
	//glBindAttribLocation(mShaderProgram, 2, "vNorm");
	//getGlError("RenderWindow::setupShaders() line:336, glBindAttribLocation");
	//glVertexAttribDivisorARB(2, 3);
	//getGlError("RenderWindow::setupShaders() line:336, glVertexAttribDivisorARB");
	
	glLinkProgram(mShaderProgram);
	
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &testVal);
    if(testVal == GL_FALSE)
	{
		char infoLog[2048];
		glGetProgramInfoLog(mShaderProgram, 2048, NULL, infoLog);
		getGlError("RenderWindow::setupShaders() line:342, glGetShaderInfoLog");
		cout << "Link failed! Error: " << infoLog << endl;
	}
	
	glValidateProgram(mShaderProgram);
	glGetProgramiv(mShaderProgram, GL_VALIDATE_STATUS, &testVal);
	if(testVal == GL_FALSE)
	{
		char infoLog[2048];
		glGetProgramInfoLog(mShaderProgram, 2048, NULL, infoLog);
		getGlError("RenderWindow::setupShaders() line:352, glGetShaderInfoLog");
		cout << "Program Validation error: " << infoLog << endl;
	}
}

string RenderWindow::readShaderFile(string fileName)
{
	ifstream iFile;
	string output;
	
	iFile.open(fileName.c_str());
	
	if(iFile.fail())
	{
		cout << fileName << endl;
		cout << "fail" << endl;
		return "fail";
	}
	
	bool forFind = false;
	while(!iFile.eof())
	{
		string temp;
		iFile >> temp;
		if(temp.find("for") != -1)
			if((temp[temp.find("for")+3] == '(') || (temp[temp.find("for")+3] == ' '))
				forFind = true;
		if(temp.find(")") != -1)
			if(forFind)
			{
				temp += "\n";
				forFind = false;
			}
		
		if(temp.find(";") != -1)
			if(!forFind)
				temp += "\n";
		if(temp.find("}") != -1)
			temp += "\n";
		if(temp.find("{") != -1)
			temp += "\n";
		output += (" " + temp);
	}
	cout << output << endl;
	return output;
}

void RenderWindow::setWindow(int _w, int _h)
{
	mWidth = _w;
	mHeight = _h;
}

void RenderWindow::setWidth(int _w)
{
	mWidth = _w;
}

void RenderWindow::setHeight(int _h)
{
	mHeight = _h;
}

void RenderWindow::setWindowPosition(int _x, int _y)
{
	mX = _x;
	mY = _y;
}

void RenderWindow::setWindowX(int _x)
{
	mX = _x;
}

void RenderWindow::setWindowY(int _y)
{
	mY = _y;
}

void RenderWindow::getWindow(int* _w, int* _h)
{
	_w = &mWidth;
	_h = &mHeight;
}

int RenderWindow::getWidth()
{
	return mWidth;
}

int RenderWindow::getHeight()
{
	return mHeight;
}

void RenderWindow::getWindowPosition(int* _x, int* _y)
{
	_x = &mX;
	_y = &mY;
}

int RenderWindow::getWindowX()
{
	return mX;
}

int RenderWindow::getWindowY()
{
	return mY;
}

void RenderWindow::_registerListener(EventListener* _listener)
{
	mFrameListener = _listener;
}

void RenderWindow::getGlError(std::string errTxt)
{
	int err = glGetError();
	if(err != GL_NO_ERROR)
	{
		std::cout << errTxt << std::endl;
		if(err == GL_INVALID_ENUM)
		{
			std::cout << "GL_INVALID_ENUM" << std::endl;
		}
		else if(err == GL_INVALID_VALUE)
		{
			std::cout << "GL_INVALID_VALUE" << std::endl;
		}
		else if(err == GL_INVALID_OPERATION)
		{
			std::cout << "GL_INVALID_OPERATION" << std::endl;
		}
		/*else if(err == GL_STACK_OVERFLOW)
		{
			std::cout << "GL_STACK_OVERFLOW" << std::endl;
		}
		else if(err == GL_STACK_UNDERFLOW)
		{
			std::cout << "GL_STACK_UNDERFLOW" << std::endl;
		}*/
		else if(err == GL_OUT_OF_MEMORY)
		{
			std::cout << "GL_OUT_OF_MEMORY" << std::endl;
		}
		//else if(err == GL_TABLE_TOO_LARGE)
		//{
		//	std::cout << "GL_TABLE_TOO_LARGE" << std::endl;
		//}
	}
}

GLuint RenderWindow::getProgram()
{
	return mShaderProgram;
}
