//
//  Frustrum.cpp
//  QtGLEngine
//
//  Created by Rob Rau on 3/3/12.
//  Copyright (c) 2012 Robert F. Rau II. All rights reserved.
//

#include <iostream>
#include "Frustrum.h"
#include "math.h"

Frustrum::Frustrum(float fovY, float aspect, float clipNear, float clipFar)
{
	float xmin, xmax, ymin, ymax;       // Dimensions of near clipping plane
	float xFmin, xFmax, yFmin, yFmax;   // Dimensions of far clipping plane
	
	// Do the Math for the near clipping plane
	ymax = clipNear * float(tan( (fovY * 3.141592) / 360.0 ));
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = -xmin;
	
	mProjectionMatrix[0] = (2.0f * clipNear)/(xmax - xmin);
	mProjectionMatrix[5] = (2.0f * clipNear)/(ymax - ymin);
	mProjectionMatrix[8] = (xmax + xmin) / (xmax - xmin);
	mProjectionMatrix[9] = (ymax + ymin) / (ymax - ymin);
	mProjectionMatrix[10] = -((clipFar + clipNear)/(clipFar - clipNear));
	mProjectionMatrix[11] = -1.0f;
	mProjectionMatrix[14] = -((2.0f * clipFar * clipNear)/(clipFar - clipNear));
	mProjectionMatrix[15] = 0.0f;
	
	// Do the Math for the far clipping plane
	/*yFmax = clipFar * float(tan((fovY * 3.141592) / 360.0));
	yFmin = -yFmax;
	xFmin = yFmin * aspect;
	xFmax = -xFmin;
	
	
	// Fill in values for untransformed Frustum corners
	// Near Upper Left
	nearUL[0] = xmin; nearUL[1] = ymax; nearUL[2] = -fNear; nearUL[3] = 1.0f;
	
	// Near Lower Left
	nearLL[0] = xmin; nearLL[1] = ymin; nearLL[2] = -fNear; nearLL[3] = 1.0f;
	
	// Near Upper Right
	nearUR[0] = xmax; nearUR[1] = ymax; nearUR[2] = -fNear; nearUR[3] = 1.0f;
	
	// Near Lower Right
nearLR[0] = xmax; nearLR[1] = ymin; nearLR[2] = -fNear; nearLR[3] = 1.0f;
	
	// Far Upper Left
	farUL[0] = xFmin; farUL[1] = yFmax; farUL[2] = -fFar; farUL[3] = 1.0f;
	
	// Far Lower Left
	farLL[0] = xFmin; farLL[1] = yFmin; farLL[2] = -fFar; farLL[3] = 1.0f;
	
	// Far Upper Right
	farUR[0] = xFmax; farUR[1] = yFmax; farUR[2] = -fFar; farUR[3] = 1.0f;
	
	// Far Lower Right
	farLR[0] = xFmax; farLR[1] = yFmin; farLR[2] = -fFar; farLR[3] = 1.0f;*/
	
}

Matrix4* Frustrum::getProjectionMatrix()
{
	return &mProjectionMatrix;
}