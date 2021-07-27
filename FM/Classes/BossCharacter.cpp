#include "BossCharacter.h"
#include "Definitions.h"

USING_NS_CC;

BossCharacter::BossCharacter(int level) {

#if 1
	floder = StringUtils::format("plist/Boss_%i/", level);

	SpriteBatchNode* spriteNode = SpriteBatchNode::create(floder + "Attack_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Attack_1.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(floder + "Attack_2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Attack_2.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(floder + "Block.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Block.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(floder + "Charge.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Charge.plist");

	/*SpriteBatchNode**/ spriteNode = SpriteBatchNode::create(floder + "Death.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Death.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(floder + "Hurt.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Hurt.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(floder + "Jump.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Jump.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(floder + "Jump_Attack_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Jump_Attack_1.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(floder + "Jump_Attack_2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Jump_Attack_2.plist");

	/*SpriteBatchNode**/ spriteNode = SpriteBatchNode::create(floder + "Idle.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Idle.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(floder + "Run.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Run.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(floder + "Shoot_Bow.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Shoot_Bow.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create(floder + "Walk.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(floder + "Walk.plist");
#endif

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName("Idle1.png");

	characterStats.SetStats(100.0f * level, 100.0f * level, 10 * level, 10 * level);

	characterSprite = Sprite::create();
	characterSpriteAnimation = Sprite::createWithSpriteFrame(frame);

	attackSprite = Sprite::create();

	//shapeCache = PhysicsShapeCache::getInstance();
	//shapeCache->addShapesWithFile(boss + "body.plist");
	
	characterPhysicsBody = GameManager::getInstace()->getPhysicsShapeCache()->createBodyWithName("Idle");
	characterPhysicsBody->setDynamic(true);
	characterPhysicsBody->setRotationEnable(false);

	characterPhysicsBody->setCategoryBitmask(ENEMIES_CATEGORY_BITMASK);
	characterPhysicsBody->setCollisionBitmask(ENEMIES_COLLISION_BITMASK);
	characterPhysicsBody->setContactTestBitmask(ALLSET_BITMASK);

	characterSprite->setPhysicsBody(characterPhysicsBody);

	characterSprite->addChild(characterSpriteAnimation);
	characterSprite->addChild(attackSprite);

	characterSprite->setScale(0.5);
	characterSprite->setScaleX(-0.5);//characterSprite->setFlippedX(true);
	characterDirection = Direction::LEFT;
	action = 0;
	numAttack = 5;

	characterSprite->addChild(characterStats.GetSprite());
	characterStats.GetSprite()->setScale(2.0f);
	characterStats.GetSprite()->setPosition(Vec2(0, characterSpriteAnimation->getContentSize().height / 6));
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

#if 0
void BossCharacter::updateAnimation(State actionState, bool repeatForever) {
	//if (characterState != actionState) {
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
	//}
}
#endif

void BossCharacter::setDirection(Direction actionDirection) {
	if (action != 1) {
		characterDirection = actionDirection;
		if (characterDirection == Direction::LEFT) {
			characterSprite->setScaleX(-0.5);//characterSprite->setFlippedX(true);
		}
		else {
			characterSprite->setScaleX(0.5);//characterSprite->setFlippedX(false);
		}
	}	
}

void BossCharacter::updateAction(cocos2d::Vec2 positionPlayer) {
	if (characterStats.HP > 0) {
		if (abs(position.x - positionPlayer.x) > visibleSize.width / 2) {
			idle();
			action = 0;
		}
		else {
			if (abs(positionPlayer.x - characterSprite->getPosition().x) <= visibleSize.width / 8) {
				if (positionPlayer.y > characterSprite->getPosition().y + characterSprite->getContentSize().height) {
					if (action == 0) {
						jumpAttack();
						action = 2;
					}
					else if (action == 2) {
						idle();
						action = 0;
					}

				}
				else {
					if (action == 0) {
						attack();
						action = 2;
					}
					else if (action == 2) {
						idle();
						action = 0;
					}

				}
			}
			else if (abs(positionPlayer.x - characterSprite->getPosition().x) <= visibleSize.width / 4) {
				if (numAttack >= 5) {
					skill(1);
				}
				else {
					walk();
				}
			}
			else if (abs(positionPlayer.x - characterSprite->getPosition().x) <= visibleSize.width / 2) {
				if (numAttack >= 5) {
					skill(2);
				}
				else {
					run();
				}
			}
			else {
				idle();
				action = 0;
			}
		}
	}
}

void BossCharacter::idle() {
	characterState = State::IDLE;
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	characterSpriteAnimation->stopAllActions();

	animation = createAnimation("Idle", 16, 0.05);
	Animate* animate = Animate::create(animation);
	animate->retain();
	characterSpriteAnimation->runAction(RepeatForever::create(animate));
}
void BossCharacter::death()
{
	characterState = State::DEATH;
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	characterSpriteAnimation->stopAllActions();

	animation = createAnimation("Death", 15, 0.1);
	Animate* animate = Animate::create(animation);
	animate->retain();	
	characterSpriteAnimation->runAction(animate);

	auto callback = CallFunc::create([this]() {
		characterSprite->removeFromParent();
	});

	cocos2d::DelayTime* delay = cocos2d::DelayTime::create(3);
	auto seq = Sequence::create(delay, callback, nullptr);
	characterSprite->runAction(seq);
}
void BossCharacter::attack_1() {
	attackSprite->setPosition(Vec2::ZERO);
	characterState = State::ATTACK;
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	characterSpriteAnimation->stopAllActions();

	animation = createAnimation("Attack_1", 8, 0.05);
	Animate* animate = Animate::create(animation);
	animate->retain();
	auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), nullptr);
	characterSpriteAnimation->runAction(seq);

	cocos2d::PhysicsBody* attackBody = GameManager::getInstace()->getPhysicsShapeCache()->createBodyWithName("Attack_1");
	attackBody->setDynamic(false);
	attackBody->setRotationEnable(false);
	attackBody->setGravityEnable(false);
	attackBody->setCategoryBitmask(ENEMIES_ATTACK_CATEGORY_BITMASK);
	attackBody->setCollisionBitmask(ENEMIES_ATTACK_COLLISION_BITMASK);
	attackBody->setContactTestBitmask(ALLSET_BITMASK);
	attackBody->setMass(0.0f);

	attackSprite->setPhysicsBody(attackBody);
}
void BossCharacter::attack_2() {
	attackSprite->setPosition(Vec2::ZERO);
	characterState = State::ATTACK;
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	characterSpriteAnimation->stopAllActions();

	animation = createAnimation("Attack_2", 7, 0.05);
	Animate* animate = Animate::create(animation);
	animate->retain();
	auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), nullptr);
	characterSpriteAnimation->runAction(seq);

	cocos2d::PhysicsBody* attackBody = GameManager::getInstace()->getPhysicsShapeCache()->createBodyWithName("Attack_2");
	attackBody->setDynamic(false);
	attackBody->setRotationEnable(false);
	attackBody->setGravityEnable(false);
	attackBody->setCategoryBitmask(ENEMIES_ATTACK_CATEGORY_BITMASK);
	attackBody->setCollisionBitmask(ENEMIES_ATTACK_COLLISION_BITMASK);
	attackBody->setContactTestBitmask(ALLSET_BITMASK);
	attackBody->setMass(0.0f);

	attackSprite->setPhysicsBody(attackBody);
}
void BossCharacter::jumpAttack_1() {
	attackSprite->setPosition(Vec2::ZERO);
	characterState = State::ATTACK;
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	characterSpriteAnimation->stopAllActions();

	animation = createAnimation("Jump_Attack_1", 8, 0.05);
	Animate* animate = Animate::create(animation);
	animate->retain();
	auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), nullptr);
	characterSpriteAnimation->runAction(seq);

	cocos2d::PhysicsBody* attackBody = GameManager::getInstace()->getPhysicsShapeCache()->createBodyWithName("Jump_Attack_1");
	attackBody->setDynamic(false);
	attackBody->setRotationEnable(false);
	attackBody->setGravityEnable(false);
	attackBody->setCategoryBitmask(ENEMIES_ATTACK_CATEGORY_BITMASK);
	attackBody->setCollisionBitmask(ENEMIES_ATTACK_COLLISION_BITMASK);
	attackBody->setContactTestBitmask(ALLSET_BITMASK);
	attackBody->setMass(0.0f);
	auto move = MoveBy::create(0.8, Vec2(0, visibleSize.height / 4));
	characterSprite->runAction(move);
	attackSprite->setPhysicsBody(attackBody);
}
void BossCharacter::jumpAttack_2() {
	attackSprite->setPosition(Vec2::ZERO);
	characterState = State::ATTACK;
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	characterSpriteAnimation->stopAllActions();

	animation = createAnimation("Jump_Attack_2", 7, 0.05);
	Animate* animate = Animate::create(animation);
	animate->retain();
	auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), nullptr);
	characterSpriteAnimation->runAction(seq);

	cocos2d::PhysicsBody* attackBody = GameManager::getInstace()->getPhysicsShapeCache()->createBodyWithName("Jump_Attack_2");
	attackBody->setDynamic(false);
	attackBody->setRotationEnable(false);
	attackBody->setGravityEnable(false);
	attackBody->setCategoryBitmask(ENEMIES_ATTACK_CATEGORY_BITMASK);
	attackBody->setCollisionBitmask(ENEMIES_ATTACK_COLLISION_BITMASK);
	attackBody->setContactTestBitmask(ALLSET_BITMASK);
	attackBody->setMass(0.0f);
	auto move = MoveBy::create(0.8, Vec2(0, visibleSize.height / 4));
	characterSprite->runAction(move);
	attackSprite->setPhysicsBody(attackBody);
}
void BossCharacter::run() {
	characterState = State::RUN;
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	characterSpriteAnimation->stopAllActions();

	animation = createAnimation("Run", 6, 0.05);
	Animate* animate = Animate::create(animation);
	animate->retain();
	auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), nullptr);
	characterSpriteAnimation->runAction(seq);

	if (characterDirection == Direction::RIGHT) {
		auto move = MoveBy::create(0.3, Vec2(visibleSize.width / 6, 0));
		characterSprite->runAction(move);
	}
	else
	{
		auto move = MoveBy::create(0.6, Vec2(-visibleSize.width / 6, 0));
		characterSprite->runAction(move);
	}
}
void BossCharacter::walk() {
	characterState = State::WALK;
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	characterSpriteAnimation->stopAllActions();

	animation = createAnimation("Walk", 12, 0.05);
	Animate* animate = Animate::create(animation);
	animate->retain();
	auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), nullptr);
	characterSpriteAnimation->runAction(seq);

	if (characterDirection == Direction::RIGHT) {
		auto move = MoveBy::create(0.6, Vec2(visibleSize.width / 8, 0));
		characterSprite->runAction(move);
	}
	else
	{
		auto move = MoveBy::create(1.2, Vec2(-visibleSize.width / 8, 0));
		characterSprite->runAction(move);
	}
}
void BossCharacter::skill_1() {
	attackSprite->setPosition(Vec2::ZERO);
	characterState = State::ATTACK;
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	characterSpriteAnimation->stopAllActions();

	animation = createAnimation("Charge", 7, 0.05);
	Animate* animate = Animate::create(animation);
	animate->retain();
	auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), nullptr);
	characterSpriteAnimation->runAction(seq);
	
	cocos2d::PhysicsBody* attackBody = GameManager::getInstace()->getPhysicsShapeCache()->createBodyWithName("Charge");
	attackBody->setDynamic(false);
	attackBody->setRotationEnable(false);
	attackBody->setGravityEnable(false);
	attackBody->setCategoryBitmask(ENEMIES_ATTACK_CATEGORY_BITMASK);
	attackBody->setCollisionBitmask(ENEMIES_ATTACK_COLLISION_BITMASK);
	attackBody->setContactTestBitmask(ALLSET_BITMASK);
	attackBody->setMass(0.0f);
	if (characterDirection == Direction::RIGHT) {
		auto move = MoveBy::create(0.7, Vec2(visibleSize.width / 3, 0));
		characterSprite->runAction(move);
	}
	else
	{
		auto move = MoveBy::create(0.7, Vec2(-visibleSize.width / 3, 0));
		characterSprite->runAction(move);
	}
	attackSprite->setPhysicsBody(attackBody);
}
void BossCharacter::skill_2() {
	attackSprite->setPosition(Vec2::ZERO);
	characterState = State::ATTACK;
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	characterSpriteAnimation->stopAllActions();

	animation = createAnimation("Shoot_Bow", 1.2, 0.05);
	Animate* animate = Animate::create(animation);
	animate->retain();
	auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), nullptr);
	characterSpriteAnimation->runAction(seq);

	arrow = Sprite::create(floder + "arrow.png");
	arrow->setScale(0.5);
	arrow->setPosition(Vec2::ZERO);
	characterSprite->addChild(arrow);
	PhysicsBody* arrowBody = PhysicsBody::createBox(arrow->getContentSize());
	arrowBody->setDynamic(false);
	arrowBody->setRotationEnable(false);
	arrowBody->setGravityEnable(false);
	arrowBody->setCategoryBitmask(ENEMIES_ATTACK_CATEGORY_BITMASK);
	arrowBody->setCollisionBitmask(ENEMIES_ATTACK_COLLISION_BITMASK);
	arrowBody->setContactTestBitmask(ALLSET_BITMASK);
	arrowBody->setMass(0.0f);
	arrow->setPhysicsBody(arrowBody);
	if (characterDirection == Direction::RIGHT) {
		auto move = MoveBy::create(1, Vec2(-visibleSize.width, 0));
		auto callback = CallFunc::create([this]() {
			arrow->removeFromParent();
		});
		auto seq = Sequence::create(move, callback, nullptr);
		arrow->runAction(seq);
	}
	else
	{
		auto move = MoveBy::create(1, Vec2(visibleSize.width, 0));
		auto callback = CallFunc::create([this]() {
			arrow->removeFromParent();
		});
		auto seq = Sequence::create(move, callback, nullptr);
		arrow->runAction(seq);
	}

}
void BossCharacter::skill_3() {
	characterState = State::BLOCK;
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	characterSpriteAnimation->stopAllActions();

	animation = createAnimation("Block", 9, 0.1);
	Animate* animate = Animate::create(animation);
	animate->retain();
	auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), nullptr);
	characterSpriteAnimation->runAction(seq);
}

void BossCharacter::attack() {
	int type = rand() % 2 + 1;
	if (type == 1) {
		attack_1();
	}
	else if (type == 2) {
		attack_2();
	}
	numAttack++;
}
void BossCharacter::jumpAttack() {
	int type = rand() % 2 + 1;
	if (type == 1) {
		jumpAttack_1();
	}
	else if (type == 2) {
		jumpAttack_2();
	}
	numAttack++;
}
void BossCharacter::skill(int type) {
	if (type == 1) {
		skill_1();	
	}
	else if (type == 2) {
		skill_2();
	}
	else if (type == 3) {
		skill_3();
	}
	numAttack=0;
}

void BossCharacter::takeHit(float dame)
{
	characterStats.HP -= dame;
	characterStats.UpdateStatsBar();
	
	characterState = State::HURT;
	if (attackSprite->getPhysicsBody() != nullptr)
		attackSprite->getPhysicsBody()->removeFromWorld();

	characterSpriteAnimation->stopAllActions();

	animation = createAnimation("Hurt", 8, 0.1);
	Animate* animate = Animate::create(animation);
	animate->retain();
	auto seq = Sequence::create(animate, CallFuncN::create(CC_CALLBACK_0(BossCharacter::idle, this)), nullptr);
	characterSpriteAnimation->runAction(seq);
	
	if (characterStats.HP <= 0.0f) {
		death();
		GameManager::getInstace()->getMission()->updateMission(5);
	}
}
