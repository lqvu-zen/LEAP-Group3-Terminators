#ifndef __VILLAGE_SCENE_H__
#define __VILLAGE_SCENE_H__

#include "cocos2d.h"
#include "PlayerCharacter.h"
#include "ui//CocosGUI.h"
#include "PlayGameScene.h"
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
	bool isLocked = false;
	CREATE_FUNC(VillageScene);
	Node *lockNode;
private:
	
	TMXTiledMap *map;
	Size visibleSize;
	Vec2 origin;
	Sprite *player;
	Vector<Node*> pausedActions;
	Sprite *NPC;
	Vector<SpriteFrame*> anim_NPC;
	PlayerCharacter* playerChar;
	std::vector<EventKeyboard::KeyCode> heldKeys;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void update(float dt);
	void updateCharacter(float dt);
	void onClickMoveMenu(cocos2d::Ref* sender);
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	void onClickAttackMenu(cocos2d::Ref* sender);
};

#endif // __VILLAGE_SCENE_H__