#ifndef __MONSTER_CHARACTER_H__
#define __MONSTER_CHARACTER_H__

#include "cocos2d.h"
#include "Character.h"
#include "PhysicsShapeCache.h"

using namespace std;

class MonsterCharacter //: public Character
{
public:

    int hp;    
    int atk;
    int level;

    enum class Direction {
        LEFT, RIGHT
    };

    MonsterCharacter(cocos2d::Node* _scene, int _level);

    cocos2d::Sprite* getSprite();

    void setPosition(cocos2d::Vec2 _position);

    void setDirection(Direction _actionDirection);

    void attack();

    void attackAction(float dt);

    void death();

    void hurt(int dame);

    void idle();

    void walk();
private:

    cocos2d::Node* scene;
    string floder;

    cocos2d::PhysicsBody* monsterBody;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite* monster;
    cocos2d::Vec2 position;
    cocos2d::Sprite* bullet;
    Direction actionDirection;

    cocos2d::Animation* animation;

    cocos2d::Animation *createAnimation(string prefixName, int pFrames, float delay);
};

#endif // __MONSTER_CHARACTER_H__
