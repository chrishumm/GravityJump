#include "LevelChunk.h"
#include "NormalWall.h"
#include "BadWall.h"
#include "InfiniteGravitySwitching.h"
#include "DestructionBlockPowerup.h"

LevelChunk::LevelChunk()
{
}
LevelChunk::~LevelChunk()
{
	delete m_currentPiece;
	m_currentPiece = NULL;

	/*
	for(int i = 0; i < levelSpritePieces.size();i++)
	{
		//delete levelSpritePieces[i];
		//levelPhysicsPieces[i] = NULL;
	}
	*/
}
LevelChunk::LevelChunk(CCLayer* currentLayer, b2World* currentWorld) : WorldObject(currentLayer, currentWorld)
{
	m_previousChunk = NULL;
}

LevelChunk::LevelChunk(CCLayer* currentLayer, b2World* currentWorld, LevelChunk* prev) : WorldObject(currentLayer, currentWorld)
{
	m_previousChunk = prev;
}

LevelChunk* LevelChunk::generateBlocks(char* levelsetPiece)
{
	numofpieces = 0;

	m_object_name = "Level Chunk";
	m_currentPiece = NULL;
	if(levelsetPiece == "Default" && m_previousChunk == NULL)
		defaultBlocks();
	if(levelsetPiece == "Level Boundaries")
		levelBoundaries();
	else if(levelsetPiece == "Default 1")
		defaultBlocks(m_layerWidth, false);
	else if (levelsetPiece == "Default 2")
		defaultBlocks(m_layerWidth, true);
	else if (levelsetPiece == "Default 3")
		harderBlocks(false);
	else if (levelsetPiece == "Default 4")
		harderBlocks2(true);
	else if (levelsetPiece == "Default 5")
		harderBlocks3(true);
	else if (levelsetPiece == "Default 6")
		harderBlocks4(true);
	else if (levelsetPiece == "Default 7")
		harderBlocks2(true);
	else if (levelsetPiece == "Default 8")
		harderBlocks2(true);
	else
		defaultBlocks();

	for(size_t i = 0; i < levelSpritePieces.size();i++)
		getRenderingComponent()->addNewSprite(levelSpritePieces[i],true);

	for(size_t i = 0; i < levelPhysicsPieces.size();i++)
		getPhysicsComponent()->addPhysicsBody(levelPhysicsPieces[i],true);

	for(size_t i = 0; i < levelTypePieces.size();i++)
	{
		if(levelTypePieces[i] == "Moving Wall")
		{
			levelTypePieces[i] = "Bad Wall";
			void* test = this;
			levelPhysicsPieces[i]->SetUserData(test);
		}
	}

	levelChunkObjectOriginalName = levelTypePieces;
	return this;
}
void LevelChunk::levelBoundaries()
{
	levelPhysicsPieces.push_back(BadWall::createWallPhysics(m_layerWidth+10*WorldObject::xPTM,0.0f*WorldObject::xPTM,0.0f*WorldObject::xPTM,m_layerHeight*WorldObject::xPTM,m_objectPhysics->getCurrentWorld()));
	levelTypePieces.push_back("Bad Wall Essential");
	levelPhysicsPieces.back()->SetUserData(NULL);
	numofpieces++;

	levelPhysicsPieces.push_back(BadWall::createWallPhysics(-30.0f*WorldObject::xPTM,0.0f*WorldObject::xPTM,0.0f*WorldObject::xPTM,m_layerHeight*WorldObject::xPTM,m_objectPhysics->getCurrentWorld()));
	levelTypePieces.push_back("Bad Wall Essential");
	levelPhysicsPieces.back()->SetUserData(NULL);
	numofpieces++;
}
void LevelChunk::defaultBlocks()
{
	levelPhysicsPieces.push_back(NormalWall::createWallPhysics(0.0f*WorldObject::xPTM,100.0f*WorldObject::xPTM,m_layerWidth*WorldObject::xPTM,(100.0f)*WorldObject::xPTM,m_objectPhysics->getCurrentWorld()));
	levelSpritePieces.push_back(NormalWall::createWallSprite(0.0f,150.0f*WorldObject::xMTP));
	levelTypePieces.push_back("Essential");
	levelPhysicsPieces.back()->SetUserData(NULL);
	numofpieces++;

	levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth * 0.5)*WorldObject::xPTM ,(200.0f)*WorldObject::xPTM,0.3f,(100.0f)*WorldObject::xPTM,m_objectPhysics->getCurrentWorld()));
	levelSpritePieces.push_back(NormalWall::createWallSprite(0.0f,100.0f * xMTP));
	levelTypePieces.push_back("Wall");
	levelPhysicsPieces.back()->SetUserData(NULL);
	numofpieces++;

	levelPhysicsPieces.push_back(NormalWall::createWallPhysics(0.0f*WorldObject::xPTM ,((m_layerHeight- 70.0f))*WorldObject::xPTM,(m_layerWidth* 0.5)*WorldObject::xPTM,0.0f,m_objectPhysics->getCurrentWorld()));
	levelSpritePieces.push_back(NormalWall::createWallSprite(0.0f,(100.0f) * xMTP));
	levelTypePieces.push_back("Essential");
	levelPhysicsPieces.back()->SetUserData(NULL);
	numofpieces++;

	levelPhysicsPieces.push_back(DestructionBlockPowerup::createWallPhysics(m_layerWidth *WorldObject::xPTM, ((m_layerHeight - 170.0f))*WorldObject::xPTM, 10.0f*WorldObject::xPTM, 0.1f, m_objectPhysics->getCurrentWorld()));
	levelSpritePieces.push_back(DestructionBlockPowerup::createWallSprite(0.0f, (100.0f) * xMTP));
	levelTypePieces.push_back("Destruction Block");
	levelPhysicsPieces.back()->SetUserData(NULL);
	numofpieces++;
}

