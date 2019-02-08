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

	_rocket = IMAGEMANAGER->addImage("rocket", "rocket.bmp", 52, 64, true, RGB(255, 0, 255));
	
	_currentHP = 8000;
	_maxHP = 10000;

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2 + 300;

	_rc = RectMakeCenter(_x, _y, _rocket->getWidth(), _rocket->getHeight());

	//총알 할당한다
	_bullet = new bullet;
	_bullet->init(10, 500);

	//불꽃(광) 코딩한다
	_flame = new flame;
	_flame->init("flame", &_x, &_y);

	//미슬 할당
	_mm1 = new missileM1;
	_mm1->init(10, 200);

	return S_OK;
}

void player::release(void)
{
	gameNode::release();

	SAFE_DELETE(_bullet);
	SAFE_DELETE(_flame);
	SAFE_DELETE(_mm1);

	//SAFE_DELETE(안성댁);
}

void player::update(void)
{
	gameNode::update();

	float elpasedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elpasedTime * 300.0f; //1초에 300픽셀 이동...

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		char temp[32];
		vector<string> vStr;
		vStr.push_back(itoa(_x, temp, 10));
		vStr.push_back(itoa(_y, temp, 10));
		vStr.push_back(itoa(_currentHP, temp, 10));
		vStr.push_back(itoa(_maxHP, temp, 10));

		TXTMANAGER->save("data.txt", vStr);
	}
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		vector<string> vStr = TXTMANAGER->load("data.txt");
		
		_x = atoi(vStr[0].c_str());
		_y = atoi(vStr[1].c_str());
		_currentHP = atoi(vStr[2].c_str());
		_maxHP = atoi(vStr[3].c_str());

		vStr.clear();
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZEX)
	{
		_x += moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0)
	{
		_x -= moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < WINSIZEY)
	{
		_y += moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > 0)
	{
		_y -= moveSpeed;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		_bullet->fire(_x, _y - 50);
	}
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_mm1->fire(_x, _y - 80);
	}

	_rc = RectMakeCenter(_x, _y, _rocket->getWidth(), _rocket->getHeight());

	//총알 업데이트
	_bullet->update();

	//불꽃 업데이트
	_flame->update();

	_mm1->update();
}

void player::render(void)
{
	_rocket->render(getMemDC(), _rc.left, _rc.top);
	_bullet->render();
	_flame->render();
	_mm1->render();
}

void player::removeMissile(int arrNum)
{
	if (_mm1)
	{
		_mm1->removeMissile(arrNum);
	}
}
