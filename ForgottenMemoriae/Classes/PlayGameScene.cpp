#include "Definitions.h"
#include "PlayGameScene.h"
USING_NS_CC;

Scene* PlayGameScene::createScene()
{
	auto scene = PlayGameScene::create();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//background already added in the .tmx

	//map setup + add map
	//scale map with SCALE_FACTOR
	map = TMXTiledMap::create("map/playMap.tmx");
	map->setScale(SCALE_FACTOR);
	this->addChild(map, 0);

	//collision with map edges
	auto mapSize = Size((map->getMapSize().width * map->getTileSize().width) * SCALE_FACTOR, ((map->getMapSize().height * map->getTileSize().height) * SCALE_FACTOR) );
	auto edgeBody = PhysicsBody::createEdgeBox(mapSize, PhysicsMaterial(1.0f, 0.0f, 0.0f), 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(mapSize.width/2, mapSize.height/2));
	edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);

	edgeBody->setDynamic(false);
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);

	//setup map physics. Since we are doing a 60x34 map so width = 60 and height = 34 (2 loops)
	TMXLayer *Foreground = map->getLayer("Foreground");
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 34; j++)
		{
			auto spriteTile = Foreground->getTileAt(Vec2(i, j));
			if (spriteTile != NULL)
			{
				
				PhysicsBody* tilePhysics = PhysicsBody::createBox(spriteTile->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 0.0f));
				tilePhysics->setDynamic(false);
				tilePhysics->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
				tilePhysics->setContactTestBitmask(true);
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
	
	playerChar = new PlayerCharacter();
	playerChar->getSprite()->setScale(1.5);
	playerChar->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	
	
	

	//cameraTarget for the followCamera to follow the player.
	cameraTarget = Node::create();
	cameraTarget->setPositionX(playerChar->getSprite()->getPositionX());
	cameraTarget->setPositionY(visibleSize.height / 2 + origin.y);
	this->addChild(cameraTarget);
	this->addChild(playerChar->getSprite());

	//Add enemies here!!
	//Algorithm: get the EnemySpawn ValueMap from the objectGroup then check if the EnemySpawn has the value "Enemy == 1".
	//If true -> add enemey at the EnemySpawn.
	for each (Value SpawnPoint in objectGroup->getObjects())
	{
		//Spawn enemy
		if (SpawnPoint.asValueMap()["Enemy"].asInt() == 1)
		{
			int eneX = SpawnPoint.asValueMap()["x"].asInt();
			int eneY = SpawnPoint.asValueMap()["y"].asInt();
			this->addAt(eneX * SCALE_FACTOR, eneY * SCALE_FACTOR, 1);
		}

		//Spawn gem
		if (SpawnPoint.asValueMap()["Gem"].asInt() == 1)
		{
			int gemX = SpawnPoint.asValueMap()["x"].asInt();
			int gemY = SpawnPoint.asValueMap()["y"].asInt();
			this->addAt(gemX * SCALE_FACTOR, gemY * SCALE_FACTOR, 2);
		}
	}


	//Keyboard test
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PlayGameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(PlayGameScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	//Add a follow action to follow the cameraTarget(the player) with boundaries to follow.
	//The boundaries are the origin point (0, 0) and the total size of the map (in pixels) * SCALE_FACTOR.
	followCamera = Follow::create(cameraTarget, Rect(origin.x, origin.y, mapSize.width, mapSize.height));
	
	this->runAction(followCamera);
	this->scheduleUpdate();
	return true;
}


void PlayGameScene::addAt(int x, int y, int type)
{
	//Add new objects based on their type.
	//1 for enemy; 2 for gem
	switch (type)
	{
	case 1:
		{
		monsters[numOfMonster] = new MonsterCharacter(this, 1);
		monsters[numOfMonster]->get()->setPosition(x, y);
		//auto enemyBody = PhysicsBody::createBox(enemy->getContentSize());
		//enemy->setPhysicsBody(enemyBody);
		this->addChild(monsters[numOfMonster]->get());
		numOfMonster++;
		//this->schedule(CC_SCHEDULE_SELECTOR(PlayGameScene::monster->attack()));
		}
		break;
	case 2:
		{
		Sprite *gem = Sprite::create("sprites/Gem.png");
		gem->setPosition(x, y);
		auto gemBody = PhysicsBody::createBox(gem->getContentSize());
		gemBody->setDynamic(false);
		gem->setPhysicsBody(gemBody);
		this->addChild(gem);
		}
		break;
	default:
		break;
	}
}

void PlayGameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	CCLOG("Key with keycode %d pressed, Character position: %f", keyCode, playerChar->getSprite()->getPositionX());
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
	if (followCamera->isBoundarySet() == true)
	{
		CCLOG("Camera boundary is set!");
	}
	cameraTarget->setPositionX(playerChar->getSprite()->getPositionX());
	this->updateCharacter(dt);
	CCLOG("player position: %f. camera position: %f", playerChar->getSprite()->getPositionX(), cameraTarget->getPositionX());
}

void PlayGameScene::updateCharacter(float dt)
{
	//keys movement
	if (heldKeys.empty()) {
		playerChar->setVelocity(Vec2::ZERO);
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), UP_ARROW) != heldKeys.end()) {
		if (playerChar->isGrounded() && playerChar->getRealtimeVolocity().y <= 0) {
			playerChar->setVelocity(Vec2(playerChar->getVolocity().x, PLAYER_JUMP_VELOCITY));
		}
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), RIGHT_ARROW) != heldKeys.end()) {
		playerChar->setVelocity(Vec2(PLAYER_MAX_VELOCITY, playerChar->getVolocity().y));
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), LEFT_ARROW) != heldKeys.end()) {
		playerChar->setVelocity(Vec2(-PLAYER_MAX_VELOCITY, playerChar->getVolocity().y));
	}

	//keys action

	playerChar->updateAction(dt);
}
