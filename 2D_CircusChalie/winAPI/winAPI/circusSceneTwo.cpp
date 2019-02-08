#include "stdafx.h"
#include "circusSceneTwo.h"


circusSceneTwo::circusSceneTwo()
{
}


circusSceneTwo::~circusSceneTwo()
{
}

HRESULT circusSceneTwo::init(void)
{
	gameNode::init();

	/*enum LINEPDIRECTION
	{
		RIGHT_STOP,
		LEFT_STOP,
		RIGHT_RUN,
		LEFT_RUN,
		RIGHT_JUMP,
		LEFT_JUMP
	};*/

	IMAGEMANAGER->addImage("stage2BackGroundCenter", "stage2BackGroundCenter.bmp", 800, 600, true);
	IMAGEMANAGER->addImage("lionBackGroundUp", "lionBackGroundUp.bmp", 800, 100, true);

	_playerImage = IMAGEMANAGER->addFrameImage("linePlayer", "linePlayer.bmp", 256, 64, 4, 1, true);

	int arrStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("STOP", "linePlayer", arrStop, 1, 10, false);

	int arrRun[] = { 0, 1, 2 };
	KEYANIMANAGER->addArrayFrameAnimation("RUN", "linePlayer", arrRun, 3, 6, true);

	int arrJump[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("JUMP", "linePlayer", arrJump, 1, 10, false);

	_playerMotion = KEYANIMANAGER->findAnimation("STOP");
	_playerDirect = RIGHT_STOP;

	_x = 200;
	_y = 310;

	_rc = RectMakeCenter(_x, _y, _playerImage->getFrameWidth(), _playerImage->getFrameHeight());

	return S_OK;
}

void circusSceneTwo::release(void)
{
	gameNode::release();




}

void circusSceneTwo::update(void)
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_playerMotion = KEYANIMANAGER->findAnimation("RUN");
		_playerDirect = RIGHT_RUN;
		_playerMotion->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_playerMotion = KEYANIMANAGER->findAnimation("STOP");
		_playerDirect = RIGHT_STOP;
		_playerMotion->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_playerMotion = KEYANIMANAGER->findAnimation("RUN");
		_playerDirect = LEFT_RUN;
		_playerMotion->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_playerMotion = KEYANIMANAGER->findAnimation("STOP");
		_playerDirect = LEFT_STOP;
		_playerMotion->start();
	}



	switch (_playerDirect)
	{
	case RIGHT_STOP: case LEFT_STOP:
		break;
	case RIGHT_RUN:
		_x += 2.3f;
		break;
	case LEFT_RUN:
		_x -= 2.3f;
		break;
	}

	KEYANIMANAGER->update();

	_rc = RectMakeCenter(_x, _y, _playerImage->getFrameWidth(), _playerImage->getFrameHeight());
}

void circusSceneTwo::render(void)
{
	IMAGEMANAGER->findImage("stage2BackGroundCenter")->render(getMemDC());
	IMAGEMANAGER->findImage("lionBackGroundUp")->render(getMemDC());

	_playerImage->aniRender(getMemDC(), _rc.left, _rc.top, _playerMotion);
}