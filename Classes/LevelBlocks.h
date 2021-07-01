#pragma once
#include "LevelChunk.h"
#include "cocos2d.h"
#include "Box2D\Box2D.h"
using namespace cocos2d;

class LevelBlocks 
{
public:

private:

protected:
	CCSprite* m_block_sprite;
	b2Body* m_block_body;
};