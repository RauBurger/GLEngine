//
//  SceneTree.cpp
//  QtGLEngine
//
//  Created by Rob Rau on 11/4/11.
//  Copyright (c) 2011 Robert F. Rau II. All rights reserved.
//

#include <iostream>
#include "SceneTree.h"
#include "Camera.h"
#include "Object.h"
#include "Node.h"
#include "RenderWindow.h"
#include "Matrix4.h"

SceneTree::SceneTree()
{
	mRenderWindow = NULL;
	mWorldViewMat = new Matrix4();
	mProjectionMat = NULL;
	mRootNode = new Node("RootNode");
	mCamera = NULL;
	mNodes.clear();
}

SceneTree::SceneTree(RenderWindow* renderWin)
{
	mRenderWindow = NULL;
	mWorldViewMat = new Matrix4();
	mProjectionMat = NULL;
	mRootNode = new Node("RootNode");
	mCamera = NULL;
	mRenderWindow = renderWin;
	mRenderWindow->_setWorldViewMatrixPtr(mWorldViewMat);
	mRenderWindow->_setSceneTree(this);
	mNodes.clear();
}

SceneTree::~SceneTree()
{
	
}

Node* SceneTree::createNode(std::string name)
{
	name += '\0';
	Node* tmp = new Node(name);
	//tmp->setSceneTree(this);
	tmp->setWorldViewMatrixPtr(mWorldViewMat);
	std::cout << mNodes.size() << std::endl;
	//mNodes.insert(std::pair<std::string, Node*>(name, tmp));
	return tmp;
}

Node* SceneTree::getRootNode()
{
	if(mRootNode)
		return mRootNode;
	return 0;
}

Matrix4* SceneTree::_getWorldViewMatrixPtr()
{
	return mWorldViewMat;
}

void SceneTree::_setRenderWindow(RenderWindow* renderWin)
{
	mRenderWindow = renderWin;
	mRenderWindow->_setWorldViewMatrixPtr(mWorldViewMat);
}

Object* SceneTree::createObject(std::string name)
{
	return mRenderWindow->_newObject(name);
}

void SceneTree::update()
{
	if(mRootNode)
	{
		mRootNode->update();
	}
}