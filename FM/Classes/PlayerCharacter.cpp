#include "PlayerCharacter.h"

USING_NS_CC;

PlayerCharacter::PlayerCharacter()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/Warrior/Warrior.plist", "sprites/Warrior/Warrior.png");

	//set Stats
	characterStats.SetStats(100.0f, 100.0f, 20.0f, 10.0f);

	characterAnimate.clear();

	characterSprite = nullptr;

	init();

	//init inventory 
	characterInventory.init();

	//set inventory
	characterStats.GetSprite()->addChild(characterInventory.GetSprite(), 200);

	characterInventory.GetSprite()->setPosition(Vec2(
		characterStats.GetSpriteSize().width * SCALE_RATIO * 1.1f, -characterStats.GetSpriteSize().height * 1.5f
	));

	characterInventory.GetSprite()->setVisible(false);
}

PlayerCharacter::PlayerCharacter(cocos2d::Vec2 position)
{
	PlayerCharacter();
	setPosition(position);
}

void PlayerCharacter::init()
{
	if (characterSprite != nullptr) {
		characterSprite->removeAllChildren();
		characterSprite->removeFromParent();

		characterStats.GetSprite()->setParent(nullptr);
	}

	characterDirection = Direction::RIGHT;
	
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Warrior-Idle-0.png");

	characterSize = Size(frame->getOriginalSize().width * 0.5f, frame->getOriginalSize().height * 0.8f);

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
	
	skillSprite = nullptr;

	attackMode = 1;

	//set skill
	castingSkill = false;
	attacking = false;
	characterSkill = new Skill();

	characterSkillCountdown[Skill::SkillType::Normal] = 0.0f;
	characterSkillCountdown[Skill::SkillType::Special] = 0.0f;
	characterSkillCountdown[Skill::SkillType::Ultimate] = 0.0f;

	//--
	died = false;

	
}

void PlayerCharacter::setPosition(cocos2d::Vec2 position)
{
	characterSprite->setPosition(position);
	characterSpriteAnimation->setPosition(Vec2::ZERO);
}

