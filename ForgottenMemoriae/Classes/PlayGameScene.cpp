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
 THE SOFTWARE.
 ****************************************************************************/

#include "PlayGameScene.h"
USING_NS_CC;

Scene* PlayGameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setGravity(Vect(0, -100));//test world with gravity physics!!! Working for now!!!
	auto layer = PlayGameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
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
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//add background
	auto bgSprite = Sprite::create("sprites/Top sky.png");
	bgSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bgSprite->setScale(visibleSize.width /bgSprite->getContentSize().width, visibleSize.height / bgSprite->getContentSize().height);
	this->addChild(bgSprite);

	//collision with map edges
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);
	this->addChild(edgeNode);
	
	//map setup + add map
	auto map = TMXTiledMap::create("map/playMap.tmx");
	map->setPosition(0, 0);
	addChild(map, 0, 99);
	
	//setup map physics. Since we are doing a 60x34 map so width = 60 and height = 34 (2 loops)
	TMXLayer *Foreground = map->getLayer("Foreground");
	for (int i = 0; i < 60; i++)
	{
		for (int j = 0; j < 34; j++)
		{
			auto spriteTile = Foreground->getTileAt(Vec2(i, j));
			if (spriteTile != NULL)
			{
				PhysicsBody* tilePhysics = PhysicsBody::createBox(spriteTile->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0.0f));
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
	CCLOG("spawnPoint x value: %d; y value: %d", x,y);
	
	//Add character here!!!
	player = Sprite::create("sprites/yellowbird-midflap.png");
	player->setPosition(x, y);
	auto playerBody = PhysicsBody::createBox(player->getContentSize());
	//playerBody->setDynamic(true);//test Gravity physics. Working 
	player->setPhysicsBody(playerBody);
	this->addChild(player);
	//Add character here!!!
	
	
	
	//Add enemies here!!
	//Algorithm: get the EnemySpawn ValueMap from the objectGroup then check if the EnemySpawn has the value "Enemy == 1".
	//If true -> add enemey at the EnemySpawn.
	for each (Value EnemySpawn in objectGroup->getObjects())
	{
		if (EnemySpawn.asValueMap()["Enemy"].asInt() == 1)
		{
			int eneX = EnemySpawn.asValueMap()["x"].asInt();
			int eneY = EnemySpawn.asValueMap()["y"].asInt();
			this->addEnemyAt(eneX, eneY);
		}
	}
	//Add enemies here!!
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