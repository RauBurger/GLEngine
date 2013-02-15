#include "Win32RenderWindow.h"


LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

Win32RenderWindow::Win32RenderWindow()
{
	hDC = NULL;
	hRC = NULL;
	hWnd = NULL;

	setupRenderWindow();
}

Win32RenderWindow::Win32RenderWindow(string _name, int _w, int _h, bool _fullScreen)
{
	hDC = NULL;
	hRC = NULL;
	hWnd = NULL;

	width = _w;
	height = _h;

	setupRenderWindow();
}

void Win32RenderWindow::_start()
{
	while(1)
	{
		update();
	}
}
void Win32RenderWindow::update()
{
	render();
	SwapBuffers(hDC);
}

void Win32RenderWindow::setupRenderWindow()
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	//fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
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
								width,	// Calculate Window Width
								height,	// Calculate Window Height
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


}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			// LoWord Can Be WA_INACTIVE, WA_ACTIVE, WA_CLICKACTIVE,
			// The High-Order Word Specifies The Minimized State Of The Window Being Activated Or Deactivated.
			// A NonZero Value Indicates The Window Is Minimized.
			if ((LOWORD(wParam) != WA_INACTIVE) && !((BOOL)HIWORD(wParam))) {}
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
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}