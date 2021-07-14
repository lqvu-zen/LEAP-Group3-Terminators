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

	//load sprites
	inventorySprite = cocos2d::Sprite::create();
	inventoryImage = cocos2d::Sprite::create("sprites/Inventory.png");

	inventorySprite->addChild(inventoryImage);

	inventorySprite->setScale(3.0f);
}

void Inventory::addItem(Item * _item)
{
	itemCount++;
	itemMap[_item->getType()].push_back(_item);
}

cocos2d::Sprite * Inventory::getSprite()
{
	return inventorySprite;
}
