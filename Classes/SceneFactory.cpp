#include "SceneFactory.h"
#include "LevelScene.h"
#include "MenuScene.h"
#include "LoadingScreenScene.h"
#include "LayerFactory.h"
#include "LevelLayer.h"
#include "UIGUI.h"

cocos2d::CCScene* SceneFactory::scene()
{
	CCScene *scene = CCScene::create(); //creates our scene.
	return scene;
}

CCScene* SceneFactory::createScene(char* name)
{

	if(name == "Level")
	{
		LevelScene* newCreatedScene = LevelScene::create();
		CCLayer* levelLayer = LayerFactory::createLayer("Level");
		UIGUI* GUI = static_cast<UIGUI*>(LayerFactory::createLayer("GUI"));
		newCreatedScene->addLayers(levelLayer);
		newCreatedScene->addLayers(GUI);
		GUI->createGUI(levelLayer);
		return newCreatedScene;
	}
	else if (name == "MainMenu")
	{
		MenuScene* newCreatedScene = MenuScene::create();
		CCLayer* levelLayer = LayerFactory::createLayer("MainMenu");
		newCreatedScene->addLayers(levelLayer);
		return newCreatedScene;
	}
	else if (name == "Consent")
	{
		MenuScene* newCreatedScene = MenuScene::create();
		CCLayer* levelLayer = LayerFactory::createLayer("Consent");
		newCreatedScene->addLayers(levelLayer);
		return newCreatedScene;
	}
	else if (name == "Metrics")
	{
		MenuScene* newCreatedScene = MenuScene::create();
		CCLayer* levelLayer = LayerFactory::createLayer("Metrics");
		newCreatedScene->addLayers(levelLayer);
		return newCreatedScene;
	}
	else if (name == "Achievements")
	{
		MenuScene* newCreatedScene = MenuScene::create();
		CCLayer* levelLayer = LayerFactory::createLayer("Achievements");
		newCreatedScene->addLayers(levelLayer);
		return newCreatedScene;
	}
	else if (name == "Credits")
	{
		MenuScene* newCreatedScene = MenuScene::create();
		CCLayer* levelLayer = LayerFactory::createLayer("Credits");
		newCreatedScene->addLayers(levelLayer);
		return newCreatedScene;
	}
	else if (name == "LevelTest")
	{
		MenuScene* newCreatedScene = MenuScene::create();
		CCLayer* levelLayer = LayerFactory::createLayer("LevelTest");
		newCreatedScene->addLayers(levelLayer);
		return newCreatedScene;
	}
	else if (name == "Loading")
	{
		LoadingScreenScene* newCreatedScene = LoadingScreenScene::create();
		return reinterpret_cast<CCScene*>(newCreatedScene);
	}
	else{}

	CCScene* newCreatedScene = CCScene::create();

	return newCreatedScene;
}

CCScene* SceneFactory::createScene(char* name,CCLayer* defaultLayers[], int count)
{
	if(name == "Level")
	{
		LevelScene* newCreatedScene = LevelScene::create();
		//newCreatedScene->addLayers(NULL);
		for(int i = 0; i < count;i++)
		{
			newCreatedScene->addLayers(defaultLayers[i]);
		}
		return newCreatedScene;
	}
	else{}

	CCScene* newCreatedScene = CCScene::create();

	return newCreatedScene;
}

void SceneFactory::createScene(char* name,CCScene* test)
{
	test->release();
	if (name == "Level")
	{
		LevelScene* newCreatedScene = LevelScene::create();
		CCLayer* levelLayer = LayerFactory::createLayer("Level");
		UIGUI* GUI = static_cast<UIGUI*>(LayerFactory::createLayer("GUI"));
		newCreatedScene->addLayers(levelLayer);
		newCreatedScene->addLayers(GUI);
		GUI->createGUI(levelLayer);
		CCDirector::sharedDirector()->pushScene(newCreatedScene);
	}
}
/*Manual Scene Creation....// Causes memory leak issues with autorelease
CCScene* SceneFactory::buildScene(CCScene* newCreatedScene)
{
    if (newCreatedScene && newCreatedScene->init()) 
    { 
        newCreatedScene->autorelease(); 
        return newCreatedScene; 
    } 
    else 
    { 
        delete newCreatedScene; 
        newCreatedScene = NULL; 
        return NULL; 
    }
}*/

