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

	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Idle1.png");
	
	characterSprite = Sprite::create();
	characterSpriteAnimation = Sprite::createWithSpriteFrame(frame);

	attackSprite = Sprite::create();

	shapeCache = PhysicsShapeCache::getInstance();
	shapeCache->addShapesWithFile(boss + "body.plist");
	
	characterPhysicsBody = shapeCache->createBodyWithName("Idle");
	characterPhysicsBody->setDynamic(false);
	characterPhysicsBody->setRotationEnable(false);
	characterSprite->setPhysicsBody(characterPhysicsBody);
	
	characterSprite->addChild(characterSpriteAnimation);
	characterSprite->addChild(attackSprite);
	
	characterSprite->setScale(0.5);
}

void BossCharacter::attack(float dt) {
	int type = rand() % 4 + 1;
	if (type == 1) {
		attack_1();
	}
	else if (type == 2) {
		attack_2();
	}
	else if (type == 3) {
		jump_attack_1();
	}
	else if (type == 4) {
		jump_attack_2();
	}
}

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
	//auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), NULL);
	characterSpriteAnimation->runAction(animate);
}

void BossCharacter::attack_2() {
	//animation->release();

	cocos2d::PhysicsBody* attackBody = shapeCache->createBodyWithName("Attack_2");
	attackBody->setDynamic(false);
	attackBody->setRotationEnable(false);
	attackBody->setGravityEnable(false);
	attackBody->setCollisionBitmask(BOSS_ATTACK_COLLISION_BITMASK);
	attackBody->setContactTestBitmask(false);
	attackBody->setMass(0.0f);

	attackSprite->setPhysicsBody(attackBody);

	animation = BossCharacter::createAnimation("Attack_2", 7, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	//auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), NULL);
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

	//auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), NULL);
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
	//auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), NULL);
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


void BossCharacter::updateCharacter() {

}