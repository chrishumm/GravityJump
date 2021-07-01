#include "LevelOne.h"
#include "LevelChunkFactory.h"
#include "MovingPhysicsComponent.h"
#include "LayerFactory.h"
#include "UIGUI.h"
#include "UIMessage.h"
#include "command.h"
#include "soundManager.h"
#define Player levelObjects[0]
//#ifdef _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
//#define new DEBUG_NEW
//#endif
static bool run_once = false; //Have to do because cocos2dx auto-creates parameter for CCobject
bool LevelOne::init()
{
	m_state = initialising;
	m_layer_width = CCDirector::sharedDirector()->getWinSize().width;
	m_layer_height = CCDirector::sharedDirector()->getWinSize().height;
	m_inputHandler = new inputHandler();
	run_once = false;
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	createWorldPhysics();
	levelObjects.push_back(new DefaultPlayer(this, m_world));
	//_CrtDumpMemoryLeaks();
	collision_handler = new collision(m_world);
	//_CrtDumpMemoryLeaks();
	//GUILayer = (UIGUI
	LayerFactory::createLayer("GUI");
	//addChild(GUILayer, 1111);
	//GUILayer->createGUI(this);
	deltaTime = 0.0f;
	createLevelGeometry();
	setTouchEnabled(true);
	schedule(schedule_selector(LevelOne::gameLoop));
	schedule(schedule_selector(LevelOne::updateLayer));
	m_state = game_loop;
	return true;
}

void LevelOne::gameLoop(float dt)
{
	float fixedTimeStep = 1 / 60.0;
	float vphysicsAccuracy = 1.0;
	float pphysicsAccuracy = 1.0;

	m_world->Step(fixedTimeStep, vphysicsAccuracy, pphysicsAccuracy);
	logic(dt);
	//GUILayer->updateGUI(dt);
	//render();
}

void LevelOne::logic(float dt)
{
	if (Player->getActive() == false)
	{
		schedule(schedule_selector(LevelOne::endGame));
	}

//	UIMessage::displayUIMessage(m_layer_width*0.5, m_layer_height*0.5, 0.0f, 0.0f, "This is a test", 0, this);

	for (size_t i = 0; i < levelObjects.size(); i++)
	{
		if (levelObjects[i]->getActive() == true)
		{
			collision_handler->updateCollision(levelObjects);
			vector<b2Vec2> currentPos = levelObjects[i]->getPhysicsComponent()->updatePhysics(dt);

			levelObjects[i]->getRenderingComponent()->updateRendering(currentPos,dt);

			//levelObjects[i]->setX(levelObjects[i]->getRenderingComponent()->getSprite()->getPositionX());
			//levelObjects[i]->setY(levelObjects[i]->getRenderingComponent()->getSprite()->getPositionY());
		}
	}
	Player->getPhysicsComponent()->getPhysicsBody()->ApplyTorque(0.0f);
}

void LevelOne::render()
{
}

void LevelOne::createWorldPhysics()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT);
	m_gravity_y = -5.0f;
	m_worldGravity.Set(0.0f, m_gravity_y); //set default crazy
	m_worldGravity *= 5.0f;
	m_gravity_y = m_worldGravity.y;
	m_world = new b2World(m_worldGravity); //add gravity to world
	//_CrtDumpMemoryLeaks();
	B2DebugDrawLayer* mDebugLayer = B2DebugDrawLayer::create(m_world, WorldObject::xMTP);
	addChild(mDebugLayer, 9999);// debug, do not include on build
}

