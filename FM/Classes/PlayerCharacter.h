#ifndef __PLAYERCHARACTER_H__
#define __PLAYERCHARACTER_H__

#include "cocos2d.h"
#include "json/document.h"
#include "json//rapidjson.h"

#include "Definitions.h"
#include "Stats.h"
#include "Skill.h"
#include "Character.h"
#include "Inventory.h"

class PlayerCharacter : public Character
{
public:
	enum class State {
		IDLE, JUMPING, FALLING, RUNING, ATTACK1, ATTACK2, ATTACK3, TAKE_HIT, DEATH
	};

	State characterState;
	State characterStateOnce;
	Direction characterDirection;

	PlayerCharacter(int characterType = 0);

	void init(int characterType = 0);

	void setPosition(cocos2d::Vec2 position);

	void updateAnimation(State actionState, Direction actionDirection = Direction::RIGHT, bool repeatForever = true);
	void updateAction(float dt);
	void reupdateAnimation();

	bool isFalling();
	bool isGrounded();
	bool isJumping();
	bool isDead();
	void setFalling();
	void setGrounded();
	void setJumping();

	void getDarker();

	void resetJump();

	void attack(int mode = 0);

	void takeHit(float dame = 10.0f);

	void revive();

	void openInventory();
	void closeInventory();

	void colectItem(Item* item, int mount = 1);
	void addGold(int num);
	bool exceptGold(int num);

	void useItem(Item::ItemType itemType);

	cocos2d::Sprite* getSprite();
	Stats getStats();
	void LoadStats(float hp, float mp, float atk, float def, int karma, float m_hp, float m_mp, float m_atk, float m_def, int m_jump);
	Inventory getInventory();

	void setVelocity(cocos2d::Vec2 velocity);
	cocos2d::Vec2 getVolocity();
	cocos2d::Vec2 getRealtimeVolocity();

	//save option
	void savePosition();
	void returnSavePosition();

private:
	//document
	rapidjson::Document characterDocument;
	rapidjson::Value characterValue;
	inline void getValue(int characterType = 0);

	//character body
	cocos2d::Sprite* characterSprite;
	cocos2d::Sprite* characterSpriteAnimation;
	cocos2d::PhysicsBody* characterPhysicsBody;

	cocos2d::Size characterSize;
	cocos2d::Vec2 characterVelocity;

	std::map<std::string, cocos2d::Animate*> characterAnimate;

	//character attack
	cocos2d::Sprite* attackSprite;
	cocos2d::Sprite* skillSprite;

	cocos2d::Size attackSize;

	Skill* characterSkill;

	Skill::SkillType attackSkill;

	std::map<Skill::SkillType, float> characterSkillCountdown;

	//character state
	bool castingSkill;
	bool attacking;
	bool falling;
	bool grounded;
	bool jumping;
	bool takingHit;
	bool died;
	int attackMode;

	//character inventory
	Inventory characterInventory;

	//save position
	cocos2d::Vec2 characterSavePosition;
	
	//Karma
	int countDT;

	//color
	cocos2d::Color3B characterColor;
};

#endif // __PLAYERCHARACTER_H__
