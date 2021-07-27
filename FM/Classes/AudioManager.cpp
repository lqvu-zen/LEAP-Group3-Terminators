//#include "AudioManager.h"
//
//USING_NS_CC;
//
//static int backgroundAudioID = AudioEngine::INVALID_AUDIO_ID;
//static int playerActionAudioID = AudioEngine::INVALID_AUDIO_ID;
//static int randomAudioID = AudioEngine::INVALID_AUDIO_ID;
//
//void AudioManager::preloadAudio()
//{
//	AudioEngine::preload("audio/1 Exploration LOOP TomMusic.ogg");
//	AudioEngine::preload("audio/2 Journey LOOP TomMusic.ogg");
//	AudioEngine::preload("audio/3 A Magic Forest LOOP TomMusic.ogg");
//	AudioEngine::preload("audio/4 Battle Track LOOP TomMusic.ogg");
//
//
//}
//
//void AudioManager::playBackgroundAudio(SceneName _sceneName)
//{
//	if (backgroundAudioID != AudioEngine::INVALID_AUDIO_ID) {
//		AudioEngine::stop(backgroundAudioID);
//	}
//
//	switch (_sceneName)
//	{
//	case SceneName::MainMenu:
//		backgroundAudioID = AudioEngine::play2d("audio/2 Journey LOOP TomMusic.ogg", true);
//		break;
//	case SceneName::Village:
//		backgroundAudioID = AudioEngine::play2d("audio/1 Exploration LOOP TomMusic.ogg", true);
//		break;
//	case SceneName::Play:
//		backgroundAudioID = AudioEngine::play2d("audio/3 A Magic Forest LOOP TomMusic.ogg", true);
//		break;
//	case SceneName::Battle:
//		AudioEngine::play2d("audio/kill_him.ogg");
//		backgroundAudioID = AudioEngine::play2d("audio/4 Battle Track LOOP TomMusic.ogg", true);
//		break;
//	case SceneName::Victory:
//		AudioEngine::play2d("audio/you_win.ogg");
//		backgroundAudioID = AudioEngine::play2d("audio/Creme.ogg", true);
//		break;
//	default:
//		break;
//	}
//}
//
//void AudioManager::playPlayerAudio(PlayerCharacter::State _playerState)
//{
//	if (playerActionAudioID != AudioEngine::INVALID_AUDIO_ID) {
//		AudioEngine::stop(playerActionAudioID);
//	}
//
//	switch (_playerState)
//	{
//	case PlayerCharacter::State::IDLE:
//		break;
//	case PlayerCharacter::State::JUMPING:
//		playerActionAudioID = AudioEngine::play2d("audio/hero_jump.ogg");
//		break;
//	case PlayerCharacter::State::FALLING:
//		playerActionAudioID = AudioEngine::play2d("audio/hero_falling.ogg", true);
//		break;
//	case PlayerCharacter::State::RUNING:
//		playerActionAudioID = AudioEngine::play2d("audio/hero_run_footsteps_grass.ogg", true);
//		break;
//	case PlayerCharacter::State::ATTACK1:
//	case PlayerCharacter::State::ATTACK2:
//	case PlayerCharacter::State::ATTACK3:
//		playerActionAudioID = AudioEngine::play2d("audio/veBF_03at.ogg");
//		AudioEngine::play2d("audio/sword sound.ogg");
//		break;
//	case PlayerCharacter::State::TAKE_HIT:
//		playerActionAudioID = AudioEngine::play2d("audio/veBF_04dm.ogg");
//		break;
//	case PlayerCharacter::State::DEATH:
//		playerActionAudioID = AudioEngine::play2d("audio/veBF_10dead.ogg");
//		break;
//	default:
//		break;
//	}
//}
//
//void AudioManager::playKarmaAudio(KarmaEmotion _state)
//{
//}
//
//void AudioManager::playRandomAudio(RandomAction _action)
//{
//	switch (_action)
//	{
//	case AudioManager::RandomAction::Collect:
//		randomAudioID = AudioEngine::play2d("audio/Get_Item3.ogg");
//		break;
//	case AudioManager::RandomAction::Hit:
//		randomAudioID = AudioEngine::play2d("audio/Hit_Hurt1.ogg");
//		break;
//	case AudioManager::RandomAction::Click:
//		randomAudioID = AudioEngine::play2d("audio/Click5.ogg");
//		break;
//	default:
//		break;
//	}
//}
//
//
