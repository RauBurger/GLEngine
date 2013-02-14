//
//  InputHandler.h
//  QtGLEngine
//
//  Created by Rob Rau on 3/7/12.
//  Copyright (c) 2012 Robert F. Rau II. All rights reserved.
//

#ifndef INPUTHANDLER_h
#define INPUTHANDLER_h

class InputHandler
{
public:
	
	enum KeyCode
	{
		KEY_A = 65,
		KEY_B = 66,
		KEY_C = 67,
		KEY_D = 68,
		KEY_E = 69,
		KEY_F = 70,
		KEY_G = 71,
		KEY_H = 72,
		KEY_I = 73,
		KEY_J = 74,
		KEY_K = 75,
		KEY_L = 76,
		KEY_M = 77,
		KEY_N = 78,
		KEY_O = 79,
		KEY_P = 80,
		KEY_Q = 81,
		KEY_R = 82,
		KEY_S = 83,
		KEY_T = 84,
		KEY_U = 85,
		KEY_V = 86,
		KEY_W = 87,
		KEY_X = 88,
		KEY_Y = 89,
		KEY_Z = 90,
		
		KEY_a = 97,
		KEY_b = 98,
		KEY_c = 99,
		KEY_d = 100,
		KEY_e = 101,
		KEY_f = 102,
		KEY_g = 103,
		KEY_h = 104,
		KEY_i = 105,
		KEY_j = 106,
		KEY_k = 107,
		KEY_l = 108,
		KEY_m = 109,
		KEY_n = 110,
		KEY_o = 111,
		KEY_p = 112,
		KEY_q = 113,
		KEY_r = 114,
		KEY_s = 115,
		KEY_t = 116,
		KEY_u = 117,
		KEY_v = 118,
		KEY_w = 119,
		KEY_x = 120,
		KEY_y = 121,
		KEY_z = 122,
		
		KEY_UA = 63232,
		KEY_DA = 63233,
		KEY_RA = 63235,
		KEY_LA = 63234
	};
	
	enum MouseButton
	{
		LEFT_MOUSE_BUTTON = 0,
		MIDDLE_MOUSE_BUTTON = 1,
		RIGHT_MOUSE_BUTTON = 2
	};
	
	InputHandler();
	~InputHandler();
	
	virtual void keyDown(KeyCode key) = 0;
	virtual void keyUp(KeyCode key) = 0;
	virtual void mouseDown(MouseButton button, float x, float y) = 0;
	virtual void mouseUp(MouseButton button, float x, float y) = 0;
	virtual void mouseMoved(float xMag, float yMag) = 0;
	virtual void scrollWheel(float delta) = 0;
private:
	
	
};

#endif //INPUTHANDLER_h
