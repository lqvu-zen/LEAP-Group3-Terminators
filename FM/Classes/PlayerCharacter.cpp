#include "PlayerCharacter.h"
#include "GameManager.h"
#include "Popup.h"

USING_NS_CC;

PlayerCharacter::PlayerCharacter(int characterType)
{
	characterTYPE = CharacterType::Player;

	getValue(characterType);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
		characterValue["SPRITES"]["PLIST"].GetString(), 
		characterValue["SPRITES"]["PNG"].GetString()
	);

	//set Stats
	characterStats.SetStats(
		characterValue["STATS"]["HP"].GetFloat(), 
		characterValue["STATS"]["MP"].GetFloat(), 
		characterValue["STATS"]["ATK"].GetFloat(), 
		characterValue["STATS"]["DEF"].GetFloat()
	);

	characterAnimate.clear();

	characterSprite = nullptr;

	init(characterType);

	//init inventory 
	characterInventory.init();

	//set inventory
	characterStats.GetSprite()->addChild(characterInventory.GetSprite(), 200);

	characterInventory.GetSprite()->setPosition(Vec2(
		characterStats.GetSpriteSize().width * SCALE_RATIO * 1.1f, -characterStats.GetSpriteSize().height * 1.5f
	));

	characterInventory.GetSprite()->setVisible(false);

	characterColor = cocos2d::Color3B::WHITE;
}

void PlayerCharacter::init(int characterType)
{
	
	if (characterSprite != nullptr) {
		characterSprite->removeAllChildren();
		characterSprite->removeFromParent();

		characterStats.GetSprite()->setParent(nullptr);
	}

	characterDirection = Direction::RIGHT;

	characterSize = Size(
		characterValue["SPRITES"]["SIZE_X"].GetFloat(), 
		characterValue["SPRITES"]["SIZE_Y"].GetFloat()
	);

	//create sprites
	characterSprite = Sprite::create();
	characterSpriteAnimation = Sprite::create();
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
	characterSkill = new Skill(characterValue["SKILL_TYPE"].GetInt());

	characterSkillCountdown[Skill::SkillType::Normal] = 0.0f;
	characterSkillCountdown[Skill::SkillType::Special] = 0.0f;
	characterSkillCountdown[Skill::SkillType::Ultimate] = 0.0f;

	//--
	takingHit = false;
	died = false;

	//set scale
	characterSprite->setScale(characterValue["SPRITES"]["SCALE"].GetFloat());
}

void PlayerCharacter::setPosition(cocos2d::Vec2 position)
{
	characterSprite->setPosition(position);
	characterSpriteAnimation->setPosition(Vec2::ZERO);
}

