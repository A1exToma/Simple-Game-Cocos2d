#pragma once

#include"Includes.h"

class HealthBar
{
public:

	HealthBar();
	Sprite* GetSprite();

	void updateHealth(int health);

private:
	Sprite* healthSprite;

	vector<string>mLifeBar = {
	  "LifeBar/0.png",
	  "LifeBar/10.png" ,
	  "LifeBar/20.png" ,
	  "LifeBar/30.png" ,
	  "LifeBar/40.png" ,
	  "LifeBar/50.png" ,
	  "LifeBar/60.png" ,
	  "LifeBar/70.png" ,
	  "LifeBar/80.png" ,
	  "LifeBar/90.png" ,
	  "LifeBar/100.png"
	};

};