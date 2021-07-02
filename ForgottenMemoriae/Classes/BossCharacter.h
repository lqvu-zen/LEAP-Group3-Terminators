/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __BOSS_CHARACTER_H__
#define __BOSS_CHARACTER_H__

#include "cocos2d.h"
#include "Character.h"
#include "PhysicsShapeCache.h"

using namespace std;

class BossCharacter //: public Character
{
public:  
    BossCharacter(cocos2d::Scene* scene, int level);

    cocos2d::Sprite* get() {
        return monster;
    };

    void attack();

    void block();

    void charge();

    void death();

    void hurt();

    void idle();

    void jump();

    void jump_attack();

    void run();

    void shoot_bow();

    void walk();

    void attack_1();

    void attack_2();

    void jump_attack_1();

    void jump_attack_2();
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    cocos2d::Sprite* monster;

    cocos2d::Animation* animation;

    cocos2d::Animation *createAnimation(string prefixName, int pFrames, float delay);

    string boss;

    PhysicsShapeCache* shapeCache;
};

#endif // __BOSS_CHARACTER_H__
