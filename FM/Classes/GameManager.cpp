#include "GameManager.h"

static GameManager * _shareGameManager = nullptr;
GameManager * GameManager::getInstace()
{
	if (!_shareGameManager) {
		_shareGameManager = create();
	}
	
	return _shareGameManager;
}

PlayerCharacter * GameManager::GetPlayerCharacter()
{
	if (playerCharacter == nullptr) {
		playerCharacter = new PlayerCharacter();
	}
	return playerCharacter;
}

Mission* GameManager::getMission() {
	if (mission == nullptr) {
		mission = new Mission();
	}
	return mission;
}

MonsterCharacter * GameManager::GetMonsterCharacter(int tag)
{
	if (tag >= monsterCharacters.size()) {
		return nullptr;
	}
	return monsterCharacters[tag];
}

int GameManager::AddMonsterCharacter(MonsterCharacter * ref)
{
	monsterCharacters[++countMonsterCharacter] = ref;

	return countMonsterCharacter;
}

void GameManager::hit(int attacker, int victim)
{
	int dame = playerCharacter->getStats().ATK;
	monsterCharacters[victim]->hurt(dame);
}

GameManager * GameManager::create()
{
	GameManager* gameManager = new GameManager();

	if (gameManager)
	{
		//gameManager->autorelease();
	}
	else
	{
		delete gameManager;
		gameManager = 0;
	}
	return gameManager;
}
