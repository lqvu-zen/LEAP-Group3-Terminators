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
	Follow *followCamera;

	static cocos2d::Scene* createScene();
	virtual bool init();
	bool isLocked = false;
	CREATE_FUNC(PlayGameScene);
	Node *lockNode;
	int numOfMonster = 0;
private:
	
	TMXTiledMap *map;
	Size visibleSize;
	Vec2 origin;
	Sprite *player;
	MonsterCharacter* monsters[2];
	BossCharacter* boss;


	void addAt(int x, int y, int type);
	Vector<Node*> pausedActions;
	
	PlayerCharacter* playerChar;
	std::vector<EventKeyboard::KeyCode> heldKeys;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void update(float dt);
	void updateCharacter(float dt);
};

#endif // __PLAYGAME_SCENE_H__