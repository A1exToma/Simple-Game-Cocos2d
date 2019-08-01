#include"EnemiesCollection.h"


EnemiesCollection::EnemiesCollection(Updater* updater)
	:Updatable(updater)
{
}

void EnemiesCollection::AddEnemy(cocos2d::Scene* aScene, float X, float Y)
{
	scene = aScene;
	auto enemy = new Enemy(updater, X, Y);
	mEnemies.insert(enemy);
	aScene->addChild(enemy->GetSprite());
}

void EnemiesCollection::Attack()
{
	auto pos = mHero->GetPosition();
	auto heroPoint = Point(pos.first, pos.second);
	int count = mHitAtOnceMax;
	for (auto enemy : mEnemies)
	{
		auto posEnemy = enemy->GetPosition();
		auto enemyPoint = Point(posEnemy.first, posEnemy.second);

		auto dist = heroPoint.getDistance(enemyPoint);


		if (dist < 75 && count > 0 && enemy->IsAlive())
		{
 			enemy->TakeDamage(mHero->HeroStrengt);
		    //count--;
		}
	}
}

int EnemiesCollection::GetNumberKilled()
{
	return killed;
}

void EnemiesCollection::DoUpdate(float delta)
{
	auto heroPos = mHero->GetPosition();
	Vec2 heroPoint = Vec2(heroPos.first, heroPos.second);

	vector<Enemy*> toDelete;

	// set action for each enemy
	for (auto enemy : mEnemies)
	{
		if (enemy->IsVisibile() == false)
		{
			toDelete.push_back(enemy);
			continue;
		}

		// get enemy position
		auto enemyPos = enemy->GetPosition();
		Vec2 enemyPoint = Vec2(enemyPos.first, enemyPos.second);

		// distance to target
		auto dist = heroPoint.getDistance(enemyPoint);

		// if target alive
		if (mHero->IsAlive())
		{
			// if in range for attack 
			if (dist < 200)
			{
				int xDirection = 0;
				int yDiretion = 0;

				if (heroPos.first < enemyPos.first - 10)
				{
					xDirection = -2;
				}
				if (heroPos.first - 10 > enemyPos.first)
				{
					xDirection = 2;
				}

				if (heroPos.second < enemyPos.second)
				{
					yDiretion = -2;
				}
				if (heroPos.second > enemyPos.second)
				{
					yDiretion = 2;
				}

				// move towards target
				enemy->MoveAt(xDirection, yDiretion);
				

				if (dist < 50)
				{
					// if the enemy provoked damage to the target
					if (enemy->DidFinishAttack())
					{
						mHero->TakeDamage(1);
					}
					// try provoke damage
					else
					{
						enemy->Attack();
					}
				}
			}
		}
	}

	killed += toDelete.size();
	for (auto enemy : toDelete)
	{
		auto ptr = enemy;
		mEnemies.erase(enemy);
		scene->removeChild(ptr->GetSprite());
		//delete ptr;
	}
}

void EnemiesCollection::SetHero(Hero* aHero)
{
	mHero = aHero;
}