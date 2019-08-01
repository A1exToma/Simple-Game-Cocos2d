#include"HealthBar.h"

HealthBar::HealthBar()
{
	healthSprite = cocos2d::Sprite::create("LifeBar/100.png");
	healthSprite->setScale(0.2f);
	healthSprite->setPosition(Director::getInstance()->getVisibleSize().width / 12, Director::getInstance()->getVisibleSize().height / 1.02);
}

Sprite* HealthBar::GetSprite()
{
	return healthSprite;
}

void HealthBar::updateHealth(int health)
{
	healthSprite->setTexture(mLifeBar[health / 10]);
}