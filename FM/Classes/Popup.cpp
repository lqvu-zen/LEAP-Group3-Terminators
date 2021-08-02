//
//  Popup.cpp
//  dreamWeek
//
//  Created by Bilal Mirza on 07/08/2017.
//
//

#include "Popup.h"
#include <string.h>

USING_NS_CC;

using namespace ui;
using namespace std;

namespace {
    cocos2d::Size CONFIRM_DIALOGUE_SIZE_OFFSET = Size(100, 150);
    const float ANIMATION_TIME = 0.15f;
    const float FADE_RATIO = 150;
}

namespace FONT {
    const float LABEL_OFFSET = 50;
    const float DESCRIPTION_TEXT_SIZE = 45;
    const float TITLE_TEXT_SIZE = 70;
    const char* GAME_FONT = "fonts/Dimbo Regular.ttf";
    const float LABEL_STROKE = 4;
}

namespace IMAGEPATH {
    const char* OK_BUTTON = "popup/Ok.png";
    const char* OK_BUTTON_PRESSED = "popup/OkPressed.png";
    const char* CANCEL_BUTTON = "popup/Cancel.png";
    const char* CANCEL_BUTTON_PRESSED = "popup/CancelPressed.png";
    const char* CLOSE_BUTTON = "popup/close.png";
    const char* BACKGROUND_IMAGE = "popup/popUpBase.png";
}

namespace UICustom {



    PopupDelegates* PopupDelegates::create()
    {
        PopupDelegates* node = new (std::nothrow)PopupDelegates();
        if (node && node->init(true))
        {
            node->autorelease();
            return node;
        }
        CC_SAFE_DELETE(node);
        return nullptr;
    }

    bool PopupDelegates::init(const bool close)
    {
        Size winSize = Director::getInstance()->getWinSize();

        if (!LayerRadialGradient::initWithColor(Color4B(0, 0, 0, 0), Color4B(0, 0, 0, FADE_RATIO), winSize.width / 1.7f, winSize / 2, 0.075f))
        {
            return false;
        }
        this->setOpacity(0);
        show(true);
        this->setUpTouches(close);


        return true;
    }

    void PopupDelegates::show(const bool animated)
    {
        if (animated) {
            this->runAction(FadeTo::create(ANIMATION_TIME, FADE_RATIO));
        }
        else {
            this->setOpacity(FADE_RATIO);
        }
    }
    void PopupDelegates::dismiss(const bool animated)
    {
        if (animated) {
            this->runAction(Sequence::create(FadeTo::create(ANIMATION_TIME, 0), RemoveSelf::create(), NULL));
        }
        else {
            //this->removeFromParentAndCleanup(false);
        }
    }

