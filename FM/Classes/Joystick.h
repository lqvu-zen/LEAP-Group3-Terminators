/*
 * Joystick.h
 *
 *  Created on: 2015-2-1
 *      Author: yong
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "cocos2d.h"
using namespace cocos2d;

enum class JoyStickEventType
{
	BEGAN,
	MOVED,
	ENDED
};


class JoystickEvent : public Ref {
private:
	JoystickEvent();

public:
	JoyStickEventType type;
	virtual ~JoystickEvent();
	virtual bool init(); CREATE_FUNC(JoystickEvent)
		;

public:
	static const std::string EVENT_JOYSTICK;
	double mAnagle;
	
	//	double mX;
	//	double mY;
};

class Joystick : public Layer {
private:
	Joystick();

protected:
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

public:
	double getDistanceFromCenter();
	virtual ~Joystick();
	virtual bool init(); CREATE_FUNC(Joystick)
		;
	
private:
	double distanceOfTouchPointToCenter = 0;
	Sprite* mJsBg;
	Sprite* mJsCenter;
	Vec2 mJsPos = Vec2(120, 100);
};

#endif /* JOYSTICK_H_ */