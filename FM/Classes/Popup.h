//
//  Popup.h
//  dreamWeek
//
//  Created by Bilal Mirza on 07/08/2017.
//
//

#ifndef Popup_h
#define Popup_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

/*
 -Displays a popup
 -Resizes itself
 -Automatically swallows rest of the touches
 -Exit is called if touch is outside Bg
 */

namespace UICustom {


    class PopupDelegates : public cocos2d::LayerRadialGradient
    {

    public:
        static PopupDelegates* create();

    protected:
        virtual bool init(const bool close);
        virtual void setUpTouches(const bool close);

        virtual void show(const bool animated = true);
        virtual void dismiss(const bool animated = true);
        void setAnimated(const bool animated) { _isAnimated = animated; };

        cocos2d::ui::ImageView* _bg = nullptr;

    private:
        bool _isAnimated = false;
    };


    enum {
        eSldMusic = 0,
        eSldSound
    };

    class Popup : public PopupDelegates
    {

    public:
        static Popup* createAsMessage(const std::string& title, const std::string& msg);
        static Popup* createAsConfirmDialogue(const std::string& title, const std::string& msg, const std::function<void()>& YesFunc);
        static Popup* create(const std::string& title, const std::string& msg, cocos2d::Label* lbl, const std::function<void()>& YesFunc);

        //Edit
        static Popup* createAsConfirmRejectDialogue(const std::string& title, const std::string& msg, cocos2d::Label* lbl, const std::function<void()>& YesFunc, const std::function<void()>& NoFunc);
        static Popup* createPauseMenuVillage(const std::function<void()>& MissionFunc, const std::function<void()>& SettingFunc, const std::function<void()>& MenuFunc, const std::function<void()>& ExitFunc);
        static Popup* createPauseMenuPlayGame(const std::function<void()>& MissionFunc, const std::function<void()>& VillageFunc, const std::function<void()>& SettingFunc, const std::function<void()>& MenuFunc, const std::function<void()>& ExitFunc, const std::function<void()>& SaveFunc);
        static Popup* createSetting();
		static Popup* createSelectMapInVillage(const std::function<void()>& GoToMap1Func, const std::function<void()>& GoToMap2Func);

        static Popup* createLoss(const std::function<void()>& Revival1Func, const std::function<void()>& Revival2Func, const std::function<void()>& ExitFunc);
        static Popup* countdown(int time, cocos2d::Label* lbl);

    private:
        void initBg(const cocos2d::Size size, const std::string& title);

		void sliderEvent(Ref *pSender, cocos2d::ui::Slider::EventType type);
		void checkBoxSelectedEvent(Ref *pSender, cocos2d::ui::CheckBox::EventType type);
    };

}

#endif /* Popup_h */

