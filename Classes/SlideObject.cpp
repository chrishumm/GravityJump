#include "SlideObject.h"

bool SlideObject::sounds_preloaded = false;

SlideObject::SlideObject(int direction)
{
	sound = NULL;
	switch (direction)
	{
	case right:
		m_direction = right;
		break;

	case left:
		m_direction = left;
		break;

	case up:
		m_direction = up;
		break;

	case down:
		m_direction = down;
		break;

	default:
		m_direction = down;
	}
}

SlideObject::SlideObject(int direction, char* s)
{
	sound = s;
	switch (direction)
	{
	case right:
		m_direction = right;
		break;

	case left:
		m_direction = left;
		break;

	case up:
		m_direction = up;
		break;

	case down:
		m_direction = down;
		break;

	default:
		m_direction = down;
	}

	soundManager::preloadObjectSounds(sound);
}

void SlideObject::execute(WorldObject* object, float dt)
{
	object->getPhysicsComponent()->getPhysicsBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	object->getPhysicsComponent()->getPhysicsBody()->SetAngularVelocity(0.0f);
	switch (m_direction)
	{
	case right:
	{
		object->getPhysicsComponent()->getPhysicsBody()->ApplyForce(b2Vec2(150.0f,0.0f), object->getPhysicsComponent()->getPhysicsBody()->GetPosition());
	}
		break;
	case left:
	{
		object->getPhysicsComponent()->getPhysicsBody()->ApplyForce(b2Vec2(-150.0f, 0.0f), object->getPhysicsComponent()->getPhysicsBody()->GetPosition());
	}
		break;
	case up:
		break;

	case down:
		break;

	default:
		break;
	}

	if (sound != NULL)
		soundManager::playSound(sound);
}