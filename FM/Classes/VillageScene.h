#ifndef __VILLAGE_SCENE_H__
#define __VILLAGE_SCENE_H__

#include "cocos2d.h"
#include "PlayerCharacter.h"
#include "ui//CocosGUI.h"
#include "Popup2.h"
#include "NPC.h"
#include "GameManager.h"
#include "Portal.h"


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
	CREATE_FUNC(VillageScene);

	cocos2d::MenuItemImage* interactiveItem;

private:
	
	TMXTiledMap *map;
	Size visibleSize;
	Vec2 origin;
	PlayerCharacter* playerChar;
	NPC* npc;
	Portal* portal;
	std::vector<EventKeyboard::KeyCode> heldKeys;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void update(float dt);
	void updateCharacter(float dt);
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	void onClickAttackMenu(cocos2d::Ref* sender);

	//Pause
	void goToMission();
	void goToSetting();
	void goToMainMenu();
	void goToExit();
	void goToMap1();

	void onContactSeperate(cocos2d::PhysicsContact &contact);

	//UnlockSkill
	void unlockSkill(int index);
};

#endif // __VILLAGE_SCENE_H__