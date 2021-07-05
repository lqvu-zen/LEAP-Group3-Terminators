#include "Stats.h"

Stats::Stats()
{
	statsSprite = Sprite::create();
	statsEmblemSpace = Sprite::create("sprites/HB_EmblemSpace.png");
	statsBorder = Sprite::create("sprites/HB_Border.png");

	statsSprite->addChild(statsEmblemSpace, 4);
	statsSprite->addChild(statsBorder, 3);

	statsEmblemSpace->setPosition(Vec2(statsEmblemSpace->getContentSize().width / 2, statsEmblemSpace->getContentSize().height / 2));
	statsBorder->setPosition(
		Vec2(
			statsEmblemSpace->getPositionX() + statsBorder->getContentSize().width / 2 + statsEmblemSpace->getContentSize().width / 4,
			statsEmblemSpace->getPositionY()
		)
	);

	spriteSize = Size(statsEmblemSpace->getContentSize().width * 0.75f + statsEmblemSpace->getContentSize().width, statsEmblemSpace->getContentSize().height);

	//set HP and MP
	statsHP = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("sprites/HB_HP.png"));
	statsMP = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("sprites/HB_MP.png"));

	statsHP->setType(cocos2d::ProgressTimer::Type::BAR);
	statsMP->setType(cocos2d::ProgressTimer::Type::BAR);

	statsHP->setPercentage(100.0f);
	statsMP->setPercentage(100.0f);

	statsHP->setBarChangeRate(Vec2(1.0f, 0.f));
	statsMP->setBarChangeRate(Vec2(1.0f, 0.f));

	statsHP->setMidpoint(Vec2(-1.0f, 0.0f));
	statsMP->setMidpoint(Vec2(-1.0f, 0.0f));

	statsHP->setPosition(
		Vec2(
			statsBorder->getPositionX(), 
			statsBorder->getPositionY() + statsMP->getContentSize().height / 2 + (statsBorder->getContentSize().height / 2 - statsMP->getContentSize().height) / 4 * 3
		)
	);
	statsMP->setPosition(
		Vec2(
			statsBorder->getPositionX(),
			statsBorder->getPositionY() - statsMP->getContentSize().height / 2 - (statsBorder->getContentSize().height / 2 - statsMP->getContentSize().height) / 2
		)
	);

	statsSprite->addChild(statsHP, 1);
	statsSprite->addChild(statsMP, 2);
}

void Stats::SetHeroStats(float hp, float mp, float atk, float def)
{
	maxHP = 100.0f;
	maxMP = 100.0f;
	maxATK = 20.0f;
	maxDEF = 10.0f;
	HP = hp;
	MP = mp;
	ATK = atk;
	DEF = def;
}

cocos2d::Sprite * Stats::GetSprite()
{
	return statsSprite;
}

cocos2d::Size Stats::GetSpriteSize()
{
	return spriteSize;
}

void Stats::UpdateStatsBar()
{
	statsHP->setPercentage(HP / maxHP * 100.0f);
	statsMP->setPercentage(MP / maxMP * 100.0f);
}