void PlayerCharacter::updateAnimation(State actionState, Direction actionDirection, bool repeatForever)
{
	if (characterState != actionState && attacking != true) {

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
		case PlayerCharacter::State::TAKE_HIT:
			numberSprite = 3;
			sprintf(nameSprite, "Take hit");
			break;
		default:
			break;
		}

		if (characterAnimate[nameSprite] == nullptr) {
			Vector<SpriteFrame*> animFrames;

			char spriteFrameByName[maxWord] = { 0 };

			for (int index = 0; index < numberSprite; index++)
			{
				sprintf(spriteFrameByName, "%s-%s-%d.png", nameCharacter, nameSprite, index);

				auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
				animFrames.pushBack(frame);
			}

			Animation* animation = Animation::createWithSpriteFrames(animFrames);

			if (repeatForever == true || actionState == State::DEATH) {
				animation->setDelayPerUnit(ANIMATION_DELAY);
			}
			else {
				animation->setDelayPerUnit(FAST_ANIMATION_DELAY);
			}
			//Animation* animation = Animation::createWithSpriteFrames(animFrames, repeatForever == true ? ANIMATION_DELAY : FAST_ANIMATION_DELAY);
			//Animate* animate = Animate::create(animation);

			characterAnimate[nameSprite] = Animate::create(animation);
			characterAnimate[nameSprite]->retain();
		}

		if (repeatForever) {
			characterSpriteAnimation->stopAllActions();

			characterSpriteAnimation->runAction(RepeatForever::create(characterAnimate[nameSprite]));

			characterState = actionState;
		}
		else {
			characterSpriteAnimation->stopAllActions();

			auto callbackAction = CallFunc::create(
				CC_CALLBACK_0(PlayerCharacter::reupdateAnimation, this)
			);

			characterSpriteAnimation->runAction(Sequence::create(characterAnimate[nameSprite], callbackAction, nullptr));

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
	//CCLOG("PhysicBody velocity: x:%f - y:%f", characterPhysicsBody->getVelocity().x, characterPhysicsBody->getVelocity().y);
	if (!died) {
		//update stats
		characterStats.UpdateStatsBar();

		//update countdown
		characterSkillCountdown[Skill::SkillType::Normal] -= (characterSkillCountdown[Skill::SkillType::Normal] > 0.0f ? dt : 0.0f);
		characterSkillCountdown[Skill::SkillType::Special] -= (characterSkillCountdown[Skill::SkillType::Special] > 0.0f ? dt : 0.0f);
		characterSkillCountdown[Skill::SkillType::Ultimate] -= (characterSkillCountdown[Skill::SkillType::Ultimate] > 0.0f ? dt : 0.0f);

		Direction direction = (characterVelocity.x == 0 ? characterDirection : (characterVelocity.x > 0 ? Direction::RIGHT : Direction::LEFT));

		if (characterStats.HP <= 0.0f) {
			died = true;
			updateAnimation(State::DEATH, characterDirection, false);
			return;
		}

		//update position
		if (characterPhysicsBody->getVelocity().y > PADDING_VELOCITY) {
			setJumping();
		}
		else if (characterPhysicsBody->getVelocity().y < -PADDING_VELOCITY) {
			setFalling();
		}
		else{
			if (isFalling() || isGrounded()) {
				//reset after fall, i want to reset when player contact with ground or wall
				resetJump();
			}
			setGrounded();
		}

		if (characterVelocity.y > PADDING_VELOCITY && characterStats.canJump() && characterPhysicsBody->getVelocity().y <= PLAYER_JUMP_VELOCITY * 0.5f) {
			characterStats.jump++;
			CCLOG("Jump from: %f", characterPhysicsBody->getVelocity().y);
			characterPhysicsBody->setVelocity(
				Vec2(
					characterPhysicsBody->getVelocity().x, characterVelocity.y
				)
			);
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
					0.0f, characterPhysicsBody->getVelocity().y
				)
			);
		}

		characterVelocity = Vec2::ZERO;

		//update animation
		if (falling) {
			//CCLOG("FALLING");
			updateAnimation(State::FALLING, direction);
		}

		if (jumping) {
			//CCLOG("JUMPING");
			updateAnimation(State::JUMPING, direction, false);
		}

		if (grounded) {
			if (characterPhysicsBody->getVelocity().x > PADDING_VELOCITY || characterPhysicsBody->getVelocity().x < -PADDING_VELOCITY) {
				//CCLOG("RUNING");
				updateAnimation(State::RUNING, direction);
			}
			else {
				//CCLOG("IDLE");
				updateAnimation(State::IDLE, direction);
			}
		}
	}
}

