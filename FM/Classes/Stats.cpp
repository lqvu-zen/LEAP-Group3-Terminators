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

	statsHP->setPercentage(100.0f);
	statsMP->setPercentage(100.0f);

	//Karma
	auto scaleRatio = 0.7f;
	karmaSprite = Sprite::create();
	karmaBorder = Sprite::create("sprites/KB_Border.png");

	karmaSprite->addChild(karmaBorder, 5);

	karmaBorder->setPosition(
		Vec2::ZERO
	);

	karmaPoint = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("sprites/KB_Karma.png"));

	karmaPoint->setType(cocos2d::ProgressTimer::Type::BAR);

	karmaPoint->setBarChangeRate(Vec2(0.0f, 1.0f));

	karmaPoint->setMidpoint(Vec2(0.0f, -1.0f));

	karmaPoint->setPosition(
		Vec2::ZERO
	);

	karmaSprite->addChild(karmaPoint, 6);

	karmaSprite->setPosition(
		Vec2(karmaBorder->getContentSize().width / 2, -karmaBorder->getContentSize().height * scaleRatio / 2)
	);

	karmaSprite->setScale(scaleRatio);

	statsSprite->addChild(karmaSprite);

	karmaPoint->setPercentage(0.0f);
	karmaSprite->setVisible(false);
}

void Stats::SetHeroStats(float hp, float mp, float atk, float def)
{
	maxHP = HP = hp;
	maxMP = MP = mp;
	maxATK = ATK = atk;
	maxDEF = DEF = def;
	maxJump = 1;
	jump = 0;

	Karma = 0;
}

void Stats::SetMonsterStats(float hp, float mp, float atk, float def)
{
	maxHP = HP = hp;
	maxMP = MP = mp;
	maxATK = ATK = atk;
	maxDEF = DEF = def;
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

	karmaPoint->setPercentage(Karma * 1.0f);
	if (Karma >= 50 && karmaSprite->isVisible() == false) {
		karmaSprite->setVisible(true);
	}
	else if (Karma < 50) {
		karmaSprite->setVisible(false);
	}
}

bool Stats::canJump()
{
	return jump < maxJump;
}

void Stats::upgradeJump()
{
	maxJump = 2;
}
