#include "GameManager.h"

static GameManager * _shareGameManager = nullptr;
GameManager * GameManager::getInstace()
{
	if (!_shareGameManager) {
		_shareGameManager = create();
	}
	
	return _shareGameManager;
}

void GameManager::init()
{
	//load from here, when saving
	playerCharacter = nullptr;

	characterMap.clear();
	countCharacter = 0;
}

PlayerCharacter * GameManager::GetPlayerCharacter()
{
	if (playerCharacter == nullptr) {
		playerCharacter = new PlayerCharacter();

		this->AddCharacter(playerCharacter);
	}
	else {
		playerCharacter->init();
	}

	return playerCharacter;
}

Mission* GameManager::getMission() {
	if (mission == nullptr) {
		mission = new Mission();
	}
	return mission;
}

PhysicsShapeCache* GameManager::getPhysicsShapeCache() {
	if (shapeCache == nullptr) {
		shapeCache = PhysicsShapeCache::getInstance();
		shapeCache->addShapesWithFile("plist/Boss_1/body.plist");
	}
	return shapeCache;
}

void GameManager::AddCharacter(Character * ref)
{
	characterMap[++countCharacter] = ref;

	ref->getSprite()->setTag(countCharacter);
}

void GameManager::hit(int attacker, int victim)
{
	int dame = playerCharacter->getStats().ATK;
	characterMap[victim]->takeHit(dame);
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
