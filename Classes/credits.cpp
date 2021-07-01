#include "credits.h"
#include "SceneFactory.h"
bool Credits::init() //first layer player will see
{
	glClearColor(0.0, 0.0, 1.0, 1.0);
	this->setTouchEnabled(true); //allows for touch input from the 
	return true;
}

bool Credits::createCredits()
{
	CCPoint screensize = CCDirector::sharedDirector()->getWinSize(); //stores our sceen size
	//Now we reate our button, linking to our image and method we want to call when it's pressed
	CCMenuItemImage* pCloseItem = CCMenuItemImage::create("backButton.png", "backButton.png", this, menu_selector(Credits::backToGame));
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL); //Now create a menu for our button earlier
	pMenu->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 80, 20)); //position

	addChild(pMenu);
	programmer = CCLabelTTF::create("Programming by \n Christopher Humm     ", "Impact", 32);
	programmer->setPosition(ccp(0.0f, 0.0f));

	artist = CCLabelTTF::create("Art by \n Christopher Humm", "Impact", 32);
	artist->setPosition(ccp(0.0f, 0.0f));

	music = CCLabelTTF::create("Music by \n Mnargl\nChiptune Loop 29b - http://www.newgrounds.com/audio/listen/564964", "Impact", 32);
	music->setPosition(ccp(0.0f, 0.0f));

	programmer_m = CCMenuItemLabel::create(programmer);
	artist_m = CCMenuItemLabel::create(artist);
	music_m = CCMenuItemLabel::create(music);
	//We now convert our label to a menu label, adding a menu selector when it's pressed.

	creditsMenu = CCMenu::create(programmer_m, artist_m, music_m, NULL);
	creditsMenu->alignItemsVertically(); //aligns our menu vertically
	creditsMenu->setPosition(screensize.x*0.5, screensize.y*0.5); //position in centre
	creditsMenu->setColor(ccc3(240, 230, 103));
	static int menu_opened = 0;
	if (menu_opened == 0)
		m_metric_manager->createMetric(0, "Credits Menu Opened", &menu_opened, true);
	menu_opened++;

	addChild(creditsMenu);

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
void Credits::backToGame(CCObject* startGameObject)
{
	CCScene* gameStart = NULL; //create a new levelScene
	gameStart = SceneFactory::createScene("MainMenu"); //Init the level scene
	gameStart->init();
	CCDirector::sharedDirector()->replaceScene(gameStart); //Replace menu scene with the new level
}