/*
Author: Christopher Humm
Class: Collision
Description: Handles collisions during gameplay
*/
#pragma once

#include <iostream>
#include <vector>
#include "WorldObject.h"
#include "Box2D\Box2D.h"
#include "cocos2d.h"
#include "soundManager.h"
#include "LevelChunk.h"
#include "MetricManager.h"
using namespace cocos2d;

class collision : public b2ContactListener
{
public:
	collision(b2World* world);
	~collision();
	void updateCollision(vector<WorldObject*> world_object);
	bool applyPowerup(char*,LevelChunk*, size_t* body_no);
	virtual void BeginContact(b2Contact* contact); //overriden contacts
	virtual void EndContact(b2Contact* contact); // for player > platforms
	virtual	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
private:
	b2World* m_world;
	vector<WorldObject*> m_current_level_objects;
	MetricManager* collision_metrics;
	float powerups_collected;
	float blocked_destroyed;
};