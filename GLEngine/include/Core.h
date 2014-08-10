/*
 *  Core.h
 *  QtGLEngine
 *
 *  Created by Rob Rau on 12/26/10.
 *  Copyright 2010 Robert F. Rau II. All rights reserved.
 *
 */
#ifndef CORE_H
#define CORE_H

//#include <QWidget>
#ifdef __APPLE__
# include "OSXRenderWindow.h"
#elif __linux
# include "GLXRenderWindow.h"
#elif _WIN32
# include "Win32/Win32RenderWindow.h"
#endif

#include <string>
//#include "canvas.h"

class SceneTree;

using namespace std;
class Core
{
public:
	Core();
	~Core();

	//creates the window to render in (creation may not actually happen yet)
	RenderWindow* CreateRenderWindow(string name, int width, int height, bool fullScreen);
	
	SceneTree* CreateSceneTree();
	
	//starts the rendering sequence (actual window creation may happen now)
	void StartRendering();
	
	//Light* createLight();
	Object* CreateObject(string _name);
	//void registerObject(string _name, Object* obj);
	Object* GetObject(string _name);
	Camera* CreateCamera();
	
	void SetInputHandler(InputHandler* inputHandler);
	void SetEventListener(EventListener* eventListener);
	
	GLuint getProgram()
	{
		return mRenderWindow->getProgram();
	}
	
	static void GetGlError(std::string file, std::string func, int lineNum);

private:

	bool window;
	RenderWindow* mRenderWindow;
	SceneTree* mSceneTree;

};


#endif //CORE_H
