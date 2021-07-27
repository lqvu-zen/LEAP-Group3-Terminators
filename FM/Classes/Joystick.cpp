/*
 * Joystick.cpp
 *
 *  Created on: 2015-2-1
 *      Author: yong
 */

#include "Joystick.h"

#define PI 3.1415926

const std::string JoystickEvent::EVENT_JOYSTICK = "event_of_joystick";

JoystickEvent::JoystickEvent() {
	log(" JoystickEvent(), %p", this);
}

JoystickEvent::~JoystickEvent() {
	log("~JoystickEvent(), %p", this);
}

bool JoystickEvent::init() {
	return true;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------
Joystick::Joystick() {
}

Joystick::~Joystick() {
	
	_eventDispatcher->removeEventListenersForTarget(this);
}

bool Joystick::init() {
	bool result = false;
	do {
		
		if (!Layer::init()) {
			break;
		}
		
		mJsBg = Sprite::create("sprites/joystick_bg.png");
		if (nullptr == mJsBg) {
			break;
		}
		mJsBg->setPosition(mJsPos);
		mJsBg->setScale(1.2);
		mJsBg->setOpacity(140);
		addChild(mJsBg);

		
		mJsCenter = Sprite::create("sprites/joystick_center.png");
		if (nullptr == mJsCenter) {
			break;
		}
		mJsCenter->setPosition(mJsPos);
		mJsCenter->setScale(1.2);
		mJsCenter->setOpacity(140);
		addChild(mJsCenter);

		
		auto touchListener = EventListenerTouchOneByOne::create();
		if (nullptr == touchListener) {
			break;
		}
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan =
			CC_CALLBACK_2(Joystick::onTouchBegan, this);
		touchListener->onTouchMoved =
			CC_CALLBACK_2(Joystick::onTouchMoved, this);
		touchListener->onTouchEnded =
			CC_CALLBACK_2(Joystick::onTouchEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,
			this);

		result = true;
	} while (0);

	return result;
}

bool Joystick::onTouchBegan(Touch *touch, Event *unused_event) {
	log("onTouchBegan");
	/*JoystickEvent* jsEvent = JoystickEvent::create();
	jsEvent->type = JoyStickEventType::BEGAN;
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		JoystickEvent::EVENT_JOYSTICK, jsEvent);*/

	auto point = touch->getLocation();
	if (mJsCenter->getBoundingBox().containsPoint(point)) {
		
		return true;
	}
	return false;
}

void Joystick::onTouchMoved(Touch *touch, Event *unused_event) {
	log("onTouchMoved");
	Vec2 point = touch->getLocation();
	double y = point.y - mJsPos.y;
	double x = point.x - mJsPos.x;
	double angle = atan2(y, x) * 180 / PI;
	log("------------------------------------          %f", angle);

	double jsBgRadis = mJsBg->getContentSize().width * 0.5;
	
	distanceOfTouchPointToCenter = sqrt(
		pow(mJsPos.x - point.x, 2) + pow(mJsPos.y - point.y, 2));
	
	if (distanceOfTouchPointToCenter >= jsBgRadis) {
		
		double deltX = x * (jsBgRadis / distanceOfTouchPointToCenter);
		double deltY = y * (jsBgRadis / distanceOfTouchPointToCenter);
		mJsCenter->setPosition(Vec2(mJsPos.x + deltX, mJsPos.y + deltY));
	}
	else {
		mJsCenter->setPosition(point);
	}

	
	JoystickEvent* jsEvent = JoystickEvent::create();
	jsEvent->type = JoyStickEventType::MOVED;
	jsEvent->mAnagle = angle;
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		JoystickEvent::EVENT_JOYSTICK, jsEvent);
}

void Joystick::onTouchEnded(Touch *touch, Event *unused_event) {
	log("onTouchEnded");
	mJsCenter->setPosition(mJsPos);

	JoystickEvent* jsEvent = JoystickEvent::create();
	jsEvent->type = JoyStickEventType::ENDED;
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		JoystickEvent::EVENT_JOYSTICK, jsEvent);
}

double Joystick::getDistanceFromCenter()
{
	return distanceOfTouchPointToCenter;
}
