#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "BossCharacter.h"
#include "Mission.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    Mission* mission;

    BossCharacter* boss;

    void ticktock(float dt);

    int timee;
    int minutes;
    Sprite* backSprite;
    ClippingNode* backClipper;
};

#endif // __HELLOWORLD_SCENE_H__
