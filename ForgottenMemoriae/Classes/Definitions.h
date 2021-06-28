#ifndef __DIFINITIONS_H__
#define __DIFINITIONS_H__

#define DISPLAY_TIME_SPLASH_SCENE 1
#define TRANSITION_TIME 0.5

#define HERO_HITBOX_WIDTH 20
#define HERO_HITBOX_HEIGHT 40

#define ANIMATION_DELAY 0.1f
#define HERO_RUN_SPEED 0.1f
#define HERO_JUMP_SPEED 0.1f
#define HERO_FALL_SPEED -0.1f

#define OBSTACLE_COLLISION_BITMASK 0x000003
#define HERO_COLLISION_BITMASK 0x000004

// KEYBOARD
const cocos2d::EventKeyboard::KeyCode ENTER = cocos2d::EventKeyboard::KeyCode::KEY_KP_ENTER;
const cocos2d::EventKeyboard::KeyCode UP_ARROW = cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW;
const cocos2d::EventKeyboard::KeyCode DOWN_ARROW = cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW;
const cocos2d::EventKeyboard::KeyCode LEFT_ARROW = cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW;
const cocos2d::EventKeyboard::KeyCode RIGHT_ARROW = cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW;


#endif // __DIFINITIONS_H__
