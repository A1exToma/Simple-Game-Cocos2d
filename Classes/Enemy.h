#pragma once

#include"Includes.h"
#include"Updatable.h"
#include"Hero.h"


class Enemy:public Character
{
public:
	Enemy(Updater*updater,float x, float y);

	void MoveAt(float x, float y);
	bool DidFinishAttack();

	void DoUpdate(float delta);
	bool IsVisibile();

private:

	bool provokeDamage = false;
	bool mIsVisible = true;

};
