#include "MonsterCharacter.h"
#include "Definitions.h"

USING_NS_CC;

MonsterCharacter::MonsterCharacter(cocos2d::Node* _scene, int _type, int _level) {

	scene = _scene;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	/*characterStats.SetMonsterStats(100.0f * _level, 100.0f * _level, 10 * _level, 10 * _level);*/
	
	characterStats.SetStats(100.0f * _level, 100.0f * _level, 10 * _level, 10 * _level);

	level = _level;
	type = _type;

	floder = StringUtils::format("plist/Monster_%i/", type);
	name = StringUtils::format("Monster_%i", type);

	SpriteBatchNode* spriteNode = SpriteBatchNode::create(floder + name + "-Attack.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + name + "-Attack.plist");

	/*SpriteBatchNode**/ spriteNode = SpriteBatchNode::create(floder + name + "-Death.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + name + "-Death.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(floder + name + "-Hurt.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + name + "-Hurt.plist");

	/*SpriteBatchNode**/ spriteNode = SpriteBatchNode::create(floder + name + "-Idle.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + name + "-Idle.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(floder + name + "-Jump.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + name + "-Jump.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(floder + name + "-Run.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + name + "-Run.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(floder + name + "-Walk.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + name + "-Walk.plist");

	characterSprite = Sprite::create();
	characterSpriteAnimation = Sprite::createWithSpriteFrameName(name + "-Idle-0.png");
	attackSprite = Sprite::create();

	switch (type)
	{
	case 1:
		species = Species::RANGED;
		characterSize = Size(characterSpriteAnimation->getContentSize());
		numSprite = { 19,24,4,16,17,0,0 }; //Attack - 0, Death - 1, Hurt - 2, Idle - 3, Jump - 4, Run - 5, Walk - 6
		break;
	case 2:
		species = Species::MELEE;
		numSprite = { 24,24,12,12,30,24,36 }; //Attack - 0, Death - 1, Hurt - 2, Idle - 3, Jump - 4, Run - 5, Walk - 6
		characterSize = Size(characterSpriteAnimation->getContentSize().width * 0.5f, characterSpriteAnimation->getContentSize().height * 0.85f);
		break;
	case 3:
		species = Species::MELEE;
		break;
	case 4:
		species = Species::MELEE;
		break;
	default:
		break;
	}

	characterPhysicsBody = PhysicsBody::createBox(characterSize);
	characterPhysicsBody->setDynamic(true);
	characterPhysicsBody->setRotationEnable(false);

	characterPhysicsBody->setCategoryBitmask(ENEMIES_CATEGORY_BITMASK);
	characterPhysicsBody->setCollisionBitmask(ENEMIES_COLLISION_BITMASK);
	characterPhysicsBody->setContactTestBitmask(ALLSET_BITMASK);

	characterSprite->setPhysicsBody(characterPhysicsBody);
	
	characterSprite->addChild(characterSpriteAnimation);
	characterSprite->addChild(attackSprite);

	characterSprite->setScale(0.5);

	if (type != 1) {
		characterSprite->setScaleX(-0.5);
	}
	

	auto animate = Animate::create(MonsterCharacter::createAnimation(name + "-Idle-", numSprite[3], 0.1));
	animate->retain();
	characterSpriteAnimation->runAction(RepeatForever::create(animate));

	characterSpriteAnimation->addChild(characterStats.GetSprite());
	characterStats.GetSprite()->setPosition(Vec2(0.0f, characterSpriteAnimation->getContentSize().height));
}

cocos2d::Sprite* MonsterCharacter::getSprite() {
	return characterSprite;
};

void MonsterCharacter::setPosition(cocos2d::Vec2 _position) {
	position = _position;
	characterSprite->setPosition(_position);
	characterSpriteAnimation->setPosition(Vec2::ZERO);
	attackSprite->setPosition(Vec2::ZERO);
}

void MonsterCharacter::setDirection(Direction _actionDirection) {
	actionDirection = _actionDirection;
	if (actionDirection == Direction::LEFT) {
		if (type == 1) {
			characterSprite->setScaleX(0.5);
		}
		else {
			characterSprite->setScaleX(-0.5);
		}
	}
	else {
		if (type == 1) {
			characterSprite->setScaleX(-0.5);
		}
		else {
			characterSprite->setScaleX(0.5);
		}
	}
}

void MonsterCharacter::updateAction(cocos2d::Vec2 positionPlayer) {
	if (abs(position.x - positionPlayer.x) <= visibleSize.width / 3) {
		if (species == Species::RANGED) {
			attackForRanged();
		}
		else {
			if (abs(characterSprite->getPosition().x - positionPlayer.x) <= visibleSize.width / 12) {
				attackForMelee();
			}
			else if (abs(characterSprite->getPosition().x - positionPlayer.x) <= visibleSize.width / 6) {
				walk();
			}
			else {
				run();
			}
		}
	}
}

void MonsterCharacter::attack() {
	if (species == Species::RANGED) {
		attackForRanged();
	}
	else {
		attackForMelee();
	}
}

void MonsterCharacter::death() {
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	//animation->release();
	characterSpriteAnimation->stopAllActions();
	animation = MonsterCharacter::createAnimation(name + "-Death-", numSprite[1], 0.02);
	auto animate = Animate::create(animation);
	animate->retain();
	characterSpriteAnimation->runAction(animate);

	auto dieAction = MoveTo::create(0, Vec2(-100 * visibleSize.width, 0));
	cocos2d::DelayTime* delay = cocos2d::DelayTime::create(numSprite[1] * 0.02);
	auto seq = Sequence::create(delay, dieAction, nullptr);
	characterSprite->runAction(seq);
}

void MonsterCharacter::takeHit(float dame) {
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	characterStats.HP -= dame;
	characterStats.UpdateStatsBar();
	characterSpriteAnimation->stopAllActions();
	animation = MonsterCharacter::createAnimation(name + "-Hurt-", numSprite[2], 0.02);
	auto animate = Animate::create(animation);
	animate->retain();
	
	auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(MonsterCharacter::idle, this)), nullptr);
	characterSpriteAnimation->runAction(seq);

	if (characterStats.HP <= 0.0f) {
		death();
		GameManager::getInstace()->getMission()->updateMission(1);
	}
}

void MonsterCharacter::idle() {

	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	//animation->release();
	characterSpriteAnimation->stopAllActions();
	animation = MonsterCharacter::createAnimation(name + "-Idle-", numSprite[3], 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	characterSpriteAnimation->runAction(RepeatForever::create(animate));
}

void MonsterCharacter::jump() {
	//animation->release();
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	characterSpriteAnimation->stopAllActions();
	animation = MonsterCharacter::createAnimation(name + "-Jump-", numSprite[4], 0.1);
	auto animate = Animate::create(animation);
	animate->retain();

	auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(MonsterCharacter::idle, this)), nullptr);
	characterSpriteAnimation->runAction(seq);
}

void MonsterCharacter::run() {
	//animation->release();
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	characterSpriteAnimation->stopAllActions();
	animation = MonsterCharacter::createAnimation(name + "-Run-", numSprite[5], 0.1);
	auto animate = Animate::create(animation);
	animate->retain();

	auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(MonsterCharacter::idle, this)), nullptr);
	characterSpriteAnimation->runAction(seq);

	if (actionDirection == Direction::RIGHT) {
		auto move = MoveBy::create(0.1 * numSprite[5], Vec2(visibleSize.width / 8, 0));
		characterSprite->runAction(move);
	}
	else {
		auto move = MoveBy::create(0.1 * numSprite[5], Vec2(-visibleSize.width / 8, 0));
		characterSprite->runAction(move);
	}
}

void MonsterCharacter::walk() {
	//animation->release();
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	characterSpriteAnimation->stopAllActions();
	animation = MonsterCharacter::createAnimation(name + "-Walk-", numSprite[6], 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	
	auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(MonsterCharacter::idle, this)), nullptr);
	characterSpriteAnimation->runAction(seq);

	if (actionDirection == Direction::RIGHT) {
		auto move = MoveBy::create(0.1 * numSprite[5], Vec2(visibleSize.width / 12, 0));
		characterSprite->runAction(move);
	}
	else {
		auto move = MoveBy::create(0.1 * numSprite[5], Vec2(-visibleSize.width / 12, 0));
		characterSprite->runAction(move);
	}
}

cocos2d::Animation* MonsterCharacter::createAnimation(string prefixName, int pFramesOrder, float delay) {
	Vector<SpriteFrame*> animFrames;
	for (int i = 0; i < pFramesOrder; i++) {
		char buffer[20] = { 0 };
		sprintf(buffer, "%d.png", i);
		string str = prefixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames, delay);
	return animation;
}

//Attack.
void MonsterCharacter::attackForRanged() {
	if (characterStats.HP > 0.0f) {
		characterSpriteAnimation->stopAllActions();
		characterPhysicsBody->setDynamic(false);
		animation = MonsterCharacter::createAnimation(name + "-Attack-", numSprite[0], 0.02);
		auto animate = Animate::create(animation);
		animate->retain();

		auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(MonsterCharacter::idle, this)), nullptr);
		characterSpriteAnimation->runAction(seq);

		string bulletSprite = StringUtils::format("poisonspit_%i.png", level);
		bullet = Sprite::create(floder + bulletSprite);
		auto bodyBullet = PhysicsBody::createBox(bullet->getContentSize());
		bullet->setPhysicsBody(bodyBullet);
		bodyBullet->setDynamic(false);

		bodyBullet->setCategoryBitmask(ENEMIES_ATTACK_CATEGORY_BITMASK);
		bodyBullet->setCollisionBitmask(ENEMIES_ATTACK_COLLISION_BITMASK);
		bodyBullet->setContactTestBitmask(ALLSET_BITMASK);

		bullet->setPosition(characterSprite->getPosition());
		bullet->setScale(0.25 * level);
		scene->addChild(bullet);

		if (actionDirection == Direction::LEFT) {
			auto shootAction = MoveBy::create(5, Vec2(-visibleSize.width / 3, 0));
			auto disappearAction = MoveBy::create(0, Vec2(-100 * visibleSize.width, 0));
			auto seq = Sequence::create(shootAction, disappearAction, nullptr);
			bullet->runAction(seq);
		}
		else {
			auto shootAction = MoveBy::create(5, Vec2(visibleSize.width / 3, 0));
			auto disappearAction = MoveBy::create(0, Vec2(-100 * visibleSize.width, 0));
			auto seq = Sequence::create(shootAction, disappearAction, nullptr);
			bullet->runAction(seq);
		}
	}
}

void MonsterCharacter::attackForMelee() {
	if (characterStats.HP > 0.0f) {
		characterSpriteAnimation->stopAllActions();
		//characterPhysicsBody->setDynamic(false);
		animation = MonsterCharacter::createAnimation(name + "-Attack-", numSprite[0], 0.02);
		auto animate = Animate::create(animation);
		animate->retain();
		auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(MonsterCharacter::idle, this)), nullptr);
		characterSpriteAnimation->runAction(seq);

		cocos2d::PhysicsBody* attackBody = PhysicsBody::createBox(characterSpriteAnimation->getContentSize());
		attackBody->setDynamic(false);
		attackBody->setRotationEnable(false);
		attackBody->setGravityEnable(false);
		attackBody->setCategoryBitmask(ENEMIES_ATTACK_CATEGORY_BITMASK);
		attackBody->setCollisionBitmask(ENEMIES_ATTACK_COLLISION_BITMASK);
		attackBody->setContactTestBitmask(ALLSET_BITMASK);
		attackBody->setMass(0.0f);

		attackSprite->setPhysicsBody(attackBody);
	}
}