#include "MainMenu.h"
#include "levelScene.h" //for 
#include "SceneFactory.h" 
#include "GUI\CCScrollView\CCScrollView.h"

using namespace extension;

bool MainMenu::init() //first layer player will see
{
	soundManager::preloadBg("track1.mp3");
	this->setTouchEnabled(true); //allows for touch input from the 
	CCPoint screensize = CCDirector::sharedDirector()->getWinSize(); //stores our sceen size
	//Now we reate our button, linking to our image and method we want to call when it's pressed
	CCMenuItemImage* pCloseItem = CCMenuItemImage::create("closeunselected.png", "closeunselected.png", this, menu_selector(MainMenu::muteGame));
	//Now we create our label and position it
	CCLabelTTF* startGameLabel = CCLabelTTF::create("Begin Game!     ", "Impact", 32);
	startGameLabel->setPosition(ccp(0.0f, 0.0f));

	CCLabelTTF* startGameLabel2 = CCLabelTTF::create("Exit Game!     ", "Impact", 32);
	startGameLabel2->setPosition(ccp(0.0f, 0.0f));

	CCLabelTTF* startGameLabel3 = CCLabelTTF::create("View Achievements!     ", "Impact", 32);
	startGameLabel3->setPosition(ccp(0.0f, 0.0f));

	CCLabelTTF* startGameLabel4 = CCLabelTTF::create("View Metrics!     ", "Impact", 32);
	startGameLabel4->setPosition(ccp(0.0f, 0.0f));

	CCLabelTTF* startGameLabel5 = CCLabelTTF::create("View Credits!     ", "Impact", 32);
	startGameLabel5->setPosition(ccp(0.0f, 0.0f));
	//We now convert our label to a menu label, adding a menu selector when it's pressed.

	CCMenuItemLabel* startMenuLabel = CCMenuItemLabel::create(startGameLabel, this, menu_selector(MainMenu::startGame));
	startGameLabel->setColor(ccc3(0, 255, 0));

	CCMenuItemLabel* startMenuLabel2 = CCMenuItemLabel::create(startGameLabel2, this, menu_selector(MainMenu::exitGame));
	startGameLabel2->setColor(ccc3(0, 255, 0));

	CCMenuItemLabel* startMenuLabel3 = CCMenuItemLabel::create(startGameLabel3, this, menu_selector(MainMenu::viewAch));
	startGameLabel3->setColor(ccc3(0, 255, 0));

	CCMenuItemLabel* startMenuLabel4 = CCMenuItemLabel::create(startGameLabel4, this, menu_selector(MainMenu::viewMetrics));
	startGameLabel4->setColor(ccc3(0, 255, 0));

	CCMenuItemLabel* startMenuLabel5 = CCMenuItemLabel::create(startGameLabel5, this, menu_selector(MainMenu::viewCredits));
	startGameLabel5->setColor(ccc3(0, 255, 0));

	//We now combine our label to a menu. this is important if newer labels were added later.
	titleMenu = CCMenu::create(startMenuLabel, startMenuLabel2, startMenuLabel3, startMenuLabel4, startMenuLabel5, NULL);
	titleMenu->alignItemsHorizontally(); //aligns our menu vertically
	titleMenu->setPosition(screensize.x*0.5, screensize.y*0.5); //position in centre

	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL); //Now create a menu for our button earlier
	pMenu->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20)); //position

	m_gameLabelName = CCLabelTTF::create("Gravity Jump", "Impact", 32);
	m_gameLabelName->setColor(ccc3(200, 0, 0));
	m_gameLabelName->setPosition(ccp(screensize.x*0.5, screensize.y - 40));
	CCJumpBy* jump_screen_jump = CCJumpBy::create(5000.0f, m_gameLabelName->getPosition(), 10.0f, 10000);
	addChild(pMenu); //This adds this to our current running scene and displays
	//addChild(titleMenu);
	addChild(m_gameLabelName);
	
	m_gameLabelName->runAction(jump_screen_jump);
	CCLayerColor* Container = CCLayerColor::create();
	Container->setColor(ccc3(255, 0, 255));

	Container->setPosition(this->getPosition());
	Container->setScaleX(Container->getScaleX() * 2);
	Container->addChild(titleMenu);
	
	CCScrollView* scrollView = CCScrollView::create(screensize, Container);
	scrollView->setViewSize(ccp(screensize.x*0.9, screensize.y));

	scrollView->setBounceable(false);
	scrollView->setDirection(kCCScrollViewDirectionHorizontal);

	scrollView->setPosition(CCPointZero);
	addChild(scrollView);

	loadingScreen = CCSprite::create("loading.png");
	loadingScreen->setOpacity(0.0f);
	loadingScreen->setPosition(ccp(screensize.x * 0.5, screensize.y*0.5));
	addChild(loadingScreen);

	return true;
}

void MainMenu::ccTouchesMoved(CCSet* pTouches, CCEvent* pEvent)
{
	CCSetIterator itr;

	for (itr = pTouches->begin(); itr != pTouches->end(); itr++)
	{

	}
}

void MainMenu::ccTouchesBegan(CCSet * ptouches, CCEvent * pevent) //default touch
{																	//still included if we need
	screensize = CCDirector::sharedDirector()->getWinSize();	//to use later
	CCSetIterator itr;											//Overrided from CCLayer
	CCTouch* touch;

	for (itr = ptouches->begin(); itr != ptouches->end(); itr++)
	{
		touch = static_cast<CCTouch*>(*itr);
		CCPoint LeftorRight = touch->getLocation();
	}
}

void MainMenu::closeGame(CCObject* Closeobject)
{
	CCDirector::sharedDirector()->end(); //closes our game
}

void MainMenu::startGame(CCObject* startGameObject)
{
	loadingScreen->setOpacity(254.0f);
	this->update(0);
	LoadingScreenScene* newScene = reinterpret_cast<LoadingScreenScene*>(LoadingScreenScene::createScene());
	newScene->addNextScene("Level");

	CCDirector::sharedDirector()->pushScene((CCScene*)newScene);
}

void MainMenu::exitGame(CCObject* startGameObject)
{
	CCDirector::sharedDirector()->end(); //Replace menu scene with the new level
}

void MainMenu::viewAch(CCObject* startGameObject)
{
	CCScene* gameStart = NULL; //create a new levelScene
	gameStart = SceneFactory::createScene("Achievements"); //Init the level scene
	gameStart->init();
	CCDirector::sharedDirector()->replaceScene(gameStart); //Replace menu scene with the new level
}
void MainMenu::viewMetrics(CCObject* startGameObject)
{
	CCScene* gameStart = NULL; //create a new levelScene
	gameStart = SceneFactory::createScene("Metrics"); //Init the level scene
	gameStart->init();
	CCDirector::sharedDirector()->replaceScene(gameStart); //Replace menu scene with the new level
}

void MainMenu::viewCredits(CCObject* startGameObject)
{
	CCScene* gameStart = NULL; //create a new levelScene
	gameStart = SceneFactory::createScene("Credits"); //Init the level scene
	gameStart->init();
	CCDirector::sharedDirector()->replaceScene(gameStart); //Replace menu scene with the new level
}

void MainMenu::muteGame(CCObject*)
{
	soundManager::disableSounds();
}