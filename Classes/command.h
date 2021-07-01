#pragma once
#include <iostream>
#include "WorldObject.h"
#include "soundManager.h"
using namespace std;

class command
{
public:
	~command() {};
	virtual void execute(WorldObject* object, float dt) = 0;
private:

protected:
};