#ifndef __MAINGAME_H__
#define __MAINGAME_H__

#include "cocos2d.h"
#include <Box2D/Box2D.h> 

USING_NS_CC;

class Settings;

class MainGame : public cocos2d::CCLayer
{
public:
	static float xPTM;
	static float xMTP;
	
	virtual bool init();
	virtual void onEnter();

    static cocos2d::CCScene* scene();	

	CREATE_FUNC(MainGame);

	void Tick( float dt );

	virtual void didAccelerate(CCAcceleration* pAccelerationValue);

protected:
	b2World* mWorld;

	CCLabelTTF* mpLabelDebug;

	void SetupPhysics( const CCSize& winSize );
	void DropBall( const CCPoint& startPoint );
	void DropHat( const CCPoint& startPoint );

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);

	class GLESDebugDraw* mpDebugDraw;
	
};

#endif __MAINGAME_H__