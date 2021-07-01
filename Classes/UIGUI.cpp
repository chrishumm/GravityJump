#include "UIGUI.h"
#include "SceneFactory.h"
#include "UIMessage.h"
#include "LoadingScreenScene.h"
stringstream displayAsString;
const int UIGUI::default_message_ttl = 5;

bool UIGUI::init()
{
	soundManager::preloadObjectSounds("gameover.mp3");
	setTouchEnabled(true);
	return true;
}

void UIGUI::createGUI(CCLayer* currentLevel)
{
	m_currentLevel = dynamic_cast<LevelLayer*>(currentLevel);

	screensize = CCDirector::sharedDirector()->getWinSize(); //get current window size
	CCMenuItemImage* pPause = CCMenuItemImage::create("Pause.png", "Pause.png", this, menu_selector(UIGUI::pauseGUI));
	CCLabelTTF* pause = CCLabelTTF::create("Pause:", "Impact", 28);

	CCMenuItemImage* pRestart = CCMenuItemImage::create("Restart.png", "Restart.png", this, menu_selector(UIGUI::restartLevel));
	CCLabelTTF* srestart = CCLabelTTF::create("Restart:", "Impact", 28);
	////////powerups/////////////////////////
	CCMenuItemImage* pPowerup = CCMenuItemImage::create("powerup.png", "Restart.png");
	m_current_powerup = CCSprite::create("nopowerup.png");
	//CCLabelTTF* srestart = CCLabelTTF::create("Restart:", "Impact", 28);

	CCMenu* pMenu = CCMenu::create(pPause, NULL); //Adds our pause button
	pMenu->setPosition(520.0f, screensize.y - 25.0f); //set at the top of the screen

	CCMenu* pRestarmt = CCMenu::create(pRestart, NULL); //Adds our pause button
	pRestarmt->setPosition(360.0f, screensize.y - 25.0f); //set at the top of the screen
	addChild(pRestarmt);

	addChild(pPowerup);
	addChild(m_current_powerup);
	pPowerup->setPosition(100.0f, screensize.y - 25.0f);
	m_current_powerup->setPosition(ccp(200.0f, screensize.y - 25.0f));
	m_current_powerup->setTag(normal);

	CCDirector::sharedDirector()->setAlphaBlending(true);
	CCSprite* hud_layer_background = CCSprite::create("hud_layer_background.png");

	CCSprite* ArrowSwipe = CCSprite::create("Arrow.png");
	ArrowSwipe->setPosition(ccp(screensize.x*0.5, 100.0f));
	addChild(ArrowSwipe);

	darken = CCSprite::create("darken.png");
	darken->setPosition(ccp(screensize.x*0.5, screensize.y*0.5));
	darken->setOpacity(0.0f);
	addChild(darken);
	hud_layer_background->setPosition(ccp(0.0f, screensize.y - 25.0f)); //set at the top of the screen
	addChild(hud_layer_background, -10);
	addChild(pMenu, 0); //adds our pause button to scene
	addChild(pause);
	addChild(srestart);

	m_current_time_label = CCLabelTTF::create("", "fonts/04b_19.ttf", 38);
	m_current_time_label->setColor(ccc3(203, 102, 23));


	m_font_shadow = CCLabelTTF::create("", "fonts/04b_19.ttf", 37.5);

	addChild(m_current_time_label);
	addChild(m_font_shadow); //Add our current height, based from stored string


	m_paused = false;
	m_current_time_label->setPosition(ccp(500.0f, 500.0f));
	m_font_shadow->setPosition(ccp(500.0f, 500.0f));

	schedule(schedule_selector(UIGUI::updateGUI), 1);
	total_elapsed_time = 0;
	msg = "";

	m_ttl = 5.0f;
	message_displaying = false;


	m_achievement_manager->createAchievement("Survived 10 Seconds!", &total_elapsed_time, 10.0f);
	m_achievement_manager->createAchievement("Survived 15 Seconds, you're good!", &total_elapsed_time, 15.0f);
	/*
	if (m_achievement_manager->loadDb("c:/db.txt") == false)
	{
	m_achievement_manager->addCValue(0, &total_elapsed_time);
	m_achievement_manager->addCValue(1, &total_elapsed_time);
	}
	else
	{
	m_achievement_manager->createAchievement("Survived 10 Seconds!", &total_elapsed_time, 10.0f);
	m_achievement_manager->createAchievement("Survived 15 Seconds, you're good!", &total_elapsed_time, 15.0f);
	}
	*/
}

