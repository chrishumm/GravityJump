#include "inputHandler.h"
void inputHandler::onClickPositions(CCSet * pTouches)
{
	for (itr = pTouches->begin(); itr != pTouches->end(); itr++)
	{
		touch = static_cast<CCTouch*>(*itr);
		x_initial_pos = touch->getLocation().x;
		y_initial_pos = touch->getLocation().y;
	}
}

command* inputHandler::handleInput(CCSet * pTouches, b2World* currentWorld, float dt)
{
	for (itr = pTouches->begin(); itr != pTouches->end(); itr++)
	{
		touch = static_cast<CCTouch*>(*itr);
		x_current_pos = touch->getLocation().x;
		y_current_pos = touch->getLocation().y;
	}

	jump* objectJump = NULL;
	GravitySwitch* gravitySwitch = NULL;
	SlideObject* slideObject = NULL;

	if (x_initial_pos < (x_current_pos - 10))
	{
		if (y_current_pos > 150.0f)
		{
			if (currentWorld->GetGravity().y < 0.0f)
				objectJump = new jump(jump::right, jump::flipped);
			else
				objectJump = new jump(jump::right, jump::normal);
		}
		else
		{
			slideObject = new SlideObject(jump::right);
		}
	}
	else if (x_initial_pos > (x_current_pos + 10))
	{
		if (y_current_pos > 150.0f)
		{
			if (currentWorld->GetGravity().y < 0.0f)
				objectJump = new jump(jump::left, jump::flipped);
			else
				objectJump = new jump(jump::left, jump::normal);
		}
		else
		{
			slideObject = new SlideObject(jump::left);
		}
	}
	else
	{
		gravitySwitch = new GravitySwitch(currentWorld, "woosh.wav");
	}

	if (objectJump != NULL)
		return objectJump;
	if (gravitySwitch != NULL)
		return gravitySwitch;
	if (slideObject != NULL)
		return slideObject;

	return NULL;
}

bool inputHandler::handleStart(CCSet * pTouches, CCEvent * pEvent, bool* game_start)
{
	if (*game_start == true)
	{
		for (itr = pTouches->begin(); itr != pTouches->end(); itr++)
		{
			*game_start = false;
			m_point = static_cast<CCTouch*>(*itr);
			return true;
		}
	}
	else
	{
		return false;
	}

	return false;
}

CCTouch* inputHandler::getPoint()
{
	return m_point;
}