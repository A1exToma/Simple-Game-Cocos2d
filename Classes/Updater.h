#pragma once

#include"Includes.h"

class Updatable;

class Updater :cocos2d::Node
{
public:
	void RegisterUpdatable(Updatable* updatable);
	void UnregisterUpdatable(Updatable* updatable);

	void UpdateAll(float delta);

private:
	set<Updatable*> toUpdate;
};