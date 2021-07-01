#include "MainGame.h"
#include "debug/GLES-Render.h"
#include "debug/B2DebugDrawLayer.h"

USING_NS_CC;

float MainGame::xPTM = 1/300.0f;
float MainGame::xMTP = 300.0f;


cocos2d::CCScene* MainGame::scene()
{
	CCScene *scene = CCScene::create();

	MainGame *layer = MainGame::create();

	scene->addChild( layer );

	return scene;
}

void MainGame::didAccelerate(CCAcceleration* pAccelerationValue)
{
	char strBuff[92];

	if( pAccelerationValue )
		sprintf( strBuff, "x = %.4f\ny=%.4f\nz=%.4f", pAccelerationValue->x, pAccelerationValue->y, pAccelerationValue->z);

	mpLabelDebug->setString( strBuff );

	b2Vec2 gravity;
	gravity.Set( pAccelerationValue->x, pAccelerationValue->y );
	gravity.Normalize();
	gravity *= 5.0f;
	mWorld->SetGravity( gravity );
}

void MainGame::SetupPhysics( const CCSize &winSize )
{
	b2Vec2 gravity;
	gravity.Set( 0.0f, -10.0f );

	mWorld = new b2World(gravity);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set( 0.f, 0.f );

	b2Body* groundBody = mWorld->CreateBody( &groundBodyDef );

	b2EdgeShape edge;
	b2EdgeShape tSide;
	b2EdgeShape bSide;
	b2EdgeShape lSide;
	b2EdgeShape rSide;

	b2FixtureDef groundBoxDef;
	groundBoxDef.shape = &edge;
	groundBoxDef.restitution = 0.75f;

	edge.Set( b2Vec2( 0.0f, 0.0f), b2Vec2( winSize.width * xPTM, 0.0f) );
	groundBody->CreateFixture( &groundBoxDef );
	edge.Set( b2Vec2( 0.0f, winSize.height * xPTM ), b2Vec2( winSize.width * xPTM, winSize.height * xPTM ) );
	groundBody->CreateFixture( &groundBoxDef );

	edge.Set( b2Vec2( 0.f, 0.0f ), b2Vec2( 0.f, winSize.height * xPTM) );	
	groundBody->CreateFixture( &groundBoxDef );
	edge.Set( b2Vec2( winSize.width * xPTM, 0.0f ), b2Vec2( winSize.width* xPTM, winSize.height * xPTM) );	
	groundBody->CreateFixture( &groundBoxDef );

	//addChild(B2DebugDrawLayer::create( mWorld, xMTP), 9999);
   
}

void MainGame::DropBall( const CCPoint& position )
{
	CCSprite* hat = CCSprite::create( "sprites/bikewheel.png" );
	hat->setPosition( position );
	addChild(hat);

	b2BodyDef ballDef;
	ballDef.type = b2_dynamicBody;
	ballDef.position.Set( position.x * xPTM , position.y * xPTM );
	ballDef.userData = hat;
		
	b2CircleShape ballShape;
	ballShape.m_radius = 64.f * xPTM;
	
	
	b2Body* ballBody = mWorld->CreateBody( &ballDef );
	ballBody->ApplyLinearImpulse( b2Vec2( 0.f, 2.f), ballDef.position );
	 
	ballBody->CreateFixture( &ballShape, 1.0f );
}

void MainGame::DropHat( const CCPoint& position )
{
	CCSprite* hat = CCSprite::create( "sprites/hat.png" );
	hat->setPosition( position );
	addChild(hat);


	b2PolygonShape hatBase;
    hatBase.SetAsBox(120.f * xPTM * 0.5f, 20 * xPTM * 0.5f);
	
    b2PolygonShape hatTop;
    hatTop.SetAsBox( 75 * xPTM * 0.5f, 50.0f * xPTM * 0.5f);


	b2BodyDef bd;
    bd.type = b2_dynamicBody;
	bd.position.Set( position.x * xPTM, position.y * xPTM);
	bd.userData = hat;

    b2Body* body = mWorld->CreateBody(&bd);
    body->CreateFixture(&hatBase, 2.0f);
    body->CreateFixture(&hatTop, 2.0f);

}

void MainGame::Tick( float dt )
{
//	mWorld->DrawDebugData();
	mWorld->Step( dt, 8, 1 );
	for( b2Body* b = mWorld->GetBodyList(); b != NULL; b = b->GetNext() )
	{
		if( b->GetUserData() )
		{
			CCSprite *ball = (CCSprite*)b->GetUserData();
			b2Vec2 physicsPosition = b->GetPosition();
			ball->setPosition( ccp( b->GetPosition().x * xMTP, b->GetPosition().y * xMTP ));
			ball->setRotation( CC_RADIANS_TO_DEGREES( -b->GetAngle() ) );

		}
	}

}

void MainGame::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch* touchEvent = (CCTouch*)pTouches->anyObject();

	//DropBall( touchEvent->getLocation() );
	DropHat( touchEvent->getLocation() );

	


}

bool MainGame::init()
{
	if( !CCLayer::init() )
		return false;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	mpLabelDebug = CCLabelTTF::create( "DEBUG", "Impact", 16 );
	mpLabelDebug->setAnchorPoint( ccp( 1.0f, 1.0f ) );
	mpLabelDebug->setPosition( ccp(visibleSize.width, visibleSize.height ) );
	addChild( mpLabelDebug );


	setTouchEnabled( true );

	//Hello World Text
	CCLabelTTF* pLabel = CCLabelTTF::create( "Hello Pete", "Arial", 24 );

	if( pLabel )
	{
		CCPoint labelPosition = origin + ccp( visibleSize.width/4, visibleSize.height/2 );
		pLabel->setPosition( labelPosition );
	}

	addChild( pLabel, 1 );

	//Adding a sprite

	CCSprite* pBackgroundImage = CCSprite::create("bg.png");

	if( pBackgroundImage )
	{
		pBackgroundImage->setScale( visibleSize.width / pBackgroundImage->getContentSize().width );
		CCPoint centreOfScreen = ccp( visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y );
		pBackgroundImage->setPosition( centreOfScreen );
		addChild( pBackgroundImage, 0 );
	}

	SetupPhysics( visibleSize );
	//DropBall(visibleSize * 0.5f);

	schedule( schedule_selector(MainGame::Tick) );



	return true;


}

void MainGame::onEnter()
{
	CCLayer::onEnter();

	setAccelerometerEnabled( true );
	//setAccelerometerInterval( 1.0f );
}