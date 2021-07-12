#include "Portal.h"

USING_NS_CC;

Portal::Portal()
{
	portalSprite = Sprite::create();
	
	//Animation
	anim_Portal.reserve(8);
	anim_Portal.pushBack(SpriteFrame::create("sprites/PortalSpriteSheet.png", Rect(0, 0, 64, 64)));
	anim_Portal.pushBack(SpriteFrame::create("sprites/PortalSpriteSheet.png", Rect(64, 0, 64, 64)));
	anim_Portal.pushBack(SpriteFrame::create("sprites/PortalSpriteSheet.png", Rect(128, 0, 64, 64)));
	anim_Portal.pushBack(SpriteFrame::create("sprites/PortalSpriteSheet.png", Rect(192, 0, 64, 64)));
	anim_Portal.pushBack(SpriteFrame::create("sprites/PortalSpriteSheet.png", Rect(256, 0, 64, 64)));
	anim_Portal.pushBack(SpriteFrame::create("sprites/PortalSpriteSheet.png", Rect(320, 0, 64, 64)));
	anim_Portal.pushBack(SpriteFrame::create("sprites/PortalSpriteSheet.png", Rect(384, 0, 64, 64)));
	anim_Portal.pushBack(SpriteFrame::create("sprites/PortalSpriteSheet.png", Rect(448, 0, 64, 64)));
	Animation* NPCAnimation = Animation::createWithSpriteFrames(anim_Portal, 0.2f);
	Animate *NPCAnimate = Animate::create(NPCAnimation);
	portalSpriteAnimation = Sprite::createWithSpriteFrame(anim_Portal.front());
	portalSpriteAnimation->runAction(RepeatForever::create(NPCAnimate));
	portalSprite->addChild(portalSpriteAnimation);
	portalSprite->setScale(2.0f);

	//PhysicsBody
	portalSize = Size(32,64);
	portalPhysicsBody = PhysicsBody::createBox(portalSize);
	portalPhysicsBody->setDynamic(false);
	portalPhysicsBody->setRotationEnable(false);
	portalPhysicsBody->setCategoryBitmask(PORTAL_CATEGORY_BITMASK);
	//portalPhysicsBody->setCollisionBitmask(NONPLAYER_COLLISION_BITMASK);
	portalPhysicsBody->setContactTestBitmask(ALLSET_BITMASK);
	portalSprite->setPhysicsBody(portalPhysicsBody);
}

Portal::Portal(cocos2d::Vec2 position)
{
	Portal();
	setPosition(position);
}

void Portal::setPosition(cocos2d::Vec2 position)
{
	portalSprite->setPosition(position);
	portalSpriteAnimation->setPosition(Vec2::ZERO);
	
}



cocos2d::Sprite * Portal::getSprite()
{
	return portalSprite;
}

