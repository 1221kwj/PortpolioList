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

	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 12, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("minion", "ufo.bmp", 53, 30, true, RGB(255, 0, 255));

	_bullet = new bulletM1;
	_bullet->init("bullet", 15, 500);

	return S_OK;
}

void enemyManager::release(void)
{
	gameNode::release();

	SAFE_DELETE(_bullet);
}

void enemyManager::update(void)
{
	gameNode::update();

	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
	}

	//ÂÌµû±¸ ÃÑ¾Ë ¹ß½Î
	minionBulletFire();

	_bullet->update();
}

void enemyManager::render(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

	_bullet->render();
}

void enemyManager::removeMinion(int arrNum)
{
	SAFE_DELETE(_vMinion[arrNum]);
	_vMinion.erase(_vMinion.begin() + arrNum);
}

void enemyManager::minionBulletFire(void)
{
	for (_viMinion = _vMinion.begin(); _viMinion != _vMinion.end(); ++_viMinion)
	{
		
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();
			
			_bullet->fire(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2 + 30,
				getAngle(rc.left + (rc.right - rc.left) / 2,
				rc.bottom + (rc.top - rc.bottom) / 2,
				_player->getX(), _player->getY()), RND->getFromFloatTo(0.3f, 0.8f));
			
		}
	}
}

void enemyManager::setMinion(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			enemy* ufo = new minion;
			ufo->init("minion", PointMake(j * 100 + 100,
				i * 100 + 100));
			_vMinion.push_back(ufo);
		}
	}
}

