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

MonsterCharacter::MonsterCharacter(cocos2d::Scene* _scene, int level) {

	scene = _scene;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	string floder = StringUtils::format("plist/Monster_%i/", level);

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

	auto monsterBody = PhysicsBody::createBox(monster->getContentSize());
	monsterBody->setDynamic(true);
	monsterBody->setRotationEnable(false);
	monster->setPhysicsBody(monsterBody);

	auto animate = Animate::create(MonsterCharacter::createAnimation("Idle-", 16, 0.1));
	animate->retain();
	monster->runAction(RepeatForever::create(animate));

}

void MonsterCharacter::attack() {
	//animation->release();
	animation = MonsterCharacter::createAnimation("Attack-", 19, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
	
	auto bullet = Sprite::create("plist/Monster_1/poisonspit.png");
	auto bodyBullet = PhysicsBody::createBox(bullet->getContentSize());
	bullet->setPhysicsBody(bodyBullet);
	bodyBullet->setDynamic(false);
	bullet->setPosition(monster->getPosition());
	bullet->setScale(0.25);
	scene->addChild(bullet);

	auto shootAction = MoveBy::create(5, Vec2(-visibleSize.width, 0));
	bullet->runAction(shootAction);
}

void MonsterCharacter::death() {
	//animation->release();
	animation = MonsterCharacter::createAnimation("Death-", 24, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void MonsterCharacter::hurt() {
	//animation->release();
	animation = MonsterCharacter::createAnimation("Hurt-", 4, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void MonsterCharacter::idle() {
	//animation->release();
	animation = MonsterCharacter::createAnimation("Idle-", 48, 0.1);
	auto animate = Animate::create(animation);
	animate->retain();
	monster->runAction(animate);
}

void MonsterCharacter::jump() {
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