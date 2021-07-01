#include "LevelScene.h"
#include "LayerFactory.h"

bool LevelScene::init()
{
	CCScene::init(); //creates our scene

	glClearColor(1.0,1.0,1.0,1.0);
	m_added_layers = 0;
	CCDirector::sharedDirector()->getRunningScene(); 
		return true;
}

cocos2d::CCScene* LevelScene::scene()
{
	CCScene *scene = CCScene::create();
	return scene;
}

bool LevelScene::addLayers(CCLayer* newLayer)
{
	if(newLayer == NULL)
		return false;

	try
	{
		addChild(newLayer);
		current_layers_added[m_added_layers] = newLayer;
		m_added_layers++;
		return true;
	}
	catch(...)
	{
		return false;
	}
	return false;
}

bool LevelScene::addLayers(int count,CCLayer* newLayer[])
{
	for(int i = 0; i < count;i++)
	{
		if(newLayer[i] == NULL)
			return false;
		try
		{
			addChild(newLayer[i]);
		}
		catch(...)
		{
			return false;
		}
	}
	return true;
}

void LevelScene::menuCloseCallback(CCObject* pSender)
{
	for (int i = 0; i < m_added_layers; i++)
	{
		//current_layers_added[i]->deall
	}
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}