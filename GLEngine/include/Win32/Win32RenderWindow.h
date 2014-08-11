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
#include "Win32/ProcessMessageDelegate.h"

class Win32RenderWindow : public RenderWindow
{
public:
	Win32RenderWindow();
	Win32RenderWindow(string _name, int _w, int _h, bool _fullScreen);
	~Win32RenderWindow();

	void update();
	void _start();

	virtual void setInputHandler(InputHandler* inputHandler);

private:
	static ProcessMessageDelegate<Win32RenderWindow>* mProcessMessageDelegate;
	static LRESULT WindowsCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM	lParam);
	LRESULT ProcessMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM	lParam);
	void SetupRenderWindow();

	InputHandler* mInputHandler;

	//=====Window Params=====//
	HDC			hDC;		// Private GDI Device Context
	HGLRC		hRC;		// Permanent Rendering Context
	HWND		hWnd;		// Holds Our Window Handle
	HINSTANCE	hInstance;		// Holds The Instance Of The Application
	
	bool done;
	bool active;		// Window Active Flag Set To TRUE By Default
	bool fullscreen;	// Fullscreen Flag Set To Fullscreen Mode By Default
};

#endif //WIN32RENDERWINDOW_H_