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

	itemSlot = 0;

	gold = 10;

	inventorySprite = nullptr;
}

void Inventory::addItem(Item * _item)
{
	if (_item->getType() == Item::ItemType::GOLD) {
		gold++;
		return;
	}

	itemCount++;
	itemMap[_item->getType()].push_back(_item);
}

Item * Inventory::getItem(Item::ItemType itemType)
{
	Item* item = nullptr;
	if (itemMap[itemType].size() > 0) {
		item = itemMap[itemType].back();
		itemMap[itemType].pop_back();
	}
	return item;
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

		auto characterGroup = inventoryMap->getObjectGroup("Character");
		auto characterObjects = characterGroup->getObjects();

		//add gold
		TTFConfig labelConfig;
		labelConfig.fontFilePath = "fonts/arial.ttf";
		labelConfig.fontSize = 8;
		labelConfig.glyphs = GlyphCollection::DYNAMIC;
		labelConfig.outlineSize = 0;
		labelConfig.customGlyphs = nullptr;
		labelConfig.distanceFieldEnabled = false;

		std::string goldCount = StringUtils::format("%d", gold);

		goldLabel = Label::createWithTTF(labelConfig, goldCount);

		for (auto obj : characterObjects) {
			auto dict = obj.asValueMap();

			if (dict["name"].asString() == "Gold") {
				goldLabel->setPosition(
					Vec2(
						dict["x"].asFloat(), dict["y"].asFloat()
					)
				);

				goldLabel->setTag(int(Item::ItemType::GOLD) + TAG_PADDING);
				inventoryMap->addChild(goldLabel);
			}
		}
	}

	return inventorySprite;
}

void Inventory::updateInventory()
{
	TTFConfig labelConfig;
	labelConfig.fontFilePath = "fonts/arial.ttf";
	labelConfig.fontSize = 8;
	labelConfig.glyphs = GlyphCollection::DYNAMIC;
	labelConfig.outlineSize = 1;
	labelConfig.customGlyphs = nullptr;
	labelConfig.distanceFieldEnabled = false;

	//update gold
	std::string goldCount = StringUtils::format("%d", gold);

	goldLabel->setString(goldCount);

	//update item
	auto itemGroup = inventoryMap->getObjectGroup("Items");
	auto itemObjects = itemGroup->getObjects();

	for (auto itemList : itemMap) {
		//update
		if (inventoryMap->getChildByTag(int(itemList.first) + TAG_PADDING) != nullptr) {
			auto itemImage = inventoryMap->getChildByTag(int(itemList.first) + TAG_PADDING);
			auto countLabel = static_cast<Label*>(itemImage->getChildByName("CountItem"));

			int itemCounting = int(itemList.second.size());
			std::string itemCount = StringUtils::format("%d", itemCounting);

			countLabel->setString(itemCount);
		} else {
			if (itemList.second.size() > 0) {
				auto dict = itemObjects[itemSlot++].asValueMap();
				
				auto itemImage = itemList.second.front()->getSprite();
				itemImage->setPosition(
					Vec2(
						dict["x"].asFloat(), dict["y"].asFloat()
					)
				);
				
				itemImage->setScale(0.5f);

				itemImage->setTag(int(itemList.first) + TAG_PADDING);
				inventoryMap->addChild(itemImage);

				//add count item
				std::string itemCount = StringUtils::format("%d", 1);

				auto itemCountLabel = Label::createWithTTF(labelConfig, itemCount);
				itemCountLabel->setScale(1.5f);

				itemCountLabel->setName("CountItem");
				itemImage->addChild(itemCountLabel);
			}
		}
	}
}

void Inventory::addGold(int num) {
	gold += num;
}
bool Inventory::exceptGold(int num) {
	if (gold >= num) {
		gold -= num;
		return true;
	}
	return false;
}
