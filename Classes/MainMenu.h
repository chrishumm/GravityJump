#pragma once
#include <iostream>
#include "cocos2d.h"
#include "MenuLayer.h"
#include "soundManager.h"
#include <vector>

class MainMenu : public MenuLayer
{
public:
	virtual bool init();
	CREATE_FUNC(MainMenu);
	//////////Input Events//////////////
	virtual void ccTouchesBegan(CCSet * ptouches, cocos2d::CCEvent * pevent);
	virtual void ccTouchesMoved(CCSet * ptouches, cocos2d::CCEvent * pevent);
	void closeGame(CCObject*);
	void startGame(CCObject*);
	void viewAch(CCObject*);
	void viewMetrics(CCObject*);
	void viewCredits(CCObject*);
	void exitGame(CCObject*);
	/////////////////////////////////////////////////////////////////////////
	void muteGame(CCObject*);
	
private:
	CCLabelTTF* m_gameLabelName;
	CCSize screensize;
	CCMenu* titleMenu;
	CCSprite* loadingScreen;
protected:
};
