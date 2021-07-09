#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "Stats.h"

class Character 
{
public:
    
	virtual void takeHit(float dame) = 0;
	virtual cocos2d::Sprite* getSprite() = 0;

	virtual Stats getStats();
private:

protected:
	Stats characterStats;
};

#endif // __CHARACTER_H__
