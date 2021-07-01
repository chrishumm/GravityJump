#pragma once
#include <iostream>
#include "cocos2d.h"
#include "MenuLayer.h"
#include <vector>

class MetricsMenu : public MenuLayer
{
public:
	virtual bool init();
	CREATE_FUNC(MetricsMenu);
	//////////Input Events//////////////
	//virtual void ccTouchesBegan(CCSet * ptouches, cocos2d::CCEvent * pevent);
	//virtual void ccTouchesMoved(CCSet * ptouches, cocos2d::CCEvent * pevent);
	bool loadMetrics();
	void createGUI();
	void deleteMetrics(CCObject*);
	void backButton(CCObject*);


	void upArrow(CCObject*);
	void downArrow(CCObject*);
	void rightArrow(CCObject*);
	void leftArrow(CCObject*);
	/////////////////////////////////////////////////////////////////////////


private:
	CCLabelTTF* m_metric_name[254];
	CCLabelTTF* m_metric_data[254][254];
	int metrics_retrieved;
	vector<int>unique_metric_id;
	char* metric_data_retrieved_int;
	CCSize screensize;
	CCMenu* titleMenu;


	CCMenuItemImage* upSprite;
	CCMenuItemImage* downSprite;
	CCMenuItemImage* leftSprite;
	CCMenuItemImage* rightSprite;
	CCMenuItemImage* deleteMetricsSprite;
	CCMenuItemImage* pCloseItem;

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
