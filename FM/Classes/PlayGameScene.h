#ifndef __PLAYGAME_SCENE_H__
#define __PLAYGAME_SCENE_H__

#include "cocos2d.h"
#include "PlayerCharacter.h"
#include "MonsterCharacter.h"
#include "ui//CocosGUI.h"
#include "BossCharacter.h"
#include "Item.h"
#include "GameManager.h"
#include "Mission.h"
#include <vector>

USING_NS_CC;
class PlayGameScene : public cocos2d::Scene
{
public:
	Node *cameraTarget;
	Follow *followCamera;
	Node *buttonNode;
	Node *gameNode;
	Sprite* trigger;
	static cocos2d::Scene* createScene();
	virtual bool init();
	cocos2d::Label* missionLabel;
	CREATE_FUNC(PlayGameScene);
	//void attackMonster(float dt);
private:
	
	TMXTiledMap *map;
	Size visibleSize;
	Vec2 origin;
	Sprite *player;
	std::list<MonsterCharacter*> monsters;
	BossCharacter* boss;
	TMXLayer* Foreground;
	std::vector<TMXLayer*> HiddenAreas;
	//void addAt(int x, int y, int type);
	Vector<Node*> pausedActions;
	bool isDeadNoticePopUp = false;
	PlayerCharacter* playerChar;
	Sprite* playerStatsSprite;
	Item* item;
	std::vector<EventKeyboard::KeyCode> heldKeys;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void update(float dt);
	void updateCharacter(float dt);
	//void onClickMoveMenu(cocos2d::Ref* sender);
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	void onContactSeperate(cocos2d::PhysicsContact &contact);
	void hideTiles(int tag);
	void showTiles();
	void onClickAttackMenu(cocos2d::Ref* sender);
	void updateMonster(float dt);
	void monsterAction(float dt);
	void updateBoss(float dt);

	//Pause
	void goToMission();
	void goToVillage();
	void goToSetting();
	void goToMainMenu();
	void goToExit();
	void playerDeadNotice();

	//Unlock Skill
	void unlockSkill(int index);
	bool checkVector(vector<int>list, int num);

	//Revival
	void Revival1Func();
	void Revival2Func();
	int time;
	cocos2d::Label* lblCountDown;
	void updateCountDown(float);
};

#endif // __PLAYGAME_SCENE_H__