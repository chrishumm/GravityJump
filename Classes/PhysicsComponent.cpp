#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent()
{
	m_physicsBody = NULL;
}

PhysicsComponent::PhysicsComponent(b2World* world)
{
	m_currentWorld = world;
	multiple_bodies = false;
}

vector<b2Vec2> PhysicsComponent::updatePhysics(float dt)
{
	vector<b2Vec2> physicsPosition;
	if(multiple_bodies == false)
	{
		physicsPosition.push_back(m_physicsBody->GetPosition());
		m_physicsBody->SetTransform(physicsPosition[0],0.0f);
		float velo = m_physicsBody->GetAngularVelocity();
		return physicsPosition;
	}
	else
	{
		for(size_t i = 0; i < m_physicsBodies.size();i++)
		{
			physicsPosition.push_back(m_physicsBodies[i]->GetPosition());
			m_physicsBodies[i]->SetTransform(physicsPosition[i],0.0f);
		}
		return physicsPosition;
	}
}

void PhysicsComponent::addPhysicsBody(b2Body* body)
{
	m_physicsBody = body;
}

void PhysicsComponent::removePhysics()
{
	for(size_t i = 0; i < m_physicsBodies.size();i++)
	{
		m_physicsBodies[i]->DestroyFixture(m_physicsBodies[i]->GetFixtureList());
		m_currentWorld->DestroyBody(m_physicsBodies[i]);
	}
}

void PhysicsComponent::addPhysicsBody(b2Body* body, bool bodies)
{
	multiple_bodies = true;
	this->multiple_bodies = bodies;
	m_physicsBodies.push_back(body);
}

b2Body* PhysicsComponent::getPhysicsBody()
{
	return m_physicsBody;
}

vector<b2Body*> PhysicsComponent::getPhysicsBodies()
{
	return m_physicsBodies;
}

b2World* PhysicsComponent::getCurrentWorld()
{
	return m_currentWorld;
}

bool PhysicsComponent::isMultipleBodiesAttached()
{
	if(this == NULL)
		return false;

	if(multiple_bodies == true)
		return true;
	else
		return false;
}

void PhysicsComponent::saveInitialPosition()
{
	for(size_t i = 0; i < m_physicsBodies.size();i++)
	{
		original_x.push_back(m_physicsBodies[i]->GetPosition().x);
		original_y.push_back(m_physicsBodies[i]->GetPosition().y);
	}
}

void PhysicsComponent::saveInitialPosition(vector<float> xpos, vector<float> ypos)
{
	for(size_t i = 0; i < xpos.size();i++)
	{
		original_x.push_back(xpos[i]);
		original_y.push_back(ypos[i]);
	}
}

void PhysicsComponent::loadPosition(float offset)
{
	for(size_t i = 0; i < m_physicsBodies.size();i++)
	{
		m_physicsBodies[i]->SetTransform(b2Vec2(m_physicsBodies[i]->GetPosition().x+offset,m_physicsBodies[i]->GetPosition().y),0.0f);
		if (m_physicsBodies[i]->IsActive() == false)
		{
			m_physicsBodies[i]->SetActive(true);
		}
	}
}

vector<float> PhysicsComponent::getPhysicsXPositions()
{
	return original_x;
}

vector<float> PhysicsComponent::getPhysicsYPositions()
{
	return original_y;
}

void PhysicsComponent::setAsleep(bool sleeping)
{
	if(multiple_bodies == false)
	{
		m_physicsBody->SetAwake(sleeping);
	}
	else
	{
		for(size_t i = 0; i < m_physicsBodies.size();i++)
		{
			m_physicsBodies[i]->SetAwake(sleeping);
		}
	}
}