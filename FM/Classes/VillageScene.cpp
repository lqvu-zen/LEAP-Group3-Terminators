#include "Definitions.h"
#include "VillageScene.h"
#include "Popup2.h"
#include "MainMenuScene.h"
#include "PlayGameScene.h"
#include "Popup2.h"
USING_NS_CC;

Scene* VillageScene::createScene()
{
	auto scene = VillageScene::create();
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
bool VillageScene::init()
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

	//Popup menu
	popupMenu = new Popup();
	popupMenu->init();
	auto mainMenuItem = MenuItemFont::create("Go To Main Menu", CC_CALLBACK_1(VillageScene::onClickMenuItem, this));
	mainMenuItem->setTag(1);
	mainMenuItem->setColor(Color3B::BLACK);
	auto playGameItem = MenuItemFont::create("Go To Play Game", CC_CALLBACK_1(VillageScene::onClickMenuItem, this));
	playGameItem->setTag(2);
	playGameItem->setColor(Color3B::BLACK);
	auto menu = Menu::create(mainMenuItem, playGameItem, nullptr);
	menu->setPosition(visibleSize / 2);
	menu->alignItemsVertically();
	popupMenu->getPopUpLayer()->addChild(menu);
	buttonNode->addChild(popupMenu, 100);
	//End Popup menu

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
			UICustom::Popup* popup = UICustom::Popup::createAsMessage("Mission", "Defeat 2 toads to become chimpanzees ");
			buttonNode->addChild(popup, 100);
			break;
		}
	});
	buttonNode->addChild(pauseButton, 100);
#endif

#if 1
	auto playButton = ui::Button::create("sprites/play.png");
	playButton->setScale(0.07);
	playButton->setPosition(Vec2(visibleSize.width - pauseButton->getContentSize().width * 0.15, visibleSize.height - pauseButton->getContentSize().height * 0.05));
	playButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			if (!isPopUpDisplay)
			{	//to display the popup menu and to close it.
				isPopUpDisplay = true;
				popupMenu->appear();
			}
			else
			{
				isPopUpDisplay = false;
				popupMenu->disappear();
			}
			break;
		}
	});
	buttonNode->addChild(playButton, 100);
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

	auto attackItem = MenuItemImage::create("sprites/interact.png", "sprites/interact.png", CC_CALLBACK_1(VillageScene::onClickAttackMenu, this));
	attackItem->setScale(0.5);
	attackItem->setPosition(Vec2(visibleSize.width - attackItem->getContentSize().width * 0.35, attackItem->getContentSize().height * 0.35));
	attackItem->setTag(1);

	auto attackMenu = Menu::create(attackItem, nullptr);
	attackMenu->setPosition(Vec2::ZERO);
	buttonNode->addChild(attackMenu, 100);
