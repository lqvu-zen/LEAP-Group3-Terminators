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
			UICustom::Popup* popup = UICustom::Popup::createPauseMenuVillage([=]() {
				goToMission();
			}, [=]() {
				goToSetting();
			}, [=]() {
				goToMainMenu();
			}, [=]() {
				goToExit();
			});
			
			buttonNode->addChild(popup);
			break;
		}
	});
	buttonNode->addChild(pauseButton);
#endif

#if 1
	auto button = Sprite::create("sprites/button.png");
	button->setScale(0.2);
	button->setPosition(Vec2(button->getContentSize().width * 0.1, button->getContentSize().height * 0.05));
	//buttonNode->addChild(button);

	auto upItem = ui::Button::create("sprites/up.png");
	upItem->setScale(0.4);
	upItem->setPosition(Vec2(button->getPosition().x, button->getPosition().y + button->getContentSize().height * 0.2 / 4));
	upItem->setOpacity(200);
	buttonNode->addChild(upItem);
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
	leftItem->setOpacity(200);
	buttonNode->addChild(leftItem);
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
	rightItem->setOpacity(200);
	buttonNode->addChild(rightItem);
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
	//Interact button setup
	interactiveItem = MenuItemImage::create("sprites/interact.png", "sprites/interact.png", CC_CALLBACK_1(VillageScene::onClickAttackMenu, this));
	interactiveItem->setScale(0.5);
	interactiveItem->setPosition(Vec2(visibleSize.width - interactiveItem->getContentSize().width * 0.35, interactiveItem->getContentSize().height * 0.35));
	interactiveItem->setTag(1);
	interactiveItem->setOpacity(100);
	interactiveItem->setEnabled(false);

	auto attackItem = MenuItemImage::create("sprites/attack.png", "sprites/attack.png", CC_CALLBACK_1(VillageScene::onClickAttackMenu, this));
	attackItem->setScale(0.3);
	attackItem->setPosition(Vec2(visibleSize.width - interactiveItem->getContentSize().width * 0.8, interactiveItem->getContentSize().height * 0.2));
	attackItem->setTag(2);

	auto attackMenu = Menu::create(attackItem, interactiveItem, nullptr);
	attackMenu->setPosition(Vec2::ZERO);
	attackMenu->setOpacity(200);
	buttonNode->addChild(attackMenu);
#endif

	//Buton recuperate
#if 1
	auto mpButton = ui::Button::create("sprites/mpButton.png");
	mpButton->setScale(0.1);
	//mpButton->setAnchorPoint(Vec2::ZERO);
	mpButton->setPosition(Vec2(visibleSize.width - 7 * mpButton->getContentSize().width * 0.05, mpButton->getContentSize().height * 0.05));
	mpButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			//Your function
			break;
		}
	});
	buttonNode->addChild(mpButton, 1);

	auto hpButton = ui::Button::create("sprites/hpButton.png");
	hpButton->setScale(0.1);
	hpButton->setPosition(Vec2(visibleSize.width - 9.5 * hpButton->getContentSize().width * 0.05, hpButton->getContentSize().height * 0.05));
	hpButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			//Your function
			break;
		}
	});
	buttonNode->addChild(hpButton, 1);

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
	edgeBody->setCollisionBitmask(ALLSET_BITMASK);
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
				int tileGid = Foreground->getTileGIDAt(Vec2(i, j));
				PhysicsBody* tilePhysics = PhysicsBody::createBox(spriteTile->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 0.0f));
				tilePhysics->setDynamic(false);
				tilePhysics->setCategoryBitmask(ALLSET_BITMASK);
				//tilePhysics->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
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
	playerChar = GameManager::getInstace()->GetPlayerCharacter();
	//playerChar->getSprite()->setScale(1.5);
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

			GameManager::getInstace()->AddCharacter(npc);
		}

		//Spawn Portal
		if (SpawnPoint.asValueMap()["Portal"].asInt() == 1)
		{
			int portalX = SpawnPoint.asValueMap()["x"].asInt() * SCALE_FACTOR;
			int portalY = SpawnPoint.asValueMap()["y"].asInt() * SCALE_FACTOR;
			portal = new Portal();
			portal->getSprite()->setPosition(portalX, portalY);
			gameNode->addChild(portal->getSprite());
		}
	}
	
	
	

	//cameraTarget for the followCamera to follow the player.
	cameraTarget = Node::create();
	cameraTarget->setPositionX(playerChar->getSprite()->getPositionX());
	cameraTarget->setPositionY(visibleSize.height / 2 + origin.y + 150);//Push the camera a bit higher
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
	buttonNode->addChild(playerStatsSprite);

	playerStat.AddPlayerButton();
	//Contact test
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(VillageScene::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(VillageScene::onContactSeperate, this);
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
	this->addChild(buttonNode, 1);

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
	//Mission check for NPC
	if (GameManager::getInstace()->getMission()->getState() == 0)
	{
		npc->showExclamation();
	}
	if (GameManager::getInstace()->getMission()->getState() == 1) {
		npc->changeExclamation();
	}
	else if (GameManager::getInstace()->getMission()->getState() == 0)
	{
		npc->showExclamation();
	}
	else
	{
		npc->hideExclamation();
	}

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
			buttonNode->addChild(popup);
		}
		else
		{
			string request = "";
			Mission::Data yourMission = GameManager::getInstace()->getMission()->getMission();
			if (yourMission.state == 4) {
				request = yourMission.request;
			}
			else {
				vector<Mission::Reward> rewards = GameManager::getInstace()->getMission()->getReward();

				string tmp = "";
				int i = 0;
				for (int j = 0; j < rewards.size(); j++) {
					if (i == 0) {
						tmp += rewards.at(j).name;
					}
					else {
						tmp += ", " + rewards.at(j).name;
					}
					i++;
				}

				if (yourMission.state == 5) {
					request = yourMission.request + "\n You receive: " + tmp;
					UICustom::Popup* popup = UICustom::Popup::createAsMessage("Old man's quest", request);
					buttonNode->addChild(popup);
					for (int i = 0; i < rewards.size(); i++) {
						if (rewards.at(i).type == "Skill") {
							//Unlock Skill rewards.at(i).number;
							CCLOG("Unlock Skill %i", rewards.at(i).number);
							unlockSkill(rewards.at(i).number);
						}
						else if (rewards.at(i).type == "Gold") {
							//Add rewards.at(i).number Gold;
							CCLOG("Add %i gold", rewards.at(i).number);
							playerChar->addGold(rewards.at(i).number);
						}
					}


				}
				else {
					request = yourMission.request + "\n Mission reward: " + tmp;
					UICustom::Popup* popup = UICustom::Popup::createAsConfirmRejectDialogue("Old man's quest", request, NULL, [=]() {
						GameManager::getInstace()->getMission()->agreeMission();
						CCLOG("Accpect Mission!");
					}, [=]() {
						GameManager::getInstace()->getMission()->cancelMission();
						CCLOG("Reject Mission!");
					});
					buttonNode->addChild(popup);
				}
			}
		}
	}

	if (node->getTag() == 2) {
		playerChar->attack();
		CCLOG("Attack");
	}
}


