/*
Author: Christopher Humm
Class: Menu Scene
Description: This class will be abstract and parent for all other important menus.
Created: 25/03/2014
Last Modified: 04/04/2014
*/
#pragma once
#include "SceneFactory.h"

class MenuScene : public SceneFactory //This is our scene that holds our level
{
public:
	virtual bool init(); //overrided init
	static cocos2d::CCScene* scene();
	CREATE_FUNC(MenuScene);
	virtual bool addLayers(CCLayer*);
	virtual bool addLayers(int count, CCLayer**);
	virtual void menuCloseCallback(CCObject* pSender);
private:
	CCLayer* current_layers_added[5];//We use this to check if overriding layers shall be added onto the scene.
	int m_added_layers;
protected:
};

