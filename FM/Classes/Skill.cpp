#include "Skill.h"

Skill::Skill()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites/Skill/Skill-Water.plist", "sprites/Skill/Skill-Water.png");

	skillSprite = cocos2d::Sprite::create();

	skillSize = cocos2d::Size(64.0f, 80.0f);
}

void Skill::CastSkill(Skill::SkillType skillType, Direction direction)
{
	if (direction == Direction::RIGHT) {
		skillSprite->setPositionX(characterSize.width);
	}
	else {
		skillSprite->setPositionX(- characterSize.width);
	}
	createAnimation(skillType, direction);
}

cocos2d::Sprite * Skill::GetSprite()
{
	return skillSprite;
}

void Skill::SetPosition(cocos2d::Vec2 position)
{
	characterSize = position;
}

void Skill::createAnimation(SkillType actionState, Direction actionDirection)
{
	if (true) {

		const int maxWord = 50;

		int numberSprite;
		char nameSprite[maxWord] = { 0 };
		char nameElement[maxWord] = { 0 };
		char nameType[maxWord] = { 0 };

		sprintf(nameElement, "Water");
		sprintf(nameType, "Skill");

		switch (actionState)
		{
		case Skill::SkillType::Normal:
			numberSprite = 10;
			sprintf(nameSprite, "%s%d", nameElement, 1);
			break;
		case Skill::SkillType::Special:
			numberSprite = 10;
			sprintf(nameSprite, "%s%d", nameElement, 2);
			break;
		case Skill::SkillType::Ultimate:
			numberSprite = 19;
			sprintf(nameSprite, "%s%d", nameElement, 3);
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

		skillPhysicsBody->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);
		skillPhysicsBody->setCollisionBitmask(ENEMIES_CATEGORY_BITMASK);
		skillPhysicsBody->setContactTestBitmask(ALLSET_BITMASK);

		if (actionState == Skill::SkillType::Ultimate) {
			skillPhysicsBody->setVelocity(
				Vec2((actionDirection == Direction::RIGHT ? PLAYER_MAX_VELOCITY : -PLAYER_MAX_VELOCITY), 0.0f)
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
			CC_CALLBACK_0(Skill::cancelAnimation, this)
		);

		skillAnimation->runAction(Sequence::create(animate, callbackAction, nullptr));
	
	}

	if (actionDirection == Direction::LEFT) {
		skillAnimation->setFlippedX(true);
	}
	else {
		skillAnimation->setFlippedX(false);
	}

	skillSprite->setPhysicsBody(skillPhysicsBody);

	skillSprite->addChild(skillAnimation);
}

void Skill::cancelAnimation()
{
	skillSprite->getPhysicsBody()->removeAllShapes();
	skillSprite->removeAllChildren();
}
