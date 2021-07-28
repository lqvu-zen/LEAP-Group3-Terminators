#ifndef __MONSTER_CHARACTER_H__
#define __MONSTER_CHARACTER_H__

#include "cocos2d.h"
#include "Character.h"
#include "PhysicsShapeCache.h"
#include "Stats.h"
#include "Character.h"
#include "GameManager.h"
#include "Item.h"

using namespace std;

class MonsterCharacter : public Character
{
public:

    enum class Direction {
        LEFT, RIGHT
    };

    enum class Species {
        MELEE, RANGED
    };

    enum class State {
        ATTACK, DEATH, HURT, IDLE, WALK, SKILL
    };

    MonsterCharacter(cocos2d::Node* _scene, int _type, int _level);

    cocos2d::Sprite* getSprite();
    State characterState;

    void setPosition(cocos2d::Vec2 _position);

    void setDirection(Direction _actionDirection);

    void updateAction(cocos2d::Vec2 positionPlayer);

    void attack();

    void death();

    void takeHit(float dame);

    void idle();

    void jump();

    void run();

    void walk();
private:

    cocos2d::Node* scene;
    
    int level;
    int type;
    Species species;
    
    vector<int> numSprite;
    string floder;
    string name;

    cocos2d::Size characterSize;
    //cocos2d::PhysicsBody* monsterBody;

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite* characterSprite;
    cocos2d::Sprite* characterSpriteAnimation;
    cocos2d::PhysicsBody* characterPhysicsBody;

    cocos2d::Sprite* attackSprite;

    //cocos2d::Sprite* monster;
    cocos2d::Vec2 position;
    cocos2d::Sprite* bullet;

    Direction actionDirection;

    cocos2d::Animation* animation;

    cocos2d::Animation *createAnimation(string prefixName, int pFrames, float delay);

    //Attack
    void attackForRanged();
    void attackForMelee();

    //Skill
    int numAttack;
    void skillForMelee(cocos2d::Vec2 positionPlayer);
};

#endif // __MONSTER_CHARACTER_H__
