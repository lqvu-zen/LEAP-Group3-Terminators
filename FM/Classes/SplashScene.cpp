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

#include "SplashScene.h"
#include "ui/CocosGUI.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    return SplashScene::create();
}


// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object

    auto bar = Sprite::create("sprites/bar.png");
    bar->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
    this->addChild(bar);
    this->scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScene::loadSplashScene), DISPLAY_TIME_SPLASH_SCENE);

    return true;
}

void SplashScene::loadSplashScene(float dt) {
    auto scene = Scene::create();

    auto tmp = Director::getInstance()->getRunningScene();
    CCLOG("TYPE THIS SCENE: %s", typeid(this).name());
    CCLOG("TYPE SCENE: %s", typeid(tmp).name());

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /*auto logo = Sprite::create("sprites/logo.png");
    logo->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.75));
    scene->addChild(logo);*/

    auto title = Label::createWithTTF("Forgotten memoriae", "fonts/Marker Felt.ttf", 60);
    title->setTextColor(Color4B::WHITE);
    title->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
    scene->addChild(title);

    auto loadingBar = ui::LoadingBar::create("sprites/loadingbar.png");
    loadingBar->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.25));
    loadingBar->setScale(1.5);
    loadingBar->setDirection(ui::LoadingBar::Direction::LEFT);
    loadingBar->setPercent(0);
    scene->addChild(loadingBar);
    scene->schedule([=](float delta) {
        float percent = loadingBar->getPercent();
        percent+= 50;
        loadingBar->setPercent(percent);
        if (percent >= 100.0f) {
            scene->unschedule("updateLoadingBar");
            scene->scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScene::goToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE);
        }
    }, 0.1f, "updateLoadingBar");
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void SplashScene::goToMainMenuScene(float dt) {
    auto scene = MainMenuScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}