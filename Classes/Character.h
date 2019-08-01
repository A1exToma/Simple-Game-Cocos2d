#pragma once

#include"Includes.h"
#include"Updatable.h"
#include"KeyboardListener.h"

class Character :public Updatable
{
public:
	Character(Updater* updater);

	virtual void Attack();
	virtual void TakeDamage(int damage);
	virtual bool IsAlive();
	
	virtual cocos2d::Sprite* GetSprite();
	
	virtual pair<float, float> GetPosition();

protected:

	cocos2d::Sprite* characterSprite;
	
	int health = 100;
	float timeAttackStart = 0;
	float timeDeadStart = 0;
	float timeHitStart = 0;

};
