#include "LevelOne.h"
#include "LevelChunkFactory.h"
#include "LayerFactory.h"
#include "UIGUI.h"
#include "UIMessage.h"

bool LevelOne::init()
{
	m_layer_width = CCDirector::sharedDirector()->getWinSize().width;
	m_layer_height = CCDirector::sharedDirector()->getWinSize().height;
	createWorldPhysics();
	levelObjects.push_back(new DefaultPlayer(this,m_world));
	collision_handler = new collision(m_world);
	GUILayer = (UIGUI*)LayerFactory::createLayer("GUI");
	addChild(GUILayer,1111);
	GUILayer->createGUI(this);

	createLevelGeometry();
	setTouchEnabled(true);
	schedule( schedule_selector(LevelOne::gameLoop) );
	schedule( schedule_selector(LevelOne::updateLayer) );
	return true;
}

void LevelOne::gameLoop(float dt)
{
	m_world->Step( dt, 8, 1 ); 
	logic();
	GUILayer->updateGUI(dt);
	//render();
}

void LevelOne::logic()
{
	if(levelObjects[0]->getActive() == false)
	{
		schedule( schedule_selector(LevelOne::endGame) );
	}

	UIMessage::displayUIMessage(m_layer_width*0.5,m_layer_height*0.5,0.0f,0.0f,"This is a test",0,this);

	for(int i = 0; i < levelObjects.size(); i++)
	{
		if(levelObjects[i]->getActive() == true)
		{
			collision_handler->updateCollision(levelObjects);
			vector<b2Vec2> currentPos = levelObjects[i]->getPhysicsComponent()->updatePhysics();

			levelObjects[i]->getRenderingComponent()->updateRendering(currentPos);

			//levelObjects[i]->setX(levelObjects[i]->getRenderingComponent()->getSprite()->getPositionX());
			//levelObjects[i]->setY(levelObjects[i]->getRenderingComponent()->getSprite()->getPositionY());
		}
	}
	levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->ApplyTorque(0.0f);


}

void LevelOne::render()
{
	for(int i = 0; i < levelObjects.size(); i++)
	{
		//levelObjects[i]->getRenderingComponent()->updateRendering();
	}
}

void LevelOne::createWorldPhysics()
{
	m_gravity_y = -5.0f;
	m_worldGravity.Set( 0.0f, m_gravity_y ); //set default crazy
	m_worldGravity *= 5.0f;
	m_gravity_y = m_worldGravity.y;
	m_world = new b2World(m_worldGravity); //add gravity to world

	B2DebugDrawLayer* mDebugLayer = B2DebugDrawLayer::create(m_world,WorldObject::xMTP);
	addChild(mDebugLayer,9999);// debug, do not include on build
}

