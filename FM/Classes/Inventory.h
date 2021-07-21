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

	Item* getItem(Item::ItemType itemType);

	cocos2d::Sprite* GetSprite();

	void updateInventory();

	void addGold(int num);
	bool exceptGold(int num);
private:
	int gold;

	cocos2d::Label* goldLabel;

	int itemCount;
	std::map<Item::ItemType, std::list<Item *>> itemMap;

	int itemSlot;

	cocos2d::Sprite* inventorySprite;

	cocos2d::TMXTiledMap* inventoryMap;
};

#endif // __INVENTORY_H__
