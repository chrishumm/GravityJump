#include "jump.h"

bool jump::sounds_preloaded = false;

jump::jump(int direction, int gravity)
{
	sound = NULL;
	m_gravity = gravity;
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

jump::jump(int direction, int gravity, char* s)
{
	sound = s;
	m_gravity = gravity;
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

	if (jump::sounds_preloaded == false)
	{
		soundManager::preloadObjectSounds(sound);
		jump::sounds_preloaded = true;
	}

}

void jump::execute(WorldObject* object, float dt)
{
	if (object == NULL || (object->getPhysicsComponent()->getPhysicsBody()->GetLinearVelocity().y != 0.0f && object->getState() != 1))
		return;

	object->getPhysicsComponent()->getPhysicsBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	object->getPhysicsComponent()->getPhysicsBody()->SetAngularVelocity(0.0f);

	float direction_speed = 360.0f;
	float gravity_speed = 150.0f;


	switch (m_direction)
	{
		case right:
		{
			if (m_gravity == normal)
				object->getPhysicsComponent()->getPhysicsBody()->ApplyForce(b2Vec2(gravity_speed, -direction_speed), object->getPhysicsComponent()->getPhysicsBody()->GetPosition());
			else
				object->getPhysicsComponent()->getPhysicsBody()->ApplyForce(b2Vec2(gravity_speed, direction_speed), object->getPhysicsComponent()->getPhysicsBody()->GetPosition());
		}
		break;
		case left:
		{
			if (m_gravity == normal)
				object->getPhysicsComponent()->getPhysicsBody()->ApplyForce(b2Vec2(-gravity_speed, -direction_speed), object->getPhysicsComponent()->getPhysicsBody()->GetPosition());
			else
				object->getPhysicsComponent()->getPhysicsBody()->ApplyForce(b2Vec2(-gravity_speed, direction_speed), object->getPhysicsComponent()->getPhysicsBody()->GetPosition());
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