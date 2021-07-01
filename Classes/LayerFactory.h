/*
	Author: Christopher Humm
	Class: Layer Factory
	Description: This class will be used as a factory to generate and manage Layers within cocos2d.
	Created: 29/02/2014
	Last Modified: 24/03/2014
*/
#pragma once
#include <iostream>
#include "cocos2d.h"
#include <Box2D/Box2D.h> 
#include "AchievementManager.h"
#include "MetricManager.h"
using namespace cocos2d;

class LayerFactory : public CCLayer
{
public:
	static CCLayer* createLayer(char* name);
	//////////Box 2D Events/////////////
	virtual bool init() = 0;
	virtual void addAchievementManager(AchievementManager*) = 0;
	virtual void addMetricsManager(MetricManager*) = 0;
	//////////Input Events//////////////
	virtual void ccTouchesBegan( CCSet * ptouches, cocos2d::CCEvent * pevent )= 0;

	private:

	protected:
		enum m_states{ initialising, game_loop, game_pause, game_end};
		enum m_player_states{ normal, infinite, invincible, death };
};
