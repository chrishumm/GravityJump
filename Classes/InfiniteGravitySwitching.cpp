#include "InfiniteGravitySwitching.h"

b2Body* InfiniteGravitySwitching::createWallPhysics(float x, float y,float xEnd, float yEnd,b2World* m_world)
{
	/*
	b2BodyDef ballDef; //create new body def
	ballDef.type = b2_staticBody; //allow body to move
	ballDef.position.Set(x,y); //set position

	b2Body* groundBody = m_world->CreateBody( &ballDef );
	//add body  body and shaqpe to our ground

	b2CircleShape ballShape; //create shape for our ball
	ballShape.m_radius = 45.0f * WorldObject::xPTM; //define radius

	b2FixtureDef bouncy_ball; // define fixture
	bouncy_ball.shape = &ballShape;

	//now we set out boundaries on our edges
	groundBody->CreateFixture( &bouncy_ball );

	return groundBody;
	*/

	b2BodyDef groundBodyDef; //create information for our ground
	groundBodyDef.position.Set(x, y ); //set position
	groundBodyDef.type = b2_staticBody; //static, it cannot move

	b2Body* groundBody = m_world->CreateBody( &groundBodyDef );
	//add body  body and shaqpe to our ground

	b2PolygonShape  newrect; //shapedef

	b2FixtureDef platform;

	platform.restitution = 1.0f; //make them bouncy
	newrect.SetAsBox(xEnd,yEnd); //grab fixed sizes
	platform.shape = &newrect; //add shape

	b2FixtureDef ground; //define information for our fixture
	ground.shape = &newrect; //add edge shape to fixture

	//now we set out boundaries on our edges
	groundBody->CreateFixture( &ground );

	return groundBody;
}


CCSprite* InfiniteGravitySwitching::createWallSprite(float x, float y)
{
	CCSprite* newWall = CCSprite::create("wall.png");
	newWall->setPosition(ccp(x,y));

	return newWall;
}

void InfiniteGravitySwitching::effect(WorldObject* test)
{
	test->setState(1,5);
}