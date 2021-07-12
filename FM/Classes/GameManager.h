#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "PlayerCharacter.h"
#include "MonsterCharacter.h"
#include "BossCharacter.h"
#include "Character.h"
#include "Mission.h"

USING_NS_CC;

class GameManager : public cocos2d::Ref
{
public:
	enum class CharacterType {
		Player, Monster, Boss, NPC
	};

	static GameManager* getInstace();

	PlayerCharacter* GetPlayerCharacter();

	Mission* getMission();

	void AddCharacter(Character* ref);

	void hit(int attacker, int victim);
private:
	static GameManager* create();

	PlayerCharacter* playerCharacter;

	int countCharacter;
	std::map <int, Character*> characterMap;

	Mission* mission;
};

#endif // __GAMEMANAGER_H__ 
