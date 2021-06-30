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

	State characterState;
	Direction characterDirection;

	PlayerCharacter();
	PlayerCharacter(cocos2d::Vec2 position);

	void setPosition(cocos2d::Vec2 position);

	void updateAnimation(State actionState, Direction actionDirection = Direction::RIGHT, bool repeatForever = true);
	void updateAction(float dt);

	bool isFalling();
	bool isGrounded();
	bool isJumping();

	void setFalling();
	void setGrounded();
	void setJumping();

	cocos2d::Sprite* getSprite();

	void setVelocity(cocos2d::Vec2 velocity);
	cocos2d::Vec2 getVolocity();
	cocos2d::Vec2 getRealtimeVolocity();
private:
	cocos2d::Sprite* characterSprite;
	cocos2d::Sprite* characterSpriteAnimation;
	cocos2d::PhysicsBody* characterPhysicsBody;

	cocos2d::Size characterSize;
	cocos2d::Vec2 characterVelocity;

	bool falling;
	bool grounded;
	bool jumping;

	void updatePhysicsBody();
};

#endif // __PLAYERCHARACTER_H__
