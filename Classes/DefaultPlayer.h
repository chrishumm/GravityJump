#pragma once
#include "WorldObject.h"
class DefaultPlayer : public WorldObject
{
public:
	DefaultPlayer();
	DefaultPlayer(CCLayer* currentLayer, b2World* currentWorld);
	DefaultPlayer(CCLayer* currentLayer, b2World* currentWorld, PhysicsComponent*, RenderingComponent*);
private:
	void setDefaultPlayerPosition();
	void createPlayerPhysicsBody();
};