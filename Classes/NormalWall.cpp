#include "NormalWall.h"

b2Body* NormalWall::createWallPhysics(float x, float y,float xEnd, float yEnd,b2World* m_world)
{
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
CCSprite* NormalWall::createWallSprite(float x, float y)
{
	CCSprite* newWall = CCSprite::create("wall.png");
	newWall->setPosition(ccp(x,y));

	return newWall;
}

void NormalWall::effect(WorldObject* test)
{

}