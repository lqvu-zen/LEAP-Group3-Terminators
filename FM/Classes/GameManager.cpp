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
	collectedItems.clear();
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

void GameManager::PlayerDarker()
{
	playerCharacter->getDarker();
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

void GameManager::SaveGame()
{
	UserDefault::getInstance()->setIntegerForKey("SAVED", 1);
	//Save Player
	UserDefault::getInstance()->setFloatForKey("PLAYER_HP", playerCharacter->getStats().HP);
	UserDefault::getInstance()->setFloatForKey("PLAYER_MP", playerCharacter->getStats().MP);
	UserDefault::getInstance()->setFloatForKey("PLAYER_ATK", playerCharacter->getStats().ATK);
	UserDefault::getInstance()->setFloatForKey("PLAYER_DEF", playerCharacter->getStats().DEF);

	UserDefault::getInstance()->setIntegerForKey("PLAYER_KARMA", playerCharacter->getStats().Karma);

	UserDefault::getInstance()->setFloatForKey("PLAYER_MAXHP", playerCharacter->getStats().maxHP);
	UserDefault::getInstance()->setFloatForKey("PLAYER_MAXMP", playerCharacter->getStats().maxMP);
	UserDefault::getInstance()->setFloatForKey("PLAYER_MAXATK", playerCharacter->getStats().maxATK);
	UserDefault::getInstance()->setFloatForKey("PLAYER_MAXDEF", playerCharacter->getStats().maxDEF);
	UserDefault::getInstance()->setIntegerForKey("PLAYER_MAXJUMP", playerCharacter->getStats().maxJump);

	//Save Inventory
	UserDefault::getInstance()->setIntegerForKey("INVENTORY_GOLD", playerCharacter->getInventory().getItemCount(Item::ItemType::GOLD));
	UserDefault::getInstance()->setIntegerForKey("INVENTORY_GEM", playerCharacter->getInventory().getItemCount(Item::ItemType::GEM));
	UserDefault::getInstance()->setIntegerForKey("INVENTORY_HPPOTION", playerCharacter->getInventory().getItemCount(Item::ItemType::HP_POTION));
	UserDefault::getInstance()->setIntegerForKey("INVENTORY_MPPOTION", playerCharacter->getInventory().getItemCount(Item::ItemType::MP_POTION));
	UserDefault::getInstance()->setIntegerForKey("INVENTORY_DBOOTS", playerCharacter->getInventory().getItemCount(Item::ItemType::D_BOOTS));

	//Save Mission
	UserDefault::getInstance()->setIntegerForKey("INDEX_MISSION", mission->getIndexMission());
	UserDefault::getInstance()->setIntegerForKey("MISSION_ID", mission->get().id);
	UserDefault::getInstance()->setIntegerForKey("MISSION_BEGIN", mission->get().begin);
	UserDefault::getInstance()->setIntegerForKey("MISSION_STATE", mission->get().state);
	UserDefault::getInstance()->setBoolForKey("HAS_MISSION", mission->getProcesstate());

	//Save Collected Items
	UserDefault::getInstance()->setIntegerForKey("COLLECTED_ITEMS_SIZE", collectedItems.size());
	for (int i = 0; i < collectedItems.size(); ++i)
	{
		auto collectedItem = StringUtils::format("COLLECTED_ITEM%d", i);
		UserDefault::getInstance()->setIntegerForKey(collectedItem.c_str(), collectedItems.at(i));
	}
}

void GameManager::LoadGame()
{
	setLoadOption(0);
	//Load Player
	auto hp = UserDefault::getInstance()->getFloatForKey("PLAYER_HP", playerCharacter->getStats().HP);
	auto mp = UserDefault::getInstance()->getFloatForKey("PLAYER_MP", playerCharacter->getStats().MP);
	auto atk = UserDefault::getInstance()->getFloatForKey("PLAYER_ATK", playerCharacter->getStats().ATK);
	auto def = UserDefault::getInstance()->getFloatForKey("PLAYER_DEF", playerCharacter->getStats().DEF);

	auto karma = UserDefault::getInstance()->getIntegerForKey("PLAYER_KARMA", playerCharacter->getStats().Karma);

	auto max_hp = UserDefault::getInstance()->getFloatForKey("PLAYER_MAXHP", playerCharacter->getStats().maxHP);
	auto max_mp = UserDefault::getInstance()->getFloatForKey("PLAYER_MAXMP", playerCharacter->getStats().maxMP);
	auto max_atk = UserDefault::getInstance()->getFloatForKey("PLAYER_MAXATK", playerCharacter->getStats().maxATK);
	auto max_def = UserDefault::getInstance()->getFloatForKey("PLAYER_MAXDEF", playerCharacter->getStats().maxDEF);
	auto max_jump = UserDefault::getInstance()->getIntegerForKey("PLAYER_MAXJUMP", playerCharacter->getStats().maxJump);

	playerCharacter->LoadStats(hp, mp, atk, def, karma, max_hp, max_mp, max_atk, max_def, max_jump);

	//Load inventory
	auto c_gold = UserDefault::getInstance()->getIntegerForKey("INVENTORY_GOLD", playerCharacter->getInventory().getItemCount(Item::ItemType::GOLD));
	auto c_gem = UserDefault::getInstance()->getIntegerForKey("INVENTORY_GEM", playerCharacter->getInventory().getItemCount(Item::ItemType::GEM));
	auto c_hpPotion = UserDefault::getInstance()->getIntegerForKey("INVENTORY_HPPOTION", playerCharacter->getInventory().getItemCount(Item::ItemType::HP_POTION));
	auto c_mpPotion = UserDefault::getInstance()->getIntegerForKey("INVENTORY_MPPOTION", playerCharacter->getInventory().getItemCount(Item::ItemType::MP_POTION));
	auto c_dBoots = UserDefault::getInstance()->getIntegerForKey("INVENTORY_DBOOTS", playerCharacter->getInventory().getItemCount(Item::ItemType::D_BOOTS));

	if (playerCharacter->getInventory().getItemCount(Item::ItemType::GOLD) < c_gold) {
		auto tempItem = new Item(Item::ItemType::GOLD);
		playerCharacter->colectItem(tempItem, c_gold - playerCharacter->getInventory().getItemCount(Item::ItemType::GOLD));
	}

	if (playerCharacter->getInventory().getItemCount(Item::ItemType::GEM) < c_gem) {
		auto tempItem = new Item(Item::ItemType::GEM);
		playerCharacter->colectItem(tempItem, c_gem - playerCharacter->getInventory().getItemCount(Item::ItemType::GEM));
	}

	if (playerCharacter->getInventory().getItemCount(Item::ItemType::HP_POTION) < c_hpPotion) {
		auto tempItem = new Item(Item::ItemType::HP_POTION);
		playerCharacter->colectItem(tempItem, c_hpPotion - playerCharacter->getInventory().getItemCount(Item::ItemType::HP_POTION));
	}

	if (playerCharacter->getInventory().getItemCount(Item::ItemType::MP_POTION) < c_mpPotion) {
		auto tempItem = new Item(Item::ItemType::MP_POTION);
		playerCharacter->colectItem(tempItem, c_mpPotion - playerCharacter->getInventory().getItemCount(Item::ItemType::MP_POTION));
	}

	if (playerCharacter->getInventory().getItemCount(Item::ItemType::D_BOOTS) < c_dBoots) {
		auto tempItem = new Item(Item::ItemType::D_BOOTS);
		playerCharacter->colectItem(tempItem, 0);
	}
	
	//load Mission
	int index = UserDefault::getInstance()->getIntegerForKey("INDEX_MISSION");
	int id = UserDefault::getInstance()->getIntegerForKey("MISSION_ID");
	int begin = UserDefault::getInstance()->getIntegerForKey("MISSION_BEGIN");
	int state = UserDefault::getInstance()->getIntegerForKey("MISSION_STATE");
	bool has = UserDefault::getInstance()->getBoolForKey("HAS_MISSION");
	mission->loadMission(index, id, begin, state, has);

	//Load collected items.
	auto collectedItemCount = UserDefault::getInstance()->getIntegerForKey("COLLECTED_ITEMS_SIZE");
	if (collectedItemCount != 0)
	{
		for (int i = 0; i < collectedItemCount; ++i)
		{
			auto collectedItem = StringUtils::format("COLLECTED_ITEM%d", i);
			collectedItems.push_back(UserDefault::getInstance()->getIntegerForKey(collectedItem.c_str()));
		}
	}
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

void GameManager::setLoadOption(int option)
{
	loadOption = 1;
}

int GameManager::getLoadOption()
{
	return loadOption;
}

int GameManager::getMapHiddenAreasCount()
{
	return mapHiddenAreaCount;
}

int GameManager::getMapLevel()
{
	return mapLevel;
}