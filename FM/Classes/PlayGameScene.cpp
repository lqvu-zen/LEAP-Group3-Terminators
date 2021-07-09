#include "Definitions.h"
#include "PlayGameScene.h"
#include "Popup2.h"
USING_NS_CC;

Scene* PlayGameScene::createScene()
{
	auto scene = PlayGameScene::create();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setGravity(Vect(0, 0));//test world with gravity physics!!! Working for now!!!
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PlayGameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::initWithPhysics())
	{
		return false;
	}

	//buttonNode to holds the buttons and gameNode to holds the game
	buttonNode = Node::create();
	gameNode = Node::create();
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//Add buttons
#if 1
	auto pauseButton = ui::Button::create("sprites/pauseButton.png");
	pauseButton->setScale(0.1);
	pauseButton->setPosition(Vec2(visibleSize.width - pauseButton->getContentSize().width * 0.05, visibleSize.height - pauseButton->getContentSize().height * 0.05));
	pauseButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Mission* mission = new Mission();
			UICustom::Popup* popup = UICustom::Popup::createAsMessage("Mission", GameManager::getInstace()->getMission()->getNowMission().name);
			buttonNode->addChild(popup, 100);
			break;
		}
	});
	buttonNode->addChild(pauseButton, 100);
#endif

#if 1
	auto button = Sprite::create("sprites/button.png");
	button->setScale(0.2);
	button->setPosition(Vec2(button->getContentSize().width * 0.1, button->getContentSize().height * 0.05));
	//buttonNode->addChild(button, -100);

	auto upItem = ui::Button::create("sprites/up.png");
	upItem->setScale(0.4);
	upItem->setPosition(Vec2(button->getPosition().x, button->getPosition().y + button->getContentSize().height * 0.2 / 4));
	buttonNode->addChild(upItem, 100);
	upItem->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			if (std::find(heldKeys.begin(), heldKeys.end(), cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) == heldKeys.end()) {
				heldKeys.push_back(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW);
			}
			CCLOG("Up");
			break;
		case ui::Widget::TouchEventType::ENDED:
			heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW), heldKeys.end());
			CCLOG("End Up");
			break;
		}
	});

	auto leftItem = ui::Button::create("sprites/left.png");
	leftItem->setScale(0.1);
	leftItem->setPosition(Vec2(button->getPosition().x - button->getContentSize().width * 0.2 / 4, button->getPosition().y));
	buttonNode->addChild(leftItem, 100);
	leftItem->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			if (std::find(heldKeys.begin(), heldKeys.end(), cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) == heldKeys.end()) {
				heldKeys.push_back(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW);
			}
			CCLOG("Left");
			break;
		case ui::Widget::TouchEventType::ENDED:
			heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW), heldKeys.end());
			CCLOG("End Left");
			break;
		}
	});

	auto rightItem = ui::Button::create("sprites/right.png");
	rightItem->setScale(0.1);
	rightItem->setPosition(Vec2(button->getPosition().x + button->getContentSize().width * 0.2 / 4, button->getPosition().y));
	buttonNode->addChild(rightItem, 100);
	rightItem->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			if (std::find(heldKeys.begin(), heldKeys.end(), cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) == heldKeys.end()) {
				heldKeys.push_back(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
			}
			CCLOG("Right");
			break;
		case ui::Widget::TouchEventType::ENDED:
			heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW), heldKeys.end());
			CCLOG("End Right");
			break;
		}
	});
#endif

