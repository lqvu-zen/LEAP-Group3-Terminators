#include "MainMenuScene.h"
#include "Definitions.h"
#include "PlayGameScene.h"
#include "Popup.h"
#include "VillageScene.h"
#include "GameManager.h"
#include "AudioManager.h"

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

	GameManager::getInstace()->init();

	//background audio
	AudioManager::playBackgroundAudio(AudioManager::SceneName::MainMenu);
#if 1 
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
#endif 
    return true;
}

void MainMenuScene::onClickMenuItem(cocos2d::Ref* sender) {
    auto node = dynamic_cast<Node*>(sender);
    if (node->getTag() == 1) {
        goToNewGame(TRANSITION_TIME);
    }
    else if (node->getTag() == 2) {
        goToSetting(TRANSITION_TIME);
    }
    else if (node->getTag() == 3) {
        goToAbout(TRANSITION_TIME);
    }
    else if (node->getTag() == 4) {
        CCLOG("Exit");
        goToExit(TRANSITION_TIME);
    }
}

void MainMenuScene::goToNewGame(float dt) {
   GameManager::getInstace()->setMapLevel(0);
   auto scene = VillageScene::createScene();
   Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainMenuScene::goToSetting(float dt) {
    
}

void MainMenuScene::goToAbout(float dt) {
    UICustom::Popup* popup = UICustom::Popup::createAsMessage("About", "Forgotten memoriae.\n\nTrieu Tan Hung\nLe Quang Vu\nTrinh Dong Duong");
    this->addChild(popup);
}

void MainMenuScene::goToExit(float dt) {
    UICustom::Popup* popup = UICustom::Popup::createAsConfirmDialogue("Notify", "Want to Exit game", [=]() {
        Director::getInstance()->end();
    });
    this->addChild(popup);
}