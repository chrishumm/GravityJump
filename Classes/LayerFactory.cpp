#include "LayerFactory.h"
#include "LevelOne.h"
#include "MainMenu.h"
#include "ConsentMenu.h"
#include "credits.h"
#include "MetricsMenu.h"
#include "AchievementMenu.h"
#include "UIGUI.h"

CCLayer* LayerFactory::createLayer(char* name)
{
	if(name == "Level")
	{
		try
		{
			LevelOne* newLevelLayer;
			newLevelLayer = LevelOne::create();
			newLevelLayer->setLevelNumber(1);
			newLevelLayer->addMetricsManager(new MetricManager());
			return newLevelLayer;
		}
		catch(...)
		{
			CCLayer* newLevelLayer;
			newLevelLayer = CCLayer::create();
			return newLevelLayer;
		}
	}
	if(name == "GUI")
	{
		try
		{
			UIGUI* LevelGUI;
			LevelGUI = UIGUI::create();
			LevelGUI->addAchievementManager(new AchievementManager());
			LevelGUI->addMetricsManager(new MetricManager());
			return LevelGUI;
		}
		catch(...)
		{
			CCLayer* newLevelLayer;
			newLevelLayer = CCLayer::create();
			return newLevelLayer;
		}
	}
	if (name == "MainMenu")
	{
		try
		{
			MainMenu* mainMenuDisplay;
			mainMenuDisplay = MainMenu::create();
			mainMenuDisplay->addAchievementManager(new AchievementManager());
			mainMenuDisplay->addMetricsManager(new MetricManager());
			return mainMenuDisplay;
		}
		catch (...)
		{
			CCLayer* newLevelLayer;
			newLevelLayer = CCLayer::create();
			return newLevelLayer;
		}
	}
	if (name == "Credits")
	{
		try
		{
			Credits* creditsDisplay;
			creditsDisplay = Credits::create();
			creditsDisplay->addAchievementManager(new AchievementManager());
			creditsDisplay->addMetricsManager(new MetricManager());
			creditsDisplay->createCredits();
			return creditsDisplay;
		}
		catch (...)
		{
			CCLayer* newLevelLayer;
			newLevelLayer = CCLayer::create();
			return newLevelLayer;
		}
	}
	if (name == "MainMenuTest")
	{
		try
		{
			CCLayer* mainMenuDisplay;
			mainMenuDisplay = CCLayer::create();
			return mainMenuDisplay;
		}
		catch (...)
		{
			CCLayer* newLevelLayer;
			newLevelLayer = CCLayer::create();
			return newLevelLayer;
		}
	}
	if (name == "Consent")
	{
		try
		{
			ConsentMenu* mainMenuDisplay;
			mainMenuDisplay = ConsentMenu::create();
			
			mainMenuDisplay->addAchievementManager(new AchievementManager());
			mainMenuDisplay->addMetricsManager(new MetricManager());
			mainMenuDisplay->createUIConsent();
			return mainMenuDisplay;
		}
		catch (...)
		{
			CCLayer* newLevelLayer;
			newLevelLayer = CCLayer::create();
			return newLevelLayer;
		}
	}
	if (name == "ConsentTests")
	{
		try
		{
			ConsentMenu* mainMenuDisplay;
			mainMenuDisplay = ConsentMenu::create();

			mainMenuDisplay->addAchievementManager(new AchievementManager());
			mainMenuDisplay->addMetricsManager(new MetricManager());
			mainMenuDisplay->createUIConsent();
			return mainMenuDisplay;
		}
		catch (...)
		{
			CCLayer* newLevelLayer;
			newLevelLayer = CCLayer::create();
			return newLevelLayer;
		}
	}
	if (name == "Metrics")
	{
		try
		{
			MetricsMenu* metricMenuDisplay;
			metricMenuDisplay = MetricsMenu::create();

			metricMenuDisplay->addAchievementManager(new AchievementManager());
			metricMenuDisplay->addMetricsManager(new MetricManager());
			metricMenuDisplay->createGUI();
			return metricMenuDisplay;
		}
		catch (...)
		{
			CCLayer* newLevelLayer;
			newLevelLayer = CCLayer::create();
			return newLevelLayer;
		}
	}
	if (name == "MetricsTests")
	{
		try
		{
			CCLayer* newLevelLayer;
			newLevelLayer = CCLayer::create();
			return newLevelLayer;
		}
		catch (...)
		{
			CCLayer* newLevelLayer;
			newLevelLayer = CCLayer::create();
			return newLevelLayer;
		}
	}
	if (name == "Achievements")
	{
		try
		{
			AchievementMenu* AchievementDisplay;
			AchievementDisplay = AchievementMenu::create();

			AchievementDisplay->addAchievementManager(new AchievementManager());
			AchievementDisplay->addMetricsManager(new MetricManager());
			AchievementDisplay->createGUI();
			return AchievementDisplay;
		}
		catch (...)
		{
			CCLayer* newLevelLayer;
			newLevelLayer = CCLayer::create();
			return newLevelLayer;
		}
	}
	if (name == "AchievementsTests")
	{
		try
		{
			CCLayer* newLevelLayer;
			newLevelLayer = CCLayer::create();
			return newLevelLayer;
		}
		catch (...)
		{
			CCLayer* newLevelLayer;
			newLevelLayer = CCLayer::create();
			return newLevelLayer;
		}
	}
	if (name == "LevelTest")
	{
		CCLayer* defaultLayer;
		defaultLayer = CCLayer::create();
		return defaultLayer;
	}
	CCLayer* defaultLayer;
	defaultLayer = CCLayer::create();
	return defaultLayer;
}