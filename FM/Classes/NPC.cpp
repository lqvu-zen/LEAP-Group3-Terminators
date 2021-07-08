#include "NPC.h"

USING_NS_CC;

NPC::NPC()
{
	characterSprite = Sprite::create();
	
	//Animation
	anim_NPC.reserve(4);
	anim_NPC.pushBack(SpriteFrame::create("sprites/NPC/Old_man_idle.png", Rect(0, 0, 48, 48)));
	anim_NPC.pushBack(SpriteFrame::create("sprites/NPC/Old_man_idle.png", Rect(48, 0, 48, 48)));
	anim_NPC.pushBack(SpriteFrame::create("sprites/NPC/Old_man_idle.png", Rect(96, 0, 48, 48)));
	anim_NPC.pushBack(SpriteFrame::create("sprites/NPC/Old_man_idle.png", Rect(144, 0, 48, 48)));
	Animation* NPCAnimation = Animation::createWithSpriteFrames(anim_NPC, 0.5f);
	Animate *NPCAnimate = Animate::create(NPCAnimation);
	characterSpriteAnimation = Sprite::createWithSpriteFrame(anim_NPC.front());
	characterSpriteAnimation->runAction(RepeatForever::create(NPCAnimate));
	characterSprite->addChild(characterSpriteAnimation);
	characterSprite->setScale(2.0f);

	//PhysicsBody
	characterSize = characterSpriteAnimation->getContentSize();
	characterPhysicsBody = PhysicsBody::createBox(characterSize);
	characterPhysicsBody->setDynamic(true);
	characterPhysicsBody->setRotationEnable(false);
	characterPhysicsBody->setCategoryBitmask(NONPLAYER_CATEGORY_BITMASK);
	characterPhysicsBody->setCollisionBitmask(NONPLAYER_COLLISION_BITMASK);
	characterPhysicsBody->setContactTestBitmask(ALLSET_BITMASK);
	characterSprite->setPhysicsBody(characterPhysicsBody);
}

NPC::NPC(cocos2d::Vec2 position)
{
	NPC();
	setPosition(position);
}

void NPC::setPosition(cocos2d::Vec2 position)
{
	characterSprite->setPosition(position);
	characterSpriteAnimation->setPosition(Vec2::ZERO);
	
}



cocos2d::Sprite * NPC::getSprite()
{
	return characterSprite;
}