void LevelOne::createLevelGeometry()
{
	levelObjects.push_back(LevelChunkFactory::createLevelChunk("Level Boundaries", this, m_world));
	levelObjects.back()->setActive(false);

	levelObjects.push_back(LevelChunkFactory::createLevelChunk("Default", this, m_world));
	m_active_chunks.push_back(levelObjects.back());

	levelObjects.push_back(LevelChunkFactory::createLevelChunk("Default 1", this, m_world));
	m_active_chunks.push_back(levelObjects.back());

	m_active_chunks[1]->getPhysicsComponent()->saveInitialPosition();
	m_active_chunks[0]->getPhysicsComponent()->saveInitialPosition(m_active_chunks[1]->getPhysicsComponent()->getPhysicsXPositions(), m_active_chunks[1]->getPhysicsComponent()->getPhysicsYPositions());

	m_active_chunks[0]->getRenderingComponent()->saveInitialPosition();
	m_active_chunks[1]->getRenderingComponent()->saveInitialPosition();

	m_inactive_chunks.push_back(LevelChunkFactory::createLevelChunk("Default 2", this, m_world));
	m_inactive_chunks.push_back(LevelChunkFactory::createLevelChunk("Default 3", this, m_world));
	m_inactive_chunks.push_back(LevelChunkFactory::createLevelChunk("Default 4", this, m_world));
	m_inactive_chunks.push_back(LevelChunkFactory::createLevelChunk("Default 5", this, m_world));
	m_inactive_chunks.push_back(LevelChunkFactory::createLevelChunk("Default 6", this, m_world));
	m_inactive_chunks.push_back(LevelChunkFactory::createLevelChunk("Default 7", this, m_world));
	m_inactive_chunks.push_back(LevelChunkFactory::createLevelChunk("Default 8", this, m_world));
	//m_inactive_chunks.push_back(LevelChunkFactory::createLevelChunk("Default 4", this, m_world));
	for (size_t i = 0; i < m_inactive_chunks.size(); i++)
	{
		levelObjects.push_back(m_inactive_chunks[i]);
		levelObjects.back()->setActive(false);
		m_inactive_chunks[i]->getPhysicsComponent()->saveInitialPosition(m_active_chunks[1]->getPhysicsComponent()->getPhysicsXPositions(), m_active_chunks[1]->getPhysicsComponent()->getPhysicsYPositions());
	}
}

void LevelOne::BeginContact(b2Contact* contact) //overriden contacts
{
}
void LevelOne::EndContact(b2Contact* contact) // for player > platforms
{
}
void LevelOne::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}
void LevelOne::ccTouchesBegan(CCSet * ptouches, cocos2d::CCEvent * pevent)
{
	m_inputHandler->onClickPositions(ptouches);
}

void LevelOne::ccTouchesEnded(CCSet * ptouches, cocos2d::CCEvent * pevent)
{
	command* input_message = m_inputHandler->handleInput(ptouches, m_world, deltaTime);
	if (input_message)
		input_message->execute(Player, deltaTime);

	delete input_message;
	input_message = NULL;
	
}


