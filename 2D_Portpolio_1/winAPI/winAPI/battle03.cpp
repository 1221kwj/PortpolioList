#include "stdafx.h"
#include "battle03.h"

battle03::battle03() {}
battle03::~battle03() {}

HRESULT battle03::init(void)
{
	gameNode::init();

	_loadingImage = IMAGEMANAGER->addFrameImage("loading", "loading.bmp", 6400, 600, 8, 1, true, RGB(255, 0, 255));
	_loadingImage->setFrameX(_loadingImage->getMaxFrameX());
	_map1 = IMAGEMANAGER->addImage("map1", "map1.bmp", 800, 600, true, RGB(255, 0, 255));
	_movingMap3 = IMAGEMANAGER->addImage("_movingMap3", "movingMap3.bmp", 1600, 600, true, RGB(255, 0, 255));
	_myCattle = IMAGEMANAGER->addImage("myCattle", "playerBase.bmp", 160, 320, true, RGB(255, 0, 255));
	_enemyCattle3 = IMAGEMANAGER->addImage("enemyCattle3", "enemyBase3.bmp", 160, 320, true, RGB(255, 0, 255));
	_leftButton = IMAGEMANAGER->addFrameImage("leftButton", "battleLeftButton.bmp", 342, 1064, 2, 8, true, RGB(255, 0, 255));

	ZeroMemory(&_icon, sizeof(_icon));
	ZeroMemory(&_tempPlayer, sizeof(_tempPlayer));
	ZeroMemory(&_tempEnemy, sizeof(_tempEnemy));

	for (int i = 0; i < 5; i++)
	{
		_icon[i].rc = RectMake(200 + i * 120, 500, 100, 78);
		_icon[i]._catkind = CATKIND(i + 1);
		_icon[i].icon = IMAGEMANAGER->addFrameImage("icon", "playerIcon.bmp", 500, 156, 5, 2, true, RGB(255, 0, 255));
	}

	_icon[0].cost = 50;
	_icon[1].cost = 70;
	_icon[2].cost = 100;
	_icon[3].cost = 150;
	_icon[4].cost = 200;

	_battle03On = false;
	_loading = false;

	_loopX = 0;
	_dLoopX = 0;

	pC = new playerChar;
	eC = new enemyChar;

	rnd = 0;
	buttonFrameX = 0;
	buttonFrameY = 0;
	_randomFrame = 0.0f;
	_enemyFrame = 0.0f;
	_costCount = 0.0f;
	rndCount = 0;
	costCountMinus = 0;

	return S_OK;
}

void battle03::release(void)
{
	gameNode::release();

	SAFE_DELETE(pC);
	SAFE_DELETE(eC);
}

void battle03::update(void)
{
	gameNode::update();
	_dLoopX = 0;

	if (FRAMECOUNT + _battleStart <= GetTickCount())
	{
		_battleStart = GetTickCount();
		if (!_loading)
		{
			_loadingImage->setFrameX(_loadingImage->getFrameX() - 1);
			if (_loadingImage->getFrameX() <= 0)
			{
				_loadingImage->setFrameX(0);
				_loading = true;
			}
		}
		else if (_loading)
		{
			_loadingImage->setFrameX(_loadingImage->getFrameX() + 1);
			if (_loadingImage->getFrameX() >= _loadingImage->getMaxFrameX())
			{
				_loadingImage->setFrameX(_loadingImage->getMaxFrameX());
			}
		}
	}

	if (FRAMECOUNT + _costCount - costCountMinus <= GetTickCount())
	{
		_costCount = GetTickCount();
		if (_loading)
		{
			++pC->cost;
			if (pC->cost > pC->allcost) pC->cost = pC->allcost;
		}
	}

	if (pC->cost > pC->upgradeCost) buttonFrameX = 1;
	else buttonFrameX = 0;

	for (int i = 0; i < 5; i++)
	{
		if (_icon[i].cost > pC->cost) _icon[i].iconFrameY = 1;
		else _icon[i].iconFrameY = 0;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		playerSelect();
		costUP();
	}


	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _loopX < 800)
	{
		_loopX += 5;
		_dLoopX = 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _loopX > 0)
	{
		_loopX -= 5;
		_dLoopX = -5;
	}

	if (eC->enemyCattle < 0) eC->enemyCattle = 0;
	if (pC->myCattleHP < 0) pC->myCattleHP = 0;
	_leftButtonRC = RectMake(0, 467, 171, 133);
	_myCattleHitBox = RectMake(600 + _loopX, 85, 160, 320);
	_enemyCattleHitBox = RectMake(-780 + _loopX, 85, 160, 320);

	enemySelect();
	playerMove();
	enemyMove();
}