#endif
	//End add buttons

	

	//map setup + add map
	//scale map with SCALE_FACTOR
	map = TMXTiledMap::create("map/villageMap.tmx");
	map->setScale(SCALE_FACTOR);
	gameNode->addChild(map, 0);

	//collision with map edges
	auto mapSize = Size((map->getMapSize().width * map->getTileSize().width) * SCALE_FACTOR, ((map->getMapSize().height * map->getTileSize().height) * SCALE_FACTOR) );
	auto edgeBody = PhysicsBody::createEdgeBox(mapSize, PhysicsMaterial(1.0f, 0.0f, 0.0f), 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(mapSize.width/2, mapSize.height/2));
	edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);

	edgeBody->setDynamic(false);
	edgeNode->setPhysicsBody(edgeBody);
	gameNode->addChild(edgeNode);

	//setup map physics. Since we are doing a 60x34 map so width = 60 and height = 34 (2 loops)
	TMXLayer *Foreground = map->getLayer("Foreground");
	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 34; j++)
		{
			auto spriteTile = Foreground->getTileAt(Vec2(i, j));
			if (spriteTile != NULL)
			{
				
				PhysicsBody* tilePhysics = PhysicsBody::createBox(spriteTile->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 0.0f));
				tilePhysics->setDynamic(false);
				//tilePhysics->setCategoryBitmask(OBSTACLE_COLLISION_BITMASK);
				tilePhysics->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
				tilePhysics->setContactTestBitmask(ALLSET_BITMASK);
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
	playerChar = new PlayerCharacter();
	playerChar->getSprite()->setScale(1.5);
	playerChar->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	//NPC
	for (auto SpawnPoint : objectGroup->getObjects())
	{
		//Spawn NPC
		if (SpawnPoint.asValueMap()["NPC"].asInt() == 1)
		{
			int npcX = SpawnPoint.asValueMap()["x"].asInt() * SCALE_FACTOR;
			int npcY = SpawnPoint.asValueMap()["y"].asInt() * SCALE_FACTOR;
			npc = new NPC();
			npc->getSprite()->setPosition(npcX, npcY);
			gameNode->addChild(npc->getSprite());
		}
	}
	
	
	

	//cameraTarget for the followCamera to follow the player.
	cameraTarget = Node::create();
	cameraTarget->setPositionX(playerChar->getSprite()->getPositionX());
	cameraTarget->setPositionY(visibleSize.height / 2 + origin.y);
	gameNode->addChild(cameraTarget);
	gameNode->addChild(playerChar->getSprite());

	//add healthbar
	auto playerStat = playerChar->getStats();
	auto playerStatsSprite = playerStat.GetSprite();
	auto scaleRatio = 3.0f;
	playerStatsSprite->setScale(scaleRatio);
	playerStatsSprite->setPosition(
		Vec2(
			origin.x,
			visibleSize.height + origin.y - playerStat.GetSpriteSize().height * scaleRatio
		)
		//Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)
	);
	buttonNode->addChild(playerStatsSprite, 100);

	//Contact test
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(VillageScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);



	//Keyboard test
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(VillageScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(VillageScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	//Add a follow action to follow the cameraTarget(the player) with boundaries to follow.
	//The boundaries are the origin point (0, 0) and the total size of the map (in pixels) * SCALE_FACTOR.
	followCamera = Follow::create(cameraTarget, Rect(origin.x, origin.y, mapSize.width, mapSize.height));
	gameNode->runAction(followCamera);
	this->addChild(gameNode);
	this->addChild(buttonNode, 100);

	this->scheduleUpdate();
	return true;
}




void VillageScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	//CCLOG("Key with keycode %d pressed, Character position: %f", keyCode, playerChar->getSprite()->getPositionX());
	if (std::find(heldKeys.begin(), heldKeys.end(), keyCode) == heldKeys.end()) {
		heldKeys.push_back(keyCode);
	}
}

void VillageScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	CCLOG("Key with keycode %d released", keyCode);
	heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), keyCode), heldKeys.end());
}


void VillageScene::update(float dt)
{
	cameraTarget->setPositionX(playerChar->getSprite()->getPositionX());
	this->updateCharacter(dt);
	//CCLOG("player position: %f. camera position: %f", playerChar->getSprite()->getPositionX(), cameraTarget->getPositionX());
}

void VillageScene::updateCharacter(float dt)
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

	//keys action

	playerChar->updateAction(dt);
}

/// <summary>
/// Control the character to attack and use skills   
/// </summary>
/// <returns></returns>
void VillageScene::onClickAttackMenu(cocos2d::Ref* sender) {
	auto node = dynamic_cast<Node*>(sender);
	CCLOG("%i", node->getTag());
	if (node->getTag() == 1) {
		if (standAlone)
		{
			UICustom::Popup* popup = UICustom::Popup::createAsMessage("Standing Alone", "There is no one for you to talk ...");
			buttonNode->addChild(popup, 100);
		}
		else
		{
			UICustom::Popup* popup = UICustom::Popup::createAsConfirmDialogue("Old man's quest", "Hey Hero\n Can you help me kill 2 toads", [=]() {
				CCLOG("Mission added!");
			});
			buttonNode->addChild(popup, 100);
		}
	}
}


//onContactBegin to check for collisions happening in the VillageScene.
bool VillageScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	auto a = contact.getShapeA();
	auto b = contact.getShapeB();
	if ((a->getCategoryBitmask() & b->getCollisionBitmask()) == 0
		|| (b->getCategoryBitmask() & a->getCollisionBitmask()) == 0)
	{
		if ( (a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK && b->getCategoryBitmask() == NONPLAYER_CATEGORY_BITMASK)
			|| (b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK && a->getCategoryBitmask() == NONPLAYER_CATEGORY_BITMASK))
		{
			CCLOG("Hello Hero");
			standAlone = false;
		}
		else if ((a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK && b->getCategoryBitmask() != NONPLAYER_CATEGORY_BITMASK)
			|| (b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK && a->getCategoryBitmask() != NONPLAYER_CATEGORY_BITMASK))
		{
			CCLOG("Hello");
			standAlone = true;
		}
	}
	return true;
}

void VillageScene::onClickMenuItem(cocos2d::Ref* sender)
{
	auto node = dynamic_cast<Node*>(sender);
	if (node->getTag() == 1) {//Go to main menu
		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}
	else if (node->getTag() == 2) {//Go to play game scene
		auto scene = PlayGameScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}
}