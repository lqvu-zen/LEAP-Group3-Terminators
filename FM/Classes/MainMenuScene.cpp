#include "MainMenuScene.h"
#include "Definitions.h"
#include "PlayGameScene.h"
#include "Popup.h"
#include "VillageScene.h"
#include "GameManager.h"

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
	auto bg = Sprite::create("sprites/mainMenuBG.png");
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
	this->addChild(bg);
#if 1 
    ///Menu
    auto title = Label::createWithTTF("Forgotten memoriae", "fonts/Marker Felt.ttf", 60);
    title->setTextColor(Color4B::WHITE);
    title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.75));
    this->addChild(title);

    auto newGameItem = MenuItemFont::create("New Game", CC_CALLBACK_1(MainMenuScene::onClickMenuItem, this));
    newGameItem->setTag(1);

    auto aboutItem = MenuItemFont::create("About", CC_CALLBACK_1(MainMenuScene::onClickMenuItem, this));
    aboutItem->setTag(3);

    auto exitItem = MenuItemFont::create("Exit", CC_CALLBACK_1(MainMenuScene::onClickMenuItem, this));
    exitItem->setTag(4);

	auto continueItem = MenuItemFont::create("Continue", CC_CALLBACK_1(MainMenuScene::onClickMenuItem, this));
	continueItem->setTag(5);

	auto menu = Menu::create();

	if (UserDefault::getInstance()->getIntegerForKey("SAVED", 0) == 1) {
		menu = Menu::create(continueItem, newGameItem, aboutItem, exitItem, nullptr);
	}
	else {
		menu = Menu::create(newGameItem, aboutItem, exitItem, nullptr);
	}

    menu->setPosition(visibleSize / 2);
    menu->alignItemsVertically();
    this->addChild(menu);
#endif 

	//play audio
	AudioManager::playBackgroundAudio(AudioManager::SceneName::MainMenu);

	auto emitter = ParticleRain::create();

	addChild(emitter);

    return true;
}

void MainMenuScene::onClickMenuItem(cocos2d::Ref* sender) {
	//play audio
	AudioManager::playRandomAudio(AudioManager::RandomAction::Click_Menu);

    auto node = dynamic_cast<Node*>(sender);
    if (node->getTag() == 1) {
        goToNewGame(TRANSITION_TIME);
    }
    else if (node->getTag() == 3) {
        goToAbout(TRANSITION_TIME);
    }
    else if (node->getTag() == 4) {
        CCLOG("Exit");
        goToExit(TRANSITION_TIME);
    }
	else if (node->getTag() == 5)
	{
		CCLOG("Continue game");
		goToContinueGame(TRANSITION_TIME);
	}
}

void MainMenuScene::goToNewGame(float dt) {
   GameManager::getInstace()->setMapLevel(0);
   auto scene = VillageScene::createScene();
   Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
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

void MainMenuScene::goToContinueGame(float dt)
{
	//Implement continue game here.
	GameManager::getInstace()->setMapLevel(0);

	GameManager::getInstace()->setLoadOption(1);

	auto scene = VillageScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}