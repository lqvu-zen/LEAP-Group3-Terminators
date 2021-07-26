#include "AudioManager.h"

USING_NS_CC;

static int backgroundAudioID = AudioEngine::INVALID_AUDIO_ID;

void AudioManager::preloadAudio()
{
	AudioEngine::preload("audio/1 Exploration LOOP TomMusic.ogg");
	AudioEngine::preload("audio/2 Journey LOOP TomMusic.ogg");
	AudioEngine::preload("audio/3 A Magic Forest LOOP TomMusic.ogg");
}

void AudioManager::playBackgroundAudio(SceneName _sceneName)
{
	if (backgroundAudioID != AudioEngine::INVALID_AUDIO_ID) {
		AudioEngine::stop(backgroundAudioID);
	}

	switch (_sceneName)
	{
	case SceneName::MainMenu:
		backgroundAudioID = AudioEngine::play2d("audio/2 Journey LOOP TomMusic.ogg", true);
		break;
	case SceneName::Village:
		backgroundAudioID = AudioEngine::play2d("audio/1 Exploration LOOP TomMusic.ogg", true);
		break;
	case SceneName::Play:
		backgroundAudioID = AudioEngine::play2d("audio/3 A Magic Forest LOOP TomMusic.ogg", true);
		break;
	default:
		break;
	}
}

void AudioManager::playBattleAudio()
{
	if (backgroundAudioID != AudioEngine::INVALID_AUDIO_ID) {
		AudioEngine::pause(backgroundAudioID);
	}

	AudioEngine::play2d("audio/4 Battle Track LOOP TomMusic.ogg", true);
}
