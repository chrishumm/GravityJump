/*
	Author: Christopher Humm
	Class: Level Layer
	Description: This class acts as a base for all levels
*/
#pragma once
#include <iostream>
#include "cocos2d.h"
#include "LevelLayer.h"
#include "WorldObject.h"
#include "DefaultPlayer.h"
#include "B2DebugDrawLayer.h"
#include "UIGUI.h"
#include <vector>

class LevelOne : public LevelLayer, b2ContactListener
{
	public:
	virtual bool init();
	CREATE_FUNC(LevelOne);
	//////////Box 2D Events/////////////
	virtual void BeginContact(b2Contact* contact); //overriden contacts
	virtual void EndContact(b2Contact* contact); // for player > platforms
	virtual	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	//////////Input Events//////////////
	virtual void ccTouchesBegan(CCSet * ptouches, cocos2d::CCEvent * pevent );
	virtual void ccTouchesEnded(CCSet * ptouches, cocos2d::CCEvent * pevent );

	int getPlayerState(); //specific player states
	float getPlayerStateDuration(); //specific player states
	void setPlayerState(int);
	void setPlayerState(int state, float ttl);
	void setPlayerStateDuration(float); //specific player states
	/////////////////////////////////////////////////////////////////////////
	private:
		void gameLoop(float dt);
		void updateLayer(float dt);
		void createWorldPhysics();
		void createLevelGeometry();
		void endGame(float dt);
		
		void logic(float dt);
		void render();
		bool deallocateMemory();
		UIGUI* GUILayer;

		b2Vec2 m_gravity; // gravity value
		collision* collision_handler;
		b2World* m_world;
		b2Vec2   m_worldGravity;
		float m_gravity_y;
		vector<WorldObject*> m_active_chunks;
		vector<WorldObject*> m_inactive_chunks;
		vector<WorldObject*> levelObjects;
		WorldObject* objectsOnScreen[3];
		float deltaTime;
	protected:
		static B2DebugDrawLayer* create(b2World* pB2World, float pPTmratio); //debug
};
