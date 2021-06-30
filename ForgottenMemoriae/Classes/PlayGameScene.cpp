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
#include "ui/CocosGUI.h"
#include "Definitions.h"

USING_NS_CC;

Scene* PlayGameScene::createScene()
{
    //return PlayGameScene::create();


    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    auto layer = PlayGameScene::create();
    layer->SetPhysicsWord(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}


// on "init" you need to initialize your instance
bool PlayGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    numType = 1;
    numMonster = 10;
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);


    /// <summary>
    /// Character control button to move  
    /// </summary>
    /// <returns></returns>
    auto button = Sprite::create("sprites/button.png");
    button->setScale(0.1);
    button->setPosition(Vec2(button->getContentSize().width * 0.075, button->getContentSize().height * 0.075));
    this->addChild(button);

    auto upItem = MenuItemImage::create("sprites/up.png", "sprites/up.png", CC_CALLBACK_1(PlayGameScene::onClickMoveMenu, this));
    upItem->setScale(0.05);
    upItem->setPosition(Vec2(button->getPosition().x, button->getPosition().y + button->getContentSize().height * 0.1 / 4));
    upItem->setTag(1);

    auto downItem = MenuItemImage::create("sprites/down.png", "sprites/down.png", CC_CALLBACK_1(PlayGameScene::onClickMoveMenu, this));
    downItem->setScale(0.05);
    downItem->setPosition(Vec2(button->getPosition().x, button->getPosition().y - button->getContentSize().height * 0.1 / 4));
    downItem->setTag(2);

    auto leftItem = MenuItemImage::create("sprites/left.png", "sprites/left.png", CC_CALLBACK_1(PlayGameScene::onClickMoveMenu, this));
    leftItem->setScale(0.05);
    leftItem->setPosition(Vec2(button->getPosition().x - button->getContentSize().width * 0.1 / 4, button->getPosition().y));
    leftItem->setTag(3);

    auto rightItem = MenuItemImage::create("sprites/right.png", "sprites/right.png", CC_CALLBACK_1(PlayGameScene::onClickMoveMenu, this));
    rightItem->setScale(0.05);
    rightItem->setPosition(Vec2(button->getPosition().x + button->getContentSize().width * 0.1 / 4, button->getPosition().y));
    rightItem->setTag(4);

    auto moveMenu = Menu::create(upItem, downItem, leftItem, rightItem, nullptr);
    moveMenu->setPosition(Vec2::ZERO);
    this->addChild(moveMenu);


    /// <summary>
    /// Character control button to attack and use skills 
    /// </summary>
    /// <returns></returns>
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
    this->addChild(attackMenu);
    
    //////////////////        BOSS
    //boss = new BossCharacter(this, 1);
    //boss->get()->setPosition(visibleSize / 2);
    //this->addChild(boss->get());
    //boss->shoot_bow();

    ////this->schedule(CC_SCHEDULE_SELECTOR(PlayGameScene::attack), 3);


    //////////////////        MONSTER
    ///*for (int i = 0; i < numMonster; i++) {
    //    monster[i] = new MonsterCharacter(this, i % numType + 1);
    //    monster[i]->get()->setPosition(Vec2(visibleSize / 2));
    //    this->addChild(monster[i]->get());
    //}

    //this->schedule(CC_SCHEDULE_SELECTOR(PlayGameScene::attackMonster), 3);*/
    return true;
}

/// <summary>
/// Control character movement  
/// </summary>
/// <returns></returns>
void PlayGameScene::onClickMoveMenu(cocos2d::Ref* sender) {
    auto node = dynamic_cast<Node*>(sender);
    if (node->getTag() == 1) {
        CCLOG("Up");
    }
    else if (node->getTag() == 2) {
        CCLOG("Down");
    }
    else if (node->getTag() == 3) {
        CCLOG("Left");
    }
    else if (node->getTag() == 4) {
        CCLOG("Right");
    }
}

/// <summary>
/// Control the character to attack and use skills   
/// </summary>
/// <returns></returns>
void PlayGameScene::onClickAttackMenu(cocos2d::Ref* sender) {
    auto node = dynamic_cast<Node*>(sender);
    CCLOG("%i", node->getTag());
    if (node->getTag() == 1) {
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

void PlayGameScene::attack(float dt) {
    boss->attack();
}

void PlayGameScene::attackMonster(float dt) {
    for (int i = 0; i < numMonster; i++) {
        monster[i]->attack();
    }  
}

bool PlayGameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    return true;
}