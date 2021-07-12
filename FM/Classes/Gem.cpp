#include "Gem.h"
#include "Definitions.h"

USING_NS_CC;

Gem::Gem()
{
	gemSprite = Sprite::create();
	gemImage = Sprite::create("sprites/Gem.png");
	gemBody = PhysicsBody::createBox(gemImage->getContentSize());
	gemBody->setDynamic(true);
	gemBody->setCategoryBitmask(GEM_CATEGORY_BITMASK);
	gemBody->setCollisionBitmask(GEM_COLLISION_BITMASK);
	gemBody->setContactTestBitmask(ALLSET_BITMASK);
	gemSprite->setPhysicsBody(gemBody);
	gemSprite->addChild(gemImage);
}

cocos2d::Sprite* Gem::getSprite()
{
	return gemSprite;
}