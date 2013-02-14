#ifndef WIN32RENDERWINDOW_H_
#define WIN32RENDERWINDOW_H_
/*
 *  Win32RenderWindow.h
 *
 *  Created by Rob Rau on 12/25/10.
 *  Copyright 2010 Rob Rau. All rights reserved.
 *
 */

#include "RenderWindow.h"

class Win32RenderWindow : public RenderWindow
{
public:
	Win32RenderWindow();
	Win32RenderWindow(string _name, int _w, int _h, bool _fullScreen);
	~Win32RenderWindow();

	void update();
	void _start();

private:
	void setupRenderWindow();

	//=====Window Params=====//
	HDC			hDC;		// Private GDI Device Context
	HGLRC		hRC;		// Permanent Rendering Context
	HWND		hWnd;		// Holds Our Window Handle
	HINSTANCE	hInstance;		// Holds The Instance Of The Application

	bool	active;		// Window Active Flag Set To TRUE By Default
	bool	fullscreen;	// Fullscreen Flag Set To Fullscreen Mode By Default
};

#endif //WIN32RENDERWINDOW_H_