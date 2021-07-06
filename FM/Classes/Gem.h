#ifndef __GEM_H__
#define __GEM_H__

#include "cocos2d.h"

using namespace std;

class Gem 
{
public:
	cocos2d::Sprite* getSprite();
	Gem();
private:
	cocos2d::Sprite* gemSprite;
	cocos2d::Sprite* gemImage;
	cocos2d::PhysicsBody* gemBody;
    
};

#endif // __GEM_H__
