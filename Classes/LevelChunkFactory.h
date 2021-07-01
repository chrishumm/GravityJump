#pragma once
#include "cocos2d.h"
#include "LevelChunk.h"
#include "Box2D\Box2D.h"

class LevelChunkFactory
{
public:
	static LevelChunk* createLevelChunk(char* type,CCLayer* currentLayer,b2World* m_current_world);
	static LevelChunk* createLevelChunk(char* type,CCLayer* currentLayer,b2World* m_current_world,LevelChunk* prev);
private:
protected:
};