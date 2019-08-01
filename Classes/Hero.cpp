#include"Hero.h"
#include"EnemiesCollection.h"
#include"Tree.h"



Hero::Hero(KeyboardListener* aKeyboardListener,EnemiesCollection * aEnemiesCollection, HealthBar* aHealthBar,KeyControls aKeyControls,Updater* updater)
	:Character(updater)
{
	keyboardListener = aKeyboardListener;
	healthBar = aHealthBar;
	keyControls = aKeyControls;
	mEnemiesCollection = aEnemiesCollection;

	characterSprite = Sprite::create("hero/HeroFirst.png");
	characterSprite->setPosition(Vec2(0, 0));
	characterSprite->setAnchorPoint(Vec2(0, 0));

}

void Hero::Move()
{
	auto direction2D = Vec2(0, 0);
	float X = characterSprite->getPositionX();
	float Y = characterSprite->getPositionY();

	if (mDirection == LEFT)
		characterSprite->setFlippedX(true);
	if (mDirection == RIGHT)
		characterSprite->setFlippedX(false);

	switch (mDirection)
	{
	case LEFT:
		direction2D = Vec2(-1 * speed, 0);
		X += -1 * speed;
		break;
	case RIGHT:
		direction2D = Vec2(1 * speed, 0);
		X += speed;
		break;
	case UP:
		direction2D = Vec2(0, 1 * speed);
		Y += speed;
		break;
	case DOWN:
		direction2D = Vec2(0, -1 * speed);
		Y += -1 * speed;
		break;
	}

	if (CanMoveAt(characterSprite->getPositionX(),characterSprite->getPositionY(),X,Y)) 
	{
		auto moveBy = MoveBy::create(0.01667f, direction2D);
		characterSprite->runAction(moveBy);
	}
}

int Hero::GetHealth()
{
	return health;
}

void Hero::SetHealth(int newHealth)
{
	if (health < 80)
		health = health + newHealth;
}

void Hero::DoUpdate(float delta)
{
	timePassed += delta;
	GetKeyboardInput();
	if (health > 0)
		Move();

}

void Hero::GetKeyboardInput()
{
	mDirection = keyboardListener->GetMoveDirection();
	if (keyboardListener->GetAttackStatus())
		Attack();
}

void Hero::TakeDamage(int damage)
{
	health -= damage;
	health = max(0, health);
	healthBar->updateHealth(health);
}

Sprite* Hero::GetSprite()
{
	return characterSprite;
}

void Hero::Attack()
{
	timeAttackStart = timePassed;
	mEnemiesCollection->Attack();
}

bool Hero::CanMoveAt(float currentX, float currentY, float X, float Y)
{
	const auto width = Director::getInstance()->getVisibleSize().width;
	const auto height = Director::getInstance()->getVisibleSize().height;
	//left
	if (X < currentX && X < 0)
	{
		return false;
	}
	//right
	if (X > currentX && X > width - 60)
	{
		return false;
	}
	// top
	if (Y > currentY && Y > height - 40)
	{
		return false;
	}
	// bottom
	if (Y < currentY && Y < 0)
	{
		return false;
	}

	return true;
}