void PlayerCharacter::updateAnimation(State actionState, Direction actionDirection, bool repeatForever)
{
	if ((characterState != actionState && attacking != true && takingHit != true) || actionState == State::DEATH){

		const int maxWord = 50;

		int numberSprite;
		char nameSprite[maxWord] = { 0 };
		char nameCharacter[maxWord] = { 0 };

		sprintf(nameCharacter, "%s", characterValue["NAME"].GetString());

		characterSpriteAnimation->setColor(characterColor);

		switch (actionState)
		{
		case PlayerCharacter::State::IDLE:
			numberSprite = characterValue["SPRITES"]["COUNT_IDLE"].GetInt();
			sprintf(nameSprite, "Idle");
			break;
		case PlayerCharacter::State::JUMPING:
			numberSprite = characterValue["SPRITES"]["COUNT_JUMP"].GetInt();
			sprintf(nameSprite, "Jump");
			break;
		case PlayerCharacter::State::FALLING:
			numberSprite = characterValue["SPRITES"]["COUNT_FALL"].GetInt();
			sprintf(nameSprite, "Fall");
			break;
		case PlayerCharacter::State::RUNING:
			numberSprite = characterValue["SPRITES"]["COUNT_RUN"].GetInt();
			sprintf(nameSprite, "Run");
			break;
		case PlayerCharacter::State::ATTACK1:
			numberSprite = characterValue["SPRITES"]["COUNT_ATTACK1"].GetInt();
			sprintf(nameSprite, "Attack1");
			break;
		case PlayerCharacter::State::ATTACK2:
			numberSprite = characterValue["SPRITES"]["COUNT_ATTACK2"].GetInt();
			sprintf(nameSprite, "Attack2");
			break;
		case PlayerCharacter::State::ATTACK3:
			numberSprite = characterValue["SPRITES"]["COUNT_ATTACK3"].GetInt();
			sprintf(nameSprite, "Attack3");
			break;
		case PlayerCharacter::State::TAKE_HIT:
			numberSprite = characterValue["SPRITES"]["COUNT_TAKEHIT"].GetInt();
			sprintf(nameSprite, "Take hit");
			characterSpriteAnimation->setColor(cocos2d::Color3B::RED);
			break;
		case PlayerCharacter::State::DEATH:
			numberSprite = characterValue["SPRITES"]["COUNT_DEATH"].GetInt();
			sprintf(nameSprite, "Death");
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

		//play audio
		AudioManager::playPlayerAudio(actionState);

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
			characterState = actionState;
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
	//CCLOG("Character HP: %f", characterStats.HP);
	//CCLOG("PhysicBody velocity: x:%f - y:%f", characterPhysicsBody->getVelocity().x, characterPhysicsBody->getVelocity().y);
	if (characterStats.HP >= 0.0f) {
		//update stats
		characterStats.UpdateStatsBar();

		//update countdown
		characterSkillCountdown[Skill::SkillType::Normal] -= (characterSkillCountdown[Skill::SkillType::Normal] > 0.0f ? dt : 0.0f);
		characterSkillCountdown[Skill::SkillType::Special] -= (characterSkillCountdown[Skill::SkillType::Special] > 0.0f ? dt : 0.0f);
		characterSkillCountdown[Skill::SkillType::Ultimate] -= (characterSkillCountdown[Skill::SkillType::Ultimate] > 0.0f ? dt : 0.0f);

		Direction direction = (characterVelocity.x == 0 ? characterDirection : (characterVelocity.x > 0 ? Direction::RIGHT : Direction::LEFT));

		if (characterStats.HP <= 0.0f) {
			//died = true;
			characterStats.HP -= 1.0f;
			attacking = false;
			takingHit = false;

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
		//CCLOG("jump = %d, vec = %f", characterStats.canJump(), characterVelocity.y);
		if (characterVelocity.y > PADDING_VELOCITY && characterStats.canJump() && characterPhysicsBody->getVelocity().y <= PLAYER_JUMP_VELOCITY * 0.5f) {
			characterStats.jump++;
			CCLOG("Jump from: %f, jump = %d", characterPhysicsBody->getVelocity().y, characterStats.jump);
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

		//Karma talk
		if (countDT < 0) countDT *= -1;
		countDT++;
		countDT %= (1200 - characterStats.Karma * 2);

		//CCLOG("DT: %d", countDT);

		if (countDT == 0) {
			if (characterStats.Karma > 90) {
				AudioManager::playKarmaAudio(AudioManager::KarmaEmotion::Bloodthirsty);
			}
			else if (characterStats.Karma > 50) {
				AudioManager::playKarmaAudio(AudioManager::KarmaEmotion::Uncontrolled);
			}
			else {
				AudioManager::playKarmaAudio(AudioManager::KarmaEmotion::Normal);
			}
		}
	}
	else {
		if (characterState != State::DEATH) {
			//died = true;
			characterStats.HP -= 1.0f;
			attacking = false;
			takingHit = false;

			updateAnimation(State::DEATH, characterDirection, false);
			return;
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

		if (takingHit == true) {
			takingHit = false;
			characterSpriteAnimation->setColor(characterColor);
		}
		
		updateAnimation(characterState, characterDirection);
	}
	else {
		//Death update
		//characterSprite->removeAllChildren();
		//characterSprite->removeFromParent();
		died = true;
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

bool PlayerCharacter::isDead()
{
	return died;
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

void PlayerCharacter::getDarker()
{
#ifdef ENABLE_KARMA
	characterStats.Karma = min(characterStats.Karma + 5, 100);
#endif // ENABLE_KARMA

	if (characterStats.Karma >= 90) {
		characterColor = cocos2d::Color3B::BLACK;
	}
	else if (characterStats.Karma >= 50) {
		characterColor = cocos2d::Color3B::GRAY;
	}
	else {
		characterColor = cocos2d::Color3B::WHITE;
	}

	characterSpriteAnimation->setColor(characterColor);
}

void PlayerCharacter::resetJump()
{
	//save position when grounded
	savePosition();

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

#ifdef ENABLE_KARMA
		if (countDT % 5 == 0) {
			AudioManager::playKarmaAudio(AudioManager::KarmaEmotion::Fight);
		}
#endif // ENABLE_KARMA

		//update animation
		if (attackMode == 1) {
			attackSize = Size(
				characterValue["NORMAL_ATTACK"]["SIZE_1_X"].GetFloat(), 
				characterValue["NORMAL_ATTACK"]["SIZE_1_Y"].GetFloat()
			);
			updateAnimation(State::ATTACK1, characterDirection, false);
		}
		else if (attackMode == 2) {
			attackSize = Size(
				characterValue["NORMAL_ATTACK"]["SIZE_2_X"].GetFloat(),
				characterValue["NORMAL_ATTACK"]["SIZE_2_Y"].GetFloat()
			);
			updateAnimation(State::ATTACK2, characterDirection, false);
		}
		else if (attackMode == 3) {
			attackSize = Size(
				characterValue["NORMAL_ATTACK"]["SIZE_3_X"].GetFloat(),
				characterValue["NORMAL_ATTACK"]["SIZE_3_Y"].GetFloat()
			);
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
		else {
			if (characterValue["NORMAL_ATTACK"]["SUB_ATTACK"]["ENABLE"].GetInt() == 1) {
				auto subSprite = Sprite::create(characterValue["NORMAL_ATTACK"]["SUB_ATTACK"]["PNG"].GetString());

				auto subSize = Size(
					/*characterValue["NORMAL_ATTACK"]["SUB_ATTACK"]["SIZE_X"].GetFloat(),
					characterValue["NORMAL_ATTACK"]["SUB_ATTACK"]["SIZE_Y"].GetFloat()*/
					subSprite->getContentSize()
				);

				auto subBody = PhysicsBody::createBox(subSize);

				subBody->setDynamic(false);
				subBody->setRotationEnable(false);
				subBody->setGravityEnable(false);
				subBody->setMass(0.0f);

				subBody->setCategoryBitmask(PLAYER_ATTACK_CATEGORY_BITMASK);
				subBody->setCollisionBitmask(PLAYER_ATTACK_COLLISION_BITMASK);
				subBody->setContactTestBitmask(ALLSET_BITMASK);

				subSprite->setPhysicsBody(subBody);

				if (characterValue["NORMAL_ATTACK"]["SUB_ATTACK"]["MOVEMENT"].GetInt() == 1) {
					subBody->setVelocity(
						Vec2((characterDirection == Direction::RIGHT ? PLAYER_MAX_VELOCITY : -PLAYER_MAX_VELOCITY), 0.0f)
					);
				}

				if (characterDirection == Direction::LEFT) {
					subSprite->setFlippedX(true);
				}
				else {
					subSprite->setFlippedX(false);
				}

				subSprite->setPosition(characterSprite->getPosition());

				auto wait = DelayTime::create(characterValue["NORMAL_ATTACK"]["SUB_ATTACK"]["TIME"].GetFloat());
				auto removeSeft = RemoveSelf::create();

				subSprite->runAction(Sequence::create(wait, removeSeft, NULL));

				characterSprite->getParent()->addChild(subSprite, 2);
			}
		}
		
	}
	
}

void PlayerCharacter::takeHit(float dame)
{
	updateAnimation(State::TAKE_HIT, characterDirection, false);

	takingHit = true;

	characterStats.HP = max(characterStats.HP - dame, 0.0f);
}

void PlayerCharacter::revive()
{
	characterStats.ResetCharacterStats();

	castingSkill = false;
	attacking = false;

	takingHit = false;
	died = false;

	updateAnimation(State::IDLE, characterDirection);

	AudioManager::playKarmaAudio(AudioManager::KarmaEmotion::Loser, 2);
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

void PlayerCharacter::colectItem(Item * item, int mount)
{
	auto colectSprite = item->getColectSprite(mount);
	colectSprite->setPosition(Vec2(0.0f, characterSize.height / 2 + 5.0f));

	//auto wait = DelayTime::create(COLECT_DELAY);

	auto moveBy = MoveBy::create(COLECT_DELAY, Vec2(0.0f, 10.0f));
	auto removeSeft = RemoveSelf::create();

	auto notification = CallFunc::create([]() {
		
	});

	colectSprite->runAction(Sequence::create(moveBy, removeSeft, notification, NULL));

	characterSprite->addChild(colectSprite);

	AudioManager::playRandomAudio(AudioManager::RandomAction::Collect);

	characterInventory.addItem(item, mount);

	if (mount > 0 && item->getType() >= Item::ItemType::D_BOOTS) {
		characterStats.BuffStats(item->getStats());
		if (item->getType() == Item::ItemType::D_BOOTS) {
			UICustom::Popup* popup = UICustom::Popup::createAsMessage("Upgrade!!!", "Now you can double jump.\n Let try it.\n (Hold jump or click twice)");
			//characterSprite->getParent()->addChild(popup);
			Director::getInstance()->getRunningScene()->addChild(popup, 2);
		}
	}
}

void PlayerCharacter::addGold(int num) {
	characterInventory.addGold(num);
}

bool PlayerCharacter::exceptGold(int num) {
	return characterInventory.exceptGold(num);
}

void PlayerCharacter::useItem(Item::ItemType itemType)
{
	auto item = characterInventory.getItem(itemType);

	if (item != nullptr) {
		characterStats.BuffStats(item->getStats());
	}
}

cocos2d::Sprite * PlayerCharacter::getSprite()
{
	return characterSprite;
}

Stats PlayerCharacter::getStats()
{
	return characterStats;
}

void PlayerCharacter::LoadStats(float hp, float mp, float atk, float def, int karma, float m_hp, float m_mp, float m_atk, float m_def, int m_jump)
{
	characterStats.LoadPlayerStats(hp, mp, atk, def, karma, m_hp, m_mp, m_atk, m_def, m_jump);

	if (characterStats.Karma >= 90) {
		characterColor = cocos2d::Color3B::BLACK;
	}
	else if (characterStats.Karma >= 50) {
		characterColor = cocos2d::Color3B::GRAY;
	}
	else {
		characterColor = cocos2d::Color3B::WHITE;
	}

	characterSpriteAnimation->setColor(characterColor);
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

inline void PlayerCharacter::getValue(int characterType)
{
	auto buf = FileUtils::getInstance()->getStringFromFile("res/player.json");

	characterDocument.Parse<0>(buf.c_str());
	if (characterDocument.HasParseError()) {
		CCLOG("ERROR: Character document not found!");
	}
	else {
		if (characterDocument.HasMember("PLAYER")) {
			rapidjson::Value& playerCharacter = characterDocument["PLAYER"];
			for (rapidjson::SizeType i = 0; i < playerCharacter.Size(); i++) {
				if (playerCharacter[i]["TYPE"].GetInt() == characterType) {
					characterValue = playerCharacter[i];
				}
			}
		}
	}
}

void PlayerCharacter::savePosition()
{
	characterSavePosition = characterSprite->getPosition();
}

void PlayerCharacter::returnSavePosition()
{
	characterSprite->setPosition(characterSavePosition);
}