#ifndef __AUDIO_MANAGER_H__
#define __AUDIO_MANAGER_H__

#include "cocos2d.h"
#include "AudioEngine.h"
#include "PlayerCharacter.h"

#include "Definitions.h"

class AudioManager
{
public:
	enum class SceneName {
		MainMenu, Village, Play, Battle, Victory
	};

	enum class RandomAction {
		Collect, Hit, Click
	};

	static void preloadAudio();

	static void playBackgroundAudio(SceneName _sceneName);

	static void playPlayerAudio(PlayerCharacter::State _playerState);

	static void playRandomAudio(RandomAction _action);

private:

};

#endif // __AUDIO_MANAGER_H__
