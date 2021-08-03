#include "Definitions.h"
#include "PlayGameScene.h"
#include "MainMenuScene.h"
#include "VillageScene.h"
#include "Popup.h"

USING_NS_CC;

Scene* PlayGameScene::createScene()
{
	auto scene = PlayGameScene::create();
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

	SpriteBatchNode* spriteNode = SpriteBatchNode::create("sprites/Number/Number.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/Number/Number.plist");
	
	//Pause button
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
			UICustom::Popup* popup = UICustom::Popup::createPauseMenuPlayGame([=]() {
				goToLockUnlockSkill();
			}, [=]() {
				goToVillage();
			}, [=]() {
				goToSetting();
			}, [=]() {
				goToMainMenu();
			}, [=]() {
				goToExit();
			}, [=]() {
				goToSave();
			});
			/*Mission* mission = new Mission();
			UICustom::Popup* popup = UICustom::Popup::createAsMessage("Mission", GameManager::getInstace()->getMission()->getNowMission().name);*/
			buttonNode->addChild(popup, 2);
			//Pause will be onto of everything in the buttonNode
			break;
		}
	});
	buttonNode->addChild(pauseButton);
#endif

	//Move Buttons with press
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

	//Attak button and skill buttons
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
	attackMenu->setOpacity(140);
	buttonNode->addChild(attackMenu);
#endif

	//Lock Skill
#if 1
	lockskill_1Item = MenuItemImage::create();
	if (checkVector(GameManager::getInstace()->lockedSkills, 1)) {
		lockskill_1Item = MenuItemImage::create("sprites/lock.png", "sprites/lock.png");
		lockskill_1Item->setScale(0.3);
		lockskill_1Item->setPosition(skill_1Item->getPosition());
	}

	lockskill_2Item = MenuItemImage::create();
	if (checkVector(GameManager::getInstace()->lockedSkills, 2)) {
		lockskill_2Item = MenuItemImage::create("sprites/lock.png", "sprites/lock.png");
		lockskill_2Item->setScale(0.3);
		lockskill_2Item->setPosition(skill_2Item->getPosition());
	}

	lockskill_3Item = MenuItemImage::create();
	if (checkVector(GameManager::getInstace()->lockedSkills, 2)) {
		lockskill_3Item = MenuItemImage::create("sprites/lock.png", "sprites/lock.png");
		lockskill_3Item->setScale(0.3);
		lockskill_3Item->setPosition(skill_3Item->getPosition());
	}
	auto lockMenu = Menu::create(lockskill_1Item, lockskill_2Item, lockskill_3Item, nullptr);
	lockMenu->setPosition(Vec2::ZERO);
	lockMenu->setOpacity(140);
	buttonNode->addChild(lockMenu);
#endif

	//mp Button, hp Button
#if 1
	auto mpButton = ui::Button::create("sprites/mpButton.png");
	mpButton->setScale(0.065);
	mpButton->setPosition(Vec2(visibleSize.width - 7 * mpButton->getContentSize().width * 0.05, mpButton->getContentSize().height * 0.05));
	mpButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			playerChar->useItem(Item::ItemType::MP_POTION);
			mpPotionsLabel->setString(StringUtils::format("%d", playerChar->getInventory().getItemCount(Item::ItemType::MP_POTION)));
			break;
		}
	});
	mpButton->setOpacity(140);
	buttonNode->addChild(mpButton, 1);

	auto hpButton = ui::Button::create("sprites/hpButton.png");
	hpButton->setScale(0.065);
	hpButton->setPosition(Vec2(visibleSize.width - 9.5 * hpButton->getContentSize().width * 0.05, hpButton->getContentSize().height * 0.05));
	hpButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			playerChar->useItem(Item::ItemType::HP_POTION);
			hpPotionsLabel->setString(StringUtils::format("%d", playerChar->getInventory().getItemCount(Item::ItemType::HP_POTION)));
			break;
		}
	});
	hpButton->setOpacity(140);
	buttonNode->addChild(hpButton, 1);
