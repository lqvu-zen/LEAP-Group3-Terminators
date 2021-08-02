#include "Definitions.h"
#include "VillageScene.h"
#include "Popup.h"
#include "MainMenuScene.h"
#include "PlayGameScene.h"
USING_NS_CC;

Scene* VillageScene::createScene()
{
	auto scene = VillageScene::create();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, -GRAVITY_VELOCITY));//test world with gravity physics!!! Working for now!!!
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

	SpriteBatchNode* spriteNode = SpriteBatchNode::create("sprites/Number/Number.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/Number/Number.plist");

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
		case ui::Widget::TouchEventType::MOVED:
			break;
		case ui::Widget::TouchEventType::CANCELED:
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

#if 0
	auto button = Sprite::create("sprites/button.png");
	button->setScale(0.2);
	button->setPosition(Vec2(button->getContentSize().width * 0.1, button->getContentSize().height * 0.05));
	//buttonNode->addChild(button);

	auto upItem = ui::Button::create("sprites/up.png");
	upItem->setScale(0.4);
	upItem->setPosition(Vec2(button->getPosition().x, button->getPosition().y + button->getContentSize().height * 0.2 / 4));
	upItem->setOpacity(140);
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
	leftItem->setOpacity(140);
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
	rightItem->setOpacity(140);
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
	auto attackItem = MenuItemImage::create("sprites/attack.png", "sprites/attack.png", CC_CALLBACK_1(VillageScene::onClickAttackMenu, this));
	attackItem->setScale(0.7);
	attackItem->setPosition(Vec2(visibleSize.width - attackItem->getContentSize().width * 0.35, attackItem->getContentSize().height * 0.35));
	attackItem->setTag(1);

	auto skill_1Item = MenuItemImage::create("sprites/skill_1.png", "sprites/skill_1.png", CC_CALLBACK_1(VillageScene::onClickAttackMenu, this));
	skill_1Item->setScale(0.3);
	skill_1Item->setPosition(Vec2(visibleSize.width - attackItem->getContentSize().width * 0.7, attackItem->getContentSize().height * 0.2));
	skill_1Item->setTag(2);

	auto skill_2Item = MenuItemImage::create("sprites/skill_2.png", "sprites/skill_2.png", CC_CALLBACK_1(VillageScene::onClickAttackMenu, this));
	skill_2Item->setScale(0.3);
	skill_2Item->setPosition(Vec2(visibleSize.width - attackItem->getContentSize().width * 0.65, attackItem->getContentSize().height * 0.55));
	skill_2Item->setTag(3);

	auto skill_3Item = MenuItemImage::create("sprites/skill_3.png", "sprites/skill_3.png", CC_CALLBACK_1(VillageScene::onClickAttackMenu, this));
	skill_3Item->setScale(0.3);
	skill_3Item->setPosition(Vec2(visibleSize.width - attackItem->getContentSize().width * 0.3, attackItem->getContentSize().height * 0.7));
	skill_3Item->setTag(4);

	auto attackMenu = Menu::create(skill_1Item, skill_2Item, skill_3Item, attackItem, nullptr);
	attackMenu->setPosition(Vec2::ZERO);
	attackMenu->setOpacity(140);
	buttonNode->addChild(attackMenu);
#endif

	//Lock Skill
#if 1
	GameManager::getInstace()->LoadSkill();
	lockskill_1 = MenuItemImage::create();
	if (checkVector(GameManager::getInstace()->lockedSkills, 1)) {
		lockskill_1 = MenuItemImage::create("sprites/lock.png", "sprites/lock.png");
		lockskill_1->setScale(0.3);
		lockskill_1->setPosition(skill_1Item->getPosition());
	}

	lockskill_2 = MenuItemImage::create();
	if (checkVector(GameManager::getInstace()->lockedSkills, 2)) {
		lockskill_2 = MenuItemImage::create("sprites/lock.png", "sprites/lock.png");
		lockskill_2->setScale(0.3);
		lockskill_2->setPosition(skill_2Item->getPosition());
	}

	lockskill_3 = MenuItemImage::create();
	if (checkVector(GameManager::getInstace()->lockedSkills, 2)) {
		lockskill_3 = MenuItemImage::create("sprites/lock.png", "sprites/lock.png");
		lockskill_3->setScale(0.3);
		lockskill_3->setPosition(skill_3Item->getPosition());
	}
	auto lockMenu = Menu::create(lockskill_1, lockskill_2, lockskill_3, nullptr);
	lockMenu->setPosition(Vec2::ZERO);
	lockMenu->setOpacity(140);
	buttonNode->addChild(lockMenu);
#endif

	//Buton recuperate
