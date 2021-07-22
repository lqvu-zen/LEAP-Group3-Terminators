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
	countDead = 0;
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

std::string GameManager::getMapName()
{
	//return the mapName based on the current map level. Use GameManager::setMapLevel(int level) to set the level.
	std::string mapPath = "";
	//load map path name from the json file.
	std::string str = FileUtils::getInstance()->getStringFromFile("res/map.json");
	rapidjson::Document doc;
	doc.Parse<0>(str.c_str());
	if (doc.HasParseError())
	{
		CCLOG("Reading JSON error");
	}
	else
	{
		if (doc.HasMember("MAP"))
		{
			rapidjson::Value& map = doc["MAP"];
			for (rapidjson::SizeType i = 0; i < map.Size(); i++)
			{
				if (map[i]["ID"].GetInt() == mapLevel)
				{
					//Get the map path and the amount of hidden areas in the map from the JSON file.
					mapPath = map[i]["PATH"].GetString();
					mapHiddenAreaCount = map[i]["HIDDEN_AREAS"].GetInt();
				}
			}
		}
	}
	return mapPath;
}

void GameManager::setMapLevel(int level)
{
	//Set the map level. 0: village map, 1: playMap 1, 2: playMap 2, etc...
	mapLevel = level;
}

int GameManager::getMapHiddenAreasCount()
{
	return mapHiddenAreaCount;
}