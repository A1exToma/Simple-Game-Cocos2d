#include"Character.h"

Character::Character(Updater* updater)
	:Updatable(updater)
{
}

void Character::Attack()
{
	timeAttackStart = timePassed;
}

void Character::TakeDamage(int damage)
{
	health -= damage;
	health = max(0, health);
}

bool Character::IsAlive()
{
	return health > 0;
}

cocos2d::Sprite* Character::GetSprite()
{
	return characterSprite;
}

pair<float, float>Character::GetPosition()
{
	return make_pair(characterSprite->getPositionX(), characterSprite->getPositionY());
}