void LevelChunk::defaultBlocks(float offset, bool alt_chunk)
{
	if (alt_chunk == false)
	{
		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((offset)*WorldObject::xPTM, 100.0f*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(0.0f, 150.0f*WorldObject::xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((offset)*WorldObject::xPTM, ((m_layerHeight - 70.0f))*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, 0.0f, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(offset, (100.0f) * xMTP));
		levelTypePieces.push_back("Essential");
	//	levelPhysicsPieces.push_back(BadWall::createWallPhysics((offset + (offset * 0.5))*WorldObject::xPTM, (200.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
	//	levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
	//	levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(BadWall::createWallPhysics((offset + (offset * 0.5))*WorldObject::xPTM, (m_layerHeight - 70.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		numofpieces++;
		


	}
	else
	{
		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((offset)*WorldObject::xPTM, 100.0f*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(0.0f, 150.0f*WorldObject::xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((offset)*WorldObject::xPTM, ((m_layerHeight - 70.0f))*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, 0.0f, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(offset, (100.0f) * xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(BadWall::createWallPhysics((offset + (offset * 0.5))*WorldObject::xPTM, (200.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(BadWall::createWallPhysics((offset + (offset * 0.5))*WorldObject::xPTM, (m_layerHeight - 70.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;
	}

}

void LevelChunk::harderBlocks(bool alt_chunk)
{
	if (alt_chunk == false)
	{
		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth)*WorldObject::xPTM, 100.0f*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(0.0f, 150.0f*WorldObject::xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth)*WorldObject::xPTM, ((m_layerHeight - 70.0f))*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, 0.0f, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(m_layerWidth, (100.0f) * xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth + (m_layerWidth * 0.5))*WorldObject::xPTM, (m_layerHeight - 500.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Moving Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth + 300.0f)*WorldObject::xPTM, (m_layerHeight - 500.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Moving Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

	}
	else
	{
		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth)*WorldObject::xPTM, 100.0f*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(0.0f, 150.0f*WorldObject::xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth)*WorldObject::xPTM, ((m_layerHeight - 70.0f))*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, 0.0f, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(m_layerWidth, (100.0f) * xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(BadWall::createWallPhysics((m_layerWidth + (100.0f))*WorldObject::xPTM, (200.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(BadWall::createWallPhysics((m_layerWidth + (100.0f))*WorldObject::xPTM, (m_layerHeight - 70.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(BadWall::createWallPhysics((m_layerWidth + (m_layerWidth * 0.5))*WorldObject::xPTM, (m_layerHeight - 400.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;
	}
}
void LevelChunk::harderBlocks2(bool alt_chunk)
{
	if (alt_chunk == false)
	{
		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth)*WorldObject::xPTM, 100.0f*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(0.0f, 150.0f*WorldObject::xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth)*WorldObject::xPTM, ((m_layerHeight - 70.0f))*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, 0.0f, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(m_layerWidth, (100.0f) * xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(InfiniteGravitySwitching::createWallPhysics((m_layerWidth + (m_layerWidth * 0.5))*WorldObject::xPTM, (m_layerHeight - 500.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Infinite Gravity");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;


	}
	else
	{
		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth)*WorldObject::xPTM, 100.0f*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(0.0f, 150.0f*WorldObject::xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth)*WorldObject::xPTM, ((m_layerHeight - 70.0f))*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, 0.0f, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(m_layerWidth, (100.0f) * xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(BadWall::createWallPhysics((m_layerWidth + (100.0f))*WorldObject::xPTM, (200.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(BadWall::createWallPhysics((m_layerWidth + (100.0f))*WorldObject::xPTM, (m_layerHeight - 70.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(BadWall::createWallPhysics((m_layerWidth + (m_layerWidth * 0.5))*WorldObject::xPTM, (m_layerHeight - 400.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;
	}
}
void LevelChunk::harderBlocks3(bool alt_chunk)
{
	if (alt_chunk == false)
	{
		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth)*WorldObject::xPTM, 100.0f*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(0.0f, 150.0f*WorldObject::xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth)*WorldObject::xPTM, ((m_layerHeight - 70.0f))*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, 0.0f, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(m_layerWidth, (100.0f) * xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth + (m_layerWidth * 0.5))*WorldObject::xPTM, (m_layerHeight - 500.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;


	}
	else
	{
		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth)*WorldObject::xPTM, 100.0f*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(0.0f, 150.0f*WorldObject::xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth)*WorldObject::xPTM, ((m_layerHeight - 70.0f))*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, 0.0f, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(m_layerWidth, (100.0f) * xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(BadWall::createWallPhysics((m_layerWidth + (100.0f))*WorldObject::xPTM, (200.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(BadWall::createWallPhysics((m_layerWidth + (100.0f))*WorldObject::xPTM, (m_layerHeight - 70.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(BadWall::createWallPhysics((m_layerWidth + (m_layerWidth * 0.5))*WorldObject::xPTM, (m_layerHeight - 400.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;
	}
}
void LevelChunk::harderBlocks4(bool alt_chunk)
{
	if (alt_chunk == false)
	{
		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth)*WorldObject::xPTM, 100.0f*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(0.0f, 150.0f*WorldObject::xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth)*WorldObject::xPTM, ((m_layerHeight - 70.0f))*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, 0.0f, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(m_layerWidth, (100.0f) * xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth + (m_layerWidth * 0.5))*WorldObject::xPTM, (m_layerHeight - 500.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Moving Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth +100.0f)*WorldObject::xPTM, (m_layerHeight - 500.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

	}
	else
	{
		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth)*WorldObject::xPTM, 100.0f*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(0.0f, 150.0f*WorldObject::xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth)*WorldObject::xPTM, ((m_layerHeight - 70.0f))*WorldObject::xPTM, (m_layerWidth + 2000)*WorldObject::xPTM, 0.0f, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(NormalWall::createWallSprite(m_layerWidth, (100.0f) * xMTP));
		levelTypePieces.push_back("Essential");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth + 100.0f)*WorldObject::xPTM, (m_layerHeight - 500.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth + 600.0f)*WorldObject::xPTM, (m_layerHeight - 500.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;

		levelPhysicsPieces.push_back(NormalWall::createWallPhysics((m_layerWidth + 600.0f)*WorldObject::xPTM, (m_layerHeight - 70.0f)*WorldObject::xPTM, 0.3f, (100.0f)*WorldObject::xPTM, m_objectPhysics->getCurrentWorld()));
		levelSpritePieces.push_back(BadWall::createWallSprite(0.0f, 100.0f * xMTP));
		levelTypePieces.push_back("Bad Wall");
		levelPhysicsPieces.back()->SetUserData(NULL);
		numofpieces++;
	}
}
int LevelChunk::getNumPieces()
{
	return numofpieces;
}

void LevelChunk::resetObjects()
{
	for (size_t i = 0; i < levelTypePieces.size(); i++)
	{
		if (levelTypePieces[i] == "Delete")
		{
			levelTypePieces[i] = levelChunkObjectOriginalName[i];
		}
	}
}