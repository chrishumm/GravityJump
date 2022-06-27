#include "AchievementMenu.h"
#include "SceneFactory.h" 
#include <fstream> 
#include <sstream>


stringstream convert_to_value_a;
bool AchievementMenu::init() //first layer player will see
{
	glClearColor(0.0,0.0, 0.0, 0.0);

	CCLayerColor* Container = CCLayerColor::create();
	Container->setColor(ccc3(255, 0, 255));

	this->setTouchEnabled(true); //allows for touch input from the 
	return true;
}

void AchievementMenu::createGUI()
{

	CCPoint screensize = CCDirector::sharedDirector()->getWinSize(); //stores our sceen size
	//Now we reate our button, linking to our image and method we want to call when it's pressed
	pCloseItem = CCMenuItemImage::create("backButton.png", "backButton.png", this, menu_selector(AchievementMenu::backButton));
	//Now we create our label and position it
	upSprite = CCMenuItemImage::create("upSprite.png", "upSprite.png", this, menu_selector(AchievementMenu::upArrow));
	downSprite = CCMenuItemImage::create("downSprite.png", "downSprite.png", this, menu_selector(AchievementMenu::downArrow));
	leftSprite = CCMenuItemImage::create("leftSprite.png", "leftSprite.png", this, menu_selector(AchievementMenu::leftArrow));
	rightSprite = CCMenuItemImage::create("rightSprite.png", "rightSprite.png", this, menu_selector(AchievementMenu::rightArrow));

	upArrowMenu = CCMenu::create(upSprite, NULL);
	downArrowMenu = CCMenu::create(downSprite, NULL);
	leftArrowMenu = CCMenu::create(leftSprite, NULL);
	rightArrowMenu = CCMenu::create(rightSprite, NULL);

	upArrowMenu->setPosition(ccp(screensize.x * 0.5, 0.0f + 100.0f));
	downArrowMenu->setPosition(ccp(screensize.x * 0.5, screensize.y - 100.0f));
	leftArrowMenu->setPosition(ccp(-150.0f, 0.0f));
	rightArrowMenu->setPosition(ccp(500.0f, 0.0f));

	addChild(upArrowMenu, -100);
	addChild(downArrowMenu, -100);

	upSprite->setScale(rightArrowMenu->getScale() * 2);
	downSprite->setScale(rightArrowMenu->getScale() * 2);
	leftSprite->setScale(rightArrowMenu->getScale() * 2);
	rightSprite->setScale(rightArrowMenu->getScale() * 2);

	achievement_title = CCLabelTTF::create("Achievements!", "Impact", 32);
	achievement_title->setPosition(ccp(screensize.x*0.5, screensize.y - 200.0f));
	//achievement_title->setColor(ccc3(0, 102, 100));

	addChild(achievement_title);
	//We now convert our label to a menu label, adding a menu selector when it's pressed.

	pMenu = CCMenu::create(pCloseItem, NULL); //Now create a menu for our button earlier
	pMenu->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 80, 20)); //position

	loadAchievements();
	//We now combine our label to a menu. this is important if newer labels were added later.
	//titleMenu = CCMenu::create(startMenuLabel, startMenuLabel2, NULL);
	//titleMenu->alignItemsHorizontally(); //aligns our menu vertically
	//titleMenu->setPosition(screensize.x*0.5, screensize.y*0.5); //position in centre


	//	m_Warning_Label = CCLabelTTF::create("By playing this game you acknowledge that metrics may be recorded\nMetrics can be viewed and deleted in a seperate menu in-game", "Impact", 32);

	//m_Warning_Label->setPosition(ccp(screensize.x*0.5, screensize.y - 40));
	addChild(pMenu); //This adds this to our current running scene and displays
	//addChild(titleMenu);
	//addChild(m_Warning_Label);
	//	addChild(titleMenu);




}

