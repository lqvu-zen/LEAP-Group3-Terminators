#include "Item.h"
#include "Definitions.h"

USING_NS_CC;

Item::Item(ItemType _itemType)
{
	itemType = _itemType;

	switch (itemType)
	{
	case Item::ItemType::HP_POTION:
		itemStats.SetCItemStats(50.0f);
		break;
	case Item::ItemType::MP_POTION:
		itemStats.SetCItemStats(0.0f, 50.0f);
		break;
	default:
		break;
	}

	itemSprite = nullptr;
}

cocos2d::Sprite* Item::getSprite()
{
	if (itemSprite == nullptr) {
		itemSprite = Sprite::create();

		switch (itemType)
		{
		case Item::ItemType::GEM:
			itemImage = Sprite::create("sprites/item/Gem.png");
			break;
		case Item::ItemType::HP_POTION:
			itemImage = Sprite::create("sprites/item/StaticBigHealthPotion.png");
			break;
		case Item::ItemType::MP_POTION:
			itemImage = Sprite::create("sprites/item/StaticBigManaPotion.png");
			break;
		case Item::ItemType::GOLD:
			itemImage = Sprite::create("sprites/item/StaticCoin.png");
			break;
		default:
			break;
		}
		itemBody = PhysicsBody::createBox(itemImage->getContentSize());

		itemBody->setDynamic(false);

		itemBody->setCategoryBitmask(ITEM_CATEGORY_BITMASK);
		itemBody->setCollisionBitmask(ITEM_COLLISION_BITMASK);
		itemBody->setContactTestBitmask(ALLSET_BITMASK);

		itemSprite->setPhysicsBody(itemBody);
		itemSprite->addChild(itemImage);
	}

	return itemSprite;
}

Item::ItemType Item::getType()
{
	return itemType;
}

Stats Item::getStats()
{
	return itemStats;
}

void Item::setPosition(cocos2d::Vec2 position) {
	itemSprite->setPosition(position);
	itemImage->setPosition(Vec2::ZERO);
}
