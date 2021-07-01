#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "WorldObject.h"

using namespace cocos2d;

class InfiniteGravitySwitching
{
public:
	static b2Body* createWallPhysics(float x, float y,float xEnd, float yEnd,b2World*);
	static CCSprite* createWallSprite(float x, float y);
	static void effect(WorldObject*);
};