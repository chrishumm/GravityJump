#include "soundManager.h"

bool soundManager::play_sounds = true;

void soundManager::playSound(char* sound)
{
	if (play_sounds == true)
		SimpleAudioEngine::sharedEngine()->playEffect(sound);
}

void soundManager::preloadObjectSounds(char* sound)
{
	if (play_sounds == true)
		SimpleAudioEngine::sharedEngine()->preloadEffect(sound);
}
void soundManager::playBackgroundMusic(char* background_song)
{
	if (play_sounds == true)
	{
		if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
			SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
		else
			SimpleAudioEngine::sharedEngine()->playBackgroundMusic(background_song, true);
	}
}
void soundManager::preloadBg(char* background_song)
{
	if (play_sounds == true)
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic(background_song);
}
void soundManager::stopAllSounds()
{
	if (play_sounds == true)
	{
		SimpleAudioEngine::sharedEngine()->stopAllEffects();
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
}

void soundManager::disableSounds()
{
	play_sounds = false;
}