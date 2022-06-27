#include "HelloWorldScene.h"
#include "SceneFactory.h"
USING_NS_CC;

CCScene* HelloWorld::scene()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene* pScene = SceneFactory::createScene("Consent");
    // run
    pDirector->runWithScene(pScene);

    return pScene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    return false;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
