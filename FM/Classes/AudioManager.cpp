#include "AudioManager.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

USING_NS_CC;

static int backgroundAudioID = AudioEngine::INVALID_AUDIO_ID;
static int playerActionAudioID = AudioEngine::INVALID_AUDIO_ID;
static int randomAudioID = AudioEngine::INVALID_AUDIO_ID;

#define ENABLE_AUDIO

void AudioManager::preloadAudio()
{
#ifdef ENABLE_AUDIO
	AudioEngine::preload("audio/1 Exploration LOOP TomMusic.ogg");
	AudioEngine::preload("audio/2 Journey LOOP TomMusic.ogg");
	AudioEngine::preload("audio/3 A Magic Forest LOOP TomMusic.ogg");
	AudioEngine::preload("audio/4 Battle Track LOOP TomMusic.ogg");
#endif
}


void AudioManager::playBackgroundAudio(SceneName _sceneName)
{
#ifdef ENABLE_AUDIO
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
	case SceneName::Battle:
		playKarmaAudio(KarmaEmotion::Bloodthirsty, 2);
		backgroundAudioID = AudioEngine::play2d("audio/4 Battle Track LOOP TomMusic.ogg", true);
		break;
	case SceneName::Victory:
		playKarmaAudio(KarmaEmotion::Winner);
		backgroundAudioID = AudioEngine::play2d("audio/Creme.ogg", true);
		break;
	default:
		break;
	}
#endif
}

void AudioManager::playPlayerAudio(PlayerCharacter::State _playerState)
{
#ifdef ENABLE_AUDIO
	if (playerActionAudioID != AudioEngine::INVALID_AUDIO_ID) {
		AudioEngine::stop(playerActionAudioID);
	}

	switch (_playerState)
	{
	case PlayerCharacter::State::IDLE:
		break;
	case PlayerCharacter::State::JUMPING:
		playerActionAudioID = AudioEngine::play2d("audio/hero_jump.ogg");
		break;
	case PlayerCharacter::State::FALLING:
		playerActionAudioID = AudioEngine::play2d("audio/hero_falling.ogg", true);
		break;
	case PlayerCharacter::State::RUNING:
		playerActionAudioID = AudioEngine::play2d("audio/hero_run_footsteps_grass.ogg", true);
		break;
	case PlayerCharacter::State::ATTACK1:
	case PlayerCharacter::State::ATTACK2:
	case PlayerCharacter::State::ATTACK3:
		playerActionAudioID = AudioEngine::play2d("audio/veBF_03at.ogg");
		AudioEngine::play2d("audio/sword sound.ogg");
		break;
	case PlayerCharacter::State::TAKE_HIT:
		playerActionAudioID = AudioEngine::play2d("audio/veBF_04dm.ogg");
		break;
	case PlayerCharacter::State::DEATH:
		playerActionAudioID = AudioEngine::play2d("audio/veBF_10dead.ogg");
		break;
	default:
		break;
	}
#endif
}

void AudioManager::playKarmaAudio(KarmaEmotion _state, int option)
{
#ifdef ENABLE_AUDIO
	const float volumeAu = 0.3f;

	int iSecret, iGuess;

	/* initialize random seed: */
	srand(time(NULL));

	/* generate secret number between 1 and 10: */
	if (option >= 0) {
		iSecret = option;
	}
	else {
		iSecret = rand() % 3;
	}
	

	switch (_state)
	{
	case AudioManager::KarmaEmotion::Normal:
		if (iSecret == 2) {
			AudioEngine::play2d("audio/prepare_yourself.ogg", false, volumeAu);
		}
		else if (iSecret == 1) {
			AudioEngine::play2d("audio/it's_a_tie.ogg", false, volumeAu);
		}
		else {
			AudioEngine::play2d("audio/tie.ogg", false, volumeAu);
		}
		break;
	case AudioManager::KarmaEmotion::Winner:
		if (iSecret == 2) {
			AudioEngine::play2d("audio/winner.ogg", false, volumeAu);
		}
		else if (iSecret == 1) {
			AudioEngine::play2d("audio/flawless_victory.ogg", false, volumeAu);
		}
		else {
			AudioEngine::play2d("audio/you_win.ogg", false, volumeAu);
		}
		break;
	case AudioManager::KarmaEmotion::Loser:
		if (iSecret == 2) {
			AudioEngine::play2d("audio/loser.ogg", false, volumeAu);
		}
		else if (iSecret == 1) {
			AudioEngine::play2d("audio/game_over.ogg", false, volumeAu);
		}
		else {
			AudioEngine::play2d("audio/you_lose.ogg", false, volumeAu);
		}
		break;
	case AudioManager::KarmaEmotion::Fight:
		if (iSecret == 2) {
			AudioEngine::play2d("audio/fight.ogg", false, volumeAu);
		}
		else if (iSecret == 1) {
			AudioEngine::play2d("audio/combo.ogg", false, volumeAu);
		}
		else {
			AudioEngine::play2d("audio/combo_breaker.ogg", false, volumeAu);
		}
		break;
	case AudioManager::KarmaEmotion::Uncontrolled:
		if (iSecret == 2) {
			AudioEngine::play2d("audio/tie_breaker.ogg", false, volumeAu);
		}
		else if (iSecret == 1) {
			AudioEngine::play2d("audio/time.ogg", false, volumeAu);
		}
		else {
			AudioEngine::play2d("audio/begin.ogg", false, volumeAu);
		}
		break;
	case AudioManager::KarmaEmotion::Bloodthirsty:
		if (iSecret == 2) {
			AudioEngine::play2d("audio/kill_it.ogg", false, volumeAu);
		}
		else if (iSecret == 1) {
			AudioEngine::play2d("audio/multi_kill.ogg", false, volumeAu);
		}
		else {
			AudioEngine::play2d("audio/kill_him.ogg", false, volumeAu);
		}
		break;
	default:
		break;
	}
#endif
}

void AudioManager::playRandomAudio(RandomAction _action)
{
#ifdef ENABLE_AUDIO
	switch (_action)
	{
	case AudioManager::RandomAction::Collect:
		randomAudioID = AudioEngine::play2d("audio/Get_Item3.ogg");
		break;
	case AudioManager::RandomAction::Hit:
		randomAudioID = AudioEngine::play2d("audio/Hit_Hurt1.ogg");
		break;
	case AudioManager::RandomAction::Click:
		randomAudioID = AudioEngine::play2d("audio/Click5.ogg");
		break;
	default:
		break;
	}
#endif
}


