#pragma once
#include "command.h"

class GravitySwitch : public command
{
public:
	GravitySwitch(b2World* w);
	GravitySwitch(b2World* w, char* sound);
	void execute(WorldObject* object, float dt);
private:
	b2World* world;
	char* sound;
	static bool sounds_preloaded;
protected:
};