    void PopupDelegates::setUpTouches(const bool close)
    {

        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [=](Touch* touch, Event* event) {
            if (_bg) {
                if (!_bg->getBoundingBox().containsPoint(this->convertToNodeSpace(touch->getLocation())))
                {
                    this->dismiss(close); //Close
                }
            }
            else {
                this->dismiss(true);
            }
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }







    Popup* Popup::createAsMessage(const std::string& title, const std::string& msg)
    {
        return createAsConfirmDialogue(title, msg, NULL);
    }

    Popup* Popup::createAsConfirmDialogue(const std::string& title, const std::string& msg, const std::function<void()>& YesFunc)
    {
        return create(title, msg, NULL, YesFunc);
    }

    Popup* Popup::create(const std::string& title, const std::string& msg, cocos2d::Label* lbl, const std::function<void()>& YesFunc)
    {
        Popup* node = new (std::nothrow)Popup();
        Size winSize = Director::getInstance()->getWinSize();
        if (node && node->init(true))
        {

            if (!lbl) {
                lbl = Label::createWithTTF(msg, FONT::GAME_FONT, FONT::DESCRIPTION_TEXT_SIZE);
            }
            lbl->setPosition(winSize.width / 2, winSize.height / 2 - FONT::LABEL_OFFSET / 2);
            lbl->enableOutline(Color4B::BLACK, FONT::LABEL_STROKE);
            lbl->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
            lbl->enableShadow(Color4B::BLACK, Size(0, -2));


            if (YesFunc) {
                MenuItemImage* yesButton = MenuItemImage::create(IMAGEPATH::OK_BUTTON, IMAGEPATH::OK_BUTTON_PRESSED, [=](Ref* sender) {

                    YesFunc();
                    node->dismiss(true);
                });

                MenuItemImage* noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref* sender) {
                    node->dismiss(true);
                });


                Menu* menu = Menu::create(yesButton, noButton, NULL);
                node->addChild(menu, 2);
                menu->setPosition(winSize.width / 2, winSize.height / 2 - lbl->getContentSize().height / 2 - 75);
                menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);

                lbl->setPosition(winSize / 2);
                CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 300);
            }
            node->addChild(lbl, 3);
            node->initBg(lbl->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
            node->autorelease();
            return node;
        }

        CC_SAFE_DELETE(node);
        return nullptr;
    }

    void Popup::initBg(Size size, const std::string& title)
    {

        Size winSize = Director::getInstance()->getWinSize();

        _bg = ui::ImageView::create(IMAGEPATH::BACKGROUND_IMAGE);
        this->addChild(_bg);

        _bg->setPosition(Point(winSize.width / 2, winSize.height / 2));
        _bg->setScale9Enabled(true);
        _bg->setContentSize(size);

        ui::ImageView* fill = ui::ImageView::create(IMAGEPATH::BACKGROUND_IMAGE);
        _bg->addChild(fill);
        fill->setColor(Color3B(210, 210, 210));
        fill->setScale9Enabled(true);
        fill->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        fill->setPosition(Point(FONT::LABEL_OFFSET / 4, FONT::LABEL_OFFSET / 4));
        fill->setContentSize(Size(size.width - FONT::LABEL_OFFSET / 2, size.height - FONT::LABEL_OFFSET * 2));


        Label* heading = Label::createWithTTF(title, FONT::GAME_FONT, FONT::TITLE_TEXT_SIZE);
        heading->setPosition(_bg->getContentSize().width / 2, _bg->getContentSize().height - FONT::LABEL_OFFSET);
        _bg->addChild(heading);
        heading->enableOutline(Color4B::BLACK, FONT::LABEL_STROKE);
        heading->enableShadow(Color4B::BLACK, Size(0, -3));
    }

    //Edit
    Popup* Popup::createAsConfirmRejectDialogue(const std::string& title, const std::string& msg, cocos2d::Label* lbl, const std::function<void()>& YesFunc, const std::function<void()>& NoFunc)
    {
        Popup* node = new (std::nothrow)Popup();
        Size winSize = Director::getInstance()->getWinSize();
        if (node && node->init(true))
        {

            if (!lbl) {
                lbl = Label::createWithTTF(msg, FONT::GAME_FONT, FONT::DESCRIPTION_TEXT_SIZE);
            }
            lbl->setPosition(winSize.width / 2, winSize.height / 2 - FONT::LABEL_OFFSET / 2);
            lbl->enableOutline(Color4B::BLACK, FONT::LABEL_STROKE);
            lbl->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
            lbl->enableShadow(Color4B::BLACK, Size(0, -2));


            if (YesFunc) {
                MenuItemImage* yesButton = MenuItemImage::create(IMAGEPATH::OK_BUTTON, IMAGEPATH::OK_BUTTON_PRESSED, [=](Ref* sender) {

                    YesFunc();
                    node->dismiss(true);
                });

                MenuItemImage* noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [=](Ref* sender) {
                    NoFunc();
                    node->dismiss(true);
                });


                Menu* menu = Menu::create(yesButton, noButton, NULL);
                node->addChild(menu, 2);
                menu->setPosition(winSize.width / 2, winSize.height / 2 - lbl->getContentSize().height / 2 - 75);
                menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);

                lbl->setPosition(winSize / 2);
                CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 300);
            }
            node->addChild(lbl, 3);
            node->initBg(lbl->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
            node->autorelease();
            return node;
        }

        CC_SAFE_DELETE(node);
        return nullptr;
    }

    Popup* Popup::createPauseMenuVillage(const std::function<void()>& MissionFunc, const std::function<void()>& SettingFunc, const std::function<void()>& MenuFunc, const std::function<void()>& ExitFunc) {
        Popup* node = new (std::nothrow)Popup();
        Size winSize = Director::getInstance()->getWinSize();
        if (node && node->init(true))
        {
            auto missionButton = MenuItemFont::create("Your Mission", [=](Ref* sender) {
                MissionFunc();
                node->dismiss(true);
            });

            auto settingButton = MenuItemFont::create("Setting", [=](Ref* sender) {
                SettingFunc();
                node->dismiss(true);
            });

            auto menuButton = MenuItemFont::create("Main Menu", [=](Ref* sender) {
                MenuFunc();
                node->dismiss(true);
            });

            auto exitButton = MenuItemFont::create("Exit", [=](Ref* sender) {
                ExitFunc();
                node->dismiss(true);
            });

            Menu* menu = Menu::create(missionButton, settingButton, menuButton, exitButton, NULL);
            node->addChild(menu, 2);
            menu->setPosition(winSize.width / 2, winSize.height / 2 - FONT::LABEL_OFFSET / 2);
            menu->alignItemsVerticallyWithPadding(FONT::LABEL_OFFSET / 2);

            node->initBg(Size(400,400), "Pause");
            node->autorelease();
            return node;
        }

        CC_SAFE_DELETE(node);
        return nullptr;
    }

    Popup* Popup::createPauseMenuPlayGame(const std::function<void()>& MissionFunc, const std::function<void()>& VillageFunc, const std::function<void()>& SettingFunc, const std::function<void()>& MenuFunc, const std::function<void()>& ExitFunc, const std::function<void()>& SaveFunc) {
        Popup* node = new (std::nothrow)Popup();
        Size winSize = Director::getInstance()->getWinSize();
        if (node && node->init(true))
        {
            auto missionButton = MenuItemFont::create("Unlock All Skill", [=](Ref* sender) {
                MissionFunc();
                node->dismiss(true);
            });

            auto villageButton = MenuItemFont::create("Return Village", [=](Ref* sender) {
                VillageFunc();
                node->dismiss(true);
            });

            auto settingButton = MenuItemFont::create("Setting", [=](Ref* sender) {
                SettingFunc();
                node->dismiss(true);
            });

            auto menuButton = MenuItemFont::create("Main Menu", [=](Ref* sender) {
                MenuFunc();
                node->dismiss(true);
            });

            auto exitButton = MenuItemFont::create("Exit", [=](Ref* sender) {
                ExitFunc();
                node->dismiss(true);
            });

			auto savetButton = MenuItemFont::create("Save", [=](Ref* sender) {
				SaveFunc();
				node->dismiss(true);
			});

            Menu* menu = Menu::create(missionButton, villageButton, savetButton, settingButton, menuButton, exitButton, NULL);
            node->addChild(menu, 2);
            menu->setPosition(winSize.width / 2, winSize.height / 2 - FONT::LABEL_OFFSET / 2);
            menu->alignItemsVerticallyWithPadding(FONT::LABEL_OFFSET / 2);

            node->initBg(Size(450, 500), "Pause");
            node->autorelease();
            return node;
        }

        CC_SAFE_DELETE(node);
        return nullptr;
    }

	Popup* Popup::createSelectMapInVillage(const std::function<void()>& GoToMap1Func, const std::function<void()>& GoToMap2Func)
	{
		Popup* node = new (std::nothrow)Popup();
		Size winSize = Director::getInstance()->getWinSize();
		if (node && node->init(true))
		{
			auto map1Button = MenuItemFont::create("Go To Map 1", [=](Ref* sender) {
				GoToMap1Func();
				node->dismiss(true);
			});

			auto map2Button = MenuItemFont::create("Go To Map 2", [=](Ref* sender) {
				GoToMap2Func();
				node->dismiss(true);
			});

			Menu* menu = Menu::create(map1Button, map2Button, NULL);
			node->addChild(menu, 2);
			menu->setPosition(winSize.width / 2, winSize.height / 2 - FONT::LABEL_OFFSET / 2);
			menu->alignItemsVerticallyWithPadding(FONT::LABEL_OFFSET / 2);

			node->initBg(Size(400, 450), "Select Map");
			node->autorelease();
			return node;
		}

		CC_SAFE_DELETE(node);
		return nullptr;
	}

