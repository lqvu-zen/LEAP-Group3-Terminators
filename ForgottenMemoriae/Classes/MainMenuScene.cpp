#include "MainMenuScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2::ZERO);

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
	hero = new PlayerCharacter();
	hero->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2  + origin.y));

	this->addChild(hero->getSprite());

	//add physics world
	auto edgeBody = PhysicsBody::createEdgeBox(
		Size(visibleSize.width, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3
	);
	//set collision bitmask
	edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);

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
	hero->updateAnimation(PlayerCharacter::State::RUNING);
}

void MainMenuScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	CCLOG("Key with keycode %d released", keyCode);
	hero->updateAnimation(PlayerCharacter::State::IDLE);
}

void MainMenuScene::update(float dt)
{
	hero->updateAction(dt);
}
