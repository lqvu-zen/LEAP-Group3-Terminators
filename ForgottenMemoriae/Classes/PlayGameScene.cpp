/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
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
	auto mapSize = Size((map->getMapSize().width * map->getTileSize().width) * SCALE_FACTOR, (map->getMapSize().height * map->getTileSize().height) * SCALE_FACTOR);
	auto edgeBody = PhysicsBody::createEdgeBox(mapSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(mapSize.width/2, mapSize.height/2));
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
	//get the x, y value from the spawnPoint in the tilemap.
	ValueMap spawnPoint = objectGroup->getObject("SpawnPoint");
	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	//Add character here!!!
	player = Sprite::create("sprites/yellowbird-midflap.png");
	player->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	auto playerBody = PhysicsBody::createBox(player->getContentSize());
	player->setPhysicsBody(playerBody);
	//cameraTarget for the followCamera to follow the player.
	cameraTarget = Node::create();
	cameraTarget->setPositionX(player->getPositionX());
	cameraTarget->setPositionY(visibleSize.height / 2 + origin.y);
	this->addChild(player);
	this->addChild(cameraTarget);

	//Add enemies here!!
	//Algorithm: get the EnemySpawn ValueMap from the objectGroup then check if the EnemySpawn has the value "Enemy == 1".
	//If true -> add enemey at the EnemySpawn.
	for each (Value EnemySpawn in objectGroup->getObjects())
	{
		if (EnemySpawn.asValueMap()["Enemy"].asInt() == 1)
		{
			int eneX = EnemySpawn.asValueMap()["x"].asInt();
			int eneY = EnemySpawn.asValueMap()["y"].asInt();
			this->addEnemyAt(eneX * SCALE_FACTOR, eneY * SCALE_FACTOR);
		}
	}


	//Keyboard test
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(PlayGameScene::onKeyPressedTest, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
	//Add a follow action to follow the cameraTarget(the player) with boundaries to follow.
	//The boundaries are the origin point (0, 0) and the total size of the map (in pixels) * SCALE_FACTOR.
	followCamera = Follow::create(cameraTarget, Rect(origin.x, origin.y, mapSize.width, mapSize.height));
	this->runAction(followCamera);
	
	this->scheduleUpdate();

	return true;
}


void PlayGameScene::addEnemyAt(int x, int y)
{
	Sprite *enemy = Sprite::create("sprites/redbird-midflap.png");
	enemy->setFlippedX(true);
	enemy->setPosition(x, y);
	auto enemyBody = PhysicsBody::createBox(enemy->getContentSize());
	enemy->setPhysicsBody(enemyBody);
	this->addChild(enemy);
}

void PlayGameScene::onKeyPressedTest(EventKeyboard::KeyCode keyCode, Event *event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		player->setPositionX(player->getPositionX() + (BIRD_JUMP * visibleSize.width));
		cameraTarget->setPositionX(player->getPositionX());
		
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		player->setPositionX(player->getPositionX() - (BIRD_JUMP * visibleSize.width));
		cameraTarget->setPositionX(player->getPositionX());
		
		
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		player->setPositionY(player->getPositionY() + (BIRD_JUMP * visibleSize.height));
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		player->setPositionY(player->getPositionY() - (BIRD_JUMP * visibleSize.height));
	}

	//testing lockScreen!!!
	/*if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		if (!isLocked)
		{
			isLocked = true;
			CCLOG("LOCK SCREEN!");
			pausedActions = Director::getInstance()->getActionManager()->pauseAllRunningActions();
			auto lockBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
			lockNode = Node::create();
			lockNode->setPosition(Point(player->getPositionX(), player->getPositionY()));
			lockNode->setPhysicsBody(lockBody);
			this->addChild(lockNode);
		}
		else
		{
			isLocked = false;
			Director::getInstance()->getActionManager()->resumeTargets(pausedActions);
			this->removeChild(lockNode);
		}
	}*/
}


void PlayGameScene::update(float dt)
{
	//Some debug log
	//CCLOG("player position: %f. camera position: %f %f; map width: %f", player->getPositionX(), cameraTarget->getPositionX(), cameraTarget->getPositionY(), map->getMapSize().width * map->getTileSize().width);
	//cameraTarget->setPositionX(player->getPositionX());
}