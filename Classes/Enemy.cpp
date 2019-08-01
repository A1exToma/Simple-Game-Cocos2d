#include"Enemy.h"

Enemy::Enemy(Updater* updater, float x, float y)
	: Character(updater)
{
	characterSprite = Sprite::create("Minotaur/MinotaurFirst.png");
	characterSprite->setPosition(Vec2(x, y));
	characterSprite->setAnchorPoint(Vec2(0.5, 0.5));
	health = 500;
}

void Enemy::MoveAt(float x, float y)
{
	if (x < 0)
		characterSprite->setFlippedX(true);
	else
		characterSprite->setFlippedX(false);

		auto moveBy = MoveBy::create(0.01667f, Vec2(x, y));
		characterSprite->runAction(moveBy);

}

void Enemy::DoUpdate(float delta)
{

	timePassed += delta;

	if (timePassed - timeAttackStart > 4.0f)
	{
		provokeDamage = true;
	}

	if (!IsAlive() && mIsVisible == true)
	{
		mIsVisible = false;
		characterSprite->setOpacity(255);
		auto fadeOut = CCFadeOut::create(1.0f);
		characterSprite->runAction(fadeOut);
	}

}

bool Enemy::IsVisibile()
{
	return mIsVisible;
}

bool Enemy::DidFinishAttack()
{
	auto before = provokeDamage;
	provokeDamage = false;
	return before;
}
