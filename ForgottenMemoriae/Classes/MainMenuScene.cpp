#include "MainMenuScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));

	//add physic scene
	auto scenePhysic = MainMenuScene::create();
	scenePhysic->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(scenePhysic);

	return scene;
}


// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// add hero
	player = new PlayerCharacter();
	player->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2  + origin.y));

	this->addChild(player->getSprite());

	this->schedule(
		CC_SCHEDULE_SELECTOR(MainMenuScene::updateCharacter), 0.0f, CC_REPEAT_FOREVER, 0.0f
	);

	//add physics world
	auto edgeBody = PhysicsBody::createEdgeBox(
		Size(visibleSize.width, visibleSize.height), PhysicsMaterial(1.0f, 0.0f, 0.0f), 1.0f
	);
	//set collision bitmask
	edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);

	edgeBody->setDynamic(false);

	auto edgeNode = Node::create();
	edgeNode->setPosition(
		Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y)
	);

	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	// creating a keyboard event listener
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(MainMenuScene::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(MainMenuScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->scheduleUpdate();
    
    return true;
}

void MainMenuScene::SetPhysicsWorld(cocos2d::PhysicsWorld * world)
{
	this->sceneWorld = world;
}

void MainMenuScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	CCLOG("Key with keycode %d pressed", keyCode);
	if (std::find(heldKeys.begin(), heldKeys.end(), keyCode) == heldKeys.end()) {
		heldKeys.push_back(keyCode);
	}
}

void MainMenuScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	CCLOG("Key with keycode %d released", keyCode);
	heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), keyCode), heldKeys.end());
}

void MainMenuScene::update(float dt)
{
	
}

void MainMenuScene::updateCharacter(float dt)
{
	if (heldKeys.empty()){
		player->setVelocity(Vec2(0.0f, player->getVolocity().y));
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), UP_ARROW) != heldKeys.end()) {
		if (player->isGrounded() && player->getVolocity().y <= 0) {
			player->setVelocity(Vec2(player->getVolocity().x, PLAYER_JUMP_VELOCITY));
		}
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), RIGHT_ARROW) != heldKeys.end()) {
		player->setVelocity(Vec2(PLAYER_MAX_VELOCITY, player->getVolocity().y));
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), LEFT_ARROW) != heldKeys.end()) {
		player->setVelocity(Vec2(-PLAYER_MAX_VELOCITY, player->getVolocity().y));
	}

	player->updateAction(dt);
}
