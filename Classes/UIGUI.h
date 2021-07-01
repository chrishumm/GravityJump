#pragma once
#include <iostream>
#include "cocos2d.h"
#include "LayerFactory.h"
#include "LevelLayer.h"
#include "MetricManager.h"
#include "soundManager.h"
using namespace std;
using namespace cocos2d;

class UIGUI : public LayerFactory
{
public:
	virtual bool init();
	CREATE_FUNC(UIGUI);
	//////////Box 2D Events/////////////

	//////////Input Events//////////////
	virtual void ccTouchesBegan(CCSet * ptouches, cocos2d::CCEvent * pevent );
	virtual void addAchievementManager(AchievementManager*);
	virtual void addMetricsManager(MetricManager*);

	virtual void ccTouchesEnded(CCSet * ptouches, cocos2d::CCEvent * pevent );
	void createGUI(CCLayer*);

	void updateGUI(float time); //Generic Interface
	void updatePlayerGUI(float time); //Specific Player Interfaces

	void pauseGUI(CCObject*);
	void restartLevel(CCObject*);
	void closeGame(CCObject*);
	void returnToMenu(CCObject*);

	void showDeathScreen();
private:
	bool m_paused;
	AchievementManager* m_achievement_manager;
	MetricManager* m_metric_manager;

	float total_elapsed_time;
	LevelLayer* m_currentLevel;
	CCLabelTTF* m_current_time_label;
	CCLabelTTF* m_font_shadow;
	CCLabelTTF* m_loading;
	CCSprite* darken;
	CCSprite* m_current_powerup;
	CCPoint screensize;
	string msg;
	float m_ttl;
	bool message_displaying;
	static const int default_message_ttl;
	float powerup_duration;
protected:
};