void battle03::render(void)
{
	if (_loading)
	{
		_movingMap3->render(getMemDC(), 0, 0, 800 - _loopX, 0, 800, 600);
		_map1->render(getMemDC(), 0, 0);
		_leftButton->frameRender(getMemDC(), _leftButtonRC.left, _leftButtonRC.top, buttonFrameX, buttonFrameY);
		_myCattle->render(getMemDC(), _myCattleHitBox.left, _myCattleHitBox.top);
		_enemyCattle3->render(getMemDC(), -780 + _loopX, 85);

		for (int i = 0; i < 5; i++)
		{
			_icon[i].icon->frameRender(getMemDC(), _icon[i].rc.left, _icon[i].rc.top, i, _icon[i].iconFrameY);
		}

		for (_viBattle01P = _vBattle01P.begin(); _viBattle01P != _vBattle01P.end(); ++_viBattle01P)
		{
			_viBattle01P->charImage->frameRender(getMemDC(),
				_viBattle01P->rc.left - _viBattle01P->charImage->getFrameX() / 2,
				_viBattle01P->rc.top - _viBattle01P->charImage->getFrameY() / 2,
				_viBattle01P->frameX, _viBattle01P->frameY);
		}

		for (_viBattle01E = _vBattle01E.begin(); _viBattle01E != _vBattle01E.end(); ++_viBattle01E)
		{
			_viBattle01E->charImage->frameRender(getMemDC(),
				_viBattle01E->rc.left - _viBattle01E->charImage->getFrameX() / 2,
				_viBattle01E->rc.top - _viBattle01E->charImage->getFrameY() / 2,
				_viBattle01E->frameX, _viBattle01E->frameY);
		}

		SystemParametersInfo(SPI_SETFONTSMOOTHING, TRUE, NULL, 0);
		SetTextAlign(getMemDC(), TA_RIGHT);
		SetTextColor(getMemDC(), RGB(125, 0, 0));
		SetBkMode(getMemDC(), TRANSPARENT);
		HFONT NanumGothic = CreateFont(40, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("Koverwatch"));
		char ptr[128];
		sprintf(ptr, "MY COST : %d / %d ", pC->cost, pC->allcost);
		SelectObject(getMemDC(), NanumGothic);
		TextOut(getMemDC(), 800, 0, ptr, strlen(ptr));

		SetTextColor(getMemDC(), RGB(0, 0, 0));
		SetBkMode(getMemDC(), TRANSPARENT);
		NanumGothic = CreateFont(30, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("Koverwatch"));
		sprintf(ptr, "%5d / 1000 ", pC->myCattleHP);
		SelectObject(getMemDC(), NanumGothic);
		TextOut(getMemDC(), _myCattleHitBox.left, _myCattleHitBox.top, ptr, strlen(ptr));

		SetTextColor(getMemDC(), RGB(0, 0, 0));
		SetBkMode(getMemDC(), TRANSPARENT);
		NanumGothic = CreateFont(30, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("Koverwatch"));
		sprintf(ptr, "%d / 1000 ", eC->enemyCattle);
		SelectObject(getMemDC(), NanumGothic);
		TextOut(getMemDC(), _enemyCattleHitBox.right + 120, _enemyCattleHitBox.top, ptr, strlen(ptr));

		for (int i = 0; i < 5; i++)
		{
			SetTextAlign(getMemDC(), TA_CENTER);
			SetTextColor(getMemDC(), RGB(255, 241, 0));
			SetBkMode(getMemDC(), TRANSPARENT);
			NanumGothic = CreateFont(25, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("Koverwatch"));
			sprintf(ptr, "%d¿ø", _icon[i].cost);
			SelectObject(getMemDC(), NanumGothic);
			TextOut(getMemDC(), _icon[i].rc.right - 10, _icon[i].rc.bottom - 20, ptr, strlen(ptr));
		}

		DeleteObject(NanumGothic);
	}

	_loadingImage->frameRender(getMemDC(), 0, 0, _loadingImage->getFrameX(), _loadingImage->getFrameY());
}

