#pragma once
#include <iostream>
#include "cocos2d.h"
#include "MenuLayer.h"
#include <vector>

class ConsentMenu : public MenuLayer
{
public:
	virtual bool init();
	CREATE_FUNC(ConsentMenu);
	bool createUIConsent();
	//////////Input Events//////////////
	void closeGame(CCObject*);
	void startGame(CCObject*);
	/////////////////////////////////////////////////////////////////////////
private:
	CCLabelTTF* m_Warning_Label;
	CCSize screensize;
	CCMenu* titleMenu;
protected:
};
