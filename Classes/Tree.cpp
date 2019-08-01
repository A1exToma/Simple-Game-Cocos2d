#include"Tree.h"

Tree::Tree(float x,float y)
{
	treeSprite = Sprite::create("tree.png");
	treeSprite->setPosition(Vec2(x, y));
	treeSprite->setAnchorPoint(Vec2(0.5, 0.5));

}

pair<float,float>Tree::GetPosition()
{
	return make_pair(treeSprite->getPositionX(), treeSprite->getPositionY());
}

void Tree::AddTree(cocos2d::Scene* aScene, float X, float Y) 
{
	scene11 = aScene;
	
	auto mtree = new Tree(X, Y);
	auto treePos = mtree->GetPosition();
	auto treePoint = Point(treePos.first, treePos.second);
	
	nrTrees += 1;
	mTrees.push_back(mtree);
	aScene->addChild(mtree->GetSprite(),100);

}

cocos2d::Sprite*  Tree::GetSprite()
{
	return treeSprite;
}

int Tree::GetNrTrees()
{
	return nrTrees;
}