void battle03::playerSelect(void)
{
	for (int i = 0; i < 5; i++)
	{
		if (PtInRect(&_icon[i].rc, _ptMouse) && _icon[i].iconFrameY == 0)
		{
			_tempPlayer = pC->playerCharacter[i];
			_tempPlayer.x = pC->playerCharacter[i].x + _loopX;
			_tempPlayer.y = pC->playerCharacter[i].y + RND->getInt(10);
			_tempPlayer.rc = RectMakeCenter(_tempPlayer.x, _tempPlayer.y,
				_tempPlayer.charImage->getFrameWidth(), _tempPlayer.charImage->getFrameHeight());
			_tempPlayer.hitBox = RectMakeCenter(_tempPlayer.x, _tempPlayer.y, 100, 90);
			_vBattle01P.push_back(_tempPlayer);

			pC->cost -= _icon[i].cost;
			break;
		}
	}
}

void battle03::playerMove(void)
{
	for (_viBattle01P = _vBattle01P.begin(); _viBattle01P != _vBattle01P.end(); ++_viBattle01P)
	{
		for (_viBattle01E = _vBattle01E.begin(); _viBattle01E != _vBattle01E.end(); ++_viBattle01E)
		{
			if (IntersectRect(&RectMake(0, 0, 0, 0), &_viBattle01E->hitBox, &_viBattle01P->hitBox)
				&& _viBattle01E->HP > 0)
			{
				_viBattle01P->move = false;
				if (_viBattle01P->attacking && _viBattle01P->frameX == _viBattle01P->charImage->getMaxFrameX())
				{
					_viBattle01E->HP -= _viBattle01P->ATTACK;
					_viBattle01P->attacking = false;
					_viBattle01P->hit = true;

					if (_viBattle01E->HP <= 0)
					{
						_viBattle01E->frameX = 0;
						_viBattle01P->move = true;
					}
				}
				break;
			}
			else _viBattle01P->move = true;
		}

		if (IntersectRect(&RectMake(0, 0, 0, 0), &_enemyCattleHitBox, &_viBattle01P->hitBox)
			&& eC->enemyCattle > 0)
		{
			_viBattle01P->move = false;
			if (_viBattle01P->attacking && _viBattle01P->frameX == _viBattle01P->charImage->getMaxFrameX())
			{
				eC->enemyCattle -= _viBattle01P->ATTACK;
				_viBattle01P->attacking = false;
				_viBattle01P->hit = true;

				if (eC->enemyCattle <= 0)
				{
					_viBattle01P->move = true;
				}
			}
		}

		if (_viBattle01P->move && _viBattle01P->HP > 0)
		{
			_viBattle01P->frameY = 0;
			_viBattle01P->x = _viBattle01P->x - _viBattle01P->speed + _dLoopX;
		}
		else if (!_viBattle01P->move && _viBattle01P->HP > 0)
		{
			_viBattle01P->frameY = 1;
			_viBattle01P->x = _viBattle01P->x + _dLoopX;
		}

		if (_viBattle01P->HP <= 0)
		{
			_viBattle01P->frameY = 2;
			if (!_viBattle01P->die)
			{
				_viBattle01P->x += 100;
				_viBattle01P->die = true;
			}
			if (_viBattle01P->frameX == _viBattle01P->charImage->getMaxFrameX())
			{
				_viBattle01P->life = false;
				_viBattle01P->hitBox = RectMake(0, 0, 0, 0);
			}
		}

		if (_viBattle01P->count / FRAME == 1)
		{
			_viBattle01P->count = 0;
			_viBattle01P->frameX += 1;
			if (_viBattle01P->frameX > _viBattle01P->charImage->getMaxFrameX())
			{
				_viBattle01P->frameX = 0;
				_viBattle01P->hit = false;
			}
		}
		else _viBattle01P->count += 1;

		if (_viBattle01P->frameY == 1 && _viBattle01P->frameX == _viBattle01P->charImage->getMaxFrameX()
			&& !_viBattle01P->hit)
		{
			_viBattle01P->attacking = true;
		}


		_viBattle01P->rc = RectMakeCenter(_viBattle01P->x, _viBattle01P->y,
			_viBattle01P->charImage->getFrameWidth(), _viBattle01P->charImage->getFrameHeight());
		_viBattle01P->hitBox = RectMakeCenter(_viBattle01P->x, _viBattle01P->y, 100, 90);
	}

	for (_viBattle01P = _vBattle01P.begin(); _viBattle01P != _vBattle01P.end(); ++_viBattle01P)
	{
		if (!_viBattle01P->life)
		{
			_vBattle01P.erase(_viBattle01P);
			break;
		}
	}
}

