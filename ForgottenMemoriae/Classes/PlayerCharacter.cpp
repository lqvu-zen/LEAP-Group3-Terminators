#include "PlayerCharacter.h"

USING_NS_CC;

PlayerCharacter::PlayerCharacter()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/Warrior/Warrior.plist", "sprites/Warrior/Warrior.png");
	characterSprite = Sprite::create("sprites/Warrior/Idle-0.png");

	characterSize = characterSprite->getContentSize();

	auto characterBody = PhysicsBody::createBox(characterSprite->getBoundingBox().size);
	//set collision bitmask
	characterBody->setDynamic(false);

	characterBody->setCollisionBitmask(HERO_COLLISION_BITMASK);
	characterBody->setContactTestBitmask(true);

	characterSprite->setPhysicsBody(characterBody);

	characterVelocity.setZero();

	updateAnimation(PlayerCharacter::State::FALLING);
}

PlayerCharacter::PlayerCharacter(cocos2d::Vec2 position)
{
	PlayerCharacter();
	setPosition(position);
}

void PlayerCharacter::setPosition(cocos2d::Vec2 position)
{
	characterSprite->setPosition(position);
}

void PlayerCharacter::updateAnimation(State actionState, Direction actionDirection, bool repeatForever)
{
	if (characterState != actionState) {

		const int maxWord = 50;

		int numberSprite;
		char nameSprite[maxWord] = { 0 };

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
			break;
		case PlayerCharacter::State::ATTACK3:
			break;
		case PlayerCharacter::State::DEATH:
			break;
		default:
			break;
		}

		Vector<SpriteFrame*> animFrames;

		char spriteFrameByName[maxWord] = { 0 };

		for (int index = 0; index < numberSprite; index++)
		{
			sprintf(spriteFrameByName, "%s-%d.png", nameSprite, index);

			auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
			animFrames.pushBack(frame);
		}

		Animation* animation = Animation::createWithSpriteFrames(animFrames, ANIMATION_DELAY);
		Animate* animate = Animate::create(animation);

		if (repeatForever) {
			characterSprite->getActionManager()->removeAllActions();

			characterSprite->runAction(RepeatForever::create(animate));
		}
		else {
			characterSprite->getActionManager()->removeAllActions();

			characterSprite->runAction(animate);
		}

		characterState = actionState;
	}

	if (actionDirection == Direction::LEFT) {
		characterSprite->setFlippedX(true);
	}
	else {
		characterSprite->setFlippedX(false);
	}
	characterDirection = actionDirection;
}

void PlayerCharacter::updateAction(float dt)
{
	CCLOG("Character velocity: x:%f - y:%f", characterVelocity.x, characterVelocity.y);

	updatePhysicsBody();

	//mimic gravity
	if (characterVelocity.y >= 0) {
		characterVelocity.y -= GRAVITY;
	}

	Direction direction = (characterVelocity.x == 0 ? characterDirection : (characterVelocity.x > 0 ? Direction::RIGHT : Direction::LEFT));

	if (characterVelocity.y < 0 && characterSprite->getPositionY() - characterSize.height / 2 + characterVelocity.y >= GROUND) {
		falling = true;
		grounded = false;
		jumping = false;
		updateAnimation(State::FALLING, direction);
	}
	else if (characterVelocity.y > 0) {
		grounded = false;
		falling = false;
		jumping = true;
		updateAnimation(State::JUMPING, direction, false);
	}
	else {
		grounded = true;
		falling = false;
		jumping = false;
		if (characterVelocity.x != 0)
			updateAnimation(State::RUNING, direction);
		else 
			updateAnimation(State::IDLE, direction);
	}

	auto velocityY = characterVelocity.y > 0 ? GRAVITY * 2.0f : -GRAVITY;

	/*if (characterSprite->getPositionY() - characterSize.height / 2 + velocityY >= GROUND) {
		characterSprite->setPositionY(characterSprite->getPositionY() + velocityY);
	}*/
		
	if (characterVelocity.x != 0) {
		characterSprite->setPositionX(characterSprite->getPositionX() + characterVelocity.x);
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

cocos2d::Sprite * PlayerCharacter::getSprite()
{
	return characterSprite;
}

void PlayerCharacter::setVelocity(cocos2d::Vec2 velocity)
{
	characterVelocity = velocity;
}

cocos2d::Vec2 PlayerCharacter::getVolocity()
{
	return characterVelocity;
}

void PlayerCharacter::updatePhysicsBody()
{
	characterSprite->getPhysicsBody()->setPositionOffset(
		Vec2(
			(characterSprite->getContentSize().width - characterSize.width) / 2,
			(characterSprite->getContentSize().height - characterSize.height) / 2
		)
	);
}
