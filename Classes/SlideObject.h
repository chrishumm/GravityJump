#pragma once
#include "command.h"

class SlideObject : public command
{
public:
	SlideObject(int jump_direction);
	SlideObject(int jump_direction, char* sound);
	void execute(WorldObject* object, float deltaTime);
	enum direction{ right, left, up, down };
private:
	static const int m_jump_value = 0.0f;
	int m_direction;
	char* sound;
	static bool sounds_preloaded;
protected:

};
