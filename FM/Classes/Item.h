#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

using namespace std;

class Item 
{
public:
	enum class ItemType {
		GEM, HP_POTION, MP_POTION
	};

	Item(ItemType _itemType);

	cocos2d::Sprite* getSprite();

	Item::ItemType getType();
private:
	cocos2d::Sprite* itemSprite;
	cocos2d::Sprite* itemImage;
	cocos2d::PhysicsBody* itemBody;
    
	Item::ItemType itemType;
};

#endif // __ITEM_H__