#if 1

	auto attackItem = MenuItemImage::create("sprites/attack.png", "sprites/attack.png", CC_CALLBACK_1(PlayGameScene::onClickAttackMenu, this));
	attackItem->setScale(0.7);
	attackItem->setPosition(Vec2(visibleSize.width - attackItem->getContentSize().width * 0.35, attackItem->getContentSize().height * 0.35));
	attackItem->setTag(1);

	auto skill_1Item = MenuItemImage::create("sprites/skill_1.png", "sprites/skill_1.png", CC_CALLBACK_1(PlayGameScene::onClickAttackMenu, this));
	skill_1Item->setScale(0.3);
	skill_1Item->setPosition(Vec2(visibleSize.width - attackItem->getContentSize().width * 0.7, attackItem->getContentSize().height * 0.2));
	skill_1Item->setTag(2);

	auto skill_2Item = MenuItemImage::create("sprites/skill_2.png", "sprites/skill_2.png", CC_CALLBACK_1(PlayGameScene::onClickAttackMenu, this));
	skill_2Item->setScale(0.3);
	skill_2Item->setPosition(Vec2(visibleSize.width - attackItem->getContentSize().width * 0.65, attackItem->getContentSize().height * 0.55));
	skill_2Item->setTag(3);

	auto skill_3Item = MenuItemImage::create("sprites/skill_3.png", "sprites/skill_3.png", CC_CALLBACK_1(PlayGameScene::onClickAttackMenu, this));
	skill_3Item->setScale(0.3);
	skill_3Item->setPosition(Vec2(visibleSize.width - attackItem->getContentSize().width * 0.3, attackItem->getContentSize().height * 0.7));
	skill_3Item->setTag(4);

	auto attackMenu = Menu::create(skill_1Item, skill_2Item, skill_3Item, attackItem, nullptr);
	attackMenu->setPosition(Vec2::ZERO);
	buttonNode->addChild(attackMenu, 100);
#endif





	//map setup + add map
	//scale map with SCALE_FACTOR
	map = TMXTiledMap::create("map/playMap.tmx");
	map->setScale(SCALE_FACTOR );
	gameNode->addChild(map, 0);

	//collision with map edges
	auto mapSize = Size((map->getMapSize().width * map->getTileSize().width) * SCALE_FACTOR, ((map->getMapSize().height * map->getTileSize().height) * SCALE_FACTOR) );
	auto edgeBody = PhysicsBody::createEdgeBox(mapSize, PhysicsMaterial(1.0f, 0.0f, 0.0f), 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(mapSize.width/2, mapSize.height/2));
	edgeBody->setCollisionBitmask(ALLSET_BITMASK);
	edgeBody->setContactTestBitmask(ALLCLEARED_BITMASK);

	edgeBody->setDynamic(false);
	edgeNode->setPhysicsBody(edgeBody);
	gameNode->addChild(edgeNode);

	//setup map physics. Since we are doing a 60x34 map so width = 60 and height = 34 (2 loops)
	TMXLayer *Foreground = map->getLayer("Foreground");
	for (int i = 0; i < 146; i++)
	{
		for (int j = 0; j < 34; j++)
		{
			auto spriteTile = Foreground->getTileAt(Vec2(i, j));
			if (spriteTile != NULL)
			{
				
				PhysicsBody* tilePhysics = PhysicsBody::createBox(spriteTile->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 0.0f));
				tilePhysics->setDynamic(false);
				tilePhysics->setCollisionBitmask(ALLSET_BITMASK);
				tilePhysics->setContactTestBitmask(ALLCLEARED_BITMASK);
				spriteTile->setPhysicsBody(tilePhysics);
			}
		}
	}

	//add character to the map
	TMXObjectGroup *objectGroup = map->getObjectGroup("Objects");
	if (objectGroup == NULL)
	{
		CCLOG("tile map has no objects layer");
	}

	//Change to spawn Player Character always in the middle of the map
	//Add character here!!!
	/*player = Sprite::create("sprites/yellowbird-midflap.png");
	player->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	auto playerBody = PhysicsBody::createBox(player->getContentSize());
	player->setPhysicsBody(playerBody);*/
	
	playerChar = GameManager::getInstace()->GetPlayerCharacter();
	playerChar->getSprite()->setScale(1.5);
	playerChar->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	
	
	

	//cameraTarget for the followCamera to follow the player.
	cameraTarget = Node::create();
	cameraTarget->setPositionX(playerChar->getSprite()->getPositionX());
	cameraTarget->setPositionY(visibleSize.height / 2 + origin.y);
	gameNode->addChild(cameraTarget);
	gameNode->addChild(playerChar->getSprite());

	//add healthbar
	auto playerStats = playerChar->getStats();
	auto playerStatsSprite = playerStats.GetSprite();
	auto scaleRatio = 3.0f;
	playerStatsSprite->setScale(scaleRatio);
	playerStatsSprite->setPosition(
		Vec2(
			origin.x,
			visibleSize.height + origin.y - playerStats.GetSpriteSize().height * scaleRatio
		)
		//Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)
	);
	buttonNode->addChild(playerStatsSprite, 100);

	//Add enemies here!!
	//Algorithm: get the EnemySpawn ValueMap from the objectGroup then check if the EnemySpawn has the value "Enemy == 1".
	//If true -> add enemey at the EnemySpawn.
	for (auto SpawnPoint : objectGroup->getObjects())
	{
		//Spawn enemy
		if (SpawnPoint.asValueMap()["Enemy"].asInt() == 1)
		{
			int eneX = SpawnPoint.asValueMap()["x"].asInt() * SCALE_FACTOR;
			int eneY = SpawnPoint.asValueMap()["y"].asInt() * SCALE_FACTOR;
			monsters[numOfMonster] = new MonsterCharacter(gameNode, 1);
			monsters[numOfMonster]->getSprite()->setPosition(eneX, eneY);

			int tag = GameManager::getInstace()->AddMonsterCharacter(monsters[numOfMonster]);

			monsters[numOfMonster]->getSprite()->setTag(tag);
			//auto enemyBody = PhysicsBody::createBox(enemy->getContentSize());
			//enemy->setPhysicsBody(enemyBody);
			gameNode->addChild(monsters[numOfMonster]->getSprite());
			numOfMonster++;
			
		}

		//Spawn gem
		if (SpawnPoint.asValueMap()["Gem"].asInt() == 1)
		{
			int gemX = SpawnPoint.asValueMap()["x"].asInt()* SCALE_FACTOR;
			int gemY = SpawnPoint.asValueMap()["y"].asInt() * SCALE_FACTOR;
			auto gem = new Gem();
			gem->getSprite()->setPosition(gemX, gemY);
			gameNode->addChild(gem->getSprite());
		}

		//Spawn boss
		if (SpawnPoint.asValueMap()["Boss"].asInt() == 1)
		{
			int bossX = SpawnPoint.asValueMap()["x"].asInt()* SCALE_FACTOR;
			int bossY = SpawnPoint.asValueMap()["y"].asInt() * SCALE_FACTOR;
			boss = new BossCharacter(1);
			boss->setPosition(Vec2(bossX, bossY));
			//boss->setPosition(visibleSize / 2);
			gameNode->addChild(boss->getSprite());
		}
	}

	//Contact test
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PlayGameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);



	//Keyboard test
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PlayGameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(PlayGameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	//Add a follow action to follow the cameraTarget(the player) with boundaries to follow.
	//The boundaries are the origin point (0, 0) and the total size of the map (in pixels) * SCALE_FACTOR.
	followCamera = Follow::create(cameraTarget, Rect(origin.x, origin.y, mapSize.width, mapSize.height));
	gameNode->runAction(followCamera);
	this->addChild(gameNode);
	this->addChild(buttonNode, 100);

	this->schedule(CC_SCHEDULE_SELECTOR(PlayGameScene::monsterAction), 3);
	
	this->schedule(CC_SCHEDULE_SELECTOR(PlayGameScene::updateBoss), 1);
	//boss->death();
	this->scheduleUpdate();

	return true;
}

void PlayGameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	//CCLOG("Key with keycode %d pressed, Character position: %f", keyCode, playerChar->getSprite()->getPositionX());
	if (std::find(heldKeys.begin(), heldKeys.end(), keyCode) == heldKeys.end()) {
		heldKeys.push_back(keyCode);
	}
}

void PlayGameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	CCLOG("Key with keycode %d released", keyCode);
	heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), keyCode), heldKeys.end());
}


void PlayGameScene::update(float dt)
{
	this->updateMonster(dt);
	cameraTarget->setPositionX(playerChar->getSprite()->getPositionX());
	this->updateCharacter(dt);
	//this->updateBoss(dt);

	//CCLOG("player position: %f. camera position: %f", playerChar->getSprite()->getPositionX(), cameraTarget->getPositionX());
}

void PlayGameScene::updateCharacter(float dt)
{
	//keys movement
	if (heldKeys.empty()) {
		playerChar->setVelocity(Vec2::ZERO);
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), UP_ARROW) != heldKeys.end()) {
		if (playerChar->isGrounded() && playerChar->getRealtimeVolocity().y <= PADDING_VELOCITY) {
			playerChar->setVelocity(Vec2(playerChar->getVolocity().x, PLAYER_JUMP_VELOCITY));
		}
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), RIGHT_ARROW) != heldKeys.end()) {
		playerChar->setVelocity(Vec2(PLAYER_MAX_VELOCITY, playerChar->getVolocity().y));
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), LEFT_ARROW) != heldKeys.end()) {
		playerChar->setVelocity(Vec2(-PLAYER_MAX_VELOCITY, playerChar->getVolocity().y));
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), ATTACK) != heldKeys.end()) {
		playerChar->attack();
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), SKILL1) != heldKeys.end()) {
		playerChar->attack(1);
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), SKILL2) != heldKeys.end()) {
		playerChar->attack(2);
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), SKILL3) != heldKeys.end()) {
		playerChar->attack(3);
	}

	//keys action

	playerChar->updateAction(dt);
}

