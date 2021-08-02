#include "AudioManager.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

USING_NS_CC;

static int backgroundAudioID = AudioEngine::INVALID_AUDIO_ID;
static int playerActionAudioID = AudioEngine::INVALID_AUDIO_ID;
static int randomAudioID = AudioEngine::INVALID_AUDIO_ID;

static float audioVolume = 0.5f;
static float effectVolume = 0.2f;
static float karmaVolume = 0.2f;

static float iAudioVolume = audioVolume;
static float iEffectVolume = effectVolume;

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
		backgroundAudioID = AudioEngine::play2d("audio/2 Journey LOOP TomMusic.ogg", true, audioVolume);
		break;
	case SceneName::Village:
		backgroundAudioID = AudioEngine::play2d("audio/1 Exploration LOOP TomMusic.ogg", true, audioVolume);
		break;
	case SceneName::Play:
		backgroundAudioID = AudioEngine::play2d("audio/3 A Magic Forest LOOP TomMusic.ogg", true, audioVolume);
		break;
	case SceneName::Battle:
		playKarmaAudio(KarmaEmotion::Bloodthirsty, 2);
		backgroundAudioID = AudioEngine::play2d("audio/4 Battle Track LOOP TomMusic.ogg", true, audioVolume);
		break;
	case SceneName::Victory:
		playKarmaAudio(KarmaEmotion::Winner);
		backgroundAudioID = AudioEngine::play2d("audio/Creme.ogg", true, audioVolume);
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
		playerActionAudioID = AudioEngine::play2d("audio/hero_jump.ogg", false, effectVolume);
		break;
	case PlayerCharacter::State::FALLING:
		playerActionAudioID = AudioEngine::play2d("audio/hero_falling.ogg", true, effectVolume);
		break;
	case PlayerCharacter::State::RUNING:
		playerActionAudioID = AudioEngine::play2d("audio/hero_run_footsteps_grass.ogg", true, effectVolume);
		break;
	case PlayerCharacter::State::ATTACK1:
	case PlayerCharacter::State::ATTACK2:
	case PlayerCharacter::State::ATTACK3:
		playerActionAudioID = AudioEngine::play2d("audio/veBF_03at.ogg", false, effectVolume);
		AudioEngine::play2d("audio/sword sound.ogg", false, effectVolume);
		break;
	case PlayerCharacter::State::TAKE_HIT:
		playerActionAudioID = AudioEngine::play2d("audio/veBF_04dm.ogg", false, effectVolume);
		break;
	case PlayerCharacter::State::DEATH:
		playerActionAudioID = AudioEngine::play2d("audio/veBF_10dead.ogg", false, effectVolume);
		break;
	default:
		break;
	}
#endif
}

void AudioManager::playKarmaAudio(KarmaEmotion _state, int option)
{
#ifdef ENABLE_AUDIO

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
			AudioEngine::play2d("audio/prepare_yourself.ogg", false, karmaVolume);
		}
		else if (iSecret == 1) {
			AudioEngine::play2d("audio/it's_a_tie.ogg", false, karmaVolume);
		}
		else {
			AudioEngine::play2d("audio/tie.ogg", false, karmaVolume);
		}
		break;
	case AudioManager::KarmaEmotion::Winner:
		if (iSecret == 2) {
			AudioEngine::play2d("audio/winner.ogg", false, karmaVolume);
		}
		else if (iSecret == 1) {
			AudioEngine::play2d("audio/flawless_victory.ogg", false, karmaVolume);
		}
		else {
			AudioEngine::play2d("audio/you_win.ogg", false, karmaVolume);
		}
		break;
	case AudioManager::KarmaEmotion::Loser:
		if (iSecret == 2) {
			AudioEngine::play2d("audio/loser.ogg", false, karmaVolume);
		}
		else if (iSecret == 1) {
			AudioEngine::play2d("audio/game_over.ogg", false, karmaVolume);
		}
		else {
			AudioEngine::play2d("audio/you_lose.ogg", false, karmaVolume);
		}
		break;
	case AudioManager::KarmaEmotion::Fight:
		if (iSecret == 2) {
			AudioEngine::play2d("audio/fight.ogg", false, karmaVolume);
		}
		else if (iSecret == 1) {
			AudioEngine::play2d("audio/combo.ogg", false, karmaVolume);
		}
		else {
			AudioEngine::play2d("audio/combo_breaker.ogg", false, karmaVolume);
		}
		break;
	case AudioManager::KarmaEmotion::Uncontrolled:
		if (iSecret == 2) {
			AudioEngine::play2d("audio/tie_breaker.ogg", false, karmaVolume);
		}
		else if (iSecret == 1) {
			AudioEngine::play2d("audio/time.ogg", false, karmaVolume);
		}
		else {
			AudioEngine::play2d("audio/begin.ogg", false, karmaVolume);
		}
		break;
	case AudioManager::KarmaEmotion::Bloodthirsty:
		if (iSecret == 2) {
			AudioEngine::play2d("audio/kill_it.ogg", false, karmaVolume);
		}
		else if (iSecret == 1) {
			AudioEngine::play2d("audio/multi_kill.ogg", false, karmaVolume);
		}
		else {
			AudioEngine::play2d("audio/kill_him.ogg", false, karmaVolume);
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
		randomAudioID = AudioEngine::play2d("audio/Get_Item3.ogg", false, effectVolume);
		break;
	case AudioManager::RandomAction::Hit:
		randomAudioID = AudioEngine::play2d("audio/Hit_Hurt1.ogg", false, effectVolume);
		break;
	case AudioManager::RandomAction::Click:
		randomAudioID = AudioEngine::play2d("audio/Click5.ogg", false, effectVolume);
		break;
	case AudioManager::RandomAction::Click_Error:
		randomAudioID = AudioEngine::play2d("audio/Click7.ogg", false, effectVolume);
		break;
	case AudioManager::RandomAction::Click_Menu:
		randomAudioID = AudioEngine::play2d("audio/Click6.ogg", false, effectVolume);
		break;
	default:
		break;
	}
#endif
}

int AudioManager::getAudioVolume()
{
	return int(iAudioVolume * 100);
}

void AudioManager::setAudioVolume(int _volume, bool _i)
{
	audioVolume = _volume * 1.f / 100;
	AudioEngine::setVolume(backgroundAudioID, audioVolume);
	if (_i) iAudioVolume = audioVolume;
}

int AudioManager::getEffectVolume()
{
	return int(iEffectVolume * 100);
}

void AudioManager::setEffectVolume(int _volume, bool _i)
{
	effectVolume = _volume * 1.f / 100;
	karmaVolume = effectVolume;
	if (_i) iEffectVolume = effectVolume;
}

void AudioManager::muteAudio()
{
	setAudioVolume(0, false);
	setEffectVolume(0, false);
}

void AudioManager::unmuteAudio()
{
	setAudioVolume(int(iAudioVolume * 100));
	setEffectVolume(int(iEffectVolume * 100));
}

bool AudioManager::isMuteAudio()
{
	return int(audioVolume * 100 + effectVolume * 100) == 0;
}


