#ifndef __VILLAGE_SCENE_H__
#define __VILLAGE_SCENE_H__

#include "cocos2d.h"
#include "PlayerCharacter.h"
#include "ui//CocosGUI.h"
#include "NPC.h"
#include "GameManager.h"
#include "Portal.h"
#include "Joystick.h"

USING_NS_CC;
class VillageScene: public cocos2d::Scene
{
public:
	Node *cameraTarget;
	Follow *followCamera;
	Node *buttonNode;
	Node *gameNode;
	static cocos2d::Scene* createScene();
	virtual bool init();
	bool isPopUpDisplay = false;
	bool standAlone = true;
	cocos2d::Label* missionLabel;
	CREATE_FUNC(VillageScene);

	cocos2d::MenuItemImage* interactiveItem;

private:
	
	Joystick* joystick;
	cocos2d::EventListenerCustom *joyStickListener;
	TMXTiledMap *map;
	Size visibleSize;
	Vec2 origin;
	PlayerCharacter* playerChar;
	Sprite* playerStatsSprite;
	NPC* npc;
	Portal* portal;
	std::vector<EventKeyboard::KeyCode> heldKeys;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void update(float dt);
	void updateCharacter(float dt);
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	void onClickAttackMenu(cocos2d::Ref* sender);
	void onClickNPCInteract();
	//Pause
	void goToMission();
	void goToSetting();
	void goToMainMenu();
	void goToExit();
	void goToMap1();
	void goToMap2();
	void onContactSeperate(cocos2d::PhysicsContact &contact);
	bool checkVector(vector<int>list, int num);
	//UnlockSkill
	void unlockSkill(int index);
};

#endif // __VILLAGE_SCENE_H__