#ifndef __SKILL_H__
#define __SKILL_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "Stats.h"

USING_NS_CC;

class Skill
{
public:
	enum class SkillType {
		Normal, Special, Ultimate
	};

	Skill();

	void CastSkill(Skill::SkillType skillType, Direction direction = Direction::RIGHT);

	Stats SkillCost(Skill::SkillType skillType);

	cocos2d::Sprite* GetSprite();

	void SetPosition(cocos2d::Vec2 position);
	
private:
	std::map<Skill::SkillType, Stats> skillStats;

	cocos2d::Sprite* skillSprite;
	cocos2d::Sprite* skillAnimation;

	cocos2d::PhysicsBody* skillPhysicsBody;

	cocos2d::Size skillSize;
	cocos2d::Size characterSize;

	void createAnimation(SkillType actionState, Direction actionDirection = Direction::RIGHT);

	void cancelAnimation(cocos2d::Sprite* ref);
};

#endif // __SKILL_H__ 
