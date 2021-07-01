#include "PlayerCharacter.h"

USING_NS_CC;

PlayerCharacter::PlayerCharacter()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/Warrior/Warrior.plist", "sprites/Warrior/Warrior.png");
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Warrior-Idle-0.png");
	
	characterSize = frame->getOriginalSize();

	characterSprite = Sprite::create();
	characterSpriteAnimation = Sprite::createWithSpriteFrame(frame);

	characterPhysicsBody = PhysicsBody::createBox(characterSize);
	//set collision bitmask
	characterPhysicsBody->setDynamic(true);
	characterPhysicsBody->setRotationEnable(false);

	characterPhysicsBody->setCollisionBitmask(HERO_COLLISION_BITMASK);
	characterPhysicsBody->setContactTestBitmask(true);

	characterSprite->setPhysicsBody(characterPhysicsBody);

	characterVelocity.setZero();

	setFalling();

	characterSprite->addChild(characterSpriteAnimation);
}

PlayerCharacter::PlayerCharacter(cocos2d::Vec2 position)
{
	PlayerCharacter();
	setPosition(position);
}

void PlayerCharacter::setPosition(cocos2d::Vec2 position)
{
	characterSprite->setPosition(position);
	characterSpriteAnimation->setPosition(Vec2::ZERO);
}

void PlayerCharacter::updateAnimation(State actionState, Direction actionDirection, bool repeatForever)
{
	if (characterState != actionState) {

		const int maxWord = 50;

		int numberSprite;
		char nameSprite[maxWord] = { 0 };
		char nameCharacter[maxWord] = { 0 };

		sprintf(nameCharacter, "Warrior");

		switch (actionState)
		{
		case PlayerCharacter::State::IDLE:
			numberSprite = 10;
			sprintf(nameSprite, "Idle");
			break;
		case PlayerCharacter::State::JUMPING:
			numberSprite = 3;
			sprintf(nameSprite, "Jump");
			break;
		case PlayerCharacter::State::FALLING:
			numberSprite = 3;
			sprintf(nameSprite, "Fall");
			break;
		case PlayerCharacter::State::RUNING:
			numberSprite = 8;
			sprintf(nameSprite, "Run");
			break;
		case PlayerCharacter::State::ATTACK1:
			numberSprite = 7;
			sprintf(nameSprite, "Attack1");
			break;
		case PlayerCharacter::State::ATTACK2:
			numberSprite = 7;
			sprintf(nameSprite, "Attack2");
			break;
		case PlayerCharacter::State::ATTACK3:
			numberSprite = 8;
			sprintf(nameSprite, "Attack3");
			break;
		case PlayerCharacter::State::DEATH:
			numberSprite = 7;
			sprintf(nameSprite, "Death");
			break;
		default:
			break;
		}

		Vector<SpriteFrame*> animFrames;

		char spriteFrameByName[maxWord] = { 0 };

		for (int index = 0; index < numberSprite; index++)
		{
			sprintf(spriteFrameByName, "%s-%s-%d.png", nameCharacter,nameSprite, index);

			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			animFrames.pushBack(frame);
		}

		Animation* animation = Animation::createWithSpriteFrames(animFrames, ANIMATION_DELAY);
		Animate* animate = Animate::create(animation);

		if (repeatForever) {
			characterSpriteAnimation->getActionManager()->removeAllActions();

			characterSpriteAnimation->runAction(RepeatForever::create(animate));
		}
		else {
			characterSpriteAnimation->getActionManager()->removeAllActions();

			characterSpriteAnimation->runAction(animate);
		}

		characterState = actionState;
	}

	if (actionDirection == Direction::LEFT) {
		characterSpriteAnimation->setFlippedX(true);
	}
	else {
		characterSpriteAnimation->setFlippedX(false);
	}
	characterDirection = actionDirection;
}

void PlayerCharacter::updateAction(float dt)
{
	//CCLOG("Character velocity: x:%f - y:%f", characterVelocity.x, characterVelocity.y);
	CCLOG("PhysicBody velocity: x:%f - y:%f", characterPhysicsBody->getVelocity().x, characterPhysicsBody->getVelocity().y);

	Direction direction = (characterVelocity.x == 0 ? characterDirection : (characterVelocity.x > 0 ? Direction::RIGHT : Direction::LEFT));

	//update position
	if (characterPhysicsBody->getVelocity().y > PADDING_VELOCITY){
		setJumping();
	}
	else if (characterPhysicsBody->getVelocity().y < - PADDING_VELOCITY){
		setFalling();
	}
	else {
		setGrounded();
	}

	if (characterVelocity.y > BASE_VELOCITY) {
		characterPhysicsBody->setVelocity(
			Vec2(
				characterPhysicsBody->getVelocity().x, characterVelocity.y
			)
		);
		characterVelocity.y = BASE_VELOCITY;
	}
		
	if (characterVelocity.x != 0.0f) {
		characterPhysicsBody->setVelocity(
			Vec2(
				characterVelocity.x, characterPhysicsBody->getVelocity().y
			)
		);
	}
	else {
		characterPhysicsBody->setVelocity(
			Vec2(
				0.0f , characterPhysicsBody->getVelocity().y
			)
		);
	}

	//update animation
	if (falling) {
		CCLOG("FALLING");
		updateAnimation(State::FALLING, direction);
	}

	if (jumping) {
		CCLOG("JUMPING");
		updateAnimation(State::JUMPING, direction, false);
	}

	if (grounded) {
		if (characterPhysicsBody->getVelocity().x > PADDING_VELOCITY || characterPhysicsBody->getVelocity().x < - PADDING_VELOCITY) {
			CCLOG("RUNING");
			updateAnimation(State::RUNING, direction);
		}
		else {
			CCLOG("IDLE");
			updateAnimation(State::IDLE, direction);
		}	
	}
}

bool PlayerCharacter::isFalling()
{
	return falling;
}

bool PlayerCharacter::isGrounded()
{
	return grounded;
}

bool PlayerCharacter::isJumping()
{
	return jumping;
}

void PlayerCharacter::setFalling()
{
	falling = true;
	jumping = false;
	grounded = false;
}

void PlayerCharacter::setGrounded()
{
	falling = false;
	jumping = false;
	grounded = true;
}

void PlayerCharacter::setJumping()
{
	falling = false;
	jumping = true;
	grounded = false;
}

cocos2d::Sprite * PlayerCharacter::getSprite()
{
	return characterSprite;
}

cocos2d::PhysicsBody* PlayerCharacter::getPhysicsBody()
{
	return characterPhysicsBody;
}

void PlayerCharacter::setVelocity(cocos2d::Vec2 velocity)
{
	characterVelocity = velocity;
}

cocos2d::Vec2 PlayerCharacter::getVolocity()
{
	return characterVelocity;
}

cocos2d::Vec2 PlayerCharacter::getRealtimeVolocity()
{
	return characterPhysicsBody->getVelocity();
}