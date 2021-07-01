#pragma once
#include "PhysicsComponent.h"
#include "Box2D\Box2D.h"
class MovingPhysicsComponent : public PhysicsComponent
{
public:
	MovingPhysicsComponent();
	MovingPhysicsComponent(b2World*);
	vector<b2Vec2> updatePhysics(float dt);
private:
	float moved_by;
	float max_moved;
	bool direction;
protected:

};