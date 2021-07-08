#ifndef __PLAYGAME_SCENE_H__
#define __PLAYGAME_SCENE_H__

#include "cocos2d.h"
#include "PlayerCharacter.h"
#include "MonsterCharacter.h"
#include "ui//CocosGUI.h"
#include "BossCharacter.h"
#include "Gem.h"
#include "Mission.h"
USING_NS_CC;
class PlayGameScene : public cocos2d::Scene
{
public:
	Node *cameraTarget;
	Follow *followCamera;
	Node *buttonNode;
	Node *gameNode;
	static cocos2d::Scene* createScene();
	virtual bool init();
	bool isLocked = false;
	CREATE_FUNC(PlayGameScene);
	Node *lockNode;
	void attackMonster(float dt);
	int numOfMonster = 0;
private:
	
	TMXTiledMap *map;
	Size visibleSize;
	Vec2 origin;
	Sprite *player;
	MonsterCharacter* monsters[2];
	BossCharacter* boss;
	//Mission* mission;
	void addAt(int x, int y, int type);
	Vector<Node*> pausedActions;
	
	PlayerCharacter* playerChar;
	std::vector<EventKeyboard::KeyCode> heldKeys;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void update(float dt);
	void updateCharacter(float dt);
	void onClickMoveMenu(cocos2d::Ref* sender);
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	void onClickAttackMenu(cocos2d::Ref* sender);
	void updateMonster(float dt);
	void monsterAction(float dt);
	void updateBoss(float dt);
	void bossAction(float dt);
	
};

#endif // __PLAYGAME_SCENE_H__