void battle03::enemySelect(void)
{
	rndCount = RND->getFromIntTo(1000, 2000) + ENEMYCOUNT;

	if (rndCount + _randomFrame <= GetTickCount())
	{
		_randomFrame = GetTickCount();
		rnd = RND->getInt(2);

		switch (rnd)
		{
		case 0:
			_tempEnemy = eC->enemyCharacter[0];
			_tempEnemy.x = eC->enemyCharacter[0].x + _loopX;
			_tempEnemy.y = eC->enemyCharacter[0].y + RND->getInt(10);
			_tempEnemy.rc = RectMakeCenter(_tempEnemy.x, _tempEnemy.y,
				_tempEnemy.charImage->getFrameWidth(), _tempEnemy.charImage->getFrameHeight());
			_tempEnemy.hitBox = RectMakeCenter(_tempEnemy.x, _tempEnemy.y, 80, 60);

			_vBattle01E.push_back(_tempEnemy);
			break;
		case 1:
			_tempEnemy = eC->enemyCharacter[1];
			_tempEnemy.x = eC->enemyCharacter[1].x + _loopX;
			_tempEnemy.y = eC->enemyCharacter[1].y + RND->getInt(10);
			_tempEnemy.rc = RectMakeCenter(_tempEnemy.x, _tempEnemy.y,
				_tempEnemy.charImage->getFrameWidth(), _tempEnemy.charImage->getFrameHeight());
			_tempEnemy.hitBox = RectMakeCenter(_tempEnemy.x, _tempEnemy.y, 80, 60);

			_vBattle01E.push_back(_tempEnemy);
			break;
		case 2:
			_tempEnemy = eC->enemyCharacter[2];
			_tempEnemy.x = eC->enemyCharacter[2].x + _loopX;
			_tempEnemy.y = eC->enemyCharacter[2].y + RND->getInt(10);
			_tempEnemy.rc = RectMakeCenter(_tempEnemy.x, _tempEnemy.y,
				_tempEnemy.charImage->getFrameWidth(), _tempEnemy.charImage->getFrameHeight());
			_tempEnemy.hitBox = RectMakeCenter(_tempEnemy.x, _tempEnemy.y, 80, 60);

			_vBattle01E.push_back(_tempEnemy);
			break;
		}
	}
}

