#pragma once
#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include <vector>

using namespace cocos2d;

class RenderingComponent
{
public:
	RenderingComponent();
	RenderingComponent(CCLayer* currentLayer);
	void updateRendering(vector<b2Vec2> currentPhysPos, float dt);

	void addNewSprite(CCSprite* newSprite);
	void addNewSprite(CCSprite* newSprite, int anim_x, int anim_y, int sprite_sheet_width, int m_sprite_sheet_height);

	void addNewSprite(CCSprite* newSprite,bool multiple_sprite);
	void addNewSprite(CCSprite* newSprite, bool multiple_sprites, int anim_x, int anim_y, int sprite_sheet_width, int m_sprite_sheet_height);
	
	CCSprite* getSprite();
	std::vector<CCSprite*> getSprites();
	void saveInitialPosition();
	void loadInitialPosition();

	void updateFrameX(float x);
	void updateFrameY(float y);
	void updateFrameY(float y, float max_x);

	bool removeSprite();
	bool isMultipleSpritesAttached();
	void setMultipleSprites(bool);
	bool chunkOffScreen();
private:
	CCSprite* m_sprite;
	vector<CCSprite*> m_sprites;
	vector<CCSprite*> m_sprites_original;
	CCLayer* m_currentLayer;
	bool multiple_sprites;

	bool has_animation;
	float max_animation_x;
	float max_animation_y;

	float current_anim_x;
	float current_anim_y;
	int m_frame;
	float m_sprite_sheet_width;
	float m_sprite_sheet_height;

	float last_update;
protected:
};