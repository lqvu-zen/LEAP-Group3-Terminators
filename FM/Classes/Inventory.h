#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Item.h"

using namespace std;

class Inventory 
{
public:
	
	Inventory();

	void init();

	void addItem(Item* _item);

	cocos2d::Sprite* getSprite();
private:
	int gold;

	int itemCount;
	std::map<Item::ItemType, std::list<Item *>> itemMap;

	cocos2d::Sprite* inventorySprite;
	cocos2d::Sprite* inventoryImage;
};

#endif // __INVENTORY_H__
