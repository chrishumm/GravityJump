#include "MetricsMenu.h"
#include "SceneFactory.h" 
#include <fstream> 
#include <sstream>
#include "GUI\CCScrollView\CCScrollView.h"

using namespace extension;

stringstream convert_to_value;
bool MetricsMenu::init() //first layer player will see
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	CCLayerColor* Container = CCLayerColor::create();
	Container->setColor(ccc3(255, 0, 255));

	this->setTouchEnabled(true); //allows for touch input from the 
	return true;
}

void MetricsMenu::createGUI()
{
	CCPoint screensize = CCDirector::sharedDirector()->getWinSize(); //stores our sceen size
	//Now we reate our button, linking to our image and method we want to call when it's pressed
	pCloseItem = CCMenuItemImage::create("backButton.png", "backButton.png", this, menu_selector(MetricsMenu::backButton));
	//Now we create our label and position it
	upSprite = CCMenuItemImage::create("upSprite.png", "upSprite.png", this, menu_selector(MetricsMenu::upArrow));
	downSprite = CCMenuItemImage::create("downSprite.png", "downSprite.png", this, menu_selector(MetricsMenu::downArrow));
	leftSprite = CCMenuItemImage::create("leftSprite.png", "leftSprite.png", this, menu_selector(MetricsMenu::leftArrow));
	rightSprite = CCMenuItemImage::create("rightSprite.png", "rightSprite.png", this, menu_selector(MetricsMenu::rightArrow));

	deleteMetricsSprite = CCMenuItemImage::create("deleteMetrics.png", "deleteMetrics.png", this, menu_selector(MetricsMenu::deleteMetrics));

	upArrowMenu = CCMenu::create(upSprite, NULL);
	downArrowMenu = CCMenu::create(downSprite, NULL);
	leftArrowMenu = CCMenu::create(leftSprite, NULL);
	rightArrowMenu = CCMenu::create(rightSprite, NULL);
	deleteMetricsMenu = CCMenu::create(deleteMetricsSprite, NULL);

	upArrowMenu->setPosition(ccp(100.0f, screensize.y*0.5));
	downArrowMenu->setPosition(ccp(100.0f, -100.0f));
	leftArrowMenu->setPosition(ccp(-150.0f, 0.0f));
	rightArrowMenu->setPosition(ccp(500.0f, 0.0f));
	deleteMetricsMenu->setPosition(ccp(700.0f, -200.0f));

	addChild(upArrowMenu,-100);
	addChild(downArrowMenu, -100);
	addChild(leftArrowMenu, -100);
	addChild(rightArrowMenu, - 100);
	addChild(deleteMetricsMenu, -100);

	upSprite->setScale(rightArrowMenu->getScale() * 2);
	downSprite->setScale(rightArrowMenu->getScale() * 2);
	leftSprite->setScale(rightArrowMenu->getScale() * 2);
	rightSprite->setScale(rightArrowMenu->getScale() * 2);

	CCLabelTTF* metric_title = CCLabelTTF::create("Metrics", "Impact", 32);
	metric_title->setPosition(ccp(screensize.x*0.5, screensize.y*0.5));

	addChild(metric_title);
	//We now convert our label to a menu label, adding a menu selector when it's pressed.
	this->setPositionX(0.0f);
	this->setPositionY(0.0f);
	pMenu = CCMenu::create(pCloseItem, NULL); //Now create a menu for our button earlier
	pMenu->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 80, 20)); //position

	if(loadMetrics())
		pMenu->setPosition(ccp(700.0f, 100.0f));
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
void MetricsMenu::deleteMetrics(CCObject* startGameObject)
{
	m_metric_manager->delete_metrics();

	this->setPositionX(0.0f);
	this->setPositionY(0.0f);
	CCScene* gameStart = NULL; //create a new levelScene
	gameStart = SceneFactory::createScene("Metrics"); //Init the level scene
	gameStart->init();
	CCDirector::sharedDirector()->replaceScene(gameStart); //Replace menu scene with the new level
}

