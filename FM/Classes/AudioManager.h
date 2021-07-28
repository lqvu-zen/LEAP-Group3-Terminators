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

	enum class KarmaEmotion {
		Normal, Winner, Loser, Bloodthirsty, Uncontrolled, Fight
	};

	static void preloadAudio();

	static void playBackgroundAudio(SceneName _sceneName);

	static void playPlayerAudio(PlayerCharacter::State _playerState);
	static void playKarmaAudio(KarmaEmotion _state, int option = -1);

	static void playRandomAudio(RandomAction _action);

private:

};

#endif // __AUDIO_MANAGER_H__
