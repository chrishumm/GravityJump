#include "RenderingComponent.h"

RenderingComponent::RenderingComponent()
{

}
RenderingComponent::RenderingComponent(CCLayer* currentLayer)
{
	if(currentLayer == NULL)
		return;

	m_currentLayer = currentLayer;
	m_sprite = CCSprite::create("default.png");
	m_currentLayer->addChild(m_sprite);

	multiple_sprites = true;

	has_animation = false;
	max_animation_x = 0;
	max_animation_y = 0;
	last_update = 0.0f;

	m_frame = 0;

}

void RenderingComponent::updateRendering(vector<b2Vec2> currentPhysPos, float dt)
{
	last_update += dt;
	if(multiple_sprites == false)
	{
		float x = currentPhysPos[0].x * 300.0f;
		float y = currentPhysPos[0].y * 300.0f;
		if (has_animation == true)
		{
			if (last_update >= 0.5)
			{
				last_update = 0.0f;
				m_frame++;
				if (m_frame >= max_animation_x)
					m_frame = 0;

				m_sprite->setTextureRect(CCRect(current_anim_x + (m_frame * m_sprite_sheet_width), current_anim_y* m_sprite_sheet_height, m_sprite_sheet_width, m_sprite_sheet_height));
			
			}
		}
		m_sprite->setPosition(ccp(x,y));
	}
	else
	{
		for(size_t i = 0; i < m_sprites.size();i++)
		{
			float x = currentPhysPos[i].x * 300.0f;
			float y = currentPhysPos[i].y * 300.0f;

			m_sprites[i]->setPosition(ccp(x,y));
		}
	}
}

void RenderingComponent::addNewSprite(CCSprite* newSprite)
{
	m_currentLayer->removeChild(m_sprite);
	m_sprite = newSprite;
	m_currentLayer->addChild(newSprite);
}

void RenderingComponent::addNewSprite(CCSprite* newSprite, int anim_x, int anim_y, int sprite_sheet_width, int sprite_sheet_height)
{
	has_animation = true;
	m_sprite_sheet_width = sprite_sheet_width;
	m_sprite_sheet_height = sprite_sheet_height;

	max_animation_x = anim_x;
	max_animation_y = anim_y;
	current_anim_x = 0;
	current_anim_y = 0;
	m_frame = 0;

	m_currentLayer->removeChild(m_sprite);
	m_sprite = newSprite;

	m_sprite->setTextureRect(CCRect(current_anim_x + (m_frame * m_sprite_sheet_width), current_anim_y * m_sprite_sheet_height, m_sprite_sheet_width, m_sprite_sheet_height));
	m_currentLayer->addChild(newSprite);
}

void RenderingComponent::addNewSprite(CCSprite* newSprite, bool multiple_sprites)
{
	multiple_sprites = true;
	m_sprites.push_back(newSprite);
	m_currentLayer->addChild(newSprite);
}

void RenderingComponent::addNewSprite(CCSprite* newSprite, bool multiple_sprites, int anim_x, int anim_y, int sprite_sheet_width, int sprite_sheet_height)
{
	has_animation = true;
	m_sprite_sheet_width = sprite_sheet_width;
	current_anim_x = 0;
	current_anim_y = 0;
	m_frame = 0;

	multiple_sprites = true;
	m_sprites.push_back(newSprite);
	m_currentLayer->addChild(newSprite);
}

CCSprite* RenderingComponent::getSprite()
{
	return m_sprite;
}

vector<CCSprite*> RenderingComponent::getSprites()
{
	return m_sprites;
}

bool RenderingComponent::removeSprite()
{
	try
	{
		for(size_t i = 0; i < m_sprites.size();i++)
		{
			m_currentLayer->removeChild(m_sprites[i]);
			m_sprites[i] = NULL;
		}
	}
	catch(...)
	{
		return false;
	}

	return true;
}

bool RenderingComponent::isMultipleSpritesAttached()
{
	if(multiple_sprites == true)
		return true;
	else
		return false;
}

void RenderingComponent::saveInitialPosition()
{
	//m_sprites_original = m_sprites;
}

void RenderingComponent::loadInitialPosition()
{
	//m_sprites = m_sprites_original;
}

void RenderingComponent::setMultipleSprites(bool x)
{
	multiple_sprites = x;
}

bool RenderingComponent::chunkOffScreen()
{
	int x = 0;
	for(size_t i = 0; i < m_sprites.size();i++)
	{
		if(m_sprites[i]->getPositionX()+ 350 < 0)
			x++;
	}

	if(x == 2)
		return true;
	else
		return false;
}

void RenderingComponent::updateFrameX(float x)
{
	if (x <= max_animation_x)
		current_anim_x = x;
}

void RenderingComponent::updateFrameY(float y)
{
	if (y <= max_animation_y)
		current_anim_y = y;
}

void RenderingComponent::updateFrameY(float y, float max_x)
{
	if (y <= max_animation_y)
		current_anim_y = y;

	max_animation_x = max_x;
}