#endif

	//Add joystick
	joystick = Joystick::create();
	buttonNode->addChild(joystick);

	//map setup + add map
	//scale map with SCALE_FACTOR
	std::string mapName = GameManager::getInstace()->getMapName();
	map = TMXTiledMap::create(mapName);
	map->setScale(SCALE_FACTOR );
	
	//Hidden areas setup
	for (int i = 0; i < GameManager::getInstace()->getMapHiddenAreasCount(); i++)
		//With the use of vector, we can simply add as much hidden Areas as we like, without touching the code.
		//Just remember to set the correspond tag for the hiddenArea Trigger in Tiled (under properties) and add the amount of
		//hidden Areas in the JSON file.
	{	//Push the hidden Areas to a vector. Then when the player hit hiddenArea Trigger, show what is inside the hiddenArea
		std::string hiddenAreaName = StringUtils::format("Hidden%d", i);
		auto hiddenArea = map->getLayer(hiddenAreaName);
		HiddenAreas.push_back(hiddenArea);
		map->removeChild(hiddenArea, true);//remove the Hidden Layer and then add it again at around line 455
	}
	//get the map backgrounds
	auto skyBackground = map->getLayer("Background");
	auto mountainBackground = map->getLayer("MountainBG");
	map->removeChild(skyBackground);
	map->removeChild(mountainBackground);
	gameNode->addChild(map, 1);

	//collision with map edges
	auto mapSize = Size((map->getMapSize().width * map->getTileSize().width) * SCALE_FACTOR, ((map->getMapSize().height * map->getTileSize().height) * SCALE_FACTOR) );
	auto edgeBody = PhysicsBody::createEdgeBox(mapSize, PhysicsMaterial(1.0f, 0.0f, 0.0f), 10.0f);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(mapSize.width/2, mapSize.height/2));
	edgeBody->setCategoryBitmask(ALLSET_BITMASK);
	edgeBody->setCollisionBitmask(ALLSET_BITMASK);
	edgeBody->setContactTestBitmask(ALLCLEARED_BITMASK);

	edgeBody->setDynamic(false);
	edgeNode->setPhysicsBody(edgeBody);
	gameNode->addChild(edgeNode);

	//a list to store the location of the hidden tiles.
	//HiddenTiles = new std::list<Vec2>();

	//setup map physics. Just loop through the map size in tiles (2 loops)
	//Foreground is the layer for the ground tiles that will have physical interaction.
	Foreground = map->getLayer("Foreground");
	
	for (int i = 0; i < map->getMapSize().width; i++)
	{
		for (int j = 0; j < map->getMapSize().height; j++)
		{
			auto spriteTile = Foreground->getTileAt(Vec2(i, j));
			if (spriteTile != NULL)
			{
				
				PhysicsBody* tilePhysics = PhysicsBody::createBox(spriteTile->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 0.0f));
				tilePhysics->setDynamic(false);
				tilePhysics->setCategoryBitmask(ALLSET_BITMASK);
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
	playerChar = GameManager::getInstace()->GetPlayerCharacter();
	//playerChar->getSprite()->setScale(1.5);
	playerChar->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	//cameraTarget for the followCamera to follow the player.
	cameraTarget = Node::create();
	cameraTarget->setPositionX(playerChar->getSprite()->getPositionX());
	cameraTarget->setPositionY(playerChar->getSprite()->getPositionY() +(32 * SCALE_FACTOR));
	gameNode->addChild(cameraTarget);
	gameNode->addChild(playerChar->getSprite(), 1);

	//add healthbar
	auto playerStats = playerChar->getStats();
	playerStatsSprite = playerStats.GetSprite();
	auto scaleRatio = 3.0f;
	playerStatsSprite->setScale(scaleRatio);
	playerStatsSprite->setPosition(
		Vec2(
			origin.x,
			visibleSize.height + origin.y - playerStats.GetSpriteSize().height * scaleRatio
		)
		//Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)
	);
	buttonNode->addChild(playerStatsSprite, 1);

	playerStats.AddPlayerButton();

	//Mission description
	std::string des = GameManager::getInstace()->getMission()->getNowMission().name;
	missionLabel = Label::createWithTTF(StringUtils::format("%s\n%d / %d", des.c_str(), GameManager::getInstace()->getMission()->getNowMission().begin, GameManager::getInstace()->getMission()->getNowMission().end), "fonts/Marker Felt.ttf", visibleSize.height*0.045);
	missionLabel->setColor(cocos2d::Color3B::ORANGE);
	buttonNode->addChild(missionLabel);

	//hp and mp potions label
	hpPotionsLabel = Label::createWithTTF(StringUtils::format("%d", playerChar->getInventory().getItemCount(Item::ItemType::HP_POTION)), "fonts/Marker Felt.ttf", visibleSize.height*0.045);
	hpPotionsLabel->setPositionX(hpButton->getPositionX() + (hpButton->getContentSize().width * 0.035));
	hpPotionsLabel->setPositionY(hpButton->getPositionY() + (hpButton->getContentSize().height * 0.035));
	hpPotionsLabel->enableOutline(Color4B::BLACK, 1);
	buttonNode->addChild(hpPotionsLabel);

	mpPotionsLabel = Label::createWithTTF(StringUtils::format("%d", playerChar->getInventory().getItemCount(Item::ItemType::MP_POTION)), "fonts/Marker Felt.ttf", visibleSize.height*0.045);
	mpPotionsLabel->setPositionX(mpButton->getPositionX() + (mpButton->getContentSize().width * 0.035));
	mpPotionsLabel->setPositionY(mpButton->getPositionY() + (mpButton->getContentSize().height * 0.035));
	mpPotionsLabel->enableOutline(Color4B::BLACK, 1);
	buttonNode->addChild(mpPotionsLabel);
	//Add Game Objects in Map here!!
	//Algorithm: get the EnemySpawn ValueMap from the objectGroup then check if the EnemySpawn has the value "Enemy == 1".
	//If true -> add enemey at the EnemySpawn.
	for (auto SpawnPoint : objectGroup->getObjects())
	{
		//Spawn enemy. Based on the monsterType defined in the tilemap. 
		if (SpawnPoint.asValueMap()["name"].asString() == "Enemy")
		{
			auto eneX = SpawnPoint.asValueMap()["x"].asFloat() * SCALE_FACTOR;
			auto eneY = SpawnPoint.asValueMap()["y"].asFloat() * SCALE_FACTOR;
			int monsterType = SpawnPoint.asValueMap()["Enemy"].asInt();
			auto monster = new MonsterCharacter(gameNode, monsterType, GameManager::getInstace()->getMapLevel());
			monster->setPosition(Vec2(eneX, eneY));
			//Using a list to  store the monsters
			monsters.push_back(monster);
			GameManager::getInstace()->AddCharacter(monsters.back());
			gameNode->addChild(monsters.back()->getSprite(), 1);	
		}


		//Spawn item. Based on the itemType defined in the tilemap. 1: gem; 2: gold; 3: Hp potion; 4: Mp potion
		if (SpawnPoint.asValueMap()["name"].asString() == "ItemSpawn")
		{
			if (std::find(GameManager::getInstace()->collectedItems.begin(), GameManager::getInstace()->collectedItems.end(), SpawnPoint.asValueMap()["id"].asInt()) != GameManager::getInstace()->collectedItems.end())
			{
				CCLOG("Collected items will not spawn again");
			}
			else
			{
				auto itemX = SpawnPoint.asValueMap()["x"].asFloat()* SCALE_FACTOR;
				auto itemY = SpawnPoint.asValueMap()["y"].asFloat() * SCALE_FACTOR;
				int itemType = SpawnPoint.asValueMap()["ItemType"].asInt();
				switch (itemType)
				{
				case 1:
					item = new Item(Item::ItemType::GEM);
					item->getSprite()->getPhysicsBody()->setTag(SpawnPoint.asValueMap()["id"].asInt());
					item->getSprite()->getPhysicsBody()->setName("GEM");
					break;
				case 2:
					item = new Item(Item::ItemType::GOLD);
					break;
				case 3:
					item = new Item(Item::ItemType::HP_POTION);
					break;
				case 4:
					item = new Item(Item::ItemType::MP_POTION);
					break;
				case 5:
					item = new Item(Item::ItemType::D_BOOTS);
					item->getSprite()->getPhysicsBody()->setTag(SpawnPoint.asValueMap()["id"].asInt());
					item->getSprite()->getPhysicsBody()->setName("BOOTS");
					break;
				}
				item->getSprite()->setPosition(itemX, itemY);
				gameNode->addChild(item->getSprite(), 1);
				GameManager::getInstace()->AddItem(item);
			}	
		}

		//Spawn boss
		if (SpawnPoint.asValueMap()["Boss"].asInt() == 1)
		{
			auto bossX = SpawnPoint.asValueMap()["x"].asFloat()* SCALE_FACTOR;
			auto bossY = SpawnPoint.asValueMap()["y"].asFloat() * SCALE_FACTOR;
			boss = new BossCharacter(1);
			boss->setPosition(Vec2(bossX, bossY));

			GameManager::getInstace()->AddCharacter(boss);

			//boss->setPosition(visibleSize / 2);
			gameNode->addChild(boss->getSprite(), 1);
		}

		//Spawn Trigger point
		if (SpawnPoint.asValueMap()["Trigger"].asInt() == 1)
		{
			auto triggerX = SpawnPoint.asValueMap()["x"].asFloat()* SCALE_FACTOR;
			auto triggerY = SpawnPoint.asValueMap()["y"].asFloat() * SCALE_FACTOR;
			trigger = Sprite::create();
			auto triggerBody = PhysicsBody::createBox(Size(64, mapSize.height));
			triggerBody->setDynamic(false);
			triggerBody->setRotationEnable(false);
			triggerBody->setCategoryBitmask(NONPLAYER_CATEGORY_BITMASK);
			triggerBody->setContactTestBitmask(ALLSET_BITMASK);
			trigger->setPhysicsBody(triggerBody);
			trigger->setPosition(triggerX, triggerY);
			gameNode->addChild(trigger);
		}

		//Spawn Trigger hidden area point
		if (SpawnPoint.asValueMap()["name"].asString() == "TriggerHidden")
		{
			auto triggerX = SpawnPoint.asValueMap()["x"].asFloat()* SCALE_FACTOR;
			auto triggerY = SpawnPoint.asValueMap()["y"].asFloat() * SCALE_FACTOR;
			auto triggerHidden = Sprite::create();
			auto triggerBody = PhysicsBody::createBox(Size(96 * SCALE_FACTOR, 80 * SCALE_FACTOR));
			triggerBody->setDynamic(false);
			triggerBody->setRotationEnable(false);
			triggerBody->setCategoryBitmask(HIDDEN_TILE_CATEGORY_BITMASK);
			triggerBody->setContactTestBitmask(ALLSET_BITMASK);
			triggerHidden->setPhysicsBody(triggerBody);
			triggerHidden->setPosition(triggerX, triggerY);
			triggerHidden->setTag(SpawnPoint.asValueMap()["TriggerHidden"].asInt());
			gameNode->addChild(triggerHidden);
		}

	}

	//Contact test
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PlayGameScene::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(PlayGameScene::onContactSeperate, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//joystick listener
	auto joyStickListener = EventListenerCustom::create(JoystickEvent::EVENT_JOYSTICK, [=](EventCustom* event) {
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

#ifdef ENABLE_KEYBOARD
	//Keyboard test
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PlayGameScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(PlayGameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
#endif
	
	//Add a follow action to follow the cameraTarget(the player) with boundaries to follow.
	//The boundaries are the origin point (0, 0) and the total size of the map (in pixels). (32 * SCALE_FACTOR) is the out of map boundaries
	followCamera = Follow::create(cameraTarget, Rect(origin.x, origin.y + (32 * SCALE_FACTOR), mapSize.width, mapSize.height));
	gameNode->runAction(followCamera);

	//re-add the Hidden layers to the map.
	for (int j = 0; j < HiddenAreas.size(); ++j)
	{
		HiddenAreas.at(j)->setScale(SCALE_FACTOR);
		gameNode->addChild(HiddenAreas.at(j), 1);
	}
	skyBackground->setScale(SCALE_FACTOR);
	mountainBackground->setScale(SCALE_FACTOR);
	gameNode->addChild(skyBackground, -1);
	gameNode->addChild(mountainBackground, -1);

	//play audio
	AudioManager::playBackgroundAudio(AudioManager::SceneName::Play);


	this->addChild(gameNode);
	this->addChild(buttonNode, 1);

	this->schedule(CC_SCHEDULE_SELECTOR(PlayGameScene::monsterAction), 3);
	
	this->schedule(CC_SCHEDULE_SELECTOR(PlayGameScene::bossAction), 1);
	//boss->death();
	this->scheduleUpdate();

	//
	timeRevival = 0;
	goldRevival = 0;
	win = false;

	return true;
}

#ifdef ENABLE_KEYBOARD
void PlayGameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	//CCLOG("Key with keycode %d pressed, Character position: %f", keyCode, playerChar->getSprite()->getPositionX());
	if (std::find(heldKeys.begin(), heldKeys.end(), keyCode) == heldKeys.end()) {
		heldKeys.push_back(keyCode);
	}
}

void PlayGameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	//CCLOG("Key with keycode %d released", keyCode);
	heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), keyCode), heldKeys.end());
}
#endif


