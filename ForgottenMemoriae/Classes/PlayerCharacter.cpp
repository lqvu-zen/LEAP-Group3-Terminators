#include "PlayerCharacter.h"

USING_NS_CC;

PlayerCharacter::PlayerCharacter()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/Warrior/Warrior.plist", "sprites/Warrior/Warrior.png");
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Warrior-Idle-0.png");
	
	characterSize = frame->getOriginalSize();

	//create sprites
	characterSprite = Sprite::create();
	characterSpriteAnimation = Sprite::createWithSpriteFrame(frame);
	attackSprite = Sprite::create();

	characterPhysicsBody = PhysicsBody::createBox(characterSize);
	//set collision bitmask
	characterPhysicsBody->setDynamic(true);
	characterPhysicsBody->setRotationEnable(false);

	characterPhysicsBody->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);
	characterPhysicsBody->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
	characterPhysicsBody->setContactTestBitmask(ALLSET_BITMASK);

	characterSprite->setPhysicsBody(characterPhysicsBody);

	characterVelocity.setZero();

	setFalling();

	characterSprite->addChild(characterSpriteAnimation);
	characterSprite->addChild(attackSprite);

	attackMode = 1;
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
	attackSprite->setPosition(Vec2::ZERO);
	
}

void PlayerCharacter::updateAnimation(State actionState, Direction actionDirection, bool repeatForever)
{
	if (characterState != actionState) {

		if (attackSprite->getPhysicsBody() != nullptr)
			attackSprite->getPhysicsBody()->removeFromWorld();

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
			characterSpriteAnimation->stopAllActions();

			characterSpriteAnimation->runAction(RepeatForever::create(animate));

			characterState = actionState;
		}
		else {
			characterSpriteAnimation->stopAllActions();

			auto callbackAction = CallFunc::create(
				CC_CALLBACK_0(PlayerCharacter::reupdateAnimation, this)
			);

			characterSpriteAnimation->runAction(Sequence::create(animate, callbackAction, nullptr));

			characterStateOnce = actionState;
		}
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

void PlayerCharacter::reupdateAnimation()
{
	characterState = characterStateOnce;

	if (characterStateOnce != State::DEATH) {
		updateAnimation(characterState, characterDirection);
		attackMode++;
	}
	else {
		//Death update
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

void PlayerCharacter::attack(int mode)
{
	CCLOG("ATTACK");
	

	if (mode > 0) {
		attackMode = mode;
	}
	else {
		attackMode = (attackMode - 1) % 3 + 1;
	}

	//update animation
	if (attackMode == 1) {
		attackSize = Size(characterSize.width * 1.5f, characterSize.height);
		updateAnimation(State::ATTACK1, characterDirection, false);
	} else if (attackMode == 2) {
		attackSize = Size(characterSize.width * 2.0f, characterSize.height);
		updateAnimation(State::ATTACK2, characterDirection, false);
	} else if (attackMode == 3) {
		attackSize = Size(characterSize.width * 2.0f, characterSize.height * 2.0f);
		updateAnimation(State::ATTACK3, characterDirection, false);
	}	

	//create physic for attack
	if (mode == 0) {

		auto attackBody = PhysicsBody::createBox(attackSize);

		attackBody->setDynamic(false);
		attackBody->setRotationEnable(false);
		attackBody->setGravityEnable(false);		
		attackBody->setMass(0.0f);		

		attackBody->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);
		attackBody->setCollisionBitmask(PLAYER_ATTACK_COLLISION_BITMASK);
		attackBody->setContactTestBitmask(ALLSET_BITMASK);

		attackSprite->setPhysicsBody(attackBody);
	}
	else {
		
	}
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

cocos2d::Vec2 PlayerCharacter::getRealtimeVolocity()
{
	return characterPhysicsBody->getVelocity();
}