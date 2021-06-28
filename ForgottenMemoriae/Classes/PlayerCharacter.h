#ifndef __PLAYERCHARACTER_H__
#define __PLAYERCHARACTER_H__

#include "cocos2d.h"
#include "Definitions.h"

class PlayerCharacter
{
public:
	enum class State {
		IDLE, JUMPING, FALLING, RUNING, ATTACK1, ATTACK2, ATTACK3, DEATH
	};
	enum class Direction {
		LEFT, RIGHT
	};

	State state;
	Direction direction;

	PlayerCharacter();
	PlayerCharacter(cocos2d::Vec2 position);

	void setPosition(cocos2d::Vec2 position);

	void updateAnimation(State actionState, Direction actionDirection = Direction::RIGHT);
	void updateAction(float dt);

	cocos2d::Sprite* getSprite();
private:
	cocos2d::Sprite* characterSprite;
	cocos2d::Size characterSize;
	cocos2d::Vec2 characterVelocity;

	bool isFalling;
	bool grounded;
};

#endif // __PLAYERCHARACTER_H__