void LevelOne::createLevelGeometry()
{
	levelObjects.push_back(LevelChunkFactory::createLevelChunk("Default",this,m_world));
	m_active_chunks.push_back(levelObjects.back());

	levelObjects.push_back(LevelChunkFactory::createLevelChunk("Default",this,m_world,(LevelChunk*)levelObjects.back()));
	m_active_chunks.push_back(levelObjects.back());

	m_active_chunks[0]->getPhysicsComponent()->saveInitialPosition();
	m_active_chunks[0]->getPhysicsComponent()->saveInitialPosition();

	m_active_chunks[1]->getRenderingComponent()->saveInitialPosition();
	m_active_chunks[1]->getRenderingComponent()->saveInitialPosition();
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
void LevelOne::ccTouchesBegan(CCSet * ptouches, cocos2d::CCEvent * pevent )
{
	CCSetIterator itr;
	for(itr = ptouches->begin(); itr != ptouches->end(); itr++)
	{
		CCTouch* touch = (CCTouch*) *itr;
		x_original_pos = touch->getLocation().x;
	}
}

void LevelOne::ccTouchesEnded(CCSet * ptouches, cocos2d::CCEvent * pevent )
{
	if(levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->GetLinearVelocity().y != 0.0f)
		return;

	CCSetIterator itr;
	for(itr = ptouches->begin(); itr != ptouches->end(); itr++)
	{
		CCTouch* touch = (CCTouch*) *itr;
		x_current_pos = touch->getLocation().x;
	}
	levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->GetLinearVelocity().x == 0.0f;
	if(x_original_pos < (x_current_pos - 10))
	{
		levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->SetLinearVelocity(b2Vec2(0.0f,0.0f));
		levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->SetAngularVelocity(0.0f);
		if(m_world->GetGravity().y < 0.0f)
			levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->ApplyForce(b2Vec2(150.0f,360.0f),levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->GetPosition());
		else
			levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->ApplyForce(b2Vec2(150.0f,-360.0f),levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->GetPosition());
	}
	else if(x_original_pos > (x_current_pos + 10))
	{
		levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->SetLinearVelocity(b2Vec2(0.0f,0.0f));
		levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->SetAngularVelocity(0.0f);
		if(m_world->GetGravity().y < 0.0f)
			levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->ApplyForce(b2Vec2(-150.0f,360.0f),levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->GetPosition());
		else
			levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->ApplyForce(b2Vec2(-150.0f,-360.0f),levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->GetPosition());
	}
	else
	{
			if(m_gravity_y > 0.0f)
				levelObjects[0]->getRenderingComponent()->getSprite()->setFlipY(false);
			else
				levelObjects[0]->getRenderingComponent()->getSprite()->setFlipY(true);

			levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->SetLinearVelocity(b2Vec2(0.0f,0.0f));
			levelObjects[0]->getPhysicsComponent()->getPhysicsBody()->SetAngularVelocity(0.0f);
			m_gravity_y *= -1;
			m_worldGravity.Set( 0.0f, m_gravity_y);
			m_world->SetGravity(m_worldGravity);
	}
}

void LevelOne::updateLayer(float dt)
{
		b2Vec2 posMov;
		vector<b2Body*> bodies;
	for(int i = 0; i < m_active_chunks.size();i++)
	{
		if(m_active_chunks[i]->getPhysicsComponent()->isMultipleBodiesAttached() == true)
		{
			bodies = m_active_chunks[i]->getPhysicsComponent()->getPhysicsBodies();
			for(int x = 0; x < bodies.size();x++)
			{
				posMov = bodies[x]->GetPosition();
				posMov.x -= (0.5f * dt);
				bodies[x]->SetTransform(posMov,0.0f);

				if(bodies[0]->GetPosition().x * WorldObject::xMTP <= -m_layer_width)
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

				if(m_active_chunks[i]->getActive() == false)
				{
					m_active_chunks[i]->setActive(true);
					m_active_chunks[i]->getPhysicsComponent()->loadPosition(m_layer_width*WorldObject::xPTM);

					collision_handler->updateCollision(levelObjects);
					int zz = this->getChildrenCount();
				}
					int zxx = this->getChildrenCount();
		}
		else
		{
			posMov = m_active_chunks[i]->getPhysicsComponent()->getPhysicsBody()->GetPosition();
			posMov.x -= (0.5f * dt);
			m_active_chunks[i]->getPhysicsComponent()->getPhysicsBody()->SetTransform(posMov,0.0f);
		}
	}
}

void LevelOne::endGame(float dt)
{
	UIMessage::displayUIMessage(m_layer_width*0.5,(m_layer_height*0.5) + 200.0f,0.0f,0.0f,"You died!",0,this);
	unschedule( schedule_selector(LevelOne::gameLoop) );
	unschedule( schedule_selector(LevelOne::updateLayer) );
}

bool LevelOne::deallocateMemory()
{
	unschedule( schedule_selector(LevelOne::gameLoop) );
	unschedule( schedule_selector(LevelOne::updateLayer) );
	
	try
	{
		for(int i = 0;i < levelObjects.size();i++)
		{
			if(levelObjects[i] != NULL)
			{
				delete levelObjects[i];
				levelObjects[i] = NULL;
			}
		}

		delete collision_handler;
		collision_handler = NULL;
	}
	catch(...)
	{
		return false;
	}

	return true;
}