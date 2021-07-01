#include "MenuLayer.h"


void MenuLayer::ccTouchesBegan(CCSet * ptouches, cocos2d::CCEvent * pevent)
{
}

void MenuLayer::ccTouchesEnded(CCSet * ptouches, cocos2d::CCEvent * pevent)
{
}

void MenuLayer::addAchievementManager(AchievementManager* current)
{
	m_achievement_manager = current;
}

void MenuLayer::addMetricsManager(MetricManager* m)
{
	m_metric_manager = m;
}