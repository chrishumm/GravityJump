#include "LevelLayer.h"


void LevelLayer::ccTouchesBegan(CCSet * ptouches, cocos2d::CCEvent * pevent )
{
}

void LevelLayer::ccTouchesEnded(CCSet * ptouches, cocos2d::CCEvent * pevent )
{
}

void LevelLayer::setLevelNumber(int levelNumber)
{
	m_level_number = levelNumber;
}

int LevelLayer::getLevelNumber()
{
	return m_level_number;
}

int LevelLayer::getState()
{
	return m_state;
}

void LevelLayer::setState(int state)
{
	m_state = state;
}

void LevelLayer::addAchievementManager(AchievementManager* current)
{
	m_achievement_manager = current;
}

void LevelLayer::addMetricsManager(MetricManager* m)
{
	m_metric_manager = m;
}

MetricManager* LevelLayer::getMetricManager()
{
	return m_metric_manager;
}
AchievementManager* LevelLayer::getAchievementManager()
{
	return m_achievement_manager;
}