#ifndef __DIFINITIONS_H__
#define __DIFINITIONS_H__

#include "cocos2d.h"

#define DISPLAY_TIME_SPLASH_SCENE 1
#define TRANSITION_TIME 0.5f
#define SCALE_FACTOR 2.0f
#define BIRD_JUMP 0.1f
#define ANIMATION_DELAY 0.085f
#define FAST_ANIMATION_DELAY 0.035f
#define COLECT_DELAY 0.5f

#define PLAYER_MAX_VELOCITY 160.0f
#define PLAYER_JUMP_VELOCITY 180.0f

#define GRAVITY_VELOCITY 300.0f

#define SCALE_RATIO 3.0f

#define PLAYER_JUMP_SPEED 2.0f

#define BASE_VELOCITY 0.0f
#define PADDING_VELOCITY 1.0f

#define OBSTACLE_COLLISION_BITMASK 0xFFFFFFFF

#define PLAYER_CATEGORY_BITMASK 0x00000001
#define PLAYER_COLLISION_BITMASK 0x00000010

#define PLAYER_ATTACK_CATEGORY_BITMASK 0x00000002
#define PLAYER_ATTACK_COLLISION_BITMASK 0x00000010

#define ENEMIES_CATEGORY_BITMASK 0x00000010
#define ENEMIES_COLLISION_BITMASK 0x00000001

#define ENEMIES_ATTACK_CATEGORY_BITMASK 0x00000020
#define ENEMIES_ATTACK_COLLISION_BITMASK 0x00000001

#define ITEM_CATEGORY_BITMASK 0x00000100
#define ITEM_COLLISION_BITMASK 0x00000001

#define NONPLAYER_CATEGORY_BITMASK 0x00000004
#define NONPLAYER_COLLISION_BITMASK 0x00000012
#define PORTAL_CATEGORY_BITMASK 0x00000005
#define HIDDEN_TILE_CATEGORY_BITMASK 0x00000006

#define ALLSET_BITMASK 0xFFFFFFFF
#define ALLCLEARED_BITMASK 0x00000000

#define TAG_PADDING 1

// KEYBOARD
const cocos2d::EventKeyboard::KeyCode ENTER = cocos2d::EventKeyboard::KeyCode::KEY_KP_ENTER;
const cocos2d::EventKeyboard::KeyCode UP_ARROW = cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW;
const cocos2d::EventKeyboard::KeyCode DOWN_ARROW = cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW;
const cocos2d::EventKeyboard::KeyCode LEFT_ARROW = cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW;
const cocos2d::EventKeyboard::KeyCode RIGHT_ARROW = cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
const cocos2d::EventKeyboard::KeyCode SPACEBAR = cocos2d::EventKeyboard::KeyCode::KEY_SPACE;
const cocos2d::EventKeyboard::KeyCode ATTACK = cocos2d::EventKeyboard::KeyCode::KEY_Q;
const cocos2d::EventKeyboard::KeyCode SKILL1 = cocos2d::EventKeyboard::KeyCode::KEY_W;
const cocos2d::EventKeyboard::KeyCode SKILL2 = cocos2d::EventKeyboard::KeyCode::KEY_E;
const cocos2d::EventKeyboard::KeyCode SKILL3 = cocos2d::EventKeyboard::KeyCode::KEY_R;

//enum
enum Direction {
	LEFT, RIGHT
};

//define / undef
#define ENABLE_AUDIO
#undef ENABLE_KEYBOARD
#undef ENABLE_KARMA

#endif // __DIFINITIONS_H__
