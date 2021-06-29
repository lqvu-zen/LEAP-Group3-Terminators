#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "PlayerCharacter.h"

class MainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScene);

private:
	cocos2d::PhysicsWorld* sceneWorld;
	PlayerCharacter* player;

	std::vector<cocos2d::EventKeyboard::KeyCode> heldKeys;

	void SetPhysicsWorld(cocos2d::PhysicsWorld* world);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void update(float dt);
	void updateCharacter(float dt);
};

#endif // __MAIN_MENU_SCENE_H__