#if 0
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

	//Add joystick
	joystick = Joystick::create();
	buttonNode->addChild(joystick);
	

	//map setup + add map
	//scale map with SCALE_FACTOR
	std::string mapName = GameManager::getInstace()->getMapName();
	map = TMXTiledMap::create(mapName);
	map->setScale(SCALE_FACTOR);
	gameNode->addChild(map, 0);

	//collision with map edges
	auto mapSize = Size((map->getMapSize().width * map->getTileSize().width) * SCALE_FACTOR, ((map->getMapSize().height * map->getTileSize().height) * SCALE_FACTOR) );
	auto edgeBody = PhysicsBody::createEdgeBox(mapSize, PhysicsMaterial(1.0f, 0.0f, 1.0f), 10.0f);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(mapSize.width/2, mapSize.height/2));
	edgeBody->setCollisionBitmask(ALLSET_BITMASK);
	edgeBody->setContactTestBitmask(true);

	edgeBody->setDynamic(false);
	edgeNode->setPhysicsBody(edgeBody);
	gameNode->addChild(edgeNode);

	//setup map physics. Since we are doing a 60x34 map so width = 60 and height = 34 (2 loops)
	TMXLayer *Foreground = map->getLayer("Foreground");
	for (int i = 0; i < map->getMapSize().width; i++)
	{
		for (int j = 0; j < map->getMapSize().height; j++)
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

	//Mission description
	std::string des = GameManager::getInstace()->getMission()->getNowMission().name;
	missionLabel = Label::createWithTTF(StringUtils::format("%s\n%d / %d", des.c_str(), GameManager::getInstace()->getMission()->getNowMission().begin, GameManager::getInstace()->getMission()->getNowMission().end), "fonts/Marker Felt.ttf", visibleSize.height*0.045);
	missionLabel->setColor(cocos2d::Color3B::ORANGE);
	buttonNode->addChild(missionLabel);


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
	
	//Test add an invsible button an the NPC location.
	auto npcInteract = ui::Button::create("sprites/interact.png");
	npcInteract->setScale(0.4);
	npcInteract->setPosition(npc->getSprite()->getPosition());
	npcInteract->setOpacity(0);
	gameNode->addChild(npcInteract);
	npcInteract->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			CCLOG("Touched the NPC");
			VillageScene::onClickNPCInteract();
			break;
		case ui::Widget::TouchEventType::ENDED:
			//Your function
			CCLOG("End touch the NPC");
			break;
		case ui::Widget::TouchEventType::MOVED:	
			break;
		case ui::Widget::TouchEventType::CANCELED:
			break;
		}
	});

	//cameraTarget for the followCamera to follow the player.
	cameraTarget = Node::create();
	cameraTarget->setPositionX(playerChar->getSprite()->getPositionX());
	cameraTarget->setPositionY(visibleSize.height / 2 + origin.y + 150);//Push the camera a bit higher
	gameNode->addChild(cameraTarget);
	gameNode->addChild(playerChar->getSprite());

	//add healthbar
	auto playerStat = playerChar->getStats();
	playerStatsSprite = playerStat.GetSprite();
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

	//joystick listener
	joyStickListener = EventListenerCustom::create(JoystickEvent::EVENT_JOYSTICK, [=](EventCustom* event) {
		JoystickEvent* jsevent = static_cast<JoystickEvent*>(event->getUserData());
		//CCLOG("--------------got joystick event, %p,  angle=%f", jsevent, jsevent->mAnagle);
		switch (jsevent->type)
		{
		case JoyStickEventType::BEGAN:
			CCLOG("BEGAN");
			break;
		case JoyStickEventType::MOVED:
			CCLOG("MOVED");
				if ((180 >= jsevent->mAnagle && jsevent->mAnagle >= 135) || (jsevent->mAnagle < -90 && jsevent->mAnagle >-180))
				{
					CCLOG("GO LEFT");
					//End right and up then go left
					heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW), heldKeys.end());
					heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW), heldKeys.end());
					if (std::find(heldKeys.begin(), heldKeys.end(), cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW) == heldKeys.end()) {
						heldKeys.push_back(cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW);
					}
				}
				else if (45 >= jsevent->mAnagle && jsevent->mAnagle >= -90)
				{

					CCLOG("GO RIGHT");
					//End left and up then go right
					heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW), heldKeys.end());
					heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW), heldKeys.end());
					if (std::find(heldKeys.begin(), heldKeys.end(), cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW) == heldKeys.end()) {
						heldKeys.push_back(cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW);
					}
				}
				else if (135 >= jsevent->mAnagle && jsevent->mAnagle >= 45)
				{
					if (std::find(heldKeys.begin(), heldKeys.end(), cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) == heldKeys.end()) {
						heldKeys.push_back(cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW);
					}
				}
			break;
		case JoyStickEventType::ENDED:
			CCLOG("ENDED");
			heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW), heldKeys.end());
			heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW), heldKeys.end());
			heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW), heldKeys.end());
			break;
		}
		// do your business you'd like to
	});
	_eventDispatcher->addEventListenerWithSceneGraphPriority(joyStickListener, this);

	//load
	if (GameManager::getInstace()->getLoadOption() == 1) {
		GameManager::getInstace()->LoadGame();
	}

	//save
	GameManager::getInstace()->SaveGame();

