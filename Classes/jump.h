#pragma once
#include "command.h"

class jump : public command
{
public:
	jump(int jump_direction, int gravity_direction);
	jump(int jump_direction, int gravity_direction, char* sound);
	void execute(WorldObject* object, float deltaTime);
	enum direction{ right, left, up, down };
	enum gravity{ normal, flipped};
private:
	static const int m_jump_value = 0.0f;
	int m_direction;
	int m_gravity;
	char* sound;
	static bool sounds_preloaded;
protected:

};