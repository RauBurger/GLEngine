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
#elif __WIN32__
# include "Win32RenderWindow.h"
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
	RenderWindow* createRenderWindow(string name, int width, int height, bool fullScreen);
	
	SceneTree* createSceneTree();
	
	//starts the rendering sequence (actual window creation may happen now)
	void startRendering();
	
	//Light* createLight();
	Object* createObject(string _name);
	void registerObject(string _name, Object* obj);
	Object* getObject(string _name);
	Camera* createCamera();
	
	void setInputHandler(InputHandler* inputHandler);
	void setEventListener(EventListener* eventListener);
	
	GLuint getProgram()
	{
		return mRenderWindow->getProgram();
	}

private:

	bool window;
	RenderWindow* mRenderWindow;
	SceneTree* mSceneTree;

};


#endif //CORE_H