#if 1 
    Popup* Popup::createSetting() {
        Popup* node = new (std::nothrow)Popup();
        Size winSize = Director::getInstance()->getWinSize();
        if (node && node->init(true))
        {
            const char* SRT_SETTING[] = { "Music", "Sound" };

            for (int index = 0; index < 2; index++) {
                // label
                auto  _label = Label::createWithTTF(SRT_SETTING[index], "fonts/arial.ttf", 30);
                _label->setPosition(Vec2(winSize.width / 2, (winSize.height - FONT::LABEL_OFFSET / 2) * (7 - index * 2) / 10));
                node->addChild(_label, 2);

                // slider bar
                Slider* m_sliderOptionMusic = Slider::create();
                m_sliderOptionMusic->setTag(index);
                m_sliderOptionMusic->setScale(0.5);
                m_sliderOptionMusic->loadBarTexture("popup/spr_slidebar_off.png");
                m_sliderOptionMusic->loadSlidBallTextures(
                    "popup/spr_slidebar_button_normal.png",
                    "popup/spr_slidebar_button_selected.png",
                    "popup/spr_slidebar_button_selected.png");
                m_sliderOptionMusic->loadProgressBarTexture("popup/spr_slidebar_on.png");

                m_sliderOptionMusic->setPosition(Vec2(winSize.width / 2, (winSize.height - FONT::LABEL_OFFSET / 2) * (6 - index * 2) / 10));

                //m_sliderOptionMusic->addEventListener(CC_CALLBACK_2(Popup::sliderEvent, node));
                node->addChild(m_sliderOptionMusic, 2);
            }


            /// init checkbox
            // label
            auto  _labelMuteAllSound = Label::createWithTTF("Mute On Sound", "fonts/arial.ttf", 30);
            _labelMuteAllSound->setPosition(Vec2(winSize.width * 4 / 10, (winSize.height / 2 - FONT::LABEL_OFFSET / 2) * 4 / 10));
            node->addChild(_labelMuteAllSound, 2);

            // checkbox
            CheckBox* m_checkboxMuteAllSound = CheckBox::create("popup/spr_checkbox_normal.png",
                "popup/spr_checkbox_normal_press.png",
                "popup/spr_checkbox_active.png",
                "popup/spr_checkbox_normal_press.png",
                "popup/spr_checkbox_active.png");
            m_checkboxMuteAllSound->setScale(0.5);
            m_checkboxMuteAllSound->setPosition(Vec2(winSize.width * 6 / 10, (winSize.height / 2 - FONT::LABEL_OFFSET / 2) * 4 / 10));
            //m_checkboxMuteAllSound->addEventListener(CC_CALLBACK_2(Popup::checkBoxSelectedEvent, node));
            node->addChild(m_checkboxMuteAllSound, 2);

            node->initBg(Size(500, 500), "Setting");
            node->autorelease();
            return node;
        }

        CC_SAFE_DELETE(node);
        return nullptr;
    }
    
    //void Popup::sliderEvent(Ref* pSender, Slider::EventType type) {
    //    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
    //        Slider* _slider = dynamic_cast<Slider*>(pSender);
    //        float _valueVolume = float(_slider->getPercent()) / 100;
    //        changeVolumeOfAudio(_slider->getTag(), _valueVolume);
    //    }
    //}
    //void Popup::checkBoxSelectedEvent(Ref* pSender, CheckBox::EventType type) {
    //    switch (type)
    //    {
    //    case CheckBox::EventType::SELECTED:
    //        m_sliderOptionMusic[eSldMusic]->setPercent(0);
    //        m_sliderOptionMusic[eSldSound]->setPercent(0);
    //        //m_audio->setEffectsVolume(0.0f);
    //        //m_audio->setBackgroundMusicVolume(0.0f);
    //        break;
    //    case CheckBox::EventType::UNSELECTED:
    //        m_sliderOptionMusic[eSldSound]->setPercent(50);
    //        m_sliderOptionMusic[eSldMusic]->setPercent(50);
    //        //m_audio->setEffectsVolume(0.5f);
    //        //m_audio->setBackgroundMusicVolume(0.5f);
    //        break;
    //    default:
    //        break;
    //    }
    //}
    //void Popup::changeVolumeOfAudio(int _typeAudio, float _valueVolume) {
    //    /*if (_typeAudio == eSldSound)
    //        m_audio->setEffectsVolume(_valueVolume);
    //    else
    //        m_audio->setBackgroundMusicVolume(_valueVolume);*/
    //}
