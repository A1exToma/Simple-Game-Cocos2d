#pragma once

#include"Includes.h"
#include"Hero.h"

class Tree
{
public:
	Tree(float x,float y);
	
	void AddTree(cocos2d::Scene* aScene, float X, float Y);

	cocos2d::Sprite* GetSprite();
	cocos2d::Scene* scene11;

	pair<float, float> GetPosition();

	int GetNrTrees();

private:

	cocos2d::Sprite* treeSprite;

	int nrTrees = 0;

	vector <Tree*> mTrees;
	Hero* mHero;
};
