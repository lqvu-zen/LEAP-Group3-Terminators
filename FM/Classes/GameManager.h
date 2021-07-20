#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "PlayerCharacter.h"
#include "MonsterCharacter.h"
#include "BossCharacter.h"
#include "Character.h"
#include "Item.h"
#include "Mission.h"
#include "PhysicsShapeCache.h"
#include <vector>

USING_NS_CC;

class GameManager : public cocos2d::Ref
{
public:
	enum class CharacterType {
		Player, Monster, Boss, NPC
	};

	static GameManager* getInstace();

	void init();

	PlayerCharacter* GetPlayerCharacter(bool withInit = true);

	Mission* getMission();

	void AddCharacter(Character* ref);
	void AddItem(Item* ref);

	void AddReward(cocos2d::Vec2 position, int type = 0);

	void hit(int attacker, int victim);
	void colect(int item);

	PhysicsShapeCache* getPhysicsShapeCache();

	bool onContactBegin(cocos2d::PhysicsContact &contact);
	void onContactSeperate(cocos2d::PhysicsContact &contact);
	
	vector<int>lockedSkills = { 1,2,3 };

private:
	static GameManager* create();

	PlayerCharacter* playerCharacter;

	int countCharacter;
	std::map <int, Character*> characterMap;

	int countItem;
	std::map <int, Item*> itemMap;

	Mission* mission;

	PhysicsShapeCache* shapeCache;
};

#endif // __GAMEMANAGER_H__ 
