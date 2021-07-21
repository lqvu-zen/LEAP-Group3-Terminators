#ifndef __SKILL_H__
#define __SKILL_H__

#include "cocos2d.h"
#include "json/document.h"
#include "json//rapidjson.h"

#include "Definitions.h"
#include "Stats.h"

USING_NS_CC;

class Skill
{
public:
	enum class SkillType {
		Normal, Special, Ultimate
	};

	Skill(int type = 0);

	void CastSkill(Skill::SkillType skillType, Direction direction = Direction::RIGHT);

	Stats SkillCost(Skill::SkillType skillType);

	cocos2d::Sprite* GetSprite();
	
private:
	//document
	rapidjson::Document skillDocument;
	rapidjson::Value skillValue;
	inline void getValue(int type = 0);

	std::map<Skill::SkillType, Stats> skillStats;

	cocos2d::Sprite* skillSprite;
	cocos2d::Sprite* skillAnimation;

	cocos2d::PhysicsBody* skillPhysicsBody;

	cocos2d::Size skillSize;
	cocos2d::Size characterSize;

	void cancelAnimation(cocos2d::Sprite* ref);
};

#endif // __SKILL_H__ 
