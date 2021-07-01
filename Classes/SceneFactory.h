/*
	Author: Christopher Humm
	Class: Scene Factory
	Description: This class will be used as a factory to generate and manage scenes within cocos2d.
	Created: 25/02/2014
	Last Modified: 25/02/2014
*/
#pragma once
#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

class SceneFactory : public CCScene
{
	public:
		static cocos2d::CCScene* scene();
		static CCScene* createScene(char* name);
		static void createScene(char* name,CCScene* SceneName);
		static CCScene* createScene(char* name,CCLayer**, int count);
		static CCScene* buildScene(CCScene*);
		virtual bool addLayers(CCLayer*) = 0;
		virtual bool addLayers(int count, CCLayer**) = 0;
	private:

	protected:

};
