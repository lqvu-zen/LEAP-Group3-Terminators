///@ Popup.h
#ifndef __SINS_POPUP_H__
#define __SINS_POPUP_H__

#include "string"
#include "cocos2d.h"

#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class SideBarMainMenu;

USING_NS_CC;

class Popup : public Node {
public:
	CREATE_FUNC(Popup);

	virtual bool init();
	virtual void onExit();

	virtual void disappear();
	virtual void appear();
	Layer* getPopUpLayer();
	virtual void setTitlePopup(std::string _titlePopup);

protected:
	LayerColor                  *m_fadingLayer;
	Layer						*m_popupLayer;

	Size						backgroundContentSize;
	Size                        visibleSize;
	Point						origin;

	ActionInterval              *m_appearAction;
	ActionInterval              *m_disappearAction;

private:
};

#endif /* defined (__SINS_POPUP_H__) */