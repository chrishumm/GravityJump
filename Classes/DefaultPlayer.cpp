#include "DefaultPlayer.h"

DefaultPlayer::DefaultPlayer()
{
}

DefaultPlayer::DefaultPlayer(CCLayer* currentLayer, b2World* currentWorld) : WorldObject(currentLayer, currentWorld)
{
	CCSprite* m_player = CCSprite::create("default.png");
	m_objectRendering->addNewSprite(m_player, 2, 1, 47, 84);
	m_object_name = "Player";

	setDefaultPlayerPosition();
	createPlayerPhysicsBody();
}

DefaultPlayer::DefaultPlayer(CCLayer* currentLayer, b2World* currentWorld, PhysicsComponent* pcom, RenderingComponent* rcom) : WorldObject(currentLayer, currentWorld, pcom, rcom)
{
	m_objectPhysics = pcom;
	m_objectRendering = rcom;
	m_object_name = "Player";

	CCSprite* m_player = CCSprite::create("default.png");
	m_objectRendering->addNewSprite(m_player,2,1,47,84);

	
	setDefaultPlayerPosition();
	createPlayerPhysicsBody();
}

void DefaultPlayer::setDefaultPlayerPosition()
{
	setX(100.0f);
	setY(m_layerHeight * 0.5);
	m_objectRendering->getSprite()->setPosition(ccp(getX(),getY()));
	m_objectRendering->getSprite()->setZOrder(199);
	m_objectRendering->setMultipleSprites(false);
}

void DefaultPlayer::createPlayerPhysicsBody()
{
		b2BodyDef ballDef; //create new body def
		ballDef.type = b2_dynamicBody; //allow body to move
		ballDef.position.Set(getBox2DX(),getBox2DY()); //set position
		//create new player class for user data

		b2CircleShape ballShape; //create shape for our ball
		ballShape.m_radius = 45.0f * xPTM; //define radius

		b2FixtureDef bouncy_ball; // define fixture
		bouncy_ball.shape = &ballShape;

		//create body
		b2Body* ballBody = m_objectPhysics->getCurrentWorld()->CreateBody(&ballDef);
		ballBody->CreateFixture(&bouncy_ball); //create fixture
		//send our player object to hud class.
		m_objectPhysics->addPhysicsBody(ballBody);
		//m_current_player->setBody(ballBody);
}