void UIGUI::updateGUI(float time)
{
	switch (m_currentLevel->getState())
	{
	case game_loop:
	{
		time = 1;
		total_elapsed_time += time;
		displayAsString << total_elapsed_time; //rounds up to nearest whole value, stores.
		string temp_display = "Highest Score: " + displayAsString.str() + " Seconds!"; //Create new string
		displayAsString.str(""); //clear stringstream
		m_current_time_label->setString(temp_display.c_str());
		m_font_shadow->setString(temp_display.c_str());

		if (message_displaying == false)
			msg = m_achievement_manager->update_all_achievements();

		if (msg != "")
		{
			UIMessage::displayUIMessage(screensize.x - 400.0f, screensize.y * 0.5, 0, 0, msg.c_str(), m_ttl, this, 400);
			message_displaying = true;
		}

		if (message_displaying == true)
		{
			m_ttl--;
			if (m_ttl <= 0.0f)
			{
				soundManager::playSound("break.wav");
				m_ttl = default_message_ttl;
				msg = "";
				m_achievement_manager->setUpdateFalse(false);
				message_displaying = false;
				UIMessage::removeMessageID(400, this);
			}
		}
		updatePlayerGUI(time); //Default UI is drawn, now we update player specific UI
	}
		break;
	case game_end:
	{
		unschedule(schedule_selector(UIGUI::updateGUI));
		showDeathScreen();
		string tempo = CCFileUtils::sharedFileUtils()->getWritablePath() + "db.txt";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//m_achievement_manager->saveDb("/data/data/org.cocos2dx.application/tmpfile");
		m_achievement_manager->saveDb(tempo);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		m_achievement_manager->saveDb("C:/");
#endif
	}
		break;
	default:
	{}
		break;
	}
}

void UIGUI::updatePlayerGUI(float time)
{
	powerup_duration = m_currentLevel->getPlayerStateDuration();
	switch (m_currentLevel->getPlayerState())
	{
	case normal:
	{
		if (m_current_powerup->getTag() != normal)
		{
			m_current_powerup->setTexture(CCTextureCache::sharedTextureCache()->addImage("nopowerup.png"));
			m_current_powerup->setTag(normal);
		}
	}
		break;
	case infinite:
	{
		if (m_current_powerup->getTag() != infinite)
		{
			powerup_duration = m_currentLevel->getPlayerStateDuration();
			m_current_powerup->setTexture(CCTextureCache::sharedTextureCache()->addImage("InfiniteGravity.png"));
			m_current_powerup->setTag(infinite);
		}
	}
		break;
	case invincible:
	{
		if (m_current_powerup->getTag() != invincible)
		{
			powerup_duration = m_currentLevel->getPlayerStateDuration();
			m_current_powerup->setTexture(CCTextureCache::sharedTextureCache()->addImage("invincible.png"));
			m_current_powerup->setTag(invincible);
		}
	}
		break;
	default:
		break;
	}


	if (m_currentLevel->getPlayerState() != normal)
	{
		if (powerup_duration > 0.0f)
			m_currentLevel->setPlayerStateDuration(m_currentLevel->getPlayerStateDuration() - time);
		else
			m_currentLevel->setPlayerState(normal);
	}
}

void UIGUI::pauseGUI(CCObject* selector)
{
	removeChild(darken);
	darken = CCSprite::create("darken.png");
	darken->setPosition(ccp(screensize.x*0.5, screensize.y*0.5));
	darken->setOpacity(60.0f);

	if (m_paused == false) //Are we paused?
	{
		m_paused = true; //No, set to pause
		CCDirector::sharedDirector()->pause(); //pauses scene
		addChild(darken, -999);
	}
	else //Yes
	{
		m_paused = false; //We're now not paused
		removeChild(darken);
		CCDirector::sharedDirector()->resume(); //resume our scene
	}
}

void UIGUI::restartLevel(CCObject* selector)
{

	int levelNumber = m_currentLevel->getLevelNumber(); // add number for next scene
	if (m_currentLevel->deallocateMemory() == true)
	{
		LoadingScreenScene* newScene = reinterpret_cast<LoadingScreenScene*>(LoadingScreenScene::createScene());
		newScene->addNextScene("Level");

		CCDirector::sharedDirector()->replaceScene((CCScene*)newScene);
	}
	//	if (m_currentLevel->deallocateMemory() == true)
	//	{
	//	CCScene* test = CCDirector::sharedDirector()->getRunningScene();
	//	test->removeChild(m_currentLevel);
	//delete m_currentLevel;
	//	m_currentLevel = NULL;
	//CCDirector::sharedDirector()->end();
	//	}
}

void UIGUI::returnToMenu(CCObject* selector)
{
	m_loading = CCLabelTTF::create("Currently Loading!", "fonts/04b_19.ttf", 32);
	m_loading->setColor(ccc3(203, 102, 23));
	m_loading->setPosition(ccp(500.0f, 400.0f));
	addChild(m_loading);
	if (m_currentLevel->deallocateMemory() == true)
	{
		CCScene* MainMenuScene = SceneFactory::createScene("MainMenu");
		removeChild(m_loading);
		CCDirector::sharedDirector()->replaceScene(MainMenuScene);
	}
}

void UIGUI::closeGame(CCObject* selector)
{
	//
}
//////////Input Events//////////////
void UIGUI::ccTouchesBegan(CCSet * ptouches, cocos2d::CCEvent * pevent)
{

}
void UIGUI::ccTouchesEnded(CCSet * ptouches, cocos2d::CCEvent * pevent)
{

}

void UIGUI::addAchievementManager(AchievementManager* ac)
{
	m_achievement_manager = ac;
}

