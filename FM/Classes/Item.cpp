#include "Item.h"
#include "Definitions.h"

USING_NS_CC;

Item::Item(ItemType _itemType)
{
	getValue(_itemType);

	itemType = _itemType;

	itemStats.SetCItemStats(
		itemValue["STATS"]["HP"].GetFloat(), 
		itemValue["STATS"]["MP"].GetFloat(),
		itemValue["STATS"]["ATK"].GetFloat(),
		itemValue["STATS"]["DEF"].GetFloat()
	);
	itemStats.SetNCItemStats(
		itemValue["STATS"]["MAX_HP"].GetFloat(),
		itemValue["STATS"]["MAX_MP"].GetFloat(),
		itemValue["STATS"]["MAX_ATK"].GetFloat(),
		itemValue["STATS"]["MAX_DEF"].GetFloat(),
		itemValue["STATS"]["MAX_JUMP"].GetInt()
	);

	itemSprite = nullptr;
}

cocos2d::Sprite* Item::getSprite()
{
	if (itemSprite == nullptr) {
		itemSprite = Sprite::create();

		itemImage = Sprite::create(itemValue["SPRITES"]["PNG"].GetString());
			
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

inline void Item::getValue(ItemType _itemType)
{
	auto buf = FileUtils::getInstance()->getStringFromFile("res/items.json");

	itemDocument.Parse<0>(buf.c_str());
	if (itemDocument.HasParseError()) {
		CCLOG("ERROR: Character document not found!");
	}
	else {
		if (itemDocument.HasMember("ITEM")) {
			rapidjson::Value& itemList = itemDocument["ITEM"];
			for (rapidjson::SizeType i = 0; i < itemList.Size(); i++) {
				if (itemList[i]["TYPE"].GetInt() == int(_itemType)) {
					itemValue = itemList[i];
				}
			}
		}
	}
}
