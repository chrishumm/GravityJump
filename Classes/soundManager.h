#pragma once
#include <cocos2d.h>
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;
class soundManager
{
public:
	static void playSound(char*);
	static void preloadObjectSounds(char*);
	static void preloadBg(char*);
	static void playBackgroundMusic(char*);
	static void disableSounds(); 
	static void stopAllSounds();
private:
	int sounds_playing;
	static bool play_sounds;
};