void LevelOne::updateLayer(float dt)
{
	deltaTime = dt;
	int state = Player->getState();
	if (run_once == false)
	{
		int temp = Player->getState();
		if ((m_metric_manager->createMetric(5, "Time Before Player Dies", &dt, true, true) == true) &&
			(m_metric_manager->createMetric(6, "Powerups Collected Per Session", &state, true, true) == true))
				run_once = true;
				
		soundManager::playBackgroundMusic("track1.mp3");
	}
	


	m_metric_manager->updateMetrics();
	b2Vec2 posMov;
	vector<b2Body*> bodies;
	for (size_t i = 0; i < m_active_chunks.size(); i++)
	{
		if (m_active_chunks[i]->getPhysicsComponent()->isMultipleBodiesAttached() == true)
		{
			bodies = m_active_chunks[i]->getPhysicsComponent()->getPhysicsBodies();
			for (size_t x = 0; x < bodies.size(); x++)
			{
				posMov = bodies[x]->GetPosition();
				posMov.x -= (1.5f * dt);
				bodies[x]->SetTransform(posMov, 0.0f);

				if (bodies[0]->GetPosition().x * WorldObject::xMTP <= -m_layer_width)
					m_active_chunks[i]->setActive(false);
			}
			/*
			m_active_chunks[i]->setActive(false);
			m_active_chunks[i]->getRenderingComponent()->removeSprite();
			m_active_chunks[i]->getPhysicsComponent()->removePhysics();
			delete m_active_chunks[i]; //deallocate the memory of the object in vector
			m_active_chunks[i] = NULL; //
			m_active_chunks.erase(m_active_chunks.begin() + i);
			*/

			//m_active_chunks[i]->getRenderingComponent()->loadInitialPosition();
			//m_active_chunks[i]->getPhysicsComponent()->loadInitialPosition();

			if (m_active_chunks[i]->getActive() == false)
			{
				int newChunk = rand() % 2;
				if (newChunk == 1)
				{
					WorldObject* temp = m_active_chunks[i];
					m_active_chunks[i] = m_inactive_chunks[i];
					m_inactive_chunks[i] = temp;
				}
				else
				{
					LevelChunk* reset_chunks = static_cast<LevelChunk*>(m_active_chunks[i]);
					reset_chunks->resetObjects();
					m_active_chunks[i]->getPhysicsComponent()->loadPosition((m_layer_width * 2)*WorldObject::xPTM);
				}
				m_active_chunks[i]->setActive(true);

				collision_handler->updateCollision(levelObjects);
			}

		}
		else
		{
			posMov = m_active_chunks[i]->getPhysicsComponent()->getPhysicsBody()->GetPosition();
			posMov.x -= (0.5f * dt);
			m_active_chunks[i]->getPhysicsComponent()->getPhysicsBody()->SetTransform(posMov, 0.0f);
		}
	}
}

void LevelOne::endGame(float dt)
{
	UIMessage::displayUIMessage(m_layer_width*0.5, (m_layer_height*0.5) + 200.0f, 0.0f, 0.0f, "You died!", 0, this);
	unschedule(schedule_selector(LevelOne::gameLoop));
	unschedule(schedule_selector(LevelOne::updateLayer));
	
	if (m_state != initialising)
	{
		soundManager::stopAllSounds();
		soundManager::playSound("gameover.mp3");
		m_state = game_end;
	}


}

bool LevelOne::deallocateMemory()
{
	soundManager::stopAllSounds();
	unschedule(schedule_selector(LevelOne::endGame));
	unschedule(schedule_selector(LevelOne::gameLoop));
	unschedule(schedule_selector(LevelOne::updateLayer));
	run_once = false;
	string temp_loc = CCFileUtils::sharedFileUtils()->getWritablePath();
	delete m_inputHandler;
	m_inputHandler = NULL;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		m_metric_manager->saveCurrentMetrics(temp_loc);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	m_metric_manager->saveCurrentMetrics("C:/");
#endif

//	m_metric_manager->saveCurrentMetrics();
	m_metric_manager->reset_all_metrics_data(); // temp data

	try
	{
		for (size_t i = 0; i < levelObjects.size(); i++)
		{
			if (levelObjects[i] != NULL)
			{
				delete levelObjects[i];
				levelObjects[i] = NULL;
			}
		}
		for (size_t i = 0; i < m_inactive_chunks.size(); i++)
		{
			if (m_inactive_chunks[i] != NULL)
			{
				m_inactive_chunks[i] = NULL;
			}
		}

		delete collision_handler;
		collision_handler = NULL;
	}
	catch (...)
	{
		return false;
	}
	delete m_world;
	m_world = NULL;

	return true;
}

int LevelOne::getPlayerState()
{
	return Player->getState();
}

void LevelOne::setPlayerState(int state)
{
	Player->setState(state,5);
}

void LevelOne::setPlayerState(int state, float ttl)
{
	Player->setState(state, ttl);
}

float LevelOne::getPlayerStateDuration()
{
	return Player->getStateDuration();
}

void LevelOne::setPlayerStateDuration(float t)
{
	Player->setStateDuration(t);
}