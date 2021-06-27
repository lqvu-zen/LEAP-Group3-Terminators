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

#include "MonsterCharacter.h"
#include "Definitions.h"

USING_NS_CC;

MonsterCharacter::MonsterCharacter(cocos2d::Scene* scene) {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	SpriteBatchNode* spriteNode = SpriteBatchNode::create("plist/Boss_1/Attack_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Boss_1/Attack_1.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create("plist/Boss_1/Attack_2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Boss_1/Attack_2.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create("plist/Boss_1/Block.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Boss_1/Block.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create("plist/Boss_1/Charge.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Boss_1/Charge.plist");

	/*SpriteBatchNode**/ spriteNode = SpriteBatchNode::create("plist/Boss_1/Death.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Boss_1/Death.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create("plist/Boss_1/Hurt.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Boss_1/Hurt.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create("plist/Boss_1/Jump.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Boss_1/Jump.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create("plist/Boss_1/Jump_Attack_1.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Boss_1/Jump_Attack_1.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create("plist/Boss_1/Jump_Attack_2.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Boss_1/Jump_Attack_2.plist");

	/*SpriteBatchNode**/ spriteNode = SpriteBatchNode::create("plist/Boss_1/Idle.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Boss_1/Idle.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create("plist/Boss_1/Run.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Boss_1/Run.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create("plist/Boss_1/Shoot_Bow.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Boss_1/Shoot_Bow.plist");

	/*SpriteBatchNode* */spriteNode = SpriteBatchNode::create("plist/Boss_1/Walk.png");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("plist/Boss_1/Walk.plist");


	monster = Sprite::createWithSpriteFrameName("Idle1.png");

	auto animate = Animate::create(MonsterCharacter::createAnimation("Idle", 16, 0.1));
	animate->retain();
	monster->runAction(RepeatForever::create(animate));
}

void MonsterCharacter::attack_1() {
	animation->release();
	animation = MonsterCharacter::createAnimation("Attack_1", 8, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void MonsterCharacter::attack_2() {
	animation->release();
	animation = MonsterCharacter::createAnimation("Attack_2", 7, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void MonsterCharacter::block() {
	animation->release();
	animation = MonsterCharacter::createAnimation("Block", 9, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void MonsterCharacter::charge() {
	animation->release();
	animation = MonsterCharacter::createAnimation("Charge", 7, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void MonsterCharacter::death() {
	animation->release();
	animation = MonsterCharacter::createAnimation("Death", 15, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void MonsterCharacter::hurt() {
	animation->release();
	animation = MonsterCharacter::createAnimation("Hurt", 8, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void MonsterCharacter::idle() {
	animation->release();
	animation = MonsterCharacter::createAnimation("Idle", 16, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void MonsterCharacter::jump() {
	animation->release();
	animation = MonsterCharacter::createAnimation("Jump", 10, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void MonsterCharacter::jump_attack_1() {
	animation->release();
	animation = MonsterCharacter::createAnimation("Jump_Attack_1", 8, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void MonsterCharacter::jump_attack_2() {
	animation->release();
	animation = MonsterCharacter::createAnimation("Jump_Attack_2", 7, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void MonsterCharacter::run() {
	animation->release();
	animation = MonsterCharacter::createAnimation("Run", 6, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void MonsterCharacter::shoot_bow() {
	animation->release();
	animation = MonsterCharacter::createAnimation("Shoot_Bow", 12, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void MonsterCharacter::walk() {
	animation->release();
	animation = MonsterCharacter::createAnimation("Walk", 12, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

cocos2d::Animation* MonsterCharacter::createAnimation(string prefixName, int pFramesOrder, float delay) {
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