void battle03::enemyMove(void)
{
	for (_viBattle01E = _vBattle01E.begin(); _viBattle01E != _vBattle01E.end(); ++_viBattle01E)
	{
		for (_viBattle01P = _vBattle01P.begin(); _viBattle01P != _vBattle01P.end(); ++_viBattle01P)
		{
			if (IntersectRect(&RectMake(0, 0, 0, 0), &_viBattle01P->hitBox, &_viBattle01E->hitBox) && _viBattle01P->HP > 0)
			{
				_viBattle01E->move = false;
				if (_viBattle01E->attacking && _viBattle01E->frameX == _viBattle01E->charImage->getMaxFrameX())
				{
					_viBattle01P->HP -= _viBattle01E->ATTACK;
					_viBattle01E->attacking = false;
					_viBattle01E->hit = true;

					if (_viBattle01P->HP <= 0)
					{
						_viBattle01P->frameX = 0;
						_viBattle01E->move = true;
					}
				}
				break;
			}
			else _viBattle01E->move = true;
		}

		if (IntersectRect(&RectMake(0, 0, 0, 0), &_myCattleHitBox, &_viBattle01E->hitBox)
			&& pC->myCattleHP > 0)
		{
			_viBattle01E->move = false;
			if (_viBattle01E->attacking && _viBattle01E->frameX == _viBattle01E->charImage->getMaxFrameX())
			{
				pC->myCattleHP -= _viBattle01E->ATTACK;
				_viBattle01E->attacking = false;
				_viBattle01E->hit = true;

				if (pC->myCattleHP <= 0)
				{
					_viBattle01E->move = true;
				}
			}
		}

		if (_viBattle01E->move && _viBattle01E->HP > 0)
		{
			_viBattle01E->frameY = 0;
			_viBattle01E->x = _viBattle01E->x + _viBattle01E->speed + _dLoopX;
		}
		else if (!_viBattle01E->move && _viBattle01E->HP > 0)
		{
			_viBattle01E->x = _viBattle01E->x + _dLoopX;
			_viBattle01E->frameY = 1;
		}

		if (_viBattle01E->HP <= 0)
		{
			_viBattle01E->frameY = 2;
			if (!_viBattle01E->die)
			{
				_viBattle01E->x -= 100;
				_viBattle01E->die = true;
			}
			if (_viBattle01E->frameX == _viBattle01E->charImage->getMaxFrameX())
			{
				_viBattle01E->life = false;
				_viBattle01E->hitBox = RectMake(0, 0, 0, 0);
			}
		}

		if (_viBattle01E->count / FRAME == 1)
		{
			_viBattle01E->count = 0;
			_viBattle01E->frameX += 1;
			if (_viBattle01E->frameX > _viBattle01E->charImage->getMaxFrameX())
			{
				_viBattle01E->frameX = 0;
				_viBattle01E->hit = false;
			}
		}
		else _viBattle01E->count += 1;

		if (_viBattle01E->frameY == 1 && _viBattle01E->frameX == _viBattle01E->charImage->getMaxFrameX()
			&& !_viBattle01E->hit)
		{
			_viBattle01E->attacking = true;
		}

		_viBattle01E->rc = RectMakeCenter(_viBattle01E->x, _viBattle01E->y,
			_viBattle01E->charImage->getFrameWidth(), _viBattle01E->charImage->getFrameHeight());
		_viBattle01E->hitBox = RectMakeCenter(_viBattle01E->x, _viBattle01E->y, 80, 60);

	}

	for (_viBattle01E = _vBattle01E.begin(); _viBattle01E != _vBattle01E.end(); ++_viBattle01E)
	{
		if (!_viBattle01E->life)
		{
			_vBattle01E.erase(_viBattle01E);
			break;
		}
	}
}

void battle03::costUP(void)
{
	if (PtInRect(&_leftButtonRC, _ptMouse) && pC->cost > pC->upgradeCost && _loading
		&& buttonFrameY < _leftButton->getMaxFrameY())
	{
		pC->allcost += 50;
		pC->cost -= pC->upgradeCost;
		pC->upgradeCost += 40;
		costCountMinus += 2;
		buttonFrameY += 1;
		if (buttonFrameY > _leftButton->getMaxFrameY()) buttonFrameY = _leftButton->getMaxFrameY();
	}
}