#ifndef __BOSS_CHARACTER_H__
#define __BOSS_CHARACTER_H__

#include "cocos2d.h"
#include "Character.h"
#include "PhysicsShapeCache.h"
#include "GameManager.h"

using namespace std;

class BossCharacter : public Character
{
public:

    enum class State {
        ATTACK, BLOCK, CHARGE, DEATH, HURT, IDLE, JUMP, RUN, SHOOTBOW, WALK
    };

    enum class Direction {
        LEFT, RIGHT
    };

    BossCharacter(int level);

    State characterState;
    Direction characterDirection;
    cocos2d::Vec2 position;
    int action;
    
    cocos2d::Sprite* getSprite() {
        return characterSprite;
    };

    void setPosition(cocos2d::Vec2 _position) {
        position = _position;
        characterSprite->setPosition(_position);
        characterSpriteAnimation->setPosition(Vec2::ZERO);
        attackSprite->setPosition(Vec2::ZERO);
    }

    void updateAction(cocos2d::Vec2 positionPlayer);

    void setDirection(Direction actionDirection);
    Direction getDirection() {
        return characterDirection;
    }

private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    string floder;
    //string boss;

    cocos2d::Sprite* characterSprite;
    cocos2d::Sprite* characterSpriteAnimation;
    cocos2d::PhysicsBody* characterPhysicsBody;

    cocos2d::Sprite* attackSprite;

    PhysicsShapeCache* shapeCache;

    cocos2d::Animation* animation;
    cocos2d::Animation* createAnimation(string prefixName, int pFrames, float delay);

    int numAttack;

    void idle();
    void death();
    void attack_1();
    void attack_2();
    void jumpAttack_1();
    void jumpAttack_2();
    void run();
    void walk();
    void skill_1();
    void skill_2();
    void skill_3();

    void attack();
    void jumpAttack();
    void skill(int type);
    void takeHit(float dame);

    Sprite* arrow;
};

#endif // __BOSS_CHARACTER_H__
