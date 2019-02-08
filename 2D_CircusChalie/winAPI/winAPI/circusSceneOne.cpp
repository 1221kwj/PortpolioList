#include "stdafx.h"
#include "circusSceneOne.h"


circusSceneOne::circusSceneOne()
	:_jump(NULL)
{
}


circusSceneOne::~circusSceneOne()
{
}

HRESULT circusSceneOne::init(void)
{
	gameNode::init();

	_playerImage = IMAGEMANAGER->addFrameImage("lionPlayer", "lionPlayer.bmp", 256, 64, 4, 1, true);
	_lionImage = IMAGEMANAGER->addFrameImage("lionImage", "lion.bmp", 483, 40, 4, 1, true);
	
	IMAGEMANAGER->addImage("stage1WinTable", "stage1WinTable.bmp", 93, 55, true);
	IMAGEMANAGER->addImage("lionBackGroundCenter", "lionBackGroundCenter.bmp", 800, 600, true);
	IMAGEMANAGER->addImage("stage1Opening", "stage1Opening.bmp", 800, 600, true);
	IMAGEMANAGER->addImage("lionBackGroundUp", "lionBackGroundUp.bmp", 800, 100, true);

	IMAGEMANAGER->addFrameImage("fireUnder", "fireUnder.bmp", 116, 78, 2, 1, true);
	IMAGEMANAGER->addFrameImage("largeFireRingLeft", "largeFireRingLeft.bmp", 60, 250, 2, 1, true);
	IMAGEMANAGER->addFrameImage("largeFireRingRight", "largeFireRingRight.bmp", 60, 250, 2, 1, true);

	
	_backGroundUp = IMAGEMANAGER->findImage("lionBackGroundUp");
	
	
	
	int arrPlayerStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("DIRECT_PLAYER_RIGHT_STOP", "lionPlayer", arrPlayerStop, 1, 10, true);
	KEYANIMANAGER->addArrayFrameAnimation("DIRECT_PLAYER_LEFT_STOP", "lionPlayer", arrPlayerStop, 1, 10, true);
	int arrPlayerRun[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("DIRECT_PLAYER_RIGHT_RUN", "lionPlayer", arrPlayerRun, 2, 4, true);
	KEYANIMANAGER->addArrayFrameAnimation("DIRECT_PLAYER_LEFT_RUN", "lionPlayer", arrPlayerRun, 2, 4, true);
	int arrPlayerRightJump[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("DIRECT_PLAYER_RIGHT_STOP_JUMP", "lionPlayer"
		, arrPlayerRightJump, 2, 4, false, cbRightStopJump, this);
	KEYANIMANAGER->addArrayFrameAnimation("DIRECT_PLAYER_LEFT_STOP_JUMP", "lionPlayer"
		, arrPlayerRightJump, 2, 4, false, cbRightStopJump, this);
	KEYANIMANAGER->addArrayFrameAnimation("DIRECT_PLAYER_RIGHT_RUN_JUMP", "lionPlayer"
		, arrPlayerRightJump, 2, 1, false, cbRightJump, this);
	KEYANIMANAGER->addArrayFrameAnimation("DIRECT_PLAYER_LEFT_RUN_JUMP", "lionPlayer"
		, arrPlayerRightJump, 2, 1, false, cbRightJump, this);

	int arrPlayerWinPause[] = { 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("DIRECT_PLAYER_WINPAUSE", "lionPlayer", arrPlayerWinPause, 2, 4, true);




	int arrLionRightStop[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("DIRECT_LION_RIGHT_STOP", "lionImage", arrLionRightStop, 1, 10, true);

	int arrLionRightRun[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("DIRECT_LION_RIGHT_RUN", "lionImage", arrLionRightRun, 2, 4, true);

	int arrLionRightJump[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation("DIRECT_LION_RIGHT_STOP_JUMP", "lionImage"
		, arrLionRightJump, 1, 1, false);
	KEYANIMANAGER->addArrayFrameAnimation("DIRECT_LION_RIGHT_RUN_JUMP", "lionImage"
		, arrLionRightJump, 1, 1, false);

	int arrLionHurt[] = { 3 };
	KEYANIMANAGER->addArrayFrameAnimation("DIRECT_LION_HURT", "lionImage", arrLionHurt, 1, 10, false, cbHurtMotion, this);

	_playerMotion = KEYANIMANAGER->findAnimation("DIRECT_PLAYER_RIGHT_STOP");
	_lionMotion = KEYANIMANAGER->findAnimation("DIRECT_LION_RIGHT_STOP");
	
	_playerDirect = DIRECT_PLAYER_RIGHT_STOP;
	_lionDirect = DIRECT_LION_RIGHT_STOP;

	_x = 100;
	_y = 440;

	_jump = new circusJump;
	_jump->init();

	ZeroMemory(&_addBackGD, sizeof(tagBackGround));
	_addBackGD.x = 0; _addBackGD.y = 0;
	_addBackGD.img = IMAGEMANAGER->findImage("lionBackGroundCenter");
	_addBackGD.underImg = IMAGEMANAGER->findImage("fireUnder");
	_addBackGD.set = false;
	_addBackGD.fireRect = RectMake(_addBackGD.x + 600, _addBackGD.y + 435,
		_addBackGD.underImg->getFrameWidth(), _addBackGD.underImg->getFrameHeight());
	_vBackGD.push_back(_addBackGD);

	_mapCount = 10;

	_frameX = 0;
	_frameCount = 0.0f;

	_opening = true;
	_ending = false;
	_openingCount = 0.0f;
	_count = 0;
	return S_OK;
}
void circusSceneOne::release(void)
{
	gameNode::release();

	SAFE_DELETE(_jump);
}
void circusSceneOne::update(void)
{
	gameNode::update();
	if (!_opening && !_ending)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_playerDirect = DIRECT_PLAYER_RIGHT_RUN;
			_lionDirect = DIRECT_LION_RIGHT_RUN;
			_playerMotion = KEYANIMANAGER->findAnimation("DIRECT_PLAYER_RIGHT_RUN");
			_lionMotion = KEYANIMANAGER->findAnimation("DIRECT_LION_RIGHT_RUN");
			_playerMotion->start();
			_lionMotion->start();
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_playerDirect = DIRECT_PLAYER_RIGHT_STOP;
			_lionDirect = DIRECT_LION_RIGHT_STOP;
			_playerMotion = KEYANIMANAGER->findAnimation("DIRECT_PLAYER_RIGHT_STOP");
			_lionMotion = KEYANIMANAGER->findAnimation("DIRECT_LION_RIGHT_STOP");
			_playerMotion->start();
			_lionMotion->start();
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_playerDirect = DIRECT_PLAYER_LEFT_RUN;
			_lionDirect = DIRECT_LION_RIGHT_RUN;
			_playerMotion = KEYANIMANAGER->findAnimation("DIRECT_PLAYER_RIGHT_RUN");
			_lionMotion = KEYANIMANAGER->findAnimation("DIRECT_LION_RIGHT_RUN");
			_playerMotion->start();
			_lionMotion->start();
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_playerDirect = DIRECT_PLAYER_LEFT_STOP;
			_lionDirect = DIRECT_LION_RIGHT_STOP;
			_playerMotion = KEYANIMANAGER->findAnimation("DIRECT_PLAYER_RIGHT_STOP");
			_lionMotion = KEYANIMANAGER->findAnimation("DIRECT_LION_RIGHT_STOP");
			_playerMotion->start();
			_lionMotion->start();
		}

		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			if (_playerDirect == DIRECT_PLAYER_RIGHT_STOP)
			{
				_playerDirect = DIRECT_PLAYER_RIGHT_STOP_JUMP;
				_lionDirect = DIRECT_LION_RIGHT_STOP_JUMP;
				_playerMotion = KEYANIMANAGER->findAnimation("DIRECT_PLAYER_RIGHT_STOP_JUMP");
				_lionMotion = KEYANIMANAGER->findAnimation("DIRECT_LION_RIGHT_STOP_JUMP");
				_playerMotion->start();
				_lionMotion->start();
				_jump->jumping(&_x, &_y, 8.1f, 0.2f, true, true);
			}
			else if (_playerDirect == DIRECT_PLAYER_RIGHT_RUN)
			{
				_playerDirect = DIRECT_PLAYER_RIGHT_RUN_JUMP;
				_lionDirect = DIRECT_LION_RIGHT_STOP_JUMP;
				_playerMotion = KEYANIMANAGER->findAnimation("DIRECT_PLAYER_RIGHT_RUN_JUMP");
				_lionMotion = KEYANIMANAGER->findAnimation("DIRECT_LION_RIGHT_STOP_JUMP");
				_playerMotion->start();
				_lionMotion->start();
				_jump->jumping(&_x, &_y, 8.1f, 0.2f, true, false);
			}
			else if (_playerDirect == DIRECT_PLAYER_LEFT_STOP)
			{
				_playerDirect = DIRECT_PLAYER_LEFT_STOP_JUMP;
				_lionDirect = DIRECT_LION_RIGHT_STOP_JUMP;
				_playerMotion = KEYANIMANAGER->findAnimation("DIRECT_PLAYER_LEFT_STOP_JUMP");
				_lionMotion = KEYANIMANAGER->findAnimation("DIRECT_LION_RIGHT_STOP_JUMP");
				_playerMotion->start();
				_lionMotion->start();
				_jump->jumping(&_x, &_y, 8.1f, 0.2f, false, true);
			}
			else if (_playerDirect == DIRECT_PLAYER_LEFT_RUN)
			{
				_playerDirect = DIRECT_PLAYER_LEFT_RUN_JUMP;
				_lionDirect = DIRECT_LION_RIGHT_STOP_JUMP;
				_playerMotion = KEYANIMANAGER->findAnimation("DIRECT_PLAYER_LEFT_RUN_JUMP");
				_lionMotion = KEYANIMANAGER->findAnimation("DIRECT_LION_RIGHT_STOP_JUMP");
				_playerMotion->start();
				_lionMotion->start();
				_jump->jumping(&_x, &_y, 8.1f, 0.2f, false, false);
			}

		}

		switch (_playerDirect)
		{
		case DIRECT_PLAYER_RIGHT_STOP: case DIRECT_PLAYER_LEFT_STOP:
			break;
		case DIRECT_PLAYER_RIGHT_RUN: case DIRECT_PLAYER_RIGHT_RUN_JUMP:
			//_x += 2.3f;
			for (int i = 0; i < _vBackGD.size(); ++i)
			{
				if (_mapCount > 0)
				{
					_vBackGD[i].x -= 2.3f;
					_vBackGD[i].fireRect = RectMake(_vBackGD[i].x + 600, _vBackGD[i].y + 435,
						_vBackGD[i].underImg->getFrameWidth(), _vBackGD[i].underImg->getFrameHeight());
				}
				else _x += 2.3f;

				if (_vBackGD[i].x < -800)
				{
					--_mapCount;
					setFireRing();
					_vBackGD.erase(_vBackGD.begin() + i);
					break;
				}
			}

			for (int i = 0; i < _vBackGD.size(); ++i)
			{
				if (_vBackGD[i].set) continue;

				if (_vBackGD[i].x <= 0)
				{
					_vBackGD[i].set = true;

					_addBackGD.x = _vBackGD[i].x + 800; _addBackGD.y = 0;
					_addBackGD.img = IMAGEMANAGER->findImage("lionBackGroundCenter");
					_addBackGD.set = false;
					_vBackGD.push_back(_addBackGD);
					break;
				}
			}
			break;
		case DIRECT_PLAYER_LEFT_RUN: case DIRECT_PLAYER_LEFT_RUN_JUMP:
			for (int i = 0; i < _vBackGD.size(); ++i)
			{
				if (_mapCount < 10)
				{
					_vBackGD[i].x += 2.3f;
					_vBackGD[i].fireRect = RectMake(_vBackGD[i].x + 600, _vBackGD[i].y + 435,
						_vBackGD[i].underImg->getFrameWidth(), _vBackGD[i].underImg->getFrameHeight());
				}
				if (_vBackGD[i].x > 900)
				{
					++_mapCount;
					_vBackGD.erase(_vBackGD.begin() + i);
					break;
				}
			}
			for (int i = 0; i < _vBackGD.size(); ++i)
			{
				if (_vBackGD[i].set) continue;

				if (_vBackGD[i].x > 0)
				{
					_vBackGD[i].set = true;

					_addBackGD.x = _vBackGD[i].x - 800; _addBackGD.y = 0;
					_addBackGD.img = IMAGEMANAGER->findImage("lionBackGroundCenter");
					_addBackGD.set = false;
					_vBackGD.push_back(_addBackGD);
					break;
				}
			}
			break;
		}

		frameWork();
		moveFireRing();
		if (_jump) _jump->update();
		KEYANIMANAGER->update();
		collision();
		_rc = RectMakeCenter(_x, _y, _playerImage->getFrameWidth(), _playerImage->getFrameHeight());
	}
}
void circusSceneOne::render(void)
{
	if (!_opening)
	{
		for (int i = 0; i < _vBackGD.size(); ++i)
		{
			_vBackGD[i].img->render(getMemDC(), _vBackGD[i].x, _vBackGD[i].y);
			if (_mapCount > 0) _vBackGD[i].underImg->frameRender(getMemDC(), _vBackGD[i].fireRect.left, _vBackGD[i].fireRect.top, _frameX, 0);
			if (_mapCount == 0)
			{
				IMAGEMANAGER->findImage("stage1WinTable")->render(getMemDC(), _vBackGD[i].x + 600, _vBackGD[i].y + 450);
				_stage1WinTable = RectMake(_vBackGD[i].x + 600, _vBackGD[i].y + 400,
					IMAGEMANAGER->findImage("stage1WinTable")->getWidth() ,
					IMAGEMANAGER->findImage("stage1WinTable")->getHeight() + 70);
				//Rectangle(getMemDC(), _stage1WinTable.left, _stage1WinTable.top, _stage1WinTable.right, _stage1WinTable.bottom);
			}
			char str[128];
			sprintf(str, "%d", _mapCount * 10);
			TextOut(getMemDC(), _vBackGD[i].x - 100, 530, str, strlen(str));
		}
		
		_backGroundUp->render(getMemDC());

		for (int i = 0; i < _largeFireRing.size(); i++)
		{
			_largeFireRing[i].left->frameRender(getMemDC(), _largeFireRing[i].rc.left, _largeFireRing[i].rc.top,
				_frameX, 0);
		}

		//Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
		_playerImage->aniRender(getMemDC(), _rc.left, _rc.top, _playerMotion);
		_lionImage->aniRender(getMemDC(), _rc.left - _playerImage->getFrameWidth() / 2, _rc.bottom, _lionMotion);


		for (int i = 0; i < _largeFireRing.size(); i++)
		{
			_largeFireRing[i].right->frameRender(getMemDC(),
				_largeFireRing[i].rc.left + _largeFireRing[i].left->getFrameWidth(),
				_largeFireRing[i].rc.top, _frameX, 0);
		}
	}
	else if (_opening)
	{
		IMAGEMANAGER->findImage("stage1Opening")->render(getMemDC());
		_backGroundUp->render(getMemDC());
		if (_openingCount + 400 < GetTickCount())
		{
			_openingCount = GetTickCount();
			++_count;
			if (_count > 5)
			{
				_opening = false;
			}
		}
	}
}

void circusSceneOne::cbRightJump(void* obj)
{
	circusSceneOne* c = (circusSceneOne*)obj;

	c->setPlayerDirection(DIRECT_PLAYER_RIGHT_RUN);
	c->setLionDirection(DIRECT_LION_RIGHT_STOP);
	c->setPlayerMotion(KEYANIMANAGER->findAnimation("DIRECT_PLAYER_RIGHT_RUN"));
	c->setLionMotion(KEYANIMANAGER->findAnimation("DIRECT_LION_RIGHT_STOP"));
	c->getPlayerMotion()->start();
	c->getLionMotion()->start();

}

void circusSceneOne::cbRightStopJump(void* obj)
{
	circusSceneOne* c = (circusSceneOne*)obj;

	c->setPlayerDirection(DIRECT_PLAYER_RIGHT_STOP);
	c->setLionDirection(DIRECT_LION_RIGHT_STOP);
	c->setPlayerMotion(KEYANIMANAGER->findAnimation("DIRECT_PLAYER_RIGHT_STOP"));
	c->setLionMotion(KEYANIMANAGER->findAnimation("DIRECT_LION_RIGHT_STOP"));
	c->getPlayerMotion()->start();
	c->getLionMotion()->start();
}

void circusSceneOne::cbHurtMotion(void* obj)
{
	circusSceneOne* c = (circusSceneOne*)obj;

	Sleep(1000);

	c->_largeFireRing.clear();

	c->_playerDirect = DIRECT_PLAYER_RIGHT_STOP;
	c->_playerMotion = KEYANIMANAGER->findAnimation("DIRECT_PLAYER_RIGHT_STOP");
	c->_playerMotion->start();

	c->_lionDirect = DIRECT_LION_RIGHT_STOP;
	c->_lionMotion = KEYANIMANAGER->findAnimation("DIRECT_LION_RIGHT_STOP");
	c->_lionMotion->start();

	c->_vBackGD.clear();

	ZeroMemory(&c->_addBackGD, sizeof(tagBackGround));
	c->_addBackGD.x = 0; c->_addBackGD.y = 0;
	c->_addBackGD.img = IMAGEMANAGER->findImage("lionBackGroundCenter");
	c->_addBackGD.underImg = IMAGEMANAGER->findImage("fireUnder");
	c->_addBackGD.set = false;
	c->_addBackGD.fireRect = RectMake(c->_addBackGD.x + 600, c->_addBackGD.y + 435,
		c->_addBackGD.underImg->getFrameWidth(), c->_addBackGD.underImg->getFrameHeight());
	c->_vBackGD.push_back(c->_addBackGD);
}

void circusSceneOne::frameWork(void)
{
	if (_frameCount + 400 < GetTickCount())
	{
		_frameCount = GetTickCount();
		++_frameX;
		if (_frameX > 1) _frameX = 0;
	}
}

void circusSceneOne::setFireRing(void)
{
	ZeroMemory(&_addlargeFireRing, sizeof(tagFireRing));

	_addlargeFireRing.appear = true;
	_addlargeFireRing.x = 850 + RND->getFromFloatTo(50, 100);
	_addlargeFireRing.y = 320;
	_addlargeFireRing.left = IMAGEMANAGER->findImage("largeFireRingLeft");
	_addlargeFireRing.right = IMAGEMANAGER->findImage("largeFireRingRight");
	_addlargeFireRing.rc = RectMakeCenter(_addlargeFireRing.x, _addlargeFireRing.y,
		_addlargeFireRing.left->getFrameWidth() * 2, _addlargeFireRing.left->getFrameHeight());
	_addlargeFireRing.hitBox1 = RectMakeCenter(_addlargeFireRing.x, _addlargeFireRing.y - 100, 30, 20);
	_addlargeFireRing.hitBox2 = RectMakeCenter(_addlargeFireRing.x, _addlargeFireRing.y + 115, 30, 20);
	
	_largeFireRing.push_back(_addlargeFireRing);
}

void circusSceneOne::moveFireRing(void)
{
	//if (_largeFireRing.empty == NULL) return;
	
	for (int i = 0; i < _largeFireRing.size(); i++)
	{
		_largeFireRing[i].x -= 4.3f;
		_largeFireRing[i].rc = RectMakeCenter(_largeFireRing[i].x, _largeFireRing[i].y,
			_largeFireRing[i].left->getFrameWidth() * 2, _largeFireRing[i].left->getFrameHeight());
		_largeFireRing[i].hitBox1 = RectMakeCenter(_largeFireRing[i].x, _largeFireRing[i].y - 100, 30, 20);
		_largeFireRing[i].hitBox2 = RectMakeCenter(_largeFireRing[i].x, _largeFireRing[i].y + 115, 30, 20);

		if (_largeFireRing[i].x < -900)
		{
			_largeFireRing.erase(_largeFireRing.begin() + i);
		}
	}
}

void circusSceneOne::collision(void)
{
	for (int i = 0; i < _largeFireRing.size(); i++)
	{
		if (IntersectRect(&RectMake(0, 0, 0, 0), &_largeFireRing[i].hitBox2, &_rc))
		{
			_playerDirect = DIRECT_PLAYER_RIGHT_STOP;
			_playerMotion = KEYANIMANAGER->findAnimation("DIRECT_PLAYER_RIGHT_STOP");
			_playerMotion->start();
			_lionDirect = DIRECT_LION_HURT;
			_lionMotion = KEYANIMANAGER->findAnimation("DIRECT_LION_HURT");
			_lionMotion->start();
			//char str[128];
			//sprintf(str, "Ãæµ¹");
			//TextOut(getMemDC(), 400, 300, str, strlen(str));
			break;
		}
	}

	for (int i = 0; i < _vBackGD.size(); i++)
	{
		if (IntersectRect(&RectMake(0, 0, 0, 0), &_vBackGD[i].fireRect, &_rc) && _mapCount > 0)
		{
			_playerDirect = DIRECT_PLAYER_RIGHT_STOP;
			_playerMotion = KEYANIMANAGER->findAnimation("DIRECT_PLAYER_RIGHT_STOP");
			_playerMotion->start();
			_lionDirect = DIRECT_LION_HURT;
			_lionMotion = KEYANIMANAGER->findAnimation("DIRECT_LION_HURT");
			_lionMotion->start();
			break;
		}
	}

	if (_mapCount == 0)
	{
		if (IntersectRect(&RectMake(0, 0, 0, 0), &_rc, &_stage1WinTable))
		{
			_x = (_stage1WinTable.left + _stage1WinTable.right) / 2;
			_y = _stage1WinTable.top - 20;
			_rc = RectMakeCenter(_x, _y, _playerImage->getFrameWidth(), _playerImage->getFrameHeight());
			setPlayerDirection(DIRECT_PLAYER_WINPAUSE);
			setPlayerMotion(KEYANIMANAGER->findAnimation("DIRECT_PLAYER_WINPAUSE"));
			setLionDirection(DIRECT_LION_RIGHT_STOP);
			setLionMotion(KEYANIMANAGER->findAnimation("DIRECT_LION_RIGHT_STOP"));
			getPlayerMotion()->start();
			getLionMotion()->start();
			_ending = true;

			Sleep(1000);
			SCENEMANAGER->changeScene("circusSceneTwo");
		}
	}
}

