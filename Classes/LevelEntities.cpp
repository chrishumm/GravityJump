#pragma once
#include "cocos2d.h"
#include <Box2D\Box2D.h>

using namespace cocos2d;

class LevelEntities
{
public:
	bool setBody(b2Body* object_body);
	bool setSprite(CCSprite* object_sprite);
	bool setObjectName(char* object_name);
	void setActive(bool object_active);
	///////////////////////////////////////
	b2Body* getBody();
	CCSprite* getSprite();
	char* getObjectName();
	bool getActive();
private:
protected:
	b2Body* m_physics_body;
	CCSprite* m_object_sprite;
	char* m_object_name;
	bool m_object_active;
};