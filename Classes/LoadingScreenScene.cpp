#include "LoadingScreenScene.h"
#include "MenuScene.h"
#include "SceneFactory.h"

CCScene* LoadingScreenScene::createScene()
{
	CCScene* scene = CCScene::create();

	// 'layer' is an autorelease object
	LoadingScreenScene* loadingLayer = LoadingScreenScene::create();
	loadingLayer->setTag(11);
	scene->addChild(dynamic_cast<CCLayer*>(loadingLayer));

	return scene;
}

bool LoadingScreenScene::init()
{

	CCPoint visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	sprite = CCSprite::create("loading.png");

	// position the sprite on the center of the screen
	sprite->setPosition(ccp(visibleSize.x *0.5, visibleSize.y *0.5));

	// add the sprite as a child to this layer
	this->addChild(dynamic_cast<CCSprite*>(sprite), 0);

	return true;
}
void LoadingScreenScene::addNextScene(char* next_scene)
{
	m_next_scene = next_scene;
}
void LoadingScreenScene::onEnter()
{
	CCLayer::onEnter();
	this->scheduleOnce(schedule_selector(LoadingScreenScene::finishSplash), 1.0f);
}
static bool first_run = false;

void LoadingScreenScene::finishSplash(float dt) 
{
	removeChild(sprite);
	removeChildByTag(11);

	CCDirector::sharedDirector()->pushScene(SceneFactory::createScene("Level"));

	
	//CCDirector::sharedDirector()->replaceScene(SceneFactory::createScene("Level"));
}