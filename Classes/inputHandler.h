#pragma once
#include <iostream>
#include "jump.h"
#include "GravitySwitch.h"
#include "SlideObject.h"
#include "DefaultPlayer.h"

class inputHandler
{
public:
	jump* objectJump;
	command* handleInput(CCSet * pTouches, b2World* currentWorld, float deltaTime);
	void onClickPositions(CCSet * pTouches);
	bool handleStart(CCSet * pTouches, CCEvent * pEvent, bool* game_start);
	CCTouch* getPoint();
private:
	CCTouch* m_point;
	CCSetIterator itr;
	CCTouch* touch;
	float x_initial_pos;
	float y_initial_pos;

	float x_current_pos;
	float y_current_pos;

protected:

};