/// <summary>
/// Control the character to attack and use skills   
/// </summary>
/// <returns></returns>
void PlayGameScene::onClickAttackMenu(cocos2d::Ref* sender) {
	auto node = dynamic_cast<Node*>(sender);
	CCLOG("%i", node->getTag());
	if (node->getTag() == 1) {
		playerChar->attack();
		CCLOG("Attack");
	}
	else if (node->getTag() == 2) {
		CCLOG("Skill 1");
	}
	else if (node->getTag() == 3) {
		CCLOG("Skill 2");
	}
	else if (node->getTag() == 4) {
		CCLOG("Skill 3");
	}
}


//onContactBegin to check for collisions happening in the PlayGameScene.
bool PlayGameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	auto a = contact.getShapeA()->getBody();
	auto b = contact.getShapeB()->getBody();

	if ((a->getCategoryBitmask() & b->getCollisionBitmask()) == 0
		|| (b->getCategoryBitmask() & a->getCollisionBitmask()) == 0)
	{
		if (a->getCategoryBitmask() == PLAYER_ATTACK_CATEGORY_BITMASK || a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK) {
			swap(a, b);
		}

		if (a->getCategoryBitmask() == GEM_CATEGORY_BITMASK)
		{
			CCLOG("Collected Gem");
			a->getNode()->removeFromParentAndCleanup(true);
			GameManager::getInstace()->getMission()->updateMission(3);
		}

		// check player hit enemies
		if (b->getCategoryBitmask() == PLAYER_ATTACK_CATEGORY_BITMASK
				&& a->getCategoryBitmask() == ENEMIES_CATEGORY_BITMASK)
		{
			CCLOG("Hit enemies %d", a->getNode()->getTag());
			
			GameManager::getInstace()->hit(b->getNode()->getTag(), a->getNode()->getTag());
		}

		// check player get hit
		if (a->getCategoryBitmask() == ENEMIES_ATTACK_CATEGORY_BITMASK
				&& b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
		{
			CCLOG("Hit player");
			playerChar->takeHit();
		}
	}
	
	return true;
}

/// <summary>
/// AI for Monster
/// </summary>
/// <param name="dt"></param>
void PlayGameScene::updateMonster(float dt) {
	for (int i = 0; i < numOfMonster; i++) {
		if (monsters[i]->getSprite()->getPosition().x >= playerChar->getSprite()->getPosition().x) {
			monsters[i]->setDirection(MonsterCharacter::Direction::LEFT);
		}
		else {
			monsters[i]->setDirection(MonsterCharacter::Direction::RIGHT);
		}
	}
}

void PlayGameScene::monsterAction(float dt) {
	for (int i = 0; i < numOfMonster; i++) {
		if (abs(monsters[i]->getSprite()->getPosition().x - playerChar->getSprite()->getPosition().x) <= visibleSize.width / 3) {
			monsters[i]->attack();
		}
		else {
			monsters[i]->idle();
		}
	}
}

/// <summary>
/// Boss
/// </summary>
/// <param name="dt"></param>
void PlayGameScene::updateBoss(float dt) {
	/*if (abs(boss->getSprite()->getPosition().x - playerChar->getSprite()->getPosition().x) <= visibleSize.width / 3) {
		if (boss->getSprite()->getPosition().x >= playerChar->getSprite()->getPosition().x) {
			boss->setDirection(BossCharacter::Direction::LEFT);
		}
		else {
			boss->setDirection(BossCharacter::Direction::RIGHT);
		}
	}*/
	if (boss->getSprite()->getPosition().x >= playerChar->getSprite()->getPosition().x) {
		boss->setDirection(BossCharacter::Direction::LEFT);
	}
	else {
		boss->setDirection(BossCharacter::Direction::RIGHT);
	}
	boss->updateAction(playerChar->getSprite()->getPosition());
}