#ifdef ENABLE_KEYBOARD
	//Keyboard test
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(VillageScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(VillageScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
	
	//Add a follow action to follow the cameraTarget(the player) with boundaries to follow.
	//The boundaries are the origin point (0, 0) and the total size of the map (in pixels) * SCALE_FACTOR.
	followCamera = Follow::create(cameraTarget, Rect(origin.x, origin.y, mapSize.width, mapSize.height));
	gameNode->runAction(followCamera);
	this->addChild(gameNode);
	this->addChild(buttonNode, 1);

	this->scheduleUpdate();

	//play audio
	AudioManager::playBackgroundAudio(AudioManager::SceneName::Village);

	return true;
}



#ifdef ENABLE_KEYBOARD
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
#endif


void VillageScene::update(float dt)
{
	//Mission check for NPC
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

	//update label
	std::string des = GameManager::getInstace()->getMission()->getNowMission().name;
	missionLabel->setString(StringUtils::format("%s\n%d / %d", des.c_str(), GameManager::getInstace()->getMission()->getNowMission().begin, GameManager::getInstace()->getMission()->getNowMission().end));
	missionLabel->setPosition(playerStatsSprite->getPositionX() + (missionLabel->getContentSize().width * 0.52), playerStatsSprite->getPositionY() - playerStatsSprite->getContentSize().height - 40);
	//CCLOG("player position: %f. camera position: %f", playerChar->getSprite()->getPositionX(), cameraTarget->getPositionX());

	GameManager::getInstace()->SaveMission();
	GameManager::getInstace()->SaveSkill();
}

void VillageScene::updateCharacter(float dt)
{
	//keys movement
	if (heldKeys.empty()) {
		playerChar->setVelocity(Vec2::ZERO);
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), UP_ARROW) != heldKeys.end()) {
		if (playerChar->getRealtimeVolocity().y <= PADDING_VELOCITY && playerChar->getStats().canJump()) {
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
	//Attack with buttons
	if (node->getTag() == 1) {
		playerChar->attack();
		CCLOG("Attack");
	}
	else if (node->getTag() == 2) {
		CCLOG("Skill 1");
		playerChar->attack(3);
		if (lock1 == false) {
			lock1 = true;
			int countDown = 5;
			char spriteFrameByName[20] = { 0 };
			sprintf(spriteFrameByName, "%d.png", countDown);
			lockskill1 = Sprite::create("sprites/Number/5.png");
			lockskill1->setPosition(node->getPosition());
			lockskill1->setScale(0.3);
			buttonNode->addChild(lockskill1, 1);

			Vector<SpriteFrame*> animFrames;
			for (int i = countDown; i >= 0; i--) {
				char buffer[20] = { 0 };
				sprintf(buffer, "%d.png", i);
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buffer);
				animFrames.pushBack(frame);
			}
			Animation* animation = Animation::createWithSpriteFrames(animFrames, 1);

			auto callback = CallFunc::create([this]() {
				lockskill1->removeFromParent();
				lock1 = false;
			});
			auto animate = Animate::create(animation);
			auto seq = Sequence::create(animate, callback, nullptr);
			lockskill1->runAction(seq);
		}
	}
	else if (node->getTag() == 3) {
		CCLOG("Skill 2");
		playerChar->attack(2);
		if (lock2 == false) {
			lock2 = true;
			int countDown = 5;
			char spriteFrameByName[20] = { 0 };
			sprintf(spriteFrameByName, "%d.png", countDown);
			lockskill2 = Sprite::create("sprites/Number/5.png");
			lockskill2->setPosition(node->getPosition());
			lockskill2->setScale(0.3);
			buttonNode->addChild(lockskill2, 1);

			Vector<SpriteFrame*> animFrames;
			for (int i = countDown; i >= 0; i--) {
				char buffer[20] = { 0 };
				sprintf(buffer, "%d.png", i);
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buffer);
				animFrames.pushBack(frame);
			}
			Animation* animation = Animation::createWithSpriteFrames(animFrames, 1);

			auto callback = CallFunc::create([this]() {
				lockskill2->removeFromParent();
				lock2 = false;
			});
			auto animate = Animate::create(animation);
			auto seq = Sequence::create(animate, callback, nullptr);
			lockskill2->runAction(seq);
		}
	}
	else if (node->getTag() == 4) {
		CCLOG("Skill 3");
		playerChar->attack(1);
		if (lock3 == false) {
			lock3 = true;
			int countDown = 5;
			char spriteFrameByName[20] = { 0 };
			sprintf(spriteFrameByName, "%d.png", countDown);
			lockskill3 = Sprite::create("sprites/Number/5.png");
			lockskill3->setPosition(node->getPosition());
			lockskill3->setScale(0.3);
			buttonNode->addChild(lockskill3, 1);

			Vector<SpriteFrame*> animFrames;
			for (int i = countDown; i >= 0; i--) {
				char buffer[20] = { 0 };
				sprintf(buffer, "%d.png", i);
				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buffer);
				animFrames.pushBack(frame);
			}
			Animation* animation = Animation::createWithSpriteFrames(animFrames, 1);

			auto callback = CallFunc::create([this]() {
				lockskill3->removeFromParent();
				lock3 = false;
			});
			auto animate = Animate::create(animation);
			auto seq = Sequence::create(animate, callback, nullptr);
			lockskill3->runAction(seq);
		}
	}
}

