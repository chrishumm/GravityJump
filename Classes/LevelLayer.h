/*
	Author: Christopher Humm
	Class: Level Layer
	Description: This class acts as a base for all levels
	Created: 29/02/2014
	Last Modified: 01/03/2014
*/
#pragma once
#include <iostream>
#include "cocos2d.h"
#include "LayerFactory.h"
#include "collision.h"
#include "inputHandler.h"
#include <Box2D/Box2D.h> 

//#include "InputHandler.h"
//#include "ObjectCommand.h"

class LevelLayer : public LayerFactory
{
	public:
	//////////Box 2D Events/////////////
	virtual bool init() = 0;
	
	//virtual void BeginContact(b2Contact* contact); //overriden contacts
	//virtual void EndContact(b2Contact* contact); // for player > platforms
	//virtual	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	//////////Input Events//////////////
	virtual void ccTouchesBegan(CCSet * ptouches, cocos2d::CCEvent * pevent );
	virtual void ccTouchesEnded(CCSet * ptouches, cocos2d::CCEvent * pevent );
	virtual void setLevelNumber(int levelNumber);
	virtual int  getLevelNumber();

	virtual int getState(); //game states only
	virtual void setState(int);

	virtual int getPlayerState() = 0; //specific player states
	virtual float getPlayerStateDuration() = 0; //specific player states
	virtual void setPlayerState(int) = 0;
	virtual void setPlayerState(int,float) = 0;
	virtual void setPlayerStateDuration(float) = 0; //specific player states

	virtual bool deallocateMemory() = 0;
	void addAchievementManager(AchievementManager* current);
	void addMetricsManager(MetricManager*);
	
	MetricManager* getMetricManager();
	AchievementManager* getAchievementManager();
	
	private:
		virtual void gameLoop(float dt) = 0;
	protected:
	
	unsigned int m_level_number;
	unsigned int m_state;
	float m_layer_width;
	float m_layer_height;
	AchievementManager* m_achievement_manager;
	MetricManager* m_metric_manager;
	inputHandler* m_inputHandler;

	float x_current_pos;
	float x_original_pos;
	float y_original_pos;
	float y_current_pos;
};
