#ifndef __Portal_H__
#define __Portal_H__

#include "cocos2d.h"
#include "Definitions.h"


class Portal
{
public:

	Portal();
	Portal(cocos2d::Vec2 position);

	void setPosition(cocos2d::Vec2 position);

	cocos2d::Sprite* getSprite();
private:
	

	cocos2d::Sprite* portalSprite;
	cocos2d::Sprite* portalSpriteAnimation;
	cocos2d::PhysicsBody* portalPhysicsBody;
	cocos2d::Vector<cocos2d::SpriteFrame*> anim_Portal;

	cocos2d::Size portalSize;

};

#endif // __Portal_H__