void PlayGameScene::update(float dt)
{
	this->updateMonster(dt);
	this->updateBoss(dt);
	this->bossAction(dt);

	cameraTarget->setPositionX(playerChar->getSprite()->getPositionX());
	cameraTarget->setPositionY(playerChar->getSprite()->getPositionY());
	this->updateCharacter(dt);

	//update label
	std::string des = GameManager::getInstace()->getMission()->getNowMission().name;
	missionLabel->setString(StringUtils::format("%s\n%d / %d", des.c_str(), GameManager::getInstace()->getMission()->getNowMission().begin, GameManager::getInstace()->getMission()->getNowMission().end));
	missionLabel->setPosition(playerStatsSprite->getPositionX() + (missionLabel->getContentSize().width * 0.52), playerStatsSprite->getPositionY() - playerStatsSprite->getContentSize().height - 40);
	//this->updateBoss(dt);
	CCLOG("player positionY: %f.", playerChar->getSprite()->getPositionY());

	GameManager::getInstace()->SaveMission();
}

void PlayGameScene::updateCharacter(float dt)
{
	if (playerChar->isDead() == true)
	{	//Player is dead
		if (isDeadNoticePopUp == false)
		{
			GameManager::getInstace()->countDead++;
			PlayGameScene::playerDeadNotice();
			isDeadNoticePopUp = true;
		}
	}
	else
	{	//Player is alive
		//keys movement
		if (heldKeys.empty()) {
			playerChar->setVelocity(Vec2::ZERO);
		}

		if (std::find(heldKeys.begin(), heldKeys.end(), UP_ARROW) != heldKeys.end()) {
			if (playerChar->getRealtimeVolocity().y <= PADDING_VELOCITY && playerChar->getStats().canJump()) {
				playerChar->setVelocity(Vec2(playerChar->getVolocity().x, PLAYER_JUMP_VELOCITY));
				//CCLOG("Jump touch!");
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

		//Character fall off the map 
		if (playerChar->getSprite()->getPositionY() < 42)
		{
			CCLOG("DEAD");
			while (playerChar->getStats().HP > 0)
			{
				playerChar->takeHit();
			}
			//playerChar->takeHit(playerChar->getStats().HP);
			//PlayGameScene::playerDeadNotice();
		}
		playerChar->updateAction(dt);
	}
	
}

/// <summary>
/// Control the character to attack and use skills   
/// </summary>
/// <returns></returns>
void PlayGameScene::onClickAttackMenu(cocos2d::Ref* sender) {
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


//onContactBegin to check for collisions happening in the PlayGameScene.
bool PlayGameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	auto a = contact.getShapeA()->getBody();
	auto b = contact.getShapeB()->getBody();

	if (a->getCategoryBitmask() == PLAYER_ATTACK_CATEGORY_BITMASK || a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK) {
		swap(a, b);
	}

	//check if player is standing on the enemies
	if (b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK
		&& a->getCategoryBitmask() == ENEMIES_CATEGORY_BITMASK)
	{
		playerChar->takeHit();
		CCLOG("Standing on enemies");
	}

	if ((a->getCategoryBitmask() & b->getCollisionBitmask()) == 0
		|| (b->getCategoryBitmask() & a->getCollisionBitmask()) == 0)
	{
		
		if (a->getCategoryBitmask() == ITEM_CATEGORY_BITMASK && b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
		{
			CCLOG("Collected item");
			if (a->getName() == "GEM" || a->getName() == "BOOTS")
			{
				GameManager::getInstace()->collectedItems.push_back(a->getTag());
				CCLOG("Collected gem or boots");
			}
			a->getNode()->retain();
			a->getNode()->removeFromParent();

			GameManager::getInstace()->colect(a->getNode()->getTag());
			//Update the label whenever the Player collect any item.
			mpPotionsLabel->setString(StringUtils::format("%d", playerChar->getInventory().getItemCount(Item::ItemType::MP_POTION)));
			hpPotionsLabel->setString(StringUtils::format("%d", playerChar->getInventory().getItemCount(Item::ItemType::HP_POTION)));
			GameManager::getInstace()->getMission()->updateMission(2);
			if (GameManager::getInstace()->getMission()->getNowMission().id == 6)
			{
				//Create a PopUp when a mission is completed.
				UICustom::Popup* popup = UICustom::Popup::createAsConfirmRejectDialogue("Quest complete", "You have complete the quest!\nHead back to the village to turn in the quest and get your rewards!", NULL, [=]() {
					PlayGameScene::goToVillage();
				}, [=]() {
					CCLOG("Stay in map");
				});
				buttonNode->addChild(popup, 1);
			}
		}

		// check player hit enemies
		if (b->getCategoryBitmask() == PLAYER_ATTACK_CATEGORY_BITMASK
				&& a->getCategoryBitmask() == ENEMIES_CATEGORY_BITMASK)
		{
			CCLOG("Hit enemies %d", a->getNode()->getTag());
			GameManager::getInstace()->hit(b->getNode()->getTag(), a->getNode()->getTag());
			if (GameManager::getInstace()->getMission()->getNowMission().id == 6)
			{
				//Create a PopUp when a mission is completed.
				UICustom::Popup* popup = UICustom::Popup::createAsConfirmRejectDialogue("Quest complete", "You have complete the quest!\nHead back to the village to turn in the quest and get your rewards!", NULL, [=]() {
					PlayGameScene::goToVillage();
				}, [=]() {
					CCLOG("Stay in map");
				});
				buttonNode->addChild(popup, 1);
			}
		}


		// check player get hit
		if (a->getCategoryBitmask() == ENEMIES_ATTACK_CATEGORY_BITMASK
				&& b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
		{
			CCLOG("Hit player");
			playerChar->takeHit();
			a->getNode()->setPosition(Vec2(-100 * visibleSize.width, 0));
		}

		//Player collide with trigger point
		if ((a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK && b->getCategoryBitmask() == NONPLAYER_CATEGORY_BITMASK)
			|| (b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK && a->getCategoryBitmask() == NONPLAYER_CATEGORY_BITMASK))
		{
			//When the Player trigger the TRIGGER Point. The followCamera action will be stop and the map will be move to the 
			//middle of the boss arena.
			CCLOG("TRIGGER!!!");
			trigger->removeFromParentAndCleanup(true);
			//stop the followCamera action
			gameNode->stopAction(followCamera);
			//Using MoveTo to move the gameNode to the middle of the boss arena(the boss X position). The Vec2's y = 0 because we only want to move the x coord. 
			auto moveTo = MoveTo::create(2, Vec2(-(boss->getSprite()->getPositionX() - visibleSize.width/2), -(32 * SCALE_FACTOR)));
			gameNode->runAction(moveTo);
			
			//play audio
			AudioManager::playBackgroundAudio(AudioManager::SceneName::Battle);
		}

		//Player collide with the hidden area in the map
		if ((a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK && b->getCategoryBitmask() == HIDDEN_TILE_CATEGORY_BITMASK)
			|| (b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK && a->getCategoryBitmask() == HIDDEN_TILE_CATEGORY_BITMASK))
		{
			
			if (b->getCategoryBitmask() == HIDDEN_TILE_CATEGORY_BITMASK)
			{
				CCLOG("Hidden area");
				hideTiles(b->getNode()->getTag());
			}
			else if (a->getCategoryBitmask() == HIDDEN_TILE_CATEGORY_BITMASK)
			{
				CCLOG("Hidden area");
				hideTiles(a->getNode()->getTag());

			}
		}
	}
	return true;
}

//onContactSeperate to handle after collision exit.
void PlayGameScene::onContactSeperate(cocos2d::PhysicsContact &contact)
{
	auto a = contact.getShapeA()->getBody();
	auto b = contact.getShapeB()->getBody();

	if (b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK
		&& a->getCategoryBitmask() == ENEMIES_CATEGORY_BITMASK)
	{
		CCLOG("Not Standing on enemies");
	}
}

/// <summary>
/// AI for Monster
/// </summary>
/// <param name="dt"></param>
void PlayGameScene::updateMonster(float dt) {
	std::list<MonsterCharacter*> ::iterator it;
	for (it = monsters.begin(); it != monsters.end() ; ++it) {
		if ((*it)->characterState != MonsterCharacter::State::DEATH) {
			if ((*it)->getSprite()->getPosition().x >= playerChar->getSprite()->getPosition().x) {
				(*it)->setDirection(MonsterCharacter::Direction::LEFT);
			}
			else {
				(*it)->setDirection(MonsterCharacter::Direction::RIGHT);
			}
		}	
	}
}
void PlayGameScene::monsterAction(float dt) {
	std::list<MonsterCharacter*> ::iterator it;
	for (it = monsters.begin(); it != monsters.end(); ++it) {
		if ((*it)->characterState != MonsterCharacter::State::DEATH) {
			if (abs((*it)->getSprite()->getPosition().x - playerChar->getSprite()->getPosition().x) <= visibleSize.width / 3) {
				(*it)->updateAction(playerChar->getSprite()->getPosition());
			}
			else {
				(*it)->idle();
			}
		}
	}
}

/// <summary>
/// Boss
/// </summary>
/// <param name="dt"></param>
void PlayGameScene::updateBoss(float dt) {
	if (boss->characterState==BossCharacter::State::DEATH) {
		if (win == false) {
			win = true;
			this->scheduleOnce(CC_SCHEDULE_SELECTOR(PlayGameScene::goToWinScene), DISPLAY_TIME_SPLASH_SCENE * 4);
		}
	}
}
void PlayGameScene::bossAction(float dt) {
	if (boss->characterState != BossCharacter::State::DEATH) {
		if (boss->getSprite()->getPosition().x >= playerChar->getSprite()->getPosition().x) {
			boss->setDirection(BossCharacter::Direction::LEFT);
		}
		else {
			boss->setDirection(BossCharacter::Direction::RIGHT);
		}

		boss->updateAction_2(playerChar->getSprite()->getPosition());
	}
}

//Pause
void PlayGameScene::goToLockUnlockSkill() {
	lockskill_1Item->removeFromParent();
	lockskill_2Item->removeFromParent();
	lockskill_3Item->removeFromParent();
}
void PlayGameScene::goToVillage() {
	joystick->removeFromParent();
	GameManager::getInstace()->setMapLevel(0);
	auto scene = VillageScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void PlayGameScene::goToSave() {
	//Implement save game here.
	CCLOG("SAVE GAME");
	GameManager::getInstace()->SaveGame();
	GameManager::getInstace()->SaveMission();
}

void PlayGameScene::goToSetting() {
	UICustom::Popup* popup = UICustom::Popup::createSetting();
	buttonNode->addChild(popup, 2);
}

void PlayGameScene::goToMainMenu() {
	joystick->removeFromParent();
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
void PlayGameScene::goToExit() {
	UICustom::Popup* popup = UICustom::Popup::createAsConfirmDialogue("Notify", "Want to Exit game", [=]() {
		Director::getInstance()->end();
	});
	buttonNode->addChild(popup, 2);
}


void PlayGameScene::playerDeadNotice()
{
	UICustom::Popup* popup = UICustom::Popup::createLoss([=]() {
		Revival1Func();
	}, [=]() {
		Revival2Func();
	}, [=]() {
		goToExit();
	});
	buttonNode->addChild(popup, 2);
}

//Hide and show the hiddenTiles
void PlayGameScene::hideTiles(int tag)
{	//just run through the list, and hide each tiles in the list
	CCLOG("Hide tile");
	HiddenAreas.at(tag)->setVisible(false);
}

//void PlayGameScene::showTiles()
//{
//	CCLOG("Show tile");
//	Hidden->setVisible(true);
//}

//Unlock Skill
void PlayGameScene::unlockSkill(int index) {

}

bool PlayGameScene::checkVector(vector<int>list, int num) {
	for (int i = 0; i < list.size(); i++) {
		if (num == list[i]) {
			return true;
		}
	}
	return false;
}

//Revival
void PlayGameScene::Revival1Func() {
	goldRevival = GameManager::getInstace()->countDead * 1;
	std::string notify = StringUtils::format("You will respawn on the spot \nYou will need to spend %i gold", goldRevival);
	UICustom::Popup* popup = UICustom::Popup::createAsConfirmRejectDialogue("Revival", notify, NULL, [=]() {
		if (playerChar->exceptGold(goldRevival)) {
			playerChar->revive();
			playerChar->returnSavePosition();
			isDeadNoticePopUp = false;
		}
		else {
			playerDeadNotice();
			UICustom::Popup* notify = UICustom::Popup::createAsMessage("Note", "You don't have enough gold to respawn. ");
			buttonNode->addChild(notify, 3);		
		}
	}, [=]() {
		playerDeadNotice();
	});
	buttonNode->addChild(popup, 2);
}
void PlayGameScene::Revival2Func() {
	timeRevival = GameManager::getInstace()->countDead * 10;
	std::string notify = StringUtils::format("You will return to the village and respawn.\nYou need to wait %i second", timeRevival);
	UICustom::Popup* popup = UICustom::Popup::createAsConfirmRejectDialogue("Revival", notify, NULL, [=]() {
		std::string tmp = StringUtils::format("%i second", timeRevival);
		lblCountDown = Label::createWithTTF(tmp, "fonts/Dimbo Regular.ttf", 45);
		UICustom::Popup* countdown = UICustom::Popup::countdown(timeRevival, lblCountDown);
		buttonNode->addChild(countdown, 2);
		this->schedule(CC_SCHEDULE_SELECTOR(PlayGameScene::updateCountDown), 1);
	}, [=] {
		playerDeadNotice();
	});
	buttonNode->addChild(popup, 2);
}
void PlayGameScene::updateCountDown(float) {
	if (timeRevival == 0) {
		playerChar->revive();
		goToVillage();
	}
	else {
		timeRevival--;
		std::string tmp = StringUtils::format("%i second", timeRevival);
		lblCountDown->setString(tmp);
	}
}

void PlayGameScene::goToWinScene(float dt) {

	auto background = Sprite::create("sprites/winBackground.png");
	background->setPosition(visibleSize / 2);
	background->setScale(0.6);
	this->addChild(background, 3);

	auto title = Label::createWithTTF("Win", "fonts/Marker Felt.ttf", 60);
	title->setTextColor(Color4B::WHITE);
	title->setPosition(visibleSize / 2);
	this->addChild(title, 3);

	//auto countine = MenuItemFont::create("Conutine", CC_CALLBACK_1(PlayGameScene::goToVillage, scene));
	auto continueItem = MenuItemFont::create("Continue", CC_CALLBACK_1(PlayGameScene::goToContinue, this));

	auto menu = Menu::create(continueItem, nullptr);
	menu->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.25));
	menu->alignItemsVertically();
	this->addChild(menu, 3);

	//play audio
	AudioManager::playBackgroundAudio(AudioManager::SceneName::Victory);
}
void PlayGameScene::goToContinue(cocos2d::Ref* sender) {
	goToVillage();
}