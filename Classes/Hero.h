#pragma once

#include"Includes.h"
#include"KeyboardListener.h"
#include"HealthBar.h"
#include"Updatable.h"
#include"Character.h"

class EnemiesCollection;
class Tree;

class Hero:public Character
{
public:

	Hero(KeyboardListener* aKeyboardListener,EnemiesCollection* aEnemiesCollection, HealthBar* aHealthBar,KeyControls aKeyControls,Updater* updater);
	cocos2d::Sprite* GetSprite();

	int HeroStrengt = 10;

	void TakeDamage(int damage)override;
	int GetHealth();
	void SetHealth(int newHealth);

	void GetKeyboardInput();

	void DoUpdate(float delta)override;
	int speed{ 3 };

	void Move();
private:

	bool CanMoveAt(float currentX, float currentY, float X, float Y);
	void Attack()override;
	
	int mDirection = 0;

	Tree* mtree;
	KeyboardListener* keyboardListener;
	KeyControls keyControls;
	HealthBar* healthBar;
	EnemiesCollection* mEnemiesCollection;

};