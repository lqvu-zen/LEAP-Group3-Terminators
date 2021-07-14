#include "Item.h"
#include "Definitions.h"

USING_NS_CC;

Item::Item(ItemType _itemType)
{
	itemType = _itemType;

	itemSprite = Sprite::create();

	switch (itemType)
	{
	case Item::ItemType::GEM:
		itemImage = Sprite::create("sprites/Gem.png");
		itemBody = PhysicsBody::createBox(itemImage->getContentSize());
		break;
	case Item::ItemType::HP_POTION:
		break;
	case Item::ItemType::MP_POTION:
		break;
	default:
		break;
	}

	itemBody->setDynamic(true);

	itemBody->setCategoryBitmask(ITEM_CATEGORY_BITMASK);
	itemBody->setCollisionBitmask(ITEM_COLLISION_BITMASK);
	itemBody->setContactTestBitmask(ALLSET_BITMASK);

	itemSprite->setPhysicsBody(itemBody);
	itemSprite->addChild(itemImage);
}

cocos2d::Sprite* Item::getSprite()
{
	return itemSprite;
}

Item::ItemType Item::getType()
{
	return itemType;
}
