/*
Author: Christopher Humm
Class: Bad Wall
Description: This class acts as a base for all levels
*/
#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "WorldObject.h"

using namespace cocos2d;

class BadWall
{
public:
	static b2Body* createWallPhysics(float x, float y,float xEnd, float yEnd,b2World*);
	static CCSprite* createWallSprite(float x, float y);
	static void effect(WorldObject*);
};