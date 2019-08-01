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

#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	InitUpdater();
	InitBackground();
	InitKeyboardListener();
	InitHealthBar();
	InitEnemyAndHero();
	InitTrees();
	InitStrengthLabel();
	InitKilledLabel();
	InitGold();
	
	this->scheduleUpdate();

	return true;
}

void MainScene::InitTrees()
{
	float X = 0;
	float Y = 0;

	mTree = make_unique<Tree>(1000,100);

	const int width = Director::getInstance()->getVisibleSize().width;
	const int height = Director::getInstance()->getVisibleSize().height;

	for (int index = 0; index < 15; index++)
	{
		X = rand() % width;
		Y = rand() % height;

		if (X > 1000)
			X -= 500;
		if (X < 100)
			X += 200;

		mTree->AddTree(this, X, Y);
	}
}

void MainScene::InitUpdater()
{
	updater = make_unique<Updater>();
}

void MainScene::InitEnemyAndHero()
{
	mEnemiesCollection = make_unique<EnemiesCollection>(updater.get());
	mHero = make_unique<Hero>(keyboardListener.get(), mEnemiesCollection.get(), healthBar.get(), KeyControlProfile::WASD(), updater.get());
	auto heroSprite = mHero->GetSprite();
	this->addChild(heroSprite, 100);
	mEnemiesCollection->SetHero(mHero.get());

}

void MainScene::InitGold()
{
	//create gold sprite
	GoldSprite = Sprite::create("gold.png");
	GoldSprite->setPosition(Vec2(600, 250));
	GoldSprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(GoldSprite, 100);

	//create gold label
	GoldLabel = Label::createWithSystemFont("Gold Bag: 0", "Arial", 30);
	GoldLabel->setPosition(Director::getInstance()->getVisibleSize().width / 9.9 * 9, Director::getInstance()->getVisibleSize().height / 1.12);
	GoldLabel->setTextColor(cocos2d::Color4B::BLACK);
	this->addChild(GoldLabel,100);
}

void MainScene::InitStrengthLabel()
{
	//create the strength sprite
	strengthSpritePng = Sprite::create("strength.png");
	strengthSpritePng->setPosition(Vec2(1100, 500));
	strengthSpritePng->setAnchorPoint(Vec2(0, 0));
	this->addChild(strengthSpritePng, 100);

	//create the strength label
	StrengthLabel = Label::createWithSystemFont("Strength: 10", "Arial", 30);
	StrengthLabel->setPosition(Director::getInstance()->getVisibleSize().width / 9.9 * 9, Director::getInstance()->getVisibleSize().height / 1.07);
	StrengthLabel->setTextColor(cocos2d::Color4B::BLACK);
	this->addChild(StrengthLabel,100);
}


void MainScene::InitKilledLabel()
{
	//create killed label

	KilledLabel = Label::createWithSystemFont("Killed: 0", "Arial", 30);
	KilledLabel->setPosition(Director::getInstance()->getVisibleSize().width / 9.9 * 9, Director::getInstance()->getVisibleSize().height / 1.03);
	KilledLabel->setTextColor(::Color4B::BLACK);
	this->addChild(KilledLabel,100);
}

void MainScene::InitBackground()
{
	// init background
	for (int i = 0; i <= Director::getInstance()->getVisibleSize().width / 1024; i++)
	{
		for (int j = 0; j <= Director::getInstance()->getVisibleSize().height / 1024; j++)
		{
			cocos2d::Sprite* background = Sprite::create("grass.png");
			background->setAnchorPoint(Vec2(0, 0));
			background->setPosition(Vec2(1024 * i, 1024 * j));
			this->addChild(background, 0);
		}
	}
}

void MainScene::InitHealthBar()
{
	// init health bar
	healthBar = make_unique<HealthBar>();
	this->addChild(healthBar->GetSprite());
}


void MainScene::InitKeyboardListener()
{
	keyboardListener = make_unique<KeyboardListener>();
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener->GetListener(), this);

}

void MainScene::update(float delta)
{
	mTimePassed += delta;

	if (isHeroDead == false && mHero->IsAlive() == false)
	{
		isHeroDead = true;
		mTimeHeroDead = mTimePassed;
	}

	if (mTimePassed - mTimeHeroDead > 1.0f && isHeroDead == true)
	{
		auto gameOverLabel = Label::createWithSystemFont("Game Over", "Arial", 60);
		gameOverLabel->setAnchorPoint(Vec2(0.5, 0.5));
		gameOverLabel->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 4 * 3);
		gameOverLabel->setTextColor(cocos2d::Color4B::BLACK);
		this->addChild(gameOverLabel, 100);
	}

	const int width = Director::getInstance()->getVisibleSize().width;
	const int height = Director::getInstance()->getVisibleSize().height;
	// spawn
	if (mTimePassed - mTimeLastSpawn > mTimeBetweenSpawns && mHero->IsAlive())
	{
		mTimeLastSpawn = mTimePassed;

		float X = 0;
		float Y = 0;

		const int direction = rand() % 4;
		if (direction == 0)
		{
			X = rand() % width;
			Y = rand() % height;
		}
		if (direction == 1)
		{
			X = rand() % width;
			Y = rand() % height;
		}
		if (direction == 2)
		{
			X = rand() % width;
			Y = rand() % height;
		}
		if (direction == 3)
		{
			X = rand() % width;
			Y = rand() % height;
		}

		mEnemiesCollection->AddEnemy(this, X, Y);
	}
	//update strength label
	pair<float, float >strengthPosition = make_pair(strengthSpritePng->getPositionX(), strengthSpritePng->getPositionY());
	auto strengthPoint = Point(strengthPosition.first, strengthPosition.second);

	auto pos = mHero->GetPosition();
	auto heroPoint = Point(pos.first, pos.second);

	auto dist = heroPoint.getDistance(strengthPoint);

	if (dist < 40)
	{
		mHero->HeroStrengt += 5;

		strengthSpritePng->setOpacity(255);
		auto fadeOut = CCFadeOut::create(1.0f);
		strengthSpritePng->runAction(fadeOut);

		float pozX;
		float pozY;

		pozX = rand() % width;
		pozY = rand() % height;

		if (pozX > 1100)
			pozX -= 500;
		if (pozX < 50)
			pozX += 500;
		if (pozY > 550)
			pozY -= 300;
		if (pozY < 50)
			pozY += 300;

		strengthSpritePng = Sprite::create("strength.png");
		strengthSpritePng->setPosition(Vec2(pozX, pozY));
		strengthSpritePng->setAnchorPoint(Vec2(0, 0));
		this->addChild(strengthSpritePng, 100);

	}

	//update gold score
	pair<float, float>goldPosition = make_pair(GoldSprite->getPositionX(), GoldSprite->getPositionY());
	auto goldPoint = Point(goldPosition.first, goldPosition.second);
	
	auto pos1 = mHero->GetPosition();
	auto heroPoint1 = Point(pos1.first, pos1.second);

	auto dist1 = heroPoint1.getDistance(goldPoint);

	if (dist1 < 40)
	{
		gold++;
		
		mHero->SetHealth(5);
		if (mHero->speed < 7)
			mHero->speed += 1;

		GoldSprite->setOpacity(255);
		auto fadeOut = CCFadeOut::create(1.0f);
		GoldSprite->runAction(fadeOut);

		float pozX;
		float pozY;

		pozX = rand() % width;
		pozY = rand() % height;

		if (pozX > 1100)
			pozX -= 500;
		if (pozX < 50)
			pozX += 500;
		if (pozY > 550)
			pozY -= 300;
		if (pozY < 50)
			pozY += 300;

		GoldSprite = Sprite::create("gold.png");
		GoldSprite->setPosition(Vec2(pozX, pozY));
		GoldSprite->setAnchorPoint(Vec2(0, 0));
		this->addChild(GoldSprite, 100);

	}

	if (mTimePassed - mTimeLastUpdate > mTimeUpdateLevel && mHero->IsAlive())
	{
		mTimeLastUpdate = mTimePassed;
		mTimeBetweenSpawns = mTimeBetweenSpawns * mDifficultyRateIncrease;
	}

	//update strength on the screen
	StrengthLabel->setString("Strength: " + to_string(mHero->HeroStrengt));

	//update killed score on the screen
	const int killed = mEnemiesCollection->GetNumberKilled();
	KilledLabel->setString("Killed: " + to_string(killed));

	//update gold score on the screen
	GoldLabel->setString("Gold Bag: " + to_string(gold));

	updater->UpdateAll(delta);
}