/*
Author: Christopher Humm
Class: Menu Layer
Description: This class will be abstract and parent for all other important menus layers to draw from
Created: 25/03/2014
Last Modified: 04/04/2014
*/
#pragma once
#include <iostream>
#include "cocos2d.h"
#include "LayerFactory.h"
#include "LoadingScreenScene.h"
//#include "InputHandler.h"
//#include "ObjectCommand.h"

class MenuLayer : public LayerFactory
{
public:
	virtual bool init() = 0;

	virtual void ccTouchesBegan(CCSet * ptouches, cocos2d::CCEvent * pevent);
	virtual void ccTouchesEnded(CCSet * ptouches, cocos2d::CCEvent * pevent);

	void addAchievementManager(AchievementManager* current);
	void addMetricsManager(MetricManager*);
private:
protected:
	float m_layer_width;
	float m_layer_height;
	AchievementManager* m_achievement_manager;
	MetricManager* m_metric_manager;
};
