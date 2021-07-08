#ifndef __STATS_H__
#define __STATS_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class Stats
{
public:
	float HP;
	float MP;
	float ATK;
	float DEF;

	Stats();

	void SetHeroStats(float hp = 100.0f, float mp = 100.0f, float atk = 20.0f, float def = 10.0f);

	void SetMonsterStats(float hp = 100.0f, float mp = 100.0f, float atk = 20.0f, float def = 10.0f);

	cocos2d::Sprite* GetSprite();
	cocos2d::Size GetSpriteSize();

	void UpdateStatsBar();

private:
	float maxHP;
	float maxMP;
	float maxATK;
	float maxDEF;

	cocos2d::Sprite* statsSprite;
	cocos2d::Sprite* statsEmblemSpace;
	cocos2d::Sprite* statsBorder;

	cocos2d::ProgressTimer* statsHP;
	cocos2d::ProgressTimer* statsMP;

	cocos2d::Size spriteSize;
};

#endif // __STATS_H__ 
