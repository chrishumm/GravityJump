#pragma once
#include "cocos2d.h"
#include <iostream>

//////////////Components//////////////////
#include "PhysicsComponent.h"
#include "RenderingComponent.h"

class WorldObject
{
public:
	WorldObject();
	~WorldObject();
	WorldObject(CCLayer* currentLayer, b2World* currentWorld);
	WorldObject(CCLayer* currentLayer, b2World* currentWorld, PhysicsComponent*, RenderingComponent*);
	void addPhysicsComponent(PhysicsComponent* component);
	void addRenderingComponent(RenderingComponent* m_objectRendering);
	virtual void update();
	bool setSprite(CCSprite* object_sprite);
	bool setObjectName(char* object_name);
	void setActive(bool object_active);

	char* getObjectName();
	bool getActive();

	PhysicsComponent* getPhysicsComponent();
	RenderingComponent* getRenderingComponent();

	float getX();
	float getY();

	float getBox2DX();
	float getBox2DY();

	void setX(float x);
	void setY(float y);

	void setState(int type, float ttl);
	float getStateDuration();
	void setStateDuration(float dur);
	int getState();
	

	static float xPTM;
	static float xMTP;
private:
protected:
	enum pstates{normal,infinite,invincible,death};
	int m_state;
	float m_state_ttl;

	PhysicsComponent* m_objectPhysics;
	RenderingComponent* m_objectRendering;
	char* m_object_name;
	bool m_object_active;
	float m_layerWidth;
	float m_layerHeight;

	float m_xPosition;
	float m_yPosition;

	vector<WorldObject*> levelObjects;
	b2World* m_world;
	b2Vec2   m_worldGravity;
	float m_gravity_y;
	vector<WorldObject*> m_active_chunks;


	float m_initial_xPosition;
	float m_initial_yPosition;

};