bool MetricsMenu::loadMetrics()
{
	bool success = false;
	string temp_loc = CCFileUtils::sharedFileUtils()->getWritablePath();
	temp_loc = temp_loc + "metricdb.txt";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//m_achievement_manager->saveDb("/data/data/org.cocos2dx.application/tmpfile");
	success = m_metric_manager->loadMetricStoredData(temp_loc);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	success = m_metric_manager->loadMetricStoredData("metricsdb.txt");
#endif

	if (!success)
	{
		CCPoint screensize = CCDirector::sharedDirector()->getWinSize();
		this->setPositionX(0.0f);
		this->setPositionY(0.0f);
		CCLabelTTF* warningMessage = CCLabelTTF::create("NO METRICS DATA FOUND","fonts/04b_19.ttf", 30);
		
		warningMessage->setPosition(ccp(screensize.x*0.5, (screensize.y*0.5) - 30.0f));

		warningMessage->setColor(ccc3(203, 102, 23));
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

	
	metrics_retrieved = m_metric_manager->getNumOfMetrics(false);
	unique_metric_id = m_metric_manager->getNumOfUniqueMetrics(false);
	vector<int*> amount_of_ids = m_metric_manager->getAllIDS(false);

	vector<float*> retrievedFloats;
	vector<int*>   retrievedInts;

	int created_label = 0;
	int created_value_label = 0;


	for (size_t i = 0; i < unique_metric_id.size(); i++)
	{
		char* type = m_metric_manager->getMetricType(unique_metric_id[i], false);
		if (type == "float")
		{
			
			m_metric_name[created_label] = CCLabelTTF::create(m_metric_manager->getName(unique_metric_id[i], false), "fonts/04b_19.ttf", 30);
			m_metric_name[created_label]->setColor(ccc3(203, 102, 23));
			addChild(m_metric_name[created_label]);
			

			retrievedFloats = m_metric_manager->getAllFloatingValue(unique_metric_id[i], false);
			retrievedFloats = m_metric_manager->sortSize(retrievedFloats);
			for (size_t x = 0; x < retrievedFloats.size(); x++)
			{
				convert_to_value << *retrievedFloats[x];
				string temp_string = convert_to_value.str();
				convert_to_value.str("");
				m_metric_data[created_label][created_value_label] = CCLabelTTF::create(temp_string.c_str(), "fonts/04b_19.ttf", 30);
				created_value_label++;
			}

				float name_offset = created_label * 500.0f;
				m_metric_name[created_label]->setPosition(ccp(name_offset, 0.0f));
				for (int s = 0; s < created_value_label; s++)
				{
					float offset = s * 50.0f;
					m_metric_name[created_label]->addChild(m_metric_data[i][s]);
					m_metric_data[created_label][s]->setPosition(ccp(100.0f, 50.0f + offset));
					m_metric_data[created_label][s]->setColor(ccc3(100, 200, 23));
				}

			
			
		}
		else if (type == "int" || type == "bool")
		{
			m_metric_name[created_label] = CCLabelTTF::create(m_metric_manager->getName(unique_metric_id[i], false), "fonts/04b_19.ttf", 30);
			m_metric_name[created_label]->setColor(ccc3(203, 102, 23));
			addChild(m_metric_name[created_label]);

			retrievedInts = m_metric_manager->getAllIntegerValue(unique_metric_id[i], false);
			retrievedInts = m_metric_manager->sortSize(retrievedInts);

			for (size_t x = 0; x < retrievedInts.size(); x++)
			{
				convert_to_value << *retrievedInts[x];
				string temp_string = convert_to_value.str();
				convert_to_value.str("");
				m_metric_data[created_label][created_value_label] = CCLabelTTF::create(temp_string.c_str(), "fonts/04b_19.ttf", 30);
				created_value_label++;
			}

			float name_offset = created_label * 500.0f;
			m_metric_name[created_label]->setPosition(ccp(name_offset, 0.0f));
			for (int s = 0; s < created_value_label; s++)
			{
				float offset = s * 50.0f;
				m_metric_name[created_label]->addChild(m_metric_data[i][s]);
				m_metric_data[created_label][s]->setPosition(ccp(100.0f, 50.0f + offset));
				m_metric_data[created_label][s]->setColor(ccc3(100, 200, 23));
			}
		}

	
		created_label++;
		created_value_label = 0;
	}

	vector<float*> retrievedNumer = m_metric_manager->getAllFloatingValue(5, false);
	m_metric_manager->sortSize(retrievedNumer);
	const char* name = m_metric_manager->getName(5, false);

	this->setPositionY(this->getPositionY() + 300.0f);
	this->setPositionX(this->getPositionX() + 300.0f);

	return true;

}

void MetricsMenu::backButton(CCObject* startGameObject)
{
	CCScene* gameStart = NULL; //create a new levelScene
	gameStart = SceneFactory::createScene("MainMenu"); //Init the level scene
	gameStart->init();
	CCDirector::sharedDirector()->replaceScene(gameStart); //Replace menu scene with the new level
}

void MetricsMenu::upArrow(CCObject*)
{
	this->setPositionY(this->getPositionY() + 30);

	upSprite->setPositionY(upSprite->getPositionY() - 30);
	downSprite->setPositionY(downSprite->getPositionY() - 30);
	leftSprite->setPositionY(leftSprite->getPositionY() - 30);
	rightSprite->setPositionY(rightSprite->getPositionY() - 30);
	deleteMetricsSprite->setPositionY(deleteMetricsSprite->getPositionY() - 30);
	pCloseItem->setPositionY(pCloseItem->getPositionY() - 30);
}
void MetricsMenu::downArrow(CCObject*)
{
	this->setPositionY(this->getPositionY() - 30);

	upSprite->setPositionY(upSprite->getPositionY() + 30);
	downSprite->setPositionY(downSprite->getPositionY() + 30);
	leftSprite->setPositionY(leftSprite->getPositionY() + 30);
	rightSprite->setPositionY(rightSprite->getPositionY() + 30);
	deleteMetricsSprite->setPositionY(deleteMetricsSprite->getPositionY() + 30);
	pCloseItem->setPositionY(pCloseItem->getPositionY() + 30);
}
void MetricsMenu::leftArrow(CCObject*)
{
	this->setPositionX(this->getPositionX() - 30);

	upSprite->setPositionX(upSprite->getPositionX() + 30);
	downSprite->setPositionX(downSprite->getPositionX() + 30);
	leftSprite->setPositionX(leftSprite->getPositionX() + 30);
	rightSprite->setPositionX(rightSprite->getPositionX() + 30);
	deleteMetricsSprite->setPositionX(deleteMetricsSprite->getPositionX() + 30);
	pCloseItem->setPositionX(pCloseItem->getPositionX() + 30);
}
void MetricsMenu::rightArrow(CCObject*)
{
	this->setPositionX(this->getPositionX() + 30);

	upSprite->setPositionX(upSprite->getPositionX() - 30);
	downSprite->setPositionX(downSprite->getPositionX() - 30);
	leftSprite->setPositionX(leftSprite->getPositionX() - 30);
	rightSprite->setPositionX(rightSprite->getPositionX() - 30);
	deleteMetricsSprite->setPositionX(deleteMetricsSprite->getPositionX() - 30);
	pCloseItem->setPositionX(pCloseItem->getPositionX() - 30);
}