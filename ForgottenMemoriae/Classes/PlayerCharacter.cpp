#include "PlayerCharacter.h"

USING_NS_CC;

PlayerCharacter::PlayerCharacter()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/Warrior/Warrior.plist", "sprites/Warrior/Warrior.png");
	characterSprite = Sprite::create("sprites/Warrior/Idle-0.png");

	characterSize = characterSprite->getContentSize();

	auto characterBody = PhysicsBody::createBox(characterSprite->getBoundingBox().size);
	//set collision bitmask
	characterBody->setDynamic(true);

	characterBody->setCollisionBitmask(HERO_COLLISION_BITMASK);
	characterBody->setContactTestBitmask(true);

	characterSprite->setPhysicsBody(characterBody);

	characterVelocity.setZero();
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

void PlayerCharacter::updateAnimation(State actionState, Direction actionDirection)
{
	if (state != actionState) {

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
			isFalling = true;
			break;
		case PlayerCharacter::State::RUNING:
			numberSprite = 8;
			sprintf(nameSprite, "Run");
			break;
		case PlayerCharacter::State::ATTACK1:
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

		characterSprite->getActionManager()->removeAllActions();

		characterSprite->runAction(RepeatForever::create(animate));

		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);

		auto characterBody = characterSprite->getPhysicsBody();

		characterBody->setPositionOffset(
			Vec2(
				0 + MAX((frame->getOriginalSize().width - characterSprite->getContentSize().width) / 2, 0),
				0 + MAX((frame->getOriginalSize().height - characterSprite->getContentSize().height) / 2, 0)
			)
		);

		state = actionState;

		if (actionDirection == Direction::LEFT) {
			characterSprite->setFlippedX(true);
		}
		else {
			characterSprite->setFlippedX(false);
		}
	}
}

void PlayerCharacter::updateAction(float dt)
{
	CCLOG("Character possition: x:%f - y:%f", characterSprite->getPositionX(), characterSprite->getPositionY());

	if (characterSprite->getPositionY() - characterSize.height / 2 - 1.0f >= 3) {
		isFalling = true;
		grounded = false;
	}
	else {
		grounded = true;
		isFalling = false;
	}

	if (isFalling && characterSprite->getPositionY() - characterSize.height / 2 - 1.0f >= 3) {
		characterSprite->setPositionY(characterSprite->getPositionY() - 1.0f);
	}
		
	if (state == State::RUNING) {
		characterSprite->setPositionX(characterSprite->getPositionX() + 1.0f);
	}
		
}

cocos2d::Sprite * PlayerCharacter::getSprite()
{
	return characterSprite;
}
