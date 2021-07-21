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
	playerCharacterType = 0;

	characterMap.clear();
	countCharacter = 0;

	itemMap.clear();
	countItem = 0;
}

PlayerCharacter * GameManager::GetPlayerCharacter(bool withInit)
{
	if (playerCharacter == nullptr) {
		playerCharacter = new PlayerCharacter(playerCharacterType);

		this->AddCharacter(playerCharacter);
	}
	else if (withInit) {
		playerCharacter->init(playerCharacterType);
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

bool GameManager::onContactBegin(cocos2d::PhysicsContact & contact)
{
	return false;
}

void GameManager::onContactSeperate(cocos2d::PhysicsContact & contact)
{
}

void GameManager::AddCharacter(Character * ref)
{
	characterMap[++countCharacter] = ref;

	ref->getSprite()->setTag(countCharacter);
}

void GameManager::AddItem(Item * ref)
{
	itemMap[++countItem] = ref;

	ref->getSprite()->setTag(countItem);
}

void GameManager::AddReward(cocos2d::Vec2 position, int type)
{
	switch (type)
	{
	default:
		auto gold = new Item(Item::ItemType::GOLD);
		
		//gold->getSprite()->setPosition(position);
		//playerCharacter->getSprite()->getParent()->addChild(gold->getSprite());

		//GameManager::getInstace()->AddItem(gold);
		playerCharacter->colectItem(gold);
		break;
	}
}

void GameManager::hit(int attacker, int victim)
{
	int dame = playerCharacter->getStats().ATK;
	characterMap[victim]->takeHit(dame);
}

void GameManager::colect(int item)
{
	playerCharacter->colectItem(itemMap[item]);
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
