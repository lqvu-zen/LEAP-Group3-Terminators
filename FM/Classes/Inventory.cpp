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

	gold = 10;

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

				inventoryMap->addChild(goldLabel);
			}
		}
	}

	return inventorySprite;
}

void Inventory::updateInventory()
{
	std::string goldCount = StringUtils::format("%d", gold);

	goldLabel->setString(goldCount);
}
