/*
 *  Core.h
 *  QtGLEngine
 *
 *  Created by Rob Rau on 12/26/10.
 *  Copyright 2010 Robert F. Rau II. All rights reserved.
 *
 */
#include "Core.h"

Core::Core()
{
	mRenderWindow = NULL;
	mSceneTree = NULL;
}

Core::~Core()
{

}

RenderWindow* Core::CreateRenderWindow(string name, int width, int height, bool fullScreen)
{
#ifdef __APPLE__
	mRenderWindow = new OSXRenderWindow(name, width, height, fullScreen);
#elif __linux
	mRenderWindow = new GLXRenderWindow(name, width, height, fullScreen);
#elif _WIN32
	mRenderWindow = new Win32RenderWindow(name, width, height, fullScreen);
#endif
	return mRenderWindow;
}

SceneTree* Core::CreateSceneTree()
{
	if(mRenderWindow)
	{
		mSceneTree = new SceneTree(mRenderWindow);
		return mSceneTree;
	}
	return 0;
}

void Core::StartRendering()
{
	mRenderWindow->_start();
}

Object* Core::CreateObject(string _name)
{
	return mRenderWindow->_newObject(_name);
}
/*
void Core::registerObject(string _name, Object* obj)
{
	mRenderWindow->_registerObject(_name, obj);
}
*/
Object* Core::GetObject(string _name)
{
	return mRenderWindow->_getObject(_name);
}

Camera* Core::CreateCamera()
{
	return mRenderWindow->createCamera();
}

void Core::SetInputHandler(InputHandler *inputHandler)
{
	mRenderWindow->setInputHandler(inputHandler);
}

void Core::SetEventListener(EventListener* eventListener)
{
	if(mRenderWindow)
		mRenderWindow->setEventListener(eventListener);
}

void Core::GetGlError(std::string file, std::string func, int lineNum)
{
	int err = glGetError();
	if(err != GL_NO_ERROR)
	{
//		std::cout << errTxt << std::endl;
		if(err == GL_INVALID_ENUM)
		{
			std::cout << "GL_INVALID_ENUM at line: " << lineNum << " in function: " << func <<
						 " in file: " << file << std::endl;
		}
		else if(err == GL_INVALID_VALUE)
		{
			std::cout << "GL_INVALID_VALUE at line: " << lineNum << " in function: " << func <<
						 " in file: " << file << std::endl;
		}
		else if(err == GL_INVALID_OPERATION)
		{
			std::cout << "GL_INVALID_OPERATION at line: " << lineNum << " in function: " << func <<
						 " in file: " << file << std::endl;
		}
		//else if(err == GL_STACK_OVERFLOW)
		//{
		//	std::cout << "GL_STACK_OVERFLOW" << std::endl;
		//}
		//else if(err == GL_STACK_UNDERFLOW)
		//{
		//	std::cout << "GL_STACK_UNDERFLOW" << std::endl;
		//}
		else if(err == GL_OUT_OF_MEMORY)
		{
			std::cout << "GL_OUT_OF_MEMORY at line: " << lineNum << " in function: " << func <<
						 " in file: " << file << std::endl;
		}
		//else if(err == GL_TABLE_TOO_LARGE)
		//{
		//	std::cout << "GL_TABLE_TOO_LARGE" << std::endl;
		//}
	}
}