#endif

    Popup* Popup::createLoss(const std::function<void()>& Revival1Func, const std::function<void()>& Revival2Func, const std::function<void()>& ExitFunc) {
        Popup* node = new (std::nothrow)Popup();
        Size winSize = Director::getInstance()->getWinSize();
        if (node && node->init(false))
        {
            auto revival1Button = MenuItemFont::create("Resurrect on the spot", [=](Ref* sender) {
                Revival1Func();
                node->dismiss(true);
            });

            auto revival2Button = MenuItemFont::create("Village revival", [=](Ref* sender) {
                Revival2Func();
                node->dismiss(true);
            });

            auto exitButton = MenuItemFont::create("Exit", [=](Ref* sender) {
                ExitFunc();
                node->dismiss(true);
            });

            Menu* menu = Menu::create(revival1Button, revival2Button, exitButton, NULL);
            node->addChild(menu, 2);
            menu->setPosition(winSize.width / 2, winSize.height / 2 - FONT::LABEL_OFFSET / 2);
            menu->alignItemsVerticallyWithPadding(FONT::LABEL_OFFSET / 2);

            node->initBg(Size(400, 450), "You Died!!!");
            node->autorelease();
            return node;
        }

        CC_SAFE_DELETE(node);
        return nullptr;
    }
    
    Popup* Popup::countdown(int time, cocos2d::Label* lbl) {
        Popup* node = new (std::nothrow)Popup();
        Size winSize = Director::getInstance()->getWinSize();
        if (node && node->init(false))
        {
            std::string tmp = StringUtils::format("%i second", time);

            //lbl = Label::createWithTTF(tmp, FONT::GAME_FONT, FONT::DESCRIPTION_TEXT_SIZE);
            
            lbl->setPosition(winSize.width / 2, winSize.height / 2 - FONT::LABEL_OFFSET / 2);
            lbl->enableOutline(Color4B::BLACK, FONT::LABEL_STROKE);
            lbl->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
            lbl->enableShadow(Color4B::BLACK, Size(0, -2));

            node->addChild(lbl, 3);
            node->initBg(Size(400, 450), "Respawn time ");
            node->autorelease();

            return node;
        }

        CC_SAFE_DELETE(node);
        return nullptr;
    }
}