//onContactBegin to check for collisions happening in the VillageScene.
bool VillageScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	auto a = contact.getShapeA()->getBody();
	auto b = contact.getShapeB()->getBody();

	if (a->getCategoryBitmask() == PLAYER_ATTACK_CATEGORY_BITMASK || a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK) {
		swap(a, b);
	}

	if ((a->getCategoryBitmask() & b->getCollisionBitmask()) == 0
		|| (b->getCategoryBitmask() & a->getCollisionBitmask()) == 0)
	{
		if ( (a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK && b->getCategoryBitmask() == NONPLAYER_CATEGORY_BITMASK)
			|| (b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK && a->getCategoryBitmask() == NONPLAYER_CATEGORY_BITMASK))
		{
			//If the player stand in range of the NPC. The button will glow and enable to interact
			CCLOG("Hello Hero");
			standAlone = false;

			//Enable the button
			interactiveItem->setEnabled(true);
			interactiveItem->setOpacity(255);
		}

		// check player hit enemies
		if (b->getCategoryBitmask() == PLAYER_ATTACK_CATEGORY_BITMASK
			&& a->getCategoryBitmask() == NONPLAYER_CATEGORY_BITMASK)
		{
			CCLOG("Hit enemies %d", a->getNode()->getTag());

			GameManager::getInstace()->hit(b->getNode()->getTag(), a->getNode()->getTag());
		}

		else if ((a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK && b->getCategoryBitmask() == PORTAL_CATEGORY_BITMASK)
			|| (b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK && a->getCategoryBitmask() == PORTAL_CATEGORY_BITMASK))
		{
			//When Player made contact with the Portal -> Send them to the PlayGameScene;
			CCLOG("Touched portal");
			UICustom::Popup* popup = UICustom::Popup::createSelectMapInVillage([=]() {
				goToMap1();
			}, [=]() {
				goToMap1();
			});

			buttonNode->addChild(popup);
			/*auto scene = PlayGameScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));*/
		}
	}
	return true;
}

//Pause
void VillageScene::goToMission() {
	UICustom::Popup* popup = UICustom::Popup::createAsMessage("Mission", GameManager::getInstace()->getMission()->getNowMission().name);
	buttonNode->addChild(popup);
}
void VillageScene::goToSetting() {
	UICustom::Popup* popup = UICustom::Popup::createSetting();
	buttonNode->addChild(popup);
}
void VillageScene::goToMainMenu() {
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
void VillageScene::goToExit() {
	UICustom::Popup* popup = UICustom::Popup::createAsConfirmDialogue("Notify", "Want to Exit game", [=]() {
		Director::getInstance()->end();
	});
	buttonNode->addChild(popup);
}

//Map
void VillageScene::goToMap1() {
	auto scene = PlayGameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

//onContactSeperate when two shapes seperate from each other.
void VillageScene::onContactSeperate(cocos2d::PhysicsContact &contact)
{
	auto a = contact.getShapeA();
	auto b = contact.getShapeB();
	if ((a->getCategoryBitmask() & b->getCollisionBitmask()) == 0
		|| (b->getCategoryBitmask() & a->getCollisionBitmask()) == 0)
	{
		if ((a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK && b->getCategoryBitmask() == NONPLAYER_CATEGORY_BITMASK)
			|| (b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK && a->getCategoryBitmask() == NONPLAYER_CATEGORY_BITMASK))
		{	//If player is far away from the NPC -> no dialogue with NPC will be trigger!
			CCLOG("Goodbye");
			standAlone = true;

			//Disable the button when the Player is not in-range of the NPC
			interactiveItem->setOpacity(100);
			interactiveItem->setEnabled(false);
		}
	}
}

//UnlockSkill
void VillageScene::unlockSkill(int index) {
	std::vector<int>::iterator iter = GameManager::getInstace()->lockedSkills.begin();
	std::vector<int>::iterator endIter = GameManager::getInstace()->lockedSkills.end();
	while (iter != endIter) {
		if (*iter == index) {
			GameManager::getInstace()->lockedSkills.erase(iter);
			break;
		}
		iter++;
	}
	
}