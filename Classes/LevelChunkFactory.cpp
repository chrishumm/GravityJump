#include "LevelChunkFactory.h"
#include "MovingPhysicsComponent.h"
//#ifdef _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#define DEBUG_NEW new(_CLIENT_BLOCK, __FILE__, __LINE__)
//#define new DEBUG_NEW
//#endif

LevelChunk* LevelChunkFactory::createLevelChunk(char* name,CCLayer* currentLayer, b2World* m_current_world)
{
	if(name == "Level Boundaries")
	{
		LevelChunk* newDefaultLevel;
		newDefaultLevel = new LevelChunk(currentLayer,m_current_world);
		newDefaultLevel->generateBlocks("Level Boundaries");
		return newDefaultLevel;
	}
	else if(name == "Default")
	{
		LevelChunk* newDefaultLevel;
		newDefaultLevel = new LevelChunk(currentLayer,m_current_world);
		//_CrtDumpMemoryLeaks();
		newDefaultLevel->generateBlocks("Default");
		return newDefaultLevel;
	}
	else if (name == "Default 1")
	{
		LevelChunk* newDefaultLevel;
		newDefaultLevel = new LevelChunk(currentLayer, m_current_world);
		//_CrtDumpMemoryLeaks();
		newDefaultLevel->generateBlocks("Default 1");
		return newDefaultLevel;
	}
	else if (name == "Default 2")
	{
		LevelChunk* newDefaultLevel;
		newDefaultLevel = new LevelChunk(currentLayer, m_current_world);
	//	_CrtDumpMemoryLeaks();
		newDefaultLevel->generateBlocks("Default 2");
		return newDefaultLevel;
	}
	else if (name == "Default 3")
	{
		LevelChunk* newDefaultLevel;
		newDefaultLevel = new LevelChunk(currentLayer, m_current_world);
		newDefaultLevel->addPhysicsComponent(new MovingPhysicsComponent(m_current_world));
		//_CrtDumpMemoryLeaks();
		newDefaultLevel->generateBlocks("Default 3");
		return newDefaultLevel;
	}
	else if (name == "Default 4")
	{
		LevelChunk* newDefaultLevel;
		newDefaultLevel = new LevelChunk(currentLayer, m_current_world);
		//_CrtDumpMemoryLeaks();
		newDefaultLevel->generateBlocks("Default 4");
		return newDefaultLevel;
	}
	else if (name == "Default 5")
	{
		LevelChunk* newDefaultLevel;
		newDefaultLevel = new LevelChunk(currentLayer, m_current_world);
		//_CrtDumpMemoryLeaks();
		newDefaultLevel->generateBlocks("Default 5");
		return newDefaultLevel;
	}
	else if (name == "Default 6")
	{
		LevelChunk* newDefaultLevel;
		newDefaultLevel = new LevelChunk(currentLayer, m_current_world);
		//_CrtDumpMemoryLeaks();
		newDefaultLevel->generateBlocks("Default 6");
		return newDefaultLevel;
	}
	else if (name == "Default 4")
	{
		LevelChunk* newDefaultLevel;
		newDefaultLevel = new LevelChunk(currentLayer, m_current_world);
		//_CrtDumpMemoryLeaks();
		newDefaultLevel->generateBlocks("Default 4");
		return newDefaultLevel;
	}
	else if (name == "Default 7")
	{
		LevelChunk* newDefaultLevel;
		newDefaultLevel = new LevelChunk(currentLayer, m_current_world);
		//_CrtDumpMemoryLeaks();
		newDefaultLevel->generateBlocks("Default 7");
		return newDefaultLevel;
	}
	else if (name == "Default 8")
	{
		LevelChunk* newDefaultLevel;
		newDefaultLevel = new LevelChunk(currentLayer, m_current_world);
		//_CrtDumpMemoryLeaks();
		newDefaultLevel->generateBlocks("Default 8");
		return newDefaultLevel;
	}
	return NULL;
}

LevelChunk* LevelChunkFactory::createLevelChunk(char* name,CCLayer* currentLayer, b2World* m_current_world,LevelChunk* prev)
{
	if(name == "Default")
	{
		LevelChunk* newDefaultLevel;
		newDefaultLevel = new LevelChunk(currentLayer,m_current_world,prev);
		//_CrtDumpMemoryLeaks();
		newDefaultLevel->generateBlocks("Default");
		return newDefaultLevel;
	}

	return NULL;
}