bool AchievementMenu::loadAchievements()
{
	bool success = false;
	string tempo = CCFileUtils::sharedFileUtils()->getWritablePath() + "db.txt";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//m_achievement_manager->saveDb("/data/data/org.cocos2dx.application/tmpfile");
	success = m_achievement_manager->loadDb(tempo);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	success = m_achievement_manager->loadDb("db.txt");
#endif

	if (!success)
	{
		CCPoint screensize = CCDirector::sharedDirector()->getWinSize();
		CCLabelTTF* warningMessage = CCLabelTTF::create("NO ACH DATA FOUND", "fonts/04b_19.ttf", 30);

		warningMessage->setPosition(ccp(screensize.x*0.5, (screensize.y*0.5) - 30.0f));

		//warningMessage->setColor(ccc3(203, 102, 23));
		addChild(warningMessage);



		removeChild(upSprite);
		removeChild(downSprite);
		removeChild(leftSprite);
		removeChild(rightSprite);
		removeChild(deleteMetricsSprite);

		removeChild(upArrowMenu);
		removeChild(downArrowMenu);
		removeChild(leftArrowMenu);
		removeChild(rightArrowMenu);
		removeChild(deleteMetricsMenu);

		return false;
	}


	achievements_recieved = m_achievement_manager->getSizeofAchievements();
	int created_label = 0;

	for (int i = 0; i < achievements_recieved; i++)
	{

		string name = m_achievement_manager->getAchievementByName(i);
		if (name != "")
		{
			convert_to_value_a << i;
			string temp_s = convert_to_value_a.str();
			temp_s.append(". " + name);
			convert_to_value_a.str("");
			m_ach_name[i] = CCLabelTTF::create(temp_s.c_str(), "fonts/04b_19.ttf", 30);
			//m_ach_name[i]->setColor(ccc3(203, 102, 23));
			addChild(m_ach_name[i]);
			created_label++;
		}
	}
	CCPoint screensize = CCDirector::sharedDirector()->getWinSize();
	for (int i= 0; i < created_label; i++)
	{
		float offset = i * 50.0f;
		m_ach_name[i]->setPosition(ccp(400.0f, screensize.y*0.5 + offset));
	}
	return true;
}

void AchievementMenu::backButton(CCObject* startGameObject)
{
	CCScene* gameStart = NULL; //create a new levelScene
	gameStart = SceneFactory::createScene("MainMenu"); //Init the level scene
	gameStart->init();
	CCDirector::sharedDirector()->replaceScene(gameStart); //Replace menu scene with the new level
}

void AchievementMenu::upArrow(CCObject*)
{
	this->setPositionY(this->getPositionY() + 30);

	upSprite->setPositionY(upSprite->getPositionY() - 30);
	downSprite->setPositionY(downSprite->getPositionY() - 30);

	pCloseItem->setPositionY(pCloseItem->getPositionY() - 30);
	achievement_title->setPositionY(achievement_title->getPositionY() - 30);
}
void AchievementMenu::downArrow(CCObject*)
{
	this->setPositionY(this->getPositionY() - 30);

	upSprite->setPositionY(upSprite->getPositionY() + 30);
	downSprite->setPositionY(downSprite->getPositionY() + 30);

	pCloseItem->setPositionY(pCloseItem->getPositionY() + 30);
	achievement_title->setPositionY(achievement_title->getPositionY() + 30);
}
void AchievementMenu::rightArrow(CCObject*)
{
	this->setPositionX(this->getPositionX() - 30);

	upSprite->setPositionX(upSprite->getPositionX() + 30);
	downSprite->setPositionX(downSprite->getPositionX() + 30);
	leftSprite->setPositionX(leftSprite->getPositionX() + 30);
	rightSprite->setPositionX(rightSprite->getPositionX() + 30);
	pCloseItem->setPositionX(pCloseItem->getPositionX() + 30);
}
void AchievementMenu::leftArrow(CCObject*)
{
	this->setPositionX(this->getPositionX() + 30);

	upSprite->setPositionX(upSprite->getPositionX() - 30);
	downSprite->setPositionX(downSprite->getPositionX() - 30);
	leftSprite->setPositionX(leftSprite->getPositionX() - 30);
	rightSprite->setPositionX(rightSprite->getPositionX() - 30);
	pCloseItem->setPositionX(pCloseItem->getPositionX() - 30);
}