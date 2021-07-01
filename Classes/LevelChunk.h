#pragma once
#include "WorldObject.h"
#include "Box2D\Box2D.h"
#include <vector>

class LevelChunk : public WorldObject
{
public:
	LevelChunk();
	~LevelChunk();
	LevelChunk(CCLayer* currentLayer, b2World* currentWorld);
	LevelChunk(CCLayer* currentLayer, b2World* currentWorld,LevelChunk* prev);
	LevelChunk* generateBlocks(char*);
	void levelBoundaries();
	void defaultBlocks();
	void defaultBlocks(float offset, bool diff);

	void harderBlocks(bool diff);
	void harderBlocks2(bool diff);
	void harderBlocks3(bool diff);
	void harderBlocks4(bool diff);

	int getNumPieces();
	void resetObjects();

	vector<char*> levelTypePieces;
	vector<char*> levelChunkObjectOriginalName;
	vector<CCSprite*> levelSpritePieces;
	vector<b2Body*> levelPhysicsPieces;
private:
	LevelChunk* m_currentPiece;
	LevelChunk* m_previousChunk;
	int numofpieces;
protected:
};