#include "Skill.h"

Skill::Skill(int type)
{
	//load data
	getValue(type);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
		skillValue["SPRITES"]["PLIST"].GetString(), 
		skillValue["SPRITES"]["PNG"].GetString()
	);

	skillStats[Skill::SkillType::Normal].SetSkillStats(
		skillValue["NORMAL"]["STATS"]["ATK"].GetFloat(), 
		skillValue["NORMAL"]["STATS"]["MP"].GetFloat(),
		skillValue["NORMAL"]["STATS"]["COUNT_DOWN"].GetFloat()
	);
	skillStats[Skill::SkillType::Special].SetSkillStats(
		skillValue["SPECIAL"]["STATS"]["ATK"].GetFloat(),
		skillValue["SPECIAL"]["STATS"]["MP"].GetFloat(),
		skillValue["SPECIAL"]["STATS"]["COUNT_DOWN"].GetFloat()
	);
	skillStats[Skill::SkillType::Ultimate].SetSkillStats(
		skillValue["ULTIMATE"]["STATS"]["ATK"].GetFloat(),
		skillValue["ULTIMATE"]["STATS"]["MP"].GetFloat(),
		skillValue["ULTIMATE"]["STATS"]["COUNT_DOWN"].GetFloat()
	);
}

void Skill::CastSkill(Skill::SkillType skillType, Direction direction)
{
	const int maxWord = 50;

	bool movement = false;

	int numberSprite;
	char nameSprite[maxWord] = { 0 };
	char nameElement[maxWord] = { 0 };
	char nameType[maxWord] = { 0 };

	sprintf(nameElement, "%s", skillValue["NAME"].GetString());
	sprintf(nameType, "Skill");

	switch (skillType)
	{
	case Skill::SkillType::Normal:
		numberSprite = skillValue["SPRITES"]["COUNT_NORMAL"].GetInt();
		sprintf(nameSprite, "%s%d", nameElement, 1);

		skillSize = cocos2d::Size(
			skillValue["NORMAL"]["SIZE_X"].GetFloat(),
			skillValue["NORMAL"]["SIZE_Y"].GetFloat()
		);

		movement = skillValue["NORMAL"]["MOVEMENT"].GetInt();
		break;
	case Skill::SkillType::Special:
		numberSprite = skillValue["SPRITES"]["COUNT_SPECIAL"].GetInt();
		sprintf(nameSprite, "%s%d", nameElement, 2);

		skillSize = cocos2d::Size(
			skillValue["SPECIAL"]["SIZE_X"].GetFloat(),
			skillValue["SPECIAL"]["SIZE_Y"].GetFloat()
		);

		movement = skillValue["SPECIAL"]["MOVEMENT"].GetInt();
		break;
	case Skill::SkillType::Ultimate:
		numberSprite = skillValue["SPRITES"]["COUNT_ULTIMATE"].GetInt();
		sprintf(nameSprite, "%s%d", nameElement, 3);

		skillSize = cocos2d::Size(
			skillValue["ULTIMATE"]["SIZE_X"].GetFloat(),
			skillValue["ULTIMATE"]["SIZE_Y"].GetFloat()
		);

		movement = skillValue["ULTIMATE"]["MOVEMENT"].GetInt();
		break;
	default:
		break;
	}

	Vector<SpriteFrame*> animFrames;

	char spriteFrameByName[maxWord] = { 0 };

	//set physic
	sprintf(spriteFrameByName, "%s-%s-%d.png", nameType, nameSprite, 0);

	skillAnimation = cocos2d::Sprite::createWithSpriteFrameName(spriteFrameByName);

	skillPhysicsBody = PhysicsBody::createBox(skillSize);

	skillPhysicsBody->setDynamic(false);
	skillPhysicsBody->setRotationEnable(false);

	skillPhysicsBody->setCategoryBitmask(PLAYER_ATTACK_CATEGORY_BITMASK);
	skillPhysicsBody->setCollisionBitmask(PLAYER_ATTACK_COLLISION_BITMASK);
	skillPhysicsBody->setContactTestBitmask(ALLSET_BITMASK);

	if (movement == true) {
		skillPhysicsBody->setVelocity(
			Vec2((direction == Direction::RIGHT ? PLAYER_MAX_VELOCITY : -PLAYER_MAX_VELOCITY), 0.0f)
		);
	}

	for (int index = 0; index < numberSprite; index++)
	{
		sprintf(spriteFrameByName, "%s-%s-%d.png", nameType, nameSprite, index);

		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(spriteFrameByName);
		animFrames.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(animFrames, ANIMATION_DELAY);
	Animate* animate = Animate::create(animation);


	skillAnimation->stopAllActions();

	auto callbackAction = CallFunc::create(
		CC_CALLBACK_0(Skill::cancelAnimation, this, skillSprite)
	);

	skillAnimation->runAction(Sequence::create(animate, callbackAction, nullptr));

	if (direction == Direction::LEFT) {
		skillAnimation->setFlippedX(true);
	}
	else {
		skillAnimation->setFlippedX(false);
	}

	skillSprite->setPhysicsBody(skillPhysicsBody);

	skillSprite->addChild(skillAnimation);
}

Stats Skill::SkillCost(Skill::SkillType skillType)
{
	return skillStats[skillType];
}

cocos2d::Sprite * Skill::GetSprite()
{
	skillSprite = Sprite::create();
	return skillSprite;
}

inline void Skill::getValue(int type)
{
	auto buf = FileUtils::getInstance()->getStringFromFile("res/skill.json");

	skillDocument.Parse<0>(buf.c_str());
	if (skillDocument.HasParseError()) {
		CCLOG("ERROR: Skill document not found!");
	}
	else {
		if (skillDocument.HasMember("SKILL")) {
			rapidjson::Value& playerCharacterSkill = skillDocument["SKILL"];
			for (rapidjson::SizeType i = 0; i < playerCharacterSkill.Size(); i++) {
				if (playerCharacterSkill[i]["TYPE"].GetInt() == type) {
					skillValue = playerCharacterSkill[i];
				}
			}
		}
	}
}

void Skill::cancelAnimation(cocos2d::Sprite* ref)
{
	ref->getPhysicsBody()->removeAllShapes();
	ref->removeAllChildren();
	ref->removeFromParent();
}
