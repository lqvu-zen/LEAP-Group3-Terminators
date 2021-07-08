#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "cocos2d.h"
#include "Definitions.h"
#include "PlayerCharacter.h"
#include "MonsterCharacter.h"

USING_NS_CC;

class GameManager : public cocos2d::Ref
{
public:
	static GameManager* getInstace();

	PlayerCharacter* GetPlayerCharacter();

	MonsterCharacter* GetMonsterCharacter(int tag);
	int AddMonsterCharacter(MonsterCharacter* ref);

	void hit(int attacker, int victim);
private:
	static GameManager* create();

	PlayerCharacter* playerCharacter;

	int countMonsterCharacter;
	std::map <int, MonsterCharacter*> monsterCharacters;
};

#endif // __GAMEMANAGER_H__ 
