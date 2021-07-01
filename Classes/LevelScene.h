/*
	Author: Christopher Humm
	Class: Level Scene
	Description: Child Class of SceneFactory. Will be created upon request to start the scene instance of a new level.
	Created: 25/02/2014
	Last Modified: 14/03/2014
*/
#pragma once
#include "SceneFactory.h"

class LevelScene : public SceneFactory //This is our scene that holds our level
{
public:
	virtual bool init(); //overrided init
	static cocos2d::CCScene* scene();
	CREATE_FUNC(LevelScene);
	virtual bool addLayers(CCLayer*);
	virtual bool addLayers(int count, CCLayer**);
	virtual void menuCloseCallback(CCObject* pSender);
private:
	CCLayer* current_layers_added[5];
	int m_added_layers;
protected:
};

