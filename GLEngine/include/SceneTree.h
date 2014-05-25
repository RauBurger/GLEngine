//
//  SceneGraph.h
//  QtGLEngine
//
//  Created by Rob Rau on 11/3/11.
//  Copyright (c) 2011 Robert F. Rau II. All rights reserved.
//

#ifndef SCENETREE_H_
#define SCENETREE_H_

/*
 When a camera is attached to a node all matrix transforms from node (and other possible parent nodes)
 are given to the camera. He then multiplies his local view matrix by those and we get the global 
 view matrix. This is now the bassis of all other matrix transforms for objects.
 
 so if we have:
   world->Node1----->Node2----->camera
	      Node1Mat * Node2Mat * ViewMat = GlobalViewMat
 This may seem bacwards from convention, but once this global view matrix is formed, all other transforms
 for objects will use this as the view matrix and things are back to normal.
 
 then for objects we have
   world---------->Node1----->Node2--->object
   GlobalViewMat * Node1Mat * Node2Mat = GlobalModelViewMatrix
 
 Each node matrix is a model matrix for its coordinate space, but the global model view matrix is what
 should be used in shaders. That's the way opengl likes it. Of course once all this is said and done the
 projection matrix should be multiplied in.
 
 Rendering the camera should consist of computing the global view matrix and making it available to objects
 in the scene.
 */
#include "Object.h"
#include <vector>
#include <string>
#include <map>

class Camera;
class Matrix3;
class Matrix4;

class Vector3;
class Vector4;

class Node;

class RenderWindow;

class SceneTree
{
public:
	SceneTree();
	SceneTree(RenderWindow*);
	~SceneTree();
	
	Node* createNode(std::string name);
	Node* getRootNode();
	
	Matrix4* _getWorldViewMatrixPtr();
	void _setRenderWindow(RenderWindow* renderWin);
	Object* createObject(std::string name);
	//Camera* createCamera();
	void update();

private:
	std::map<std::string, Node*> mNodes;
	Camera* mCamera;
	
	Node* mRootNode;
	
	Matrix4* mWorldViewMat;
	Matrix4* mProjectionMat;
	
	RenderWindow* mRenderWindow;
};

#endif