#pragma once

#include"Updatable.h"
#include"Enemy.h"


class EnemiesCollection :public Updatable
{
public:
	EnemiesCollection(Updater* updater);
	void AddEnemy(cocos2d::Scene* aScene, float X, float Y);
	void Attack();
	int GetNumberKilled();
	void SetHero(Hero* aHero);

private:
	void DoUpdate(float delta)override;

	Hero* mHero;

	int killed = 0;
	int mHitAtOnceMax = 2;

	cocos2d::Scene* scene;

	set <Enemy*> mEnemies;
};