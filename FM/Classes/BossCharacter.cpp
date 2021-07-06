#include "BossCharacter.h"
#include "Definitions.h"

USING_NS_CC;

BossCharacter::BossCharacter(int level) {

#if 1
	string boss = StringUtils::format("plist/Boss_%i/", level);

	SpriteBatchNode* spriteNode = SpriteBatchNode::create(boss + "Attack_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(boss + "Attack_1.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(boss + "Attack_2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(boss + "Attack_2.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(boss + "Block.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(boss + "Block.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(boss + "Charge.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(boss + "Charge.plist");

	/*SpriteBatchNode**/ spriteNode = SpriteBatchNode::create(boss + "Death.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(boss + "Death.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(boss + "Hurt.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(boss + "Hurt.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(boss + "Jump.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(boss + "Jump.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(boss + "Jump_Attack_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(boss + "Jump_Attack_1.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(boss + "Jump_Attack_2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(boss + "Jump_Attack_2.plist");

	/*SpriteBatchNode**/ spriteNode = SpriteBatchNode::create(boss + "Idle.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(boss + "Idle.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(boss + "Run.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(boss + "Run.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(boss + "Shoot_Bow.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(boss + "Shoot_Bow.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(boss + "Walk.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(boss + "Walk.plist");
#endif

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Idle1.png");

	characterSprite = Sprite::create();
	characterSpriteAnimation = Sprite::createWithSpriteFrame(frame);

	attackSprite = Sprite::create();

	shapeCache = PhysicsShapeCache::getInstance();
	shapeCache->addShapesWithFile(boss + "body.plist");

	characterPhysicsBody = shapeCache->createBodyWithName("Idle");
	characterPhysicsBody->setDynamic(true);
	characterPhysicsBody->setRotationEnable(false);

	characterPhysicsBody->setCategoryBitmask(BOSS_CATEGORY_BITMASK);
	characterPhysicsBody->setCollisionBitmask(BOSS_COLLISION_BITMASK);
	characterPhysicsBody->setContactTestBitmask(false);

	characterSprite->setPhysicsBody(characterPhysicsBody);

	characterSprite->addChild(characterSpriteAnimation);
	characterSprite->addChild(attackSprite);

	characterSprite->setScale(0.5);
	characterSprite->setScaleX(-0.5);//characterSprite->setFlippedX(true);
	characterDirection = Direction::LEFT;
}

#if 0
void BossCharacter::attack_1() {
	//animation->release();

	cocos2d::PhysicsBody* attackBody = shapeCache->createBodyWithName("Attack_1");
	attackBody->setDynamic(false);
	attackBody->setRotationEnable(false);
	attackBody->setGravityEnable(false);
	attackBody->setCollisionBitmask(BOSS_ATTACK_COLLISION_BITMASK);
	attackBody->setContactTestBitmask(false);
	attackBody->setMass(0.0f);

	attackSprite->setPhysicsBody(attackBody);


	//shapeCache->setBodyOnSprite("Attack_1", characterSpriteAnimation);


	animation = BossCharacter::createAnimation("Attack_1", 8, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	/*cocos2d::DelayTime* delay = cocos2d::DelayTime::create(0.8);
	auto seq = Sequence::create(animate, delay, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), NULL);*/
	characterSpriteAnimation->runAction(animate);
}

void BossCharacter::attack_2() {
	//animation->release();

	cocos2d::PhysicsBody* attackBody = shapeCache->createBodyWithName("Attack_2");
	attackBody->setDynamic(false);
	attackBody->setRotationEnable(false);
	attackBody->setGravityEnable(false);
	attackBody->setCollisionBitmask(BOSS_COLLISION_BITMASK);
	attackBody->setContactTestBitmask(false);
	attackBody->setMass(0.0f);

	attackSprite->setPhysicsBody(attackBody);

	animation = BossCharacter::createAnimation("Attack_2", 7, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	/*cocos2d::DelayTime* delay = cocos2d::DelayTime::create(0.7);
	auto seq = Sequence::create(animate, delay, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), NULL);*/
	characterSpriteAnimation->runAction(animate);
}

void BossCharacter::jump_attack_1() {
	//animation->release();

	cocos2d::PhysicsBody* attackBody = shapeCache->createBodyWithName("Jump_Attack_1");
	attackBody->setDynamic(false);
	attackBody->setRotationEnable(false);
	attackBody->setGravityEnable(false);
	attackBody->setCollisionBitmask(BOSS_ATTACK_COLLISION_BITMASK);
	attackBody->setContactTestBitmask(false);
	attackBody->setMass(0.0f);

	attackSprite->setPhysicsBody(attackBody);

	animation = BossCharacter::createAnimation("Jump_Attack_1", 8, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	/*cocos2d::DelayTime* delay = cocos2d::DelayTime::create(0.8);
	auto seq = Sequence::create(animate, delay, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), NULL);*/
	characterSpriteAnimation->runAction(animate);
}

void BossCharacter::jump_attack_2() {
	//animation->release();

	cocos2d::PhysicsBody* attackBody = shapeCache->createBodyWithName("Jump_Attack_2");
	attackBody->setDynamic(false);
	attackBody->setRotationEnable(false);
	attackBody->setGravityEnable(false);
	attackBody->setCollisionBitmask(BOSS_ATTACK_COLLISION_BITMASK);
	attackBody->setContactTestBitmask(false);
	attackBody->setMass(0.0f);

	attackSprite->setPhysicsBody(attackBody);
	animation = BossCharacter::createAnimation("Jump_Attack_2", 7, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	/*cocos2d::DelayTime* delay = cocos2d::DelayTime::create(0.7);
	auto seq = Sequence::create(animate, delay, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), NULL);*/
	characterSpriteAnimation->runAction(animate);
}

void BossCharacter::block() {
	//animation->release();
	animation = BossCharacter::createAnimation("Block", 9, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	characterSprite->runAction(animate);
}

void BossCharacter::charge() {
	//animation->release();
	cocos2d::PhysicsBody* attackBody = shapeCache->createBodyWithName("Charge");
	attackBody->setDynamic(false);
	attackBody->setRotationEnable(false);
	attackBody->setGravityEnable(false);
	attackBody->setCollisionBitmask(BOSS_ATTACK_COLLISION_BITMASK);
	attackBody->setContactTestBitmask(false);
	attackBody->setMass(0.0f);

	attackSprite->setPhysicsBody(attackBody);

	animation = BossCharacter::createAnimation("Charge", 7, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), NULL);
	characterSpriteAnimation->runAction(seq);
	auto move = MoveBy::create(0.7, Vec2(-30, 0));
	characterSprite->runAction(move);
}

void BossCharacter::death() {
	//animation->release();
	animation = BossCharacter::createAnimation("Death", 15, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	characterSprite->runAction(animate);
}

void BossCharacter::hurt() {
	//animation->release();
	animation = BossCharacter::createAnimation("Hurt", 8, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	characterSprite->runAction(animate);
}

void BossCharacter::idle() {
	animation->release();
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	animation = BossCharacter::createAnimation("Idle", 16, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	characterSpriteAnimation->runAction(RepeatForever::create(animate));
}

void BossCharacter::jump() {
	//animation->release();
	animation = BossCharacter::createAnimation("Jump", 10, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	characterSprite->runAction(animate);
}

void BossCharacter::run() {
	//animation->release();
	animation = BossCharacter::createAnimation("Run", 6, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	characterSprite->runAction(animate);
	auto move = MoveBy::create(0.6, Vec2(-30, 0));
	characterSprite->runAction(move);
}

void BossCharacter::shoot_bow() {
	//animation->release();

	animation = BossCharacter::createAnimation("Shoot_Bow", 12, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	characterSprite->runAction(animate);
}

void BossCharacter::walk() {
	//animation->release();
	animation = BossCharacter::createAnimation("Walk", 12, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	characterSprite->runAction(animate);
	auto move = MoveBy::create(1.2, Vec2(-10, 0));
	characterSprite->runAction(move);
}

#endif

void BossCharacter::setDirection(Direction actionDirection) {
	characterDirection = actionDirection;
	if (characterDirection == Direction::LEFT) {
		//characterSprite->setFlippedX(true);
		characterSprite->setScaleX(-0.5);
	}
	else {
		//characterSprite->setFlippedX(false);
		characterSprite->setScaleX(0.5);
	}
}

cocos2d::Animation* BossCharacter::createAnimation(string prefixName, int pFramesOrder, float delay) {
	Vector<SpriteFrame*> animFrames;
	for (int i = 1; i <= pFramesOrder; i++) {
		char buffer[20] = { 0 };
		sprintf(buffer, "%d.png", i);
		string str = prefixName + buffer;
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animFrames.pushBack(frame);
	}
	animation = Animation::createWithSpriteFrames(animFrames, delay);
	return animation;
}

void BossCharacter::updateAnimation(State actionState, bool repeatForever) {
	if (characterState != actionState) {
		if (attackSprite->getPhysicsBody() != nullptr)
			attackSprite->getPhysicsBody()->removeFromWorld();

		const int maxWord = 50;

		int numberSprite;
		string prefixName;

		switch (actionState)
		{
		case BossCharacter::State::ATTACK1:
			numberSprite = 8;
			prefixName = "Attack_1";;
			break;
		case BossCharacter::State::ATTACK2:
			numberSprite = 7;
			prefixName = "Attack_2";
			break;
		case BossCharacter::State::BLOCK:
			numberSprite = 9;
			prefixName = "Block";
			break;
		case BossCharacter::State::CHARGE:
			numberSprite = 7;
			prefixName = "Charge";
			break;
		case BossCharacter::State::DEATH:
			numberSprite = 15;
			prefixName = "Death";
			break;
		case BossCharacter::State::HURT:
			numberSprite = 8;
			prefixName = "Hurt";
			break;
		case BossCharacter::State::IDLE:
			numberSprite = 16;
			prefixName = "Idle";
			break;
		case BossCharacter::State::JUMP:
			numberSprite = 10;
			prefixName = "Jump";
			break;
		case BossCharacter::State::JUMPATTACK1:
			numberSprite = 8;
			prefixName = "Jump_Attack_1";
			break;
		case BossCharacter::State::JUMPATTACK2:
			numberSprite = 7;
			prefixName = "Jump_Attack_2";
			break;
		case BossCharacter::State::RUN:
			numberSprite = 6;
			prefixName = "Run";
			break;
		case BossCharacter::State::SHOOTBOW:
			numberSprite = 12;
			prefixName = "Shoot_Bow";
			break;
		case BossCharacter::State::WALK:
			numberSprite = 12;
			prefixName = "Walk";
			break;
		default:
			break;
		}

		animation = createAnimation(prefixName, numberSprite, ANIMATION_DELAY);
		auto animate = Animate::create(animation);
		animate->retain();

		if (repeatForever) {
			characterSpriteAnimation->stopAllActions();
			characterSpriteAnimation->runAction(RepeatForever::create(animate));
			characterState = actionState;
		}
		else {
			characterSpriteAnimation->stopAllActions();
			characterSpriteAnimation->runAction(animate);
			characterState = actionState;
		}
	}
}

void BossCharacter::updateAction(cocos2d::Vec2 positionPlayer) {
	
	if (abs(positionPlayer.x - characterSprite->getPosition().x) <= visibleSize.width / 8) {
		if (positionPlayer.y > characterSprite->getPosition().y + characterSprite->getContentSize().height) {
			jumpAttack();
		}
		else {
			attack();
		}
	}
	else {
		updateAnimation(State::IDLE, true);
	}
}

void BossCharacter::attack() {
	int type = rand() % 2 + 1;
	if (type == 1) {
		updateAnimation(State::ATTACK1);
		cocos2d::PhysicsBody* attackBody = shapeCache->createBodyWithName("Attack_1");
		attackBody->setDynamic(false);
		attackBody->setRotationEnable(false);
		attackBody->setGravityEnable(false);
		attackBody->setCollisionBitmask(BOSS_ATTACK_COLLISION_BITMASK);
		attackBody->setContactTestBitmask(false);
		attackBody->setMass(0.0f);

		attackSprite->setPhysicsBody(attackBody);
	}
	else if (type == 2) {
		updateAnimation(State::ATTACK2);
		cocos2d::PhysicsBody* attackBody = shapeCache->createBodyWithName("Attack_2");
		attackBody->setDynamic(false);
		attackBody->setRotationEnable(false);
		attackBody->setGravityEnable(false);
		attackBody->setCollisionBitmask(BOSS_ATTACK_COLLISION_BITMASK);
		attackBody->setContactTestBitmask(false);
		attackBody->setMass(0.0f);

		attackSprite->setPhysicsBody(attackBody);
	}
}

void BossCharacter::jumpAttack() {
	int type = rand() % 2 + 1;
	if (type == 1) {
		updateAnimation(State::JUMPATTACK1);
		cocos2d::PhysicsBody* attackBody = shapeCache->createBodyWithName("Jump_Attack_1");
		attackBody->setDynamic(false);
		attackBody->setRotationEnable(false);
		attackBody->setGravityEnable(false);
		attackBody->setCollisionBitmask(BOSS_ATTACK_COLLISION_BITMASK);
		attackBody->setContactTestBitmask(false);
		attackBody->setMass(0.0f);
		auto move = MoveBy::create(0.8, Vec2(0, visibleSize.height / 4));
		characterSprite->runAction(move);
		attackSprite->setPhysicsBody(attackBody);
	}
	else if (type == 2) {
		updateAnimation(State::JUMPATTACK2);
		cocos2d::PhysicsBody* attackBody = shapeCache->createBodyWithName("Jump_Attack_2");
		attackBody->setDynamic(false);
		attackBody->setRotationEnable(false);
		attackBody->setGravityEnable(false);
		attackBody->setCollisionBitmask(BOSS_ATTACK_COLLISION_BITMASK);
		attackBody->setContactTestBitmask(false);
		attackBody->setMass(0.0f);
		auto move = MoveBy::create(0.7, Vec2(0, visibleSize.height / 4));
		characterSprite->runAction(move);
		attackSprite->setPhysicsBody(attackBody);
	}
}

void BossCharacter::run() {
	updateAnimation(State::RUN);
	if (characterDirection == Direction::RIGHT) {
		auto move = MoveBy::create(0.7, Vec2(visibleSize.width / 6, 0));
		characterSprite->runAction(move);
	}
	else
	{
		auto move = MoveBy::create(0.7, Vec2(-visibleSize.width / 6, 0));
		characterSprite->runAction(move);
	}
}
