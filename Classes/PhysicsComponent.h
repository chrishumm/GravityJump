#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include <vector>

class PhysicsComponent
{
public:
	PhysicsComponent();
	PhysicsComponent(b2World*);
	virtual vector<b2Vec2> updatePhysics(float dt);
	void addPhysicsBody(b2Body*);
	void addPhysicsBody(b2Body*, bool);
	void removePhysics();
	void saveInitialPosition();
	void saveInitialPosition(vector<float>,vector<float>);
	void loadPosition(float offset);
	vector<float> getPhysicsXPositions();
	vector<float> getPhysicsYPositions();
	void setAsleep(bool );
	b2Body* getPhysicsBody();
	vector<b2Body*> getPhysicsBodies();
	b2World* getCurrentWorld();
	bool isMultipleBodiesAttached();
private:
protected:
	b2Body* m_physicsBody;
	vector<b2Body*> m_physicsBodies;
	vector<float> original_x;
	vector<float> original_y;
	b2World* m_currentWorld;
	bool multiple_bodies;
};