#include "StdAfx.h"
#include "enemyManager.h"

enemyManager::enemyManager(void)
{
}

enemyManager::~enemyManager(void)
{
}

HRESULT enemyManager::init(void)
{
	gameNode::init();

	//IMAGEMANAGER->addFrameImage("minion", "monster.bmp", 240, 144, 5, 3, true, RGB(255, 0, 255));

	return S_OK;
}

void enemyManager::release(void)
{
	gameNode::release();

}

void enemyManager::update(void)
{
	gameNode::update();

	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}
}

void enemyManager::render(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

}

void enemyManager::removeMinion(int arrNum)
{
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void enemyManager::setMinion(void)
{
	//enemy* enemy1 = new minion;
	//enemy1->init("minion", PointMake(168, 216));
	//_vMinion.push_back(enemy1);
	//
	//enemy* enemy2 = new minion;
	//enemy2->init("minion", PointMake(504, 216));
	//_vMinion.push_back(enemy2);
	//
	//enemy* enemy3 = new minion;
	//enemy3->init("minion", PointMake(168, 504));
	//_vMinion.push_back(enemy3);
	//
	//enemy* enemy4 = new minion;
	//enemy4->init("minion", PointMake(504, 504));
	//_vMinion.push_back(enemy4);
}

