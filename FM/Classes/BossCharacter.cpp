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
	//Nếu nhân vật chạy ra khỏi nơi đánh nhau thì boss quay lại vị trí ban đầu
	if (abs(position.x - positionPlayer.x) > visibleSize.width / 2) {
		/*if (position.x == characterSprite->getPosition().x) {
			action = 0;
			updateAnimation(State::IDLE, true);
		}
		else {
			if (characterDirection == Direction::LEFT) {
				setDirection(Direction::RIGHT);
			}
			else {
				setDirection(Direction::LEFT);
			}
			action = 1;
			walk();
		}*/
		updateAnimation(State::IDLE, true);
		action = 0;
	}
	else {
		if (abs(positionPlayer.x - characterSprite->getPosition().x) <= visibleSize.width / 6) {
			if (positionPlayer.y > characterSprite->getPosition().y + characterSprite->getContentSize().height) {
				if (action == 0) {
					jumpAttack();
					action = 2;
				}
				else if (action == 2) {
					updateAnimation(State::IDLE, true);
					action = 0;
				}

			}
			else {
				if (action == 0) {
					attack();
					action = 2;
				}
				else if (action == 2) {
					updateAnimation(State::IDLE, true);
					action = 0;
				}
				
			}
		}
		else if (abs(positionPlayer.x - characterSprite->getPosition().x) <= visibleSize.width / 2) {
			//action = 0;
			run();
		}
		else {
			updateAnimation(State::IDLE, true);
			action = 0;
		}
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
		attackBody->setCategoryBitmask(ENEMIES_ATTACK_CATEGORY_BITMASK);
		attackBody->setCollisionBitmask(ENEMIES_ATTACK_COLLISION_BITMASK);
		attackBody->setContactTestBitmask(ALLSET_BITMASK);
		attackBody->setMass(0.0f);

		attackSprite->setPhysicsBody(attackBody);
	}
	else if (type == 2) {
		updateAnimation(State::ATTACK2);
		cocos2d::PhysicsBody* attackBody = shapeCache->createBodyWithName("Attack_2");
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

void BossCharacter::jumpAttack() {
	int type = rand() % 2 + 1;
	if (type == 1) {
		updateAnimation(State::JUMPATTACK1);
		cocos2d::PhysicsBody* attackBody = shapeCache->createBodyWithName("Jump_Attack_1");
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
	else if (type == 2) {
		updateAnimation(State::JUMPATTACK2);
		cocos2d::PhysicsBody* attackBody = shapeCache->createBodyWithName("Jump_Attack_2");
		attackBody->setDynamic(false);
		attackBody->setRotationEnable(false);
		attackBody->setGravityEnable(false);
		attackBody->setCategoryBitmask(ENEMIES_ATTACK_CATEGORY_BITMASK);
		attackBody->setCollisionBitmask(ENEMIES_ATTACK_COLLISION_BITMASK);
		attackBody->setContactTestBitmask(ALLSET_BITMASK);
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

void BossCharacter::walk() {
	updateAnimation(State::WALK, true);
	if (characterDirection == Direction::RIGHT) {
		auto move = MoveTo::create(10, Vec2(position.x, position.y));
		characterSprite->runAction(move);
	}
	else
	{
		auto move = MoveTo::create(10, Vec2(position.x, position.y));
		characterSprite->runAction(move);
	}
}

void BossCharacter::death() {
	updateAnimation(State::DEATH);
	auto die = MoveTo::create(0, Vec2(-1000 * visibleSize.width, 0));
	cocos2d::DelayTime* delay = cocos2d::DelayTime::create(2);
	auto seq = Sequence::create(delay, die, nullptr);
	characterSprite->runAction(seq);
}