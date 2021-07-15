#include "Inventory.h"

USING_NS_CC;

Inventory::Inventory()
{
	init();
}

void Inventory::init()
{
	itemCount = 0;
	itemMap.clear();

	gold = 100;

	inventorySprite = nullptr;
}

void Inventory::addItem(Item * _item)
{
	itemCount++;
	itemMap[_item->getType()].push_back(_item);
}

cocos2d::Sprite * Inventory::GetSprite()
{
	if (inventorySprite == nullptr) {
		//init sprites
		inventorySprite = cocos2d::Sprite::create();

		//init map
		inventoryMap = TMXTiledMap::create("map/Inventory.tmx");
		//inventoryMap->setScale(SCALE_RATIO);

		inventoryMap->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

		inventorySprite->addChild(inventoryMap);
	}

	return inventorySprite;
}
