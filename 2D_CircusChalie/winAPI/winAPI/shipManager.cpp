#include "StdAfx.h"
#include "shipManager.h"

shipManager::shipManager(void)
{
}

shipManager::~shipManager(void)
{
}

HRESULT shipManager::init(void)
{
	gameNode::init();

	_ship[SHIPKIND_BATTLE] = new battle;
	_ship[SHIPKIND_BATTLE]->init("battle", 0, 0);

	_ship[SHIPKIND_CARRIER] = new battle;
	_ship[SHIPKIND_CARRIER]->init("carrier", 0, 0);

	_focusShip = _ship[SHIPKIND_BATTLE];

	_space = new space;
	_space->init("bgSpace");
	_space->setShip(_focusShip);

	return S_OK;
}

void shipManager::release(void)
{
	gameNode::release();

	for (int i = 0; i < SHIPKIND_END; i++)
	{
		_ship[i]->release();
		SAFE_DELETE(_ship[i]);
	}

	_space->release();
	SAFE_DELETE(_space);
}

void shipManager::update(void)
{
	gameNode::update();
	
	//포커스 변환
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_focusShip = _ship[SHIPKIND_BATTLE];
		_space->setShip(_focusShip);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		_focusShip = _ship[SHIPKIND_CARRIER];
		_space->setShip(_focusShip);
	}

	for (int i = 0; i < SHIPKIND_END; i++)
	{
		_ship[i]->update();
	}

	_focusShip->keyControl();
}

void shipManager::render(void)
{
	_space->render();

	for (int i = 0; i < SHIPKIND_END; i++)
	{
		if (_focusShip == _ship[i])
		{
			_focusShip->focusDraw();
		}
		else
		{
			_ship[i]->defaultDraw(_focusShip->getRect());
		}
	}
}
