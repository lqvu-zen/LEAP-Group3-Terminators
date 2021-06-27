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

#include "MainMenuScene.h"
#include "Definitions.h"
#include "PlayGameScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
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

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    


    ///Menu
    
    auto title = Label::createWithTTF("Forgotten memoriae", "fonts/Marker Felt.ttf", 60);
    title->setTextColor(Color4B::WHITE);
    title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.75));
    this->addChild(title);

    auto newGameItem = MenuItemFont::create("New Game", CC_CALLBACK_1(MainMenuScene::onClickMenuItem, this));
    newGameItem->setTag(1);

    auto settingItem = MenuItemFont::create("Setting", CC_CALLBACK_1(MainMenuScene::onClickMenuItem, this));
    settingItem->setTag(2);

    auto aboutItem = MenuItemFont::create("About", CC_CALLBACK_1(MainMenuScene::onClickMenuItem, this));
    aboutItem->setTag(3);

    auto exitItem = MenuItemFont::create("Exit", CC_CALLBACK_1(MainMenuScene::onClickMenuItem, this));
    exitItem->setTag(4);

    auto menu = Menu::create(newGameItem, settingItem, aboutItem, exitItem, nullptr);
    menu->setPosition(visibleSize / 2);
    menu->alignItemsVertically();
    this->addChild(menu);
    
    return true;
}

void MainMenuScene::onClickMenuItem(cocos2d::Ref* sender) {
    auto node = dynamic_cast<Node*>(sender);
    if (node->getTag() == 1) {
        goToNewGame(TRANSITION_TIME);
    }
    else if (node->getTag() == 2) {

    }
    else if (node->getTag() == 3) {

    }
    else if (node->getTag() == 4) {
        CCLOG("Exit");
        Director::getInstance()->end();
        goToExit(TRANSITION_TIME);
    }
}

void MainMenuScene::goToNewGame(float dt) {
   auto scene = PlayGameScene::createScene();
   Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainMenuScene::goToSetting(float dt) {

}

void MainMenuScene::goToExit(float dt) {
    Director::getInstance()->end();
}