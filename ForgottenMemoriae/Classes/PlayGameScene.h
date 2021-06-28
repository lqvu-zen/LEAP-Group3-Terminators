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

#ifndef __PLAYGAME_SCENE_H__
#define __PLAYGAME_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class PlayGameScene : public cocos2d::Scene
{
public:
	Node *cameraTarget;
	cocos2d::Follow *followCamera;
	static cocos2d::Scene* createScene();
	virtual bool init();
	void setViewPointCenter(float positionX, float positionY);
	virtual void update(float dt);
	CREATE_FUNC(PlayGameScene);

private:
	TMXTiledMap *map;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	Sprite *player;
	void addEnemyAt(int x, int y);
	void onKeyPressedTest(EventKeyboard::KeyCode keyCode, Event *event);

};

#endif // __PLAYGAME_SCENE_H__