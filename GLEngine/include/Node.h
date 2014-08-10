//
//  Node.h
//  QtGLEngine
//
//  Created by Rob Rau on 11/7/11.
//  Copyright (c) 2011 Robert F. Rau II. All rights reserved.
//

#ifndef QtGLEngine_Node_h
#define QtGLEngine_Node_h
#include "SceneTree.h"
#include "Object.h"
#include "Matrix4.h"

#if defined __linux || defined __APPLE__
class __attribute__ ((visibility("default"))) Node
#elif _WIN32
class Node
#endif
{
public:
	Node(std::string name);
	
	void attachObject(Object* obj);
	void attachObject(Node* node);
	Node* createNode(std::string name);
	void attachCamera(Camera* camera);
	
	void setSceneTree(SceneTree* scnTree);
	void rotateNodeLocal(float angle, float x, float y, float z);
	void translateNodeLocal(float x, float y, float z);
	const Matrix4 _getModelMatrix();
	const Matrix4& getWorldTransform();
	std::string getName();
	
	void update();
private:
	friend class Object;
	friend class SceneTree;
	void setWorldViewMatrixPtr(Matrix4* worldViewMat);
	Node* getParentNode();
	
	//std::vector<Node*>* getChildVector();
	
	//gets the world model matrix with respect to this node
	//needs to re-calc each frame
	//Matrix4* _getModelMat();
	
	//sets the world model matrix
	void  _setModelMat(Matrix4* modelMat);
	
	SceneTree* mSceneTree;
	Node* mParentNode;
	//std::vector<Node*>* mChildrenNodes;
	Node** mChildrenNodes;
	std::map<std::string, int> mChildNodeNames;
	int mNumChildNodes;
	
	Matrix4* mWorldViewMat;
	Matrix4 mLocalTransform;
	Matrix4 mWorldTransform;
	std::string mName;
};

#endif
