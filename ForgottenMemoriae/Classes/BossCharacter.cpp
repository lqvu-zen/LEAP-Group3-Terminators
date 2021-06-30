/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "BossCharacter.h"
#include "Definitions.h"

USING_NS_CC;

BossCharacter::BossCharacter(cocos2d::Scene* scene, int level) {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

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


	monster = Sprite::createWithSpriteFrameName("Idle1.png");
	monster->setScale(0.25);

	/*auto shapeCache = PhysicsShapeCache::getInstance();
	shapeCache->addShapesWithFile(boss + "body.plist");
	shapeCache->setBodyOnSprite("Idle1", monster);*/
	
	auto animate = Animate::create(BossCharacter::createAnimation("Idle", 16, 0.1));
	animate->retain();
	monster->runAction(RepeatForever::create(animate));

	monster->setFlippedX(true);
}

void BossCharacter::attack() {
	int type = rand() % 2 + 1;
	if (type == 1) {
		attack_1();
	}
	else {
		attack_2();
	}
}

void BossCharacter::attack_1() {
	//animation->release();
	animation = BossCharacter::createAnimation("Attack_1", 8, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	cocos2d::DelayTime* delay = cocos2d::DelayTime::create(1);
	monster->runAction(animate);
}

void BossCharacter::attack_2() {
	//animation->release();
	animation = BossCharacter::createAnimation("Attack_2", 7, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void BossCharacter::block() {
	//animation->release();
	animation = BossCharacter::createAnimation("Block", 9, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void BossCharacter::charge() {
	//animation->release();
	animation = BossCharacter::createAnimation("Charge", 7, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
	auto move = MoveBy::create(0.7, Vec2(-30, 0));
	monster->runAction(move);
}

void BossCharacter::death() {
	//animation->release();
	animation = BossCharacter::createAnimation("Death", 15, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void BossCharacter::hurt() {
	//animation->release();
	animation = BossCharacter::createAnimation("Hurt", 8, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void BossCharacter::idle() {
	//animation->release();
	animation = BossCharacter::createAnimation("Idle", 16, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void BossCharacter::jump() {
	//animation->release();
	animation = BossCharacter::createAnimation("Jump", 10, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void BossCharacter::jump_attack() {
	int type = rand() % 2 + 1;
	if (type == 1) {
		jump_attack_1();
	}
	else {
		jump_attack_2();
	}
}

void BossCharacter::jump_attack_1() {
	//animation->release();
	animation = BossCharacter::createAnimation("Jump_Attack_1", 8, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void BossCharacter::jump_attack_2() {
	//animation->release();
	animation = BossCharacter::createAnimation("Jump_Attack_2", 7, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void BossCharacter::run() {
	//animation->release();
	animation = BossCharacter::createAnimation("Run", 6, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
	auto move = MoveBy::create(0.6, Vec2(-30, 0));
	monster->runAction(move);
}

void BossCharacter::shoot_bow() {
	//animation->release();
	animation = BossCharacter::createAnimation("Shoot_Bow", 12, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void BossCharacter::walk() {
	//animation->release();
	animation = BossCharacter::createAnimation("Walk", 12, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
	auto move = MoveBy::create(1.2, Vec2(-10, 0));
	monster->runAction(move);
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