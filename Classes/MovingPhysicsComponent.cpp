#include "MovingPhysicsComponent.h"

MovingPhysicsComponent::MovingPhysicsComponent()
{
	m_physicsBody = NULL;
}

MovingPhysicsComponent::MovingPhysicsComponent(b2World* world)
{
	m_currentWorld = world;
	multiple_bodies = false;

	moved_by = 0;
	max_moved = 1;
	direction = false;
}

vector<b2Vec2> MovingPhysicsComponent::updatePhysics(float dt)
{
	vector<b2Vec2> physicsPosition;
	if (multiple_bodies == false)
	{
		physicsPosition.push_back(m_physicsBody->GetPosition());
		if (direction == false)
		{
			physicsPosition[0].y += (1 * dt);
			moved_by += (dt);
			if (moved_by >= max_moved)
				direction = true;
		}
		else
		{
			physicsPosition[0].y -= (1 * dt);
			moved_by -= (dt);
			if (moved_by <= 0)
				direction = false;
		}
		m_physicsBody->SetGravityScale(0.0f);
		m_physicsBody->SetTransform(physicsPosition[0], 0.0f);

		return physicsPosition;
	}
	else
	{
		for (size_t i = 0; i < m_physicsBodies.size(); i++)
		{
			physicsPosition.push_back(m_physicsBodies[i]->GetPosition());
			if(m_physicsBodies[i]->GetUserData() != NULL)
			{
				if (direction == false)
				{
					physicsPosition[i].y += (1 * dt);
					moved_by += (dt);
					if (moved_by >= max_moved)
						direction = true;
				}
				else
				{
					physicsPosition[i].y -= (1 * dt);
					moved_by -= (dt);
					if (moved_by <= 0)
						direction = false;
				}
			}
			m_physicsBodies[i]->SetTransform(physicsPosition[i], 0.0f);
		}
		return physicsPosition;
	}
}