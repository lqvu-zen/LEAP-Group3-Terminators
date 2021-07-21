#ifndef __STATS_H__
#define __STATS_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "ui//CocosGUI.h"

USING_NS_CC;

class Stats
{
public:
	float HP;
	float MP;
	float ATK;
	float DEF;
	int Karma;

	int Affection;

	int jump;

	int value;
	float countdown;

	Stats();

	void SetStats(float hp = 10.0f, float mp = 0.0f, float atk = 0.0f, float def = 0.0f);

	void SetCItemStats(float _hp = 0.0f, float _mp = 0.0f, float _atk = 0.0f, float _def = 0.0f);
	void SetNCItemStats(float _hp = 0.0f, float _mp = 0.0f, float _atk = 0.0f, float _def = 0.0f, int _jump = 0);

	void SetSkillStats(float _ATK, float _MP, float _countdown);

	void ResetCharacterStats();

	void BuffStats(Stats _stats);

	cocos2d::Sprite* GetSprite();
	cocos2d::Size GetSpriteSize();

	void UpdateStatsBar();

	void AddPlayerButton();

	bool canJump();
	void upgradeJump();

private:
	float maxHP;
	float maxMP;
	float maxATK;
	float maxDEF;

	int maxJump;

	cocos2d::Sprite* statsSprite;
	cocos2d::Sprite* statsEmblemSpace;
	cocos2d::Sprite* statsBorder;

	cocos2d::ProgressTimer* statsHP;
	cocos2d::ProgressTimer* statsMP;

	//ui::Button* statsButton;

	//Karma
	cocos2d::Sprite* karmaSprite;
	cocos2d::Sprite* karmaBorder;

	cocos2d::ProgressTimer* karmaPoint;

	cocos2d::Size spriteSize;
};

#endif // __STATS_H__ 