//Click the NPC
void VillageScene::onClickNPCInteract()
{
	if (standAlone)
	{
		UICustom::Popup* popup = UICustom::Popup::createAsMessage("Standing Alone", "There is no one for you to talk ... \nPlease come closer to the Village Elder.");
		buttonNode->addChild(popup);
	}
	else
	{
		string request = "";
		Mission::Data yourMission = GameManager::getInstace()->getMission()->getMission();
		if (yourMission.state == 4) {
			request = yourMission.request;
			UICustom::Popup* popup = UICustom::Popup::createAsMessage("Old man's quest", request);
			buttonNode->addChild(popup);
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
				
				if (GameManager::getInstace()->getMission()->getMissionCompleted().type == 2) {
					for (int i = 0; i < GameManager::getInstace()->getMission()->getMissionCompleted().end; i++) {
						playerChar->useItem(Item::ItemType::GEM);
					}
				}
			}
			else {
				request = yourMission.request + "\n Mission reward: " + tmp;
				UICustom::Popup* popup = UICustom::Popup::createAsConfirmRejectDialogue("Old man's quest", request, NULL, [=]() {
					GameManager::getInstace()->getMission()->agreeMission();
					CCLOG("Accpect Mission!");
					//Check Gem của mission
					if (GameManager::getInstace()->getMission()->getMission().type == 2) {
						int num = playerChar->getInventory().getItemCount(Item::ItemType::GEM);
						GameManager::getInstace()->getMission()->reviseMission(num);
						if (GameManager::getInstace()->getMission()->getNowMission().id == 6)
						{
							//Create a PopUp when a mission is completed.
							UICustom::Popup* popup = UICustom::Popup::createAsConfirmRejectDialogue("Quest complete", "You have complete the quest!\nHead back to the village to turn in the quest and get your rewards!", NULL, [=]() {
								CCLOG("Stay in map");
							}, [=]() {
								CCLOG("Stay in map");
							});
							buttonNode->addChild(popup, 1);
						}
					}
				}, [=]() {
					GameManager::getInstace()->getMission()->cancelMission();
					CCLOG("Reject Mission!");
				});
				buttonNode->addChild(popup);
			}
		}
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
			/*interactiveItem->setEnabled(true);
			interactiveItem->setOpacity(255);*/
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
				goToMap2();
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
	joystick->removeFromParent();
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
	joystick->removeFromParent();
	GameManager::getInstace()->setMapLevel(1);
	auto scene = PlayGameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void VillageScene::goToMap2() {
	if (GameManager::getInstace()->getMission()->getIndexMission() < 5) {
		UICustom::Popup* popup = UICustom::Popup::createAsMessage("Notify", "You must complete all training missions to open map 2 ");
		buttonNode->addChild(popup, 2);
	}
	else {
		joystick->removeFromParent();
		GameManager::getInstace()->setMapLevel(2);
		auto scene = PlayGameScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}
	
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
			/*interactiveItem->setOpacity(100);
			interactiveItem->setEnabled(false);*/
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
	if (index == 1) {
		lockskill_1->removeFromParent();
	}
	if (index == 2) {
		lockskill_2->removeFromParent();
	}
	if (index == 3) {
		lockskill_3->removeFromParent();
	}
}

bool VillageScene::checkVector(vector<int>list, int num) {
	for (int i = 0; i < list.size(); i++) {
		if (num == list[i]) {
			return true;
		}
	}
	return false;
}