#pragma once
#include <iostream>
#include "cocos2d.h"
#include "MenuLayer.h"
#include <vector>

class AchievementMenu : public MenuLayer
{
public:
	virtual bool init();
	CREATE_FUNC(AchievementMenu);
	//////////Input Events//////////////
	//virtual void ccTouchesBegan(CCSet * ptouches, cocos2d::CCEvent * pevent);
	//virtual void ccTouchesMoved(CCSet * ptouches, cocos2d::CCEvent * pevent);
	bool loadAchievements();
	void createGUI();
	void backButton(CCObject*);

	void upArrow(CCObject*);
	void downArrow(CCObject*);
	void rightArrow(CCObject*);
	void leftArrow(CCObject*);
	/////////////////////////////////////////////////////////////////////////


private:
	CCLabelTTF* m_ach_name[254];
	int achievements_recieved;
	vector<int>achievements_recieved_v;
	CCSize screensize;
	CCMenu* titleMenu;


	CCMenuItemImage* upSprite;
	CCMenuItemImage* downSprite;
	CCMenuItemImage* leftSprite;
	CCMenuItemImage* rightSprite;
	CCMenuItemImage* deleteMetricsSprite;
	CCMenuItemImage* pCloseItem;
	CCLabelTTF*		achievement_title;

	CCMenu* upArrowMenu;
	CCMenu* downArrowMenu;
	CCMenu* leftArrowMenu;
	CCMenu* rightArrowMenu;
	CCMenu* deleteMetricsMenu;
	CCMenu* pMenu;

	float initial_x;
	float initial_y;
protected:
};
