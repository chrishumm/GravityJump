#pragma once
#include "cocos2d.h"

#include <iostream>

using namespace cocos2d;

class UIMessage
{
public:
	static void displayUIMessage(float x, float y, float fx, float fy, std::string message, float ttl,CCLayer* );
	static void displayUIMessage(float x, float y, float fx, float fy, std::string message, float ttl, CCLayer*, int id);
	static void removeMessageID(int id, CCLayer* current_layer);
private:
protected:
};