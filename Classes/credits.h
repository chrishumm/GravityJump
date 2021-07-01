#pragma once
#include <iostream>
#include "cocos2d.h"
#include "MenuLayer.h"
#include <vector>

class Credits : public MenuLayer
{
public:
	virtual bool init();
	CREATE_FUNC(Credits);
	bool createCredits();
	//////////Input Events//////////////
	void backToGame(CCObject*);
	/////////////////////////////////////////////////////////////////////////
private:
	CCLabelTTF* artist;
	CCLabelTTF* programmer;
	CCLabelTTF* music;
	CCLabelTTF* misc;
	CCLabelTTF* specialthanks;

	CCMenuItemLabel* artist_m;
	CCMenuItemLabel* programmer_m;
	CCMenuItemLabel* music_m;
	CCMenuItemLabel* misc_m;
	CCMenuItemLabel* specialthanks_m;
	CCSize screensize;
	CCMenu* creditsMenu;
protected:
};