void PlayerCharacter::reupdateAnimation()
{
	characterState = characterStateOnce;

	if (characterStateOnce != State::DEATH) {
		if (attacking == true || castingSkill == true) {
			if (attackSprite->getPhysicsBody() != nullptr && int(attackSprite->getPhysicsBody()->getShapes().size() > 0))
				attackSprite->getPhysicsBody()->removeAllShapes();

			attackMode++;

			if (attacking == true || castingSkill == true) {
				castingSkill = false;
				attacking = false;
			}
		}
		
		updateAnimation(characterState, characterDirection);
	}
	else {
		//Death update
		//characterSprite->removeAllChildren();
		//characterSprite->removeFromParent();
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

void PlayerCharacter::resetJump()
{
	if (characterStats.jump > 0) characterStats.jump = 0;
}

void PlayerCharacter::attack(int mode)
{
	//CCLOG("ATTACK");
	if (attacking != true) {
		if (mode > 0) {
			attackMode = mode;

			switch (attackMode)
			{
			case 1:
				attackSkill = Skill::SkillType::Normal;
				break;
			case 2:
				attackSkill = Skill::SkillType::Special;
				break;
			case 3:
				attackSkill = Skill::SkillType::Ultimate;
				break;
			default:
				break;
			}

			if (characterSkill->SkillCost(attackSkill).MP <= characterStats.MP && characterSkillCountdown[attackSkill] <= 0.0f) {
				characterStats.MP -= characterSkill->SkillCost(attackSkill).MP;
				characterSkillCountdown[attackSkill] = characterSkill->SkillCost(attackSkill).countdown;
			}
			else {
				return;
			}
		}
		else {
			attackMode = (attackMode - 1) % 3 + 1;
		}

		//update animation
		if (attackMode == 1) {
			attackSize = Size(characterSize.width * 2.0f, characterSize.height);
			updateAnimation(State::ATTACK1, characterDirection, false);
		}
		else if (attackMode == 2) {
			attackSize = Size(characterSize.width * 2.5f, characterSize.height);
			updateAnimation(State::ATTACK2, characterDirection, false);
		}
		else if (attackMode == 3) {
			attackSize = Size(characterSize.width * 3.0f, characterSize.height * 2.0f);
			updateAnimation(State::ATTACK3, characterDirection, false);
		}

		auto attackPos = Vec2((attackSize.width - characterSize.width) / 2, (attackSize.height - characterSize.height) / 2);	

		//create physic for attack
		 
		auto attackBody = PhysicsBody::createBox(attackSize);

		attackBody->setDynamic(false);
		attackBody->setRotationEnable(false);
		attackBody->setGravityEnable(false);
		attackBody->setMass(0.0f);

		attackBody->setCategoryBitmask(PLAYER_ATTACK_CATEGORY_BITMASK);
		attackBody->setCollisionBitmask(PLAYER_ATTACK_COLLISION_BITMASK);
		attackBody->setContactTestBitmask(ALLSET_BITMASK);

		//attackSprite->setAnchorPoint(Vec2::ZERO);
		if (characterDirection == Direction::RIGHT) {
			attackSprite->setPosition(Vec2(attackPos.x, attackPos.y));
		}
		else {
			attackSprite->setPosition(Vec2(-attackPos.x, attackPos.y));
		}

		attackSprite->setPhysicsBody(attackBody);
		
		attacking = true;

		if (mode != 0) {
			castingSkill = true;

			//skillSprite->setAnchorPoint(Vec2::ZERO);
			if (skillSprite == nullptr) {
				skillSprite = Sprite::create();
				characterSprite->getParent()->addChild(skillSprite, 1);
			}

			if (characterDirection == Direction::RIGHT) {
				skillSprite->setPosition(characterSprite->getPositionX() + attackSprite->getPosition().x + attackSize.width / 2, 
					characterSprite->getPositionY() + attackSprite->getPosition().y);
			}
			else {
				skillSprite->setPosition(characterSprite->getPositionX() + attackSprite->getPosition().x - attackSize.width / 2,
					characterSprite->getPositionY() + attackSprite->getPosition().y);
			}

			skillSprite->addChild(characterSkill->GetSprite());
			characterSkill->CastSkill(attackSkill, characterDirection);
		}
		
	}
	
}

void PlayerCharacter::takeHit(float dame)
{
	updateAnimation(State::TAKE_HIT, characterDirection, false);
	characterStats.HP -= dame;
}

void PlayerCharacter::revive()
{
	died = false;
	characterStats.ResetCharacterStats();

	updateAnimation(State::IDLE, characterDirection);
}

void PlayerCharacter::openInventory()
{
	characterInventory.updateInventory();
	characterInventory.GetSprite()->setVisible(true);
}

void PlayerCharacter::closeInventory()
{
	characterInventory.GetSprite()->setVisible(false);
}

void PlayerCharacter::colectItem(Item * item)
{
	characterInventory.addItem(item);
}

void PlayerCharacter::addGold(int num) {
	characterInventory.addGold(num);
}

cocos2d::Sprite * PlayerCharacter::getSprite()
{
	return characterSprite;
}

Stats PlayerCharacter::getStats()
{
	return characterStats;
}

Inventory PlayerCharacter::getInventory()
{
	return characterInventory;
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