#ifndef __NPC_H__
#define __NPC_H__

#include "cocos2d.h"
#include "Definitions.h"


class NPC
{
public:

	NPC();
	NPC(cocos2d::Vec2 position);

	void setPosition(cocos2d::Vec2 position);

	cocos2d::Sprite* getSprite();
private:
	

	cocos2d::Sprite* characterSprite;
	cocos2d::Sprite* characterSpriteAnimation;
	cocos2d::PhysicsBody* characterPhysicsBody;
	cocos2d::Vector<cocos2d::SpriteFrame*> anim_NPC;

	cocos2d::Size characterSize;

};

#endif // __NPC_H__