void UIGUI::addMetricsManager(MetricManager* ac)
{
	m_metric_manager = ac;
}

void UIGUI::showDeathScreen()
{
	MetricManager* level_metrics;
	level_metrics = m_currentLevel->getMetricManager();

	CCPoint screensize = CCDirector::sharedDirector()->getWinSize();

	m_font_shadow->setOpacity(0);
	m_current_time_label->setOpacity(0);
	m_current_time_label->setPosition(ccp(0.0f, screensize.y * 0.5));
	m_font_shadow->setPosition(ccp(0.0f, screensize.y * 0.5));
	////////////////////Creating Actions for animating///////////////////////////////////////
	CCFadeTo* setOpacity = CCFadeTo::create(2.0f, 255);
	CCFadeTo* setOpacity2 = CCFadeTo::create(2.0f, 255);
	CCMoveTo* moveScreen = CCMoveTo::create(0.7f, ccp(screensize.x*0.5, screensize.y * 0.5));
	CCSpawn* combinedScreen = CCSpawn::create(setOpacity, moveScreen, NULL);
	////////////////////////////////////////////////////////////////////////////////////////
	m_font_shadow->runAction(combinedScreen);
	m_font_shadow->setZOrder(10);
	m_current_time_label->setZOrder(10);
	m_current_time_label->runAction(combinedScreen);

	float temp_score = 0.0f;
	temp_score = level_metrics->getFloatingValue(5, true);
	displayAsString << temp_score;
	string temp_msg = displayAsString.str();
	string message = "You have scored! " + temp_msg;
	m_current_time_label->setString(message.c_str());

	setTouchEnabled(true);
	//////////////////////////Setting Buttons/////////////////////////////////////////////
	CCLabelTTF* playAgain = CCLabelTTF::create("Again?", "fonts/04b_19.ttf", 32);
	CCLabelTTF* mainScreen = CCLabelTTF::create("Exit?", "fonts/04b_19.ttf", 32);

	CCMenuItemLabel* startMenuLabel = CCMenuItemLabel::create(playAgain, this, menu_selector(UIGUI::restartLevel));
	CCMenuItemLabel* startMenuLabelExit = CCMenuItemLabel::create(mainScreen, this, menu_selector(UIGUI::returnToMenu));

	CCMenu* titleMenu = CCMenu::create(startMenuLabel, startMenuLabelExit, NULL);
	titleMenu->alignItemsHorizontallyWithPadding(100.0f);
	titleMenu->setPosition((screensize.x*0.5), (screensize.y*0.5) - 50.0f); //position in centre
	titleMenu->setOpacity(0);

	titleMenu->runAction(setOpacity2);
	///////////////////////Background for End Screen///////////////////////////////////
	CCSprite* endScreen = CCSprite::create("endscreen.png");
	endScreen->setPosition(ccp(screensize.x*0.5, 0.0f));
	endScreen->setOpacity(0);

	CCFadeTo* setOpacity3 = CCFadeTo::create(2.0f, 255);
	CCMoveTo* moveScreen3 = CCMoveTo::create(0.7f, ccp(screensize.x*0.5, screensize.y* 0.5));
	CCSpawn* combinedScreen3 = CCSpawn::create(setOpacity3, moveScreen3, NULL);


	endScreen->runAction(combinedScreen3);
	////////////////////////////////////////////////////////////////////////////////////
	CCSprite* buttonBackground1 = CCSprite::create("endButtons.png");
	buttonBackground1->setPosition(ccp(screensize.x*0.5, 0.0f));
	buttonBackground1->setOpacity(0);

	CCFadeTo* setOpacity4 = CCFadeTo::create(2.0f, 255);
	CCMoveTo* moveScreen4 = CCMoveTo::create(0.7f, ccp(titleMenu->getPositionX() + 100.0f, titleMenu->getPositionY()));
	CCSpawn* combinedScreen4 = CCSpawn::create(setOpacity4, moveScreen4, NULL);

	buttonBackground1->runAction(combinedScreen4);
	///////////////////////////////////////////////////////////////////////////////////
	CCSprite* buttonBackground2 = CCSprite::create("endButtons.png");
	buttonBackground2->setPosition(ccp(screensize.x*0.5, 0.0f));
	buttonBackground2->setOpacity(0);
	buttonBackground2->setColor(ccc3(254.0f, 254.0f, 254.0f));
	CCFadeTo* setOpacity5 = CCFadeTo::create(2.0f, 255);
	CCMoveTo* moveScreen5 = CCMoveTo::create(0.7f, ccp(titleMenu->getPositionX() - 100.0f, titleMenu->getPositionY()));
	CCSpawn* combinedScreen5 = CCSpawn::create(setOpacity5, moveScreen5, NULL);


	buttonBackground2->runAction(combinedScreen5);
	///////////////////////////////////////////////////////////////////////////////////////
	addChild(endScreen); // background
	addChild(buttonBackground1); // buttons
	addChild(buttonBackground2);
	addChild(titleMenu);

	m_currentLevel->setState(initialising);
}