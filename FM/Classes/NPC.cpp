#include "NPC.h"
#include "GameManager.h"

USING_NS_CC;

NPC::NPC()
{
	characterTYPE = CharacterType::NonPlayer;

	characterSprite = Sprite::create();
	
	//Animation
	anim_NPC.reserve(4);
	anim_NPC.pushBack(SpriteFrame::create("sprites/NPC/Old_man_idle.png", Rect(0, 0, 19, 32)));
	anim_NPC.pushBack(SpriteFrame::create("sprites/NPC/Old_man_idle.png", Rect(19, 0, 19, 32)));
	anim_NPC.pushBack(SpriteFrame::create("sprites/NPC/Old_man_idle.png", Rect(38, 0, 19, 32)));
	anim_NPC.pushBack(SpriteFrame::create("sprites/NPC/Old_man_idle.png", Rect(57, 0, 19, 32)));
	Animation* NPCAnimation = Animation::createWithSpriteFrames(anim_NPC, 0.5f);
	Animate *NPCAnimate = Animate::create(NPCAnimation);
	characterSpriteAnimation = Sprite::createWithSpriteFrame(anim_NPC.front());
	characterSpriteAnimation->runAction(RepeatForever::create(NPCAnimate));
	characterSprite->addChild(characterSpriteAnimation);
	characterSprite->setScale(2.0f);

	//PhysicsBody
	characterSize = characterSpriteAnimation->getContentSize();
	characterPhysicsBody = PhysicsBody::createBox(characterSize);
	characterPhysicsBody->setDynamic(true);
	characterPhysicsBody->setRotationEnable(false);
	characterPhysicsBody->setCategoryBitmask(NONPLAYER_CATEGORY_BITMASK);
	characterPhysicsBody->setCollisionBitmask(NONPLAYER_COLLISION_BITMASK);
	characterPhysicsBody->setContactTestBitmask(ALLSET_BITMASK);
	characterSprite->setPhysicsBody(characterPhysicsBody);

	//Stats
	characterStats.SetStats();
	exclamation = Sprite::create("sprites/NPC/exclamationMark.png");
	exclamation->setScale(0.1);
	characterSprite->addChild(exclamation);
	exclamation->setPosition(Vec2(0.0f, characterSpriteAnimation->getContentSize().height));
	exclamation->setVisible(false);
}

NPC::NPC(cocos2d::Vec2 position)
{
	NPC();
	setPosition(position);
}

void NPC::setPosition(cocos2d::Vec2 position)
{
	characterSprite->setPosition(position);
	characterSpriteAnimation->setPosition(Vec2::ZERO);
	
}

void NPC::takeHit(float dame)
{

	GameManager::getInstace()->AddReward(Vec2::ZERO);
	GameManager::getInstace()->PlayerDarker();

	dame = 0;
	characterStats.HP -= dame;

	characterStats.Affection -= 10;

	if (characterStats.HP <= 0.0f) {
		//NPC death
		//exclamation = nullptr;
		characterSprite->removeFromParent();
	}
}

cocos2d::Sprite * NPC::getSprite()
{
	return characterSprite;
}

void NPC::showExclamation()
{
	if (characterStats.HP > 0)
	{
		exclamation->setColor(Color3B::WHITE);
		exclamation->setVisible(true);
	}
	
}

void NPC::changeExclamation() {
	if (characterStats.HP > 0)
	{
		exclamation->setColor(Color3B::YELLOW);
		exclamation->setVisible(true);
	}
}

void NPC::hideExclamation()
{
	if (characterStats.HP > 0)
	{
		exclamation->setVisible(false);
	}
}
