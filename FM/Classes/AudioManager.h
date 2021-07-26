#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include "cocos2d.h"
#include "AudioEngine.h"

#include "Definitions.h"

class AudioManager
{
public:
	enum class SceneName {
		MainMenu, Village, Play
	};

	static void preloadAudio();
	static void playBackgroundAudio(SceneName _sceneName);
	static void playBattleAudio();

private:

};

#endif // __AUDIO_MANAGER_H__
