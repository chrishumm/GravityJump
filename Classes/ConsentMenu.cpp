#include "ConsentMenu.h"
#include "SceneFactory.h" 

bool ConsentMenu::init() //first layer player will see
{
	glClearColor(1.0, 0.0, 1.0, 1.0);
	this->setTouchEnabled(true); //allows for touch input from the 
	return true;
}

bool ConsentMenu::createUIConsent()
{
	CCPoint screensize = CCDirector::sharedDirector()->getWinSize(); //stores our sceen size
	//Now we reate our button, linking to our image and method we want to call when it's pressed
	CCMenuItemImage* pCloseItem = CCMenuItemImage::create("closeunselected.png", "closeunselected.png", this, menu_selector(ConsentMenu::closeGame));
	//Now we create our label and position it
	CCLabelTTF* startGameLabel = CCLabelTTF::create("I Agree!     ", "Impact", 32);
	startGameLabel->setPosition(ccp(0.0f, 0.0f));

	CCLabelTTF* startGameLabel2 = CCLabelTTF::create("I Disagree!     ", "Impact", 32);
	startGameLabel2->setPosition(ccp(0.0f, 0.0f));

	//We now convert our label to a menu label, adding a menu selector when it's pressed.

	CCMenuItemLabel* startMenuLabel = CCMenuItemLabel::create(startGameLabel, this, menu_selector(ConsentMenu::startGame));
	startGameLabel->setColor(ccc3(255, 255, 255));

	CCMenuItemLabel* startMenuLabel2 = CCMenuItemLabel::create(startGameLabel2, this, menu_selector(ConsentMenu::closeGame));
	startGameLabel2->setColor(ccc3(255, 255, 255));

	//We now combine our label to a menu. this is important if newer labels were added later.
	titleMenu = CCMenu::create(startMenuLabel, startMenuLabel2, NULL);
	titleMenu->alignItemsHorizontally(); //aligns our menu vertically
	titleMenu->setPosition(screensize.x*0.5, screensize.y*0.5); //position in centre

	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL); //Now create a menu for our button earlier
	pMenu->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20)); //position

	m_Warning_Label = CCLabelTTF::create("By playing this game you acknowledge that metrics may be recorded\nMetrics can be viewed and deleted in a seperate menu in-game", "Impact", 32);

	m_Warning_Label->setPosition(ccp(screensize.x*0.5, screensize.y - 40));
	addChild(pMenu); //This adds this to our current running scene and displays
	//addChild(titleMenu);
	addChild(m_Warning_Label);
	addChild(titleMenu);

	m_metric_manager->createMetric(0,"ScreenSizeTest", &screensize.x,true);

	string temp_loc = CCFileUtils::sharedFileUtils()->getWritablePath();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	m_metric_manager->saveCurrentMetrics(temp_loc);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	m_metric_manager->saveCurrentMetrics("c:/");
#endif

	if (m_metric_manager->loadMetricStoredData("C:/metricdb.txt"))
	{
		m_metric_manager->getNumOfUniqueMetrics(false);
		vector<float*> retrievedNumer = m_metric_manager->getAllFloatingValue(5, false);
		retrievedNumer = m_metric_manager->sortSize(retrievedNumer);
		const char* name = m_metric_manager->getName(5, false);
	}
	return true;
}
void ConsentMenu::startGame(CCObject* startGameObject)
{
	CCScene* gameStart = NULL; //create a new levelScene
	gameStart = SceneFactory::createScene("MainMenu"); //Init the level scene
	gameStart->init();
	CCDirector::sharedDirector()->replaceScene(gameStart); //Replace menu scene with the new level
}

void ConsentMenu::closeGame(CCObject* startGameObject)
{
	CCDirector::sharedDirector()->end();
}