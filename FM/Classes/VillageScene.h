#ifndef __VILLAGE_SCENE_H__
#define __VILLAGE_SCENE_H__

#include "cocos2d.h"
#include "PlayerCharacter.h"
#include "ui//CocosGUI.h"
#include "Popup.h"
#include "NPC.h"
#include "GameManager.h"

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
	Popup* popupMenu;
private:
	
	TMXTiledMap *map;
	Size visibleSize;
	Vec2 origin;
	PlayerCharacter* playerChar;
	NPC* npc;
	std::vector<EventKeyboard::KeyCode> heldKeys;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void update(float dt);
	void updateCharacter(float dt);
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	void onClickAttackMenu(cocos2d::Ref* sender);
	void onClickMenuItem(cocos2d::Ref* sender);
<<<<<<< HEAD

	//Pause
	void goToMission();
	void goToSetting();
	void goToMainMenu();
	void goToExit();
=======
	void onContactSeperate(cocos2d::PhysicsContact &contact);
>>>>>>> 9a01d1d9d890fb3cbd5e9bbbd9d7365dcbbdba67
};

#endif // __VILLAGE_SCENE_H__