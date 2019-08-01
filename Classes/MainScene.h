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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "Includes.h"
#include"KeyboardListener.h"
#include"Hero.h"
#include"HealthBar.h"
#include"Updater.h"
#include"EnemiesCollection.h"
#include"Tree.h"

class MainScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);

	void update(float delta);

private:

	void InitUpdater();
	void InitBackground();
	void InitHealthBar();
	void InitKeyboardListener();
	void InitEnemyAndHero();
	void InitTrees();
	void InitStrengthLabel();
	void InitKilledLabel();
	void InitGold();

	float mTimePassed = 0;
	int gold=0;

	float mTimeLastSpawn = -0.5f;
	float mTimeBetweenSpawns = 5.0f;
	float mTimeLastUpdate = 1.0f;
	float mTimeUpdateLevel = 5.0f;
	float mDifficultyRateIncrease = 1;
	bool isHeroDead = false;
	float mTimeHeroDead = -0.5f;
	
	cocos2d::Sprite* strengthSpritePng;
	cocos2d::Label* StrengthLabel;
	cocos2d::Label* KilledLabel;
	cocos2d::Sprite* GoldSprite;
	cocos2d::Label* GoldLabel;

	unique_ptr<Tree> mTree;
	unique_ptr<EnemiesCollection> mEnemiesCollection;
	unique_ptr<Hero> mHero;
	unique_ptr<Updater> updater;
	unique_ptr<HealthBar> healthBar;
	unique_ptr<KeyboardListener> keyboardListener;

};

#endif // __HELLOWORLD_SCENE_H__
