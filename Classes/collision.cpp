#include "collision.h"
#include "BadWall.h"
#include "InfiniteGravitySwitching.h"
#include "DestructionBlockPowerup.h"
#include "WorldObject.h"
#define PlayerState m_current_level_objects[0]->getState()
#define Player m_current_level_objects[0]

bool run_once_t = false;

collision::collision(b2World* world)
{
	powerups_collected = 0.0;
	blocked_destroyed = 0.0f;
	m_world = world;
	m_world->SetContactListener(this);
	soundManager::preloadObjectSounds("break.wav");
	collision_metrics = new MetricManager();
	run_once_t = false;
}

collision::~collision()
{
	string temp_loc = CCFileUtils::sharedFileUtils()->getWritablePath();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	collision_metrics->saveCurrentMetrics(temp_loc);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	collision_metrics->saveCurrentMetrics("C:/");
#endif

	//	m_metric_manager->saveCurrentMetrics();
	collision_metrics->reset_all_metrics_data(); // temp data

	delete collision_metrics;
	collision_metrics = NULL;
}

void collision::updateCollision(vector<WorldObject*> worldobjects)
{
	m_current_level_objects = worldobjects;
	for(size_t i = 1; i < m_current_level_objects.size();i ++)
	{
		LevelChunk* current_piece = static_cast<LevelChunk*>(m_current_level_objects[i]);
		for(int x = 0; x < current_piece->getNumPieces();x++)
		{
			if(current_piece->levelTypePieces[x] == "Delete")
			{
				current_piece->levelPhysicsPieces[x]->SetActive(false);
			}
		}
	}

	collision_metrics->updateMetrics();
}

void collision::BeginContact(b2Contact* contact) //overriden contacts
{
}
void collision::EndContact(b2Contact* contact) // for player > platforms
{
}
void collision::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
		b2Fixture* fixtureA = contact->GetFixtureA(); //get colliding
		b2Fixture* fixtureB = contact->GetFixtureB();//fixtures

		b2Fixture* player = contact->GetFixtureB();
    //check if the fixture is a one way platform and also which fixture of the two is it.
	for(size_t i = 0; i < m_current_level_objects.size();i++) //loop through all
	{
		if (m_current_level_objects[i]->getPhysicsComponent()->isMultipleBodiesAttached() == true)
		{
			vector<b2Body*> chunk_bodies = m_current_level_objects[i]->getPhysicsComponent()->getPhysicsBodies();
			for(size_t x = 0; x < chunk_bodies.size();x++)
			{
				if(chunk_bodies[x]->GetFixtureList() == fixtureA)
				{
					LevelChunk* current_piece = static_cast<LevelChunk*>(m_current_level_objects[i]);
					char* name = current_piece->levelTypePieces[x];
					if (PlayerState == 0 || PlayerState == 1)
					{
						if (applyPowerup(name, current_piece, &x))
							return;

						if (name == "Bad Wall" || name == "Bad Wall Essential")
						{
							BadWall::effect(Player);
							return;
						}
					}
					if (PlayerState == 2)
					{
						if (applyPowerup(name, current_piece, &x))
							return;

						if (current_piece->levelTypePieces[x] != "Essential" && current_piece->levelTypePieces[x] != "Bad Wall Essential")
						{
							current_piece->levelTypePieces[x] = "Delete";
							soundManager::playSound("break.wav");
						}
						else if (current_piece->levelTypePieces[x] == "Bad Wall Essential")
							BadWall::effect(Player);
						else{}

						return;
					}
				}
			}
		}
	}
}



bool collision::applyPowerup(char* name, LevelChunk* current_piece, size_t* body_no)
{
	bool return_type;
	if (run_once_t == false)
	{
		collision_metrics->createMetric(7, "Powerups Collected", &powerups_collected, false, true);
		collision_metrics->createMetric(8, "Blocks Destroyed", &blocked_destroyed, false, true);
		run_once_t = true;
	}

	if (name == "Infinite Gravity")
	{
		InfiniteGravitySwitching::effect(Player);
		current_piece->levelTypePieces[*body_no] = "Delete";
		return_type = true;
	}
	else if (name == "Destruction Block")
	{
		blocked_destroyed++;
		DestructionBlockPowerup::effect(Player);
		current_piece->levelTypePieces[*body_no] = "Delete";
		return_type = true;
	}
	else
		return_type = false;

	if (return_type)
		powerups_collected++;

	return return_type;
}