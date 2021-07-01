///@ Popup.cpp
#include "Popup.h"

bool Popup::init() {
	if (!Node::init()) {
		return false;
	}

	
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	/// init image background
	auto _background = Sprite::create("popup/spr_background_popup.png");
	_background->setScale(0.5);
	_background->setPosition(visibleSize / 2);

	backgroundContentSize = _background->getContentSize();

	m_popupLayer = Layer::create();
	m_popupLayer->setPosition(Vec2(visibleSize.width + origin.x, origin.y));
	this->addChild(m_popupLayer, 99);

	m_popupLayer->addChild(_background);
	/*------------------------------------------------------------------*/


	/// init two acction for poup
	m_appearAction = TargetedAction::create(m_popupLayer,
		MoveTo::create(0.5f, Vec2(origin.x, origin.y)));
	
	m_disappearAction = TargetedAction::create(m_popupLayer,
		MoveTo::create(0.5f, Vec2(visibleSize.width + origin.x, origin.y)));
	/*------------------------------------------------------------------*/


	m_appearAction->retain();
	m_disappearAction->retain();
	
	return true;
}

void Popup::onExit() {
	m_appearAction->release();
	m_disappearAction->release();

	Node::onExit();
}

void Popup::disappear() {
	this->runAction(m_disappearAction->clone());
}

void Popup::appear() {	
	this->runAction(m_appearAction->clone());
}


void Popup::setTitlePopup(std::string _titlePopup) {
	auto _title = Label::createWithTTF(_titlePopup, "fonts/arial.ttf", 50);
	_title->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 9 / 10 + origin.y));
	
	m_popupLayer->addChild(_title);
}