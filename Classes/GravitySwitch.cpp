#include "GravitySwitch.h"

bool GravitySwitch::sounds_preloaded = false;

GravitySwitch::GravitySwitch(b2World* w)
{
	sound = NULL;
	world = w;
}

GravitySwitch::GravitySwitch(b2World* w, char* s)
{
	sound = s;
	world = w;

	soundManager::preloadObjectSounds(sound);
}

void GravitySwitch::execute(WorldObject* object, float dt)
{
	if (object->getPhysicsComponent()->getPhysicsBody()->GetLinearVelocity().y != 0.0f && object->getState() != 1)
		return;

	b2Vec2 m_gravity = world->GetGravity();

	if (m_gravity.y > 0.0f)
		object->getRenderingComponent()->getSprite()->setFlipY(false);
	else
		object->getRenderingComponent()->getSprite()->setFlipY(true);

	object->getPhysicsComponent()->getPhysicsBody()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	object->getPhysicsComponent()->getPhysicsBody()->SetAngularVelocity(0.0f);
	m_gravity.y *= -1;

	world->SetGravity(m_gravity);

	if (sound!= NULL)
		soundManager::playSound(sound);
}