#include "MonsterCharacter.h"
#include "Definitions.h"

USING_NS_CC;

MonsterCharacter::MonsterCharacter(cocos2d::Node* _scene, int _level) {

	scene = _scene;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	characterStats.SetStats(100.0f * _level, 100.0f * _level, 10 * _level, 10 * _level);
	level = _level;

	floder = StringUtils::format("plist/Monster_%i/", 1);

	SpriteBatchNode* spriteNode = SpriteBatchNode::create(floder + "Attack.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Attack.plist");

	/*SpriteBatchNode**/ spriteNode = SpriteBatchNode::create(floder + "Death.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Death.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(floder + "Hurt.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Hurt.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(floder + "Jump.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Jump.plist");

	/*SpriteBatchNode**/ spriteNode = SpriteBatchNode::create(floder + "Idle.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Idle.plist");

	monster = Sprite::createWithSpriteFrameName("Idle-0.png");
	monster->setScale(0.5);

	monsterBody = PhysicsBody::createBox(monster->getContentSize());
	monsterBody->setDynamic(false);
	monsterBody->setRotationEnable(false);

	monsterBody->setCategoryBitmask(ENEMIES_CATEGORY_BITMASK);
	monsterBody->setCollisionBitmask(ENEMIES_COLLISION_BITMASK);
	monsterBody->setContactTestBitmask(ALLSET_BITMASK);

	monster->setPhysicsBody(monsterBody);

	auto animate = Animate::create(MonsterCharacter::createAnimation("Idle-", 16, 0.1));
	animate->retain();
	monster->runAction(RepeatForever::create(animate));

	monster->addChild(characterStats.GetSprite());
	characterStats.GetSprite()->setPosition(Vec2(0.0f, monster->getContentSize().height));
}

cocos2d::Sprite* MonsterCharacter::getSprite() {
	return monster;
};

void MonsterCharacter::setPosition(cocos2d::Vec2 _position) {
	monster->setPosition(_position);
	position = _position;
}

void MonsterCharacter::setDirection(Direction _actionDirection) {
	actionDirection = _actionDirection;
	if (actionDirection == Direction::LEFT) {
		monster->setFlippedX(false);
	}
	else {
		monster->setFlippedX(true);
	}
}

void MonsterCharacter::attack() {

	monsterBody->setDynamic(false);
	animation = MonsterCharacter::createAnimation("Attack-", 19, 0.02);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
	
	string bulletSprite = StringUtils::format("poisonspit_%i.png", level);
	bullet = Sprite::create(floder + bulletSprite);
	auto bodyBullet = PhysicsBody::createBox(bullet->getContentSize());
	bullet->setPhysicsBody(bodyBullet);
	bodyBullet->setDynamic(false);

	bodyBullet->setCategoryBitmask(ENEMIES_ATTACK_CATEGORY_BITMASK);
	bodyBullet->setCollisionBitmask(ENEMIES_ATTACK_COLLISION_BITMASK);
	bodyBullet->setContactTestBitmask(ALLSET_BITMASK);

	bullet->setPosition(monster->getPosition());
	bullet->setScale(0.25 * level);
	scene->addChild(bullet);

	if(actionDirection == Direction::LEFT){
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

void MonsterCharacter::death() {
	//animation->release();
	animation = MonsterCharacter::createAnimation("Death-", 24, 0.02);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);

	auto dieAction = MoveTo::create(0, Vec2(-100 * visibleSize.width, 0));
	cocos2d::DelayTime* delay = cocos2d::DelayTime::create(2.4);
	auto seq = Sequence::create(delay, dieAction, nullptr);
	monster->runAction(seq);
}

void MonsterCharacter::takeHit(float dame) {
	characterStats.HP -= dame;
	characterStats.UpdateStatsBar();

	animation = MonsterCharacter::createAnimation("Hurt-", 4, 0.02);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);

	if (characterStats.HP <= 0.0f) {
		death();
		GameManager::getInstace()->getMission()->updateMission(1);
	}
}

void MonsterCharacter::idle() {
	//animation->release();
	animation = MonsterCharacter::createAnimation("Idle-", 48, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(RepeatForever::create(animate));
}

void MonsterCharacter::walk() {
	//animation->release();
	animation = MonsterCharacter::createAnimation("Jump-", 17, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
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