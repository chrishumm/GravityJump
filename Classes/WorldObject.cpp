#include "WorldObject.h"

float WorldObject::xPTM = 1/300.0f;
float WorldObject::xMTP = 300.0f;

WorldObject::WorldObject()
{
	m_objectPhysics = new PhysicsComponent;
	m_objectRendering = new RenderingComponent(NULL);
	m_layerWidth = CCDirector::sharedDirector()->getWinSize().width;
	m_layerHeight = CCDirector::sharedDirector()->getWinSize().height;
}

WorldObject::WorldObject(CCLayer* currentLayer, b2World* currentWorld)
{
	m_objectPhysics = new PhysicsComponent(currentWorld);
	m_objectRendering = new RenderingComponent(currentLayer);
	m_layerWidth = CCDirector::sharedDirector()->getWinSize().width;
	m_layerHeight = CCDirector::sharedDirector()->getWinSize().height;
	m_object_active = true;
}

WorldObject::WorldObject(CCLayer* currentLayer, b2World* currentWorld, PhysicsComponent* pcom, RenderingComponent* rcom)
{
	m_objectPhysics = pcom;
	m_objectRendering = rcom;
	m_layerWidth = CCDirector::sharedDirector()->getWinSize().width;
	m_layerHeight = CCDirector::sharedDirector()->getWinSize().height;
	m_object_active = true;
}

WorldObject::~WorldObject()
{
	//delete m_objectPhysics;
	//m_objectPhysics = NULL;

	//delete m_objectRendering;
	//m_objectRendering = NULL;
}
void WorldObject::addPhysicsComponent(PhysicsComponent* component)
{
	m_objectPhysics = component;
}

void WorldObject::addRenderingComponent(RenderingComponent* component)
{
	m_objectRendering = component;
}

void WorldObject::update()
{

}

bool WorldObject::setObjectName(char* object_name)
{
	m_object_name = object_name;

	return true;
}

void WorldObject::setActive(bool object_active)
{
	m_object_active = object_active;
	if(object_active == false)
	{
		m_objectPhysics->setAsleep(false);
		//m_objectRendering->removeSprite();
	}
}

bool WorldObject::getActive()
{
	return m_object_active;
}

char* WorldObject::getObjectName()
{
	return m_object_name;
}

PhysicsComponent* WorldObject::getPhysicsComponent()
{
	return m_objectPhysics;
}

RenderingComponent* WorldObject::getRenderingComponent()
{
	return m_objectRendering;
}

float WorldObject::getX()
{
	return m_xPosition;
}

float WorldObject::getY()
{
	return m_yPosition;
}

float WorldObject::getBox2DX()
{
	return m_xPosition * xPTM;
}

float WorldObject::getBox2DY()
{
	return m_yPosition * xPTM;
}

void WorldObject::setX(float x)
{
	m_xPosition = x;
}

void WorldObject::setY(float y)
{
	m_yPosition = y;
}

void WorldObject::setState(int state, float ttl)
{
	if (m_state == state)
		m_state_ttl += ttl;

	m_state = state;
	m_state_ttl = ttl;
}

int WorldObject::getState()
{
	return m_state;
}

float WorldObject::getStateDuration()
{
	return m_state_ttl;
}

void WorldObject::setStateDuration(float dur)
{
	m_state_ttl = dur;
}