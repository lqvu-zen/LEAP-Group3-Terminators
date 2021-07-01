#ifndef __PLAYGAME_SCENE_H__
#define __PLAYGAME_SCENE_H__

#include "cocos2d.h"
#include "PlayerCharacter.h"
#include "MonsterCharacter.h"
#include "BossCharacter.h"
USING_NS_CC;
class PlayGameScene : public cocos2d::Scene
{
public:
	Node *cameraTarget;
	cocos2d::Follow *followCamera;
	static cocos2d::Scene* createScene();
	virtual bool init();
	bool isLocked = false;
	CREATE_FUNC(PlayGameScene);
	Node *lockNode;

private:
	
	TMXTiledMap *map;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	Sprite *player;
	MonsterCharacter* monster;
	BossCharacter* boss;


	void addAt(int x, int y, int type);
	cocos2d::Vector<cocos2d::Node*> pausedActions;
	
	PlayerCharacter* playerChar;

	std::vector<cocos2d::EventKeyboard::KeyCode> heldKeys;

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void update(float dt);
	void updateCharacter(float dt);
};

#endif // __PLAYGAME_SCENE_H__