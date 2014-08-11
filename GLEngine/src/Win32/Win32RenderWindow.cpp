#include "Win32/Win32RenderWindow.h"
#include "InputHandler.h"

#include <windowsx.h>


LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

ProcessMessageDelegate<Win32RenderWindow>* Win32RenderWindow::mProcessMessageDelegate = NULL;

Win32RenderWindow::Win32RenderWindow()
{
	hDC = NULL;
	hRC = NULL;
	hWnd = NULL;
	done = false;
	SetupRenderWindow();
}

Win32RenderWindow::Win32RenderWindow(string _name, int _w, int _h, bool _fullScreen)
{
	hDC = NULL;
	hRC = NULL;
	hWnd = NULL;
	done = false;
	mWidth = _w;
	mHeight = _h;

	SetupRenderWindow();
}

void Win32RenderWindow::_start()
{
	while(!done)
	{
		update();
	}
}

void Win32RenderWindow::update()
{
	MSG msg;

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
	{
		if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
		{
			done = true;							// If So done=TRUE
		}
		else									// If Not, Deal With Window Messages
		{
			TranslateMessage(&msg);				// Translate The Message
			DispatchMessage(&msg);				// Dispatch The Message
		}
	}

	render();
	//wglSwapInterval(0);
	SwapBuffers(hDC);
}

void Win32RenderWindow::SetupRenderWindow()
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)mWidth;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long) mHeight;		// Set Bottom Value To Requested Height

	//fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	//wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.lpfnWndProc = (WNDPROC) Win32RenderWindow::WindowsCallback;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
	}
	
	/*if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}*/

	//if (fullscreen)												// Are We Still In Fullscreen Mode?
	//{
	//	dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
	//	dwStyle=WS_POPUP;										// Windows Style
	//	ShowCursor(FALSE);										// Hide Mouse Pointer
	//}
	//else
	//{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	//}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	hWnd = CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								"GLEngine",								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								mWidth,	// Calculate Window Width
								mHeight,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL);							// Dont Pass Anything To WM_CREATE
	//{
	//	KillGLWindow();								// Reset The Display
	//	MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
	//}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		32,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	hDC = GetDC(hWnd);							// Did We Get A Device Context?
	//{
	//	KillGLWindow();								// Reset The Display
	//	MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
	//}

	PixelFormat = ChoosePixelFormat(hDC,&pfd);	// Did Windows Find A Matching Pixel Format?
	//{
	//	KillGLWindow();								// Reset The Display
	//	MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
	//}

	SetPixelFormat(hDC,PixelFormat,&pfd);		// Are We Able To Set The Pixel Format?
	//{
	//	KillGLWindow();								// Reset The Display
	//	MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
	//}

	hRC = wglCreateContext(hDC);			// Are We Able To Get A Rendering Context?
	//{
	//	KillGLWindow();								// Reset The Display
	//	MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
	//}

	wglMakeCurrent(hDC,hRC);					// Try To Activate The Rendering Context
	//{
	//	KillGLWindow();								// Reset The Display
	//	MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
	//}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	//ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	mProcessMessageDelegate = new ProcessMessageDelegate<Win32RenderWindow>(this, &Win32RenderWindow::ProcessMessage);
	GLenum err = glewInit();

	setupOpenGL();
}

void Win32RenderWindow::setInputHandler(InputHandler* inputHandler)
{
	mInputHandler = inputHandler;
}

LRESULT Win32RenderWindow::ProcessMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM	lParam)
{
	switch (uMsg)									// Check For Windows Messages
	{
	case WM_QUIT:
		done = true;
		return 0;
		break;
	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
		// LoWord Can Be WA_INACTIVE, WA_ACTIVE, WA_CLICKACTIVE,
		// The High-Order Word Specifies The Minimized State Of The Window Being Activated Or Deactivated.
		// A NonZero Value Indicates The Window Is Minimized.
		if ((LOWORD(wParam) != WA_INACTIVE) && !((BOOL) HIWORD(wParam))) {}
		//active=TRUE;						// Program Is Active
		else {}
		//active=FALSE;						// Program Is No Longer Active

		return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
		switch (wParam)							// Check System Calls
		{
		case SC_SCREENSAVE:					// Screensaver Trying To Start?
		case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
			return 0;							// Prevent From Happening
		}
		break;									// Exit
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
		//ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								// Jump Back
	}
	case WM_LBUTTONDOWN:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = -GET_Y_LPARAM(lParam);

		mInputHandler->mouseDown(InputHandler::LEFT_MOUSE_BUTTON, xPos, yPos);
		return 0;
		break;
	}
	case WM_LBUTTONUP:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = -GET_Y_LPARAM(lParam);

		mInputHandler->mouseUp(InputHandler::LEFT_MOUSE_BUTTON, xPos, yPos);
		return 0;
		break;
	}
	case WM_MOUSEMOVE:
	{
		int xPos = GET_X_LPARAM(lParam);
		int yPos = -GET_Y_LPARAM(lParam);

		mInputHandler->mouseMoved(xPos, yPos);
		return 0;
		break;
	}
	case WM_KEYDOWN:
	{
		mInputHandler->keyDown((InputHandler::KeyCode)wParam);
		return 0;
		break;
	}
	case WM_KEYUP:
	{
		mInputHandler->keyUp((InputHandler::KeyCode)wParam);
		return 0;
		break;
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT Win32RenderWindow::WindowsCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM	lParam)
{
	if (mProcessMessageDelegate != NULL)
	{
		return mProcessMessageDelegate->Invoke(hWnd, uMsg, wParam, lParam);
	}
	else
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);;
	}
}