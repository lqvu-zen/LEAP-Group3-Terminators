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
#include "Joystick.h"
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
	cocos2d::Label* hpPotionsLabel;
	cocos2d::Label* mpPotionsLabel;
	CREATE_FUNC(PlayGameScene);
	//void attackMonster(float dt);
private:
	Joystick* joystick;
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
	
	//AI
	void updateMonster(float dt);
	void monsterAction(float dt);
	void updateBoss(float dt);
	void bossAction(float dt);
	bool win;

	void goToContinue(cocos2d::Ref* sender);

	//Pause
	void goToLockUnlockSkill();
	void goToVillage();
	void goToSetting();
	void goToMainMenu();
	void goToExit();
	void playerDeadNotice();
	void goToSave();
	//Unlock Skill
	Sprite* lockskill_1Item, * lockskill_2Item, * lockskill_3Item;
	void unlockSkill(int index);
	bool checkVector(vector<int>list, int num);

	//Revival
	void Revival1Func();
	void Revival2Func();
	int timeRevival;
	int goldRevival;
	cocos2d::Label* lblCountDown;
	void updateCountDown(float);

	//countDown skill
	Sprite* lockskill1, * lockskill2, * lockskill3;
	bool lock1, lock2, lock3;

	//Win scene
	void goToWinScene(float dt);
};

#endif // __PLAYGAME_SCENE_H__