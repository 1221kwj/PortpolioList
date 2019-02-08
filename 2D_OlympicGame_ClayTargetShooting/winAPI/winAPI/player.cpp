#include "StdAfx.h"
#include "player.h"


player::player(void)
{
}

player::~player(void)
{
}

HRESULT player::init(void)
{
	gameNode::init();

	_hitBox1 = new hitBox;
	_hitBox1->init(330, 350);

	_hitBox2 = new hitBox;
	_hitBox2->init(470, 350);

	_bullet = new bullet;
	_bullet->init(4, 700);

	_character = IMAGEMANAGER->addFrameImage("character", "character.bmp", 300, 300, 3, 3, true, RGB(255, 0, 255));

	_x = WINCENTER.x;
	_y = WINCENTER.y + 120;

	_rc = RectMakeCenter(_x, _y, _character->getFrameWidth(), _character->getFrameHeight());

	count = 0;
	frameX = 0;
	frameCount = 0;
	leftRight = 2;
	score = 0;

	firstTime = GetTickCount();
	myTime = 0;
	endingCounting = 0;

	gameClear = false;
	gameOver = false;
	return S_OK;
}

void player::release(void)
{
	gameNode::release();

	SAFE_DELETE(_hitBox1);
	SAFE_DELETE(_hitBox2);
	SAFE_DELETE(_bullet);
}

void player::update(void)
{
	gameNode::update();

	lastTime = GetTickCount();
	myTime = 10.0f - (lastTime - firstTime) / 1000;

	if (myTime < 0)
	{
		myTime = 0;
		if (score > 1000) gameClear = true;
		else if (score < 1000) gameOver = true;
	}
	if (!gameOver && !gameClear)
	{
		if (KEYMANAGER->isOnceKeyDown('A'))
		{
			frameX = 2;
			frameCount = 100;
			_hitBox1->setFrame(2, 100);
			_hitBox2->setFrame(2, 100);
			leftRight = 0;
		}
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			frameX = 1;
			frameCount = 100;
			_hitBox1->setFrame(2, 100);
			_hitBox2->setFrame(2, 100);
			leftRight = 1;
		}

		if (frameCount > 0)
		{
			--frameCount;
			if (frameCount == 0)
			{
				frameX = 0;
				frameCount = 0;
				leftRight = 2;
			}
		}

		int randomNum = 0;
		float x = 0;
		float y = 0;
		float angle = 0;
		float gravity = 0;

		if (++count / 200 == 1)
		{
			count = 0;
			randomNum = RND->getInt(4);

			switch (randomNum)
			{
			case 0:
				x = 50;
				angle = 0;
				gravity = 0;
				break;
			case 1:
				x = 50;
				angle = PI / 4;
				gravity = 0.001;
				break;
			case 2:
				x = 750;
				angle = PI;
				gravity = 0;
				break;
			case 3:
				x = 750;
				angle = 3 * PI / 4;
				gravity = 0.001;
				break;
			}

			y = 360;
			if (_bullet)_bullet->fire(x, y, angle, gravity);
		}

		_rc = RectMakeCenter(_x, _y, _character->getFrameWidth(), _character->getFrameHeight());
		if (_hitBox1) _hitBox1->update();
		if (_hitBox2) _hitBox2->update();
		if (_bullet) _bullet->move();
		hitBoxMoving();
		hitBoxCollision();
	}
}

void player::render(void)
{
	if (gameClear || gameOver)
	{
		if (gameClear)
		{
			frameY = 1;
			if (endingCounting / 200 == 1)
			{
				++frameX;
				endingCounting = 0;
				if (frameX > 2) frameX = 2;
			}
		}
		else if (gameOver)
		{
			frameY = 2;
			if (endingCounting / 200 == 1)
			{
				++frameX;
				endingCounting = 0;
				if (frameX > 2) frameX = 2;
			}
		}
		_character->frameRender(getMemDC(), _rc.left, _rc.top, frameX, frameY);
		++endingCounting;
		if (frameX == 2)
		{
			SetTextAlign(getMemDC(), TA_RIGHT);
			SetTextColor(getMemDC(), RGB(255, 255, 255));
			SetBkMode(getMemDC(), TRANSPARENT);
			HFONT NanumGothic = CreateFont(20, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("Koverwatch"));
			char gameOverMessage[128];
			sprintf(gameOverMessage, "G A M E  O V E R");
			SelectObject(getMemDC(), NanumGothic);
			TextOut(getMemDC(), WINSIZEX / 2, WINSIZEY / 2, gameOverMessage, strlen(gameOverMessage));
		}
	}
	else
	{
		_character->frameRender(getMemDC(), _rc.left, _rc.top, frameX, 0);
		if (_hitBox1) _hitBox1->render();
		if (_hitBox2) _hitBox2->render();
		if (_bullet) _bullet->render();
	}

	SetTextAlign(getMemDC(), TA_RIGHT);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);
	HFONT NanumGothic = CreateFont(20, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("Koverwatch"));
	char ptr[128];
	sprintf(ptr, "%d", score);
	SelectObject(getMemDC(), NanumGothic);
	TextOut(getMemDC(), 770, 520, ptr, strlen(ptr));

	NanumGothic = CreateFont(22, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("Koverwatch"));
	sprintf(ptr, "%2.2f", myTime);
	SelectObject(getMemDC(), NanumGothic);
	TextOut(getMemDC(), 600, 430, ptr, strlen(ptr));
	DeleteObject(NanumGothic);
}

void player::hitBoxMoving()
{
	for (int i = 0; i < _bullet->getsize(); i++)
	{
		if (_bullet->getFire(i) && _bullet->getX(i) < _hitBox1->getX())
		{
			_hitBox1->setY(_bullet->getY(i));
			break;
		}
	}

	for (int i = 0; i < _bullet->getsize(); i++)
	{
		if (_bullet->getFire(i) && _bullet->getX(i) > _hitBox2->getX())
		{
			_hitBox2->setY(_bullet->getY(i));
			break;
		}
		
	}
}

void player::hitBoxCollision()
{
	if (leftRight == 0)
	{
		for (int i = 0; i < _bullet->getsize(); i++)
		{
			if (IntersectRect(&RectMake(0, 0, 0, 0), &_hitBox1->getRC(), &_bullet->getRC(i)) && _bullet->getFire(i))
			{
				_bullet->fireTran(i);
				score += 100;
			}
		}
	}
	else if (leftRight == 1)
	{
		for (int i = 0; i < _bullet->getsize(); i++)
		{
			if (IntersectRect(&RectMake(0, 0, 0, 0), &_hitBox2->getRC(), &_bullet->getRC(i)) && _bullet->getFire(i))
			{
				_bullet->fireTran(i);
				score += 100;
			}
		}
	}
}