/*
Author: Christopher Humm
Class: Menu Scene
Description: This class will be abstract and parent for all other important menus.
Created: 25/03/2014
Last Modified: 04/04/2014
*/
#pragma once
#include "SceneFactory.h"
#include "LayerFactory.h"
class LoadingScreenScene :public CCLayer //This is our scene that holds our level
{
public:
	static CCScene* createScene();
	virtual bool init(); //overrided init
	static cocos2d::CCScene* scene();
	CREATE_FUNC(LoadingScreenScene);

	virtual void onEnter();
	void addNextScene(char* next_scene);
	void finishSplash(float dt);

private:
	char* m_next_scene;
	CCSprite* sprite;
	LoadingScreenScene* loadingLayer;
protected:
};

