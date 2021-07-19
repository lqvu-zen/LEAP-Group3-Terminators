#include "Stats.h"
#include "GameManager.h"

Stats::Stats()
{
	statsSprite = nullptr;

	maxHP = HP = 0;
	maxMP = MP = 0;
	maxATK = ATK = 0;
	maxDEF = DEF = 0;
}

void Stats::SetStats(float hp, float mp, float atk, float def)
{
	//Normal stats
	maxHP = HP = hp;
	maxMP = MP = mp;
	maxATK = ATK = atk;
	maxDEF = DEF = def;

	//Player stats
	maxJump = 1;
	jump = 0;

	Karma = 0;

	//NPC stats
	Affection = 10;
}

cocos2d::Sprite * Stats::GetSprite()
{
	if (statsSprite == nullptr) {
		statsSprite = Sprite::create();
		statsEmblemSpace = Sprite::create("sprites/HB_EmblemSpace_Enemies.png");
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

		//add button
		//AddPlayerButton();
	}

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

void Stats::AddPlayerButton()
{
	auto statsButton = ui::Button::create("sprites/HB_EmblemSpace_Player.png");

	statsButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	statsButton->setPosition(statsSprite->getPosition());
	statsButton->setScale(statsSprite->getScale());

	statsButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		auto playerCharacter = GameManager::getInstace()->GetPlayerCharacter(false);
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			
			break;
		case ui::Widget::TouchEventType::ENDED:
			//CCLOG("Open inventory");
			if (playerCharacter->getInventory().GetSprite()->isVisible() == true) {
				playerCharacter->closeInventory();
			}
			else {
				playerCharacter->openInventory();
			}
			break;
		default:
			break;
		}
	});

	statsSprite->getParent()->addChild(statsButton, 1);
}

bool Stats::canJump()
{
	return jump < maxJump;
}

void Stats::upgradeJump()
{
	maxJump = 2;
}
