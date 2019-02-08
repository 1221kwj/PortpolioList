#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{
}
HRESULT player::init(void)
{
	IMAGEMANAGER->addFrameImage("skillUI", "skillUI.bmp", 258, 65, 3, 1, true, RGB(255, 0, 255));
	_player.x = 100;
	_player.y = 425;
	_player.z = 0;
	_player.frameCount = 0;
	_player.frameX = 0;
	_player.state = START;
	_player.direction = true;
	_player.grab = false;
	_player.z_speed = 0;
	_player.x_speed = 0;
	_player.god = false;

	_player.skill1_CoolDown = 0;
	_player.skill2_CoolDown = 0;
	_player.skill3_CoolDown = 0;

	_player.skill1_Use = true;
	_player.skill2_Use = true;
	_player.skill3_Use = true;

	_player.skill1Count = 0;
	_player.skill2Count = 0;
	_player.skill3Count = 0;


	atk.dmg = 0;
	atk.rc = { 0, 0, 0, 0 };
	atk.xSpeed = 0;
	atk.zSpeed = 0;
	atk.special = false;
	IMAGEMANAGER->addFrameImage("player", "player.bmp", 6400, 10400, 16, 26, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("player2", "player2.bmp", 6400, 10400, 16, 26, true, RGB(255, 0, 255));
	minY = 425;
	maxY = 620;
	hurt = false;

	debug = false;

	foodCount = 0;
	return S_OK;
}
void player::release(void)
{

}
void player::update(void)
{
	CheckSkill();
	_player.rc = RectMakeCenter(_player.x, _player.y, 60, 80);
	atk.rc = RectMakeCenter(0, 0, 0, 0);
	frameWork();
	move();
	if (KEYMANAGER->isOnceKeyDown('T'))
	{
		(debug) ? debug = false : debug = true;
	}
}
void player::render(void)
{
	if (_player.direction)
		IMAGEMANAGER->frameRender("player", getMemDC(), _player.x - 200, _player.y - _player.z - 200, _player.frameX, _player.state);
	else
		IMAGEMANAGER->frameRender("player2", getMemDC(), _player.x - 200, _player.y - _player.z - 200, 15 - _player.frameX, _player.state);
	renderUI();
	if(debug) Rectangle(getMemDC(), atk.rc.left, atk.rc.top, atk.rc.right, atk.rc.bottom);
}
void player::CheckSkill()
{
	if (!_player.skill1_Use)
	{
		_player.skill1Count++;
	}
	if (!_player.skill2_Use)
	{
		_player.skill2Count++;
	}
	if (!_player.skill3_Use)
	{
		_player.skill3Count++;
	}
	if (_player.skill1Count > 60)
	{
		_player.skill1Count = 0;
		_player.skill1_CoolDown--;
	}
	if (_player.skill2Count > 60)
	{
		_player.skill2Count = 0;
		_player.skill2_CoolDown--;
	}
	if (_player.skill3Count > 60)
	{
		_player.skill3Count = 0;
		_player.skill3_CoolDown--;
	}
	if (_player.skill1_CoolDown < 0) _player.skill1_CoolDown = 0;
	if (_player.skill2_CoolDown < 0)_player.skill2_CoolDown = 0;
	if (_player.skill3_CoolDown < 0)_player.skill3_CoolDown = 0;

	if (_player.skill1_CoolDown == 0)_player.skill1_Use = true;
	if (_player.skill2_CoolDown == 0)_player.skill2_Use = true;
	if (_player.skill3_CoolDown == 0)_player.skill3_Use = true;
}
void player::frameWork()
{
	_player.frameCount++;
	switch (_player.state)
	{
	case START:
		if (_player.frameCount > 5)
		{
			_player.frameCount = 0;
			_player.frameX++;
			if (_player.frameX > 11)
			{
				_player.frameX = 0;
				_player.state = IDLE;
			}
		}
		break;
	case IDLE:
		if (_player.frameCount > 5)
		{
			_player.frameCount = 0;
			_player.frameX++;
			if (_player.frameX > 8)
			{
				_player.frameX = 0;
			}
		}
		break;
	case RUN:
		_player.state = IDLE;
		if (_player.frameCount > 5)
		{
			_player.frameCount = 0;
			_player.frameX++;
			if (_player.frameX > 7)
			{
				_player.frameX = 0;
			}
		}
		break;
	case ATK1:
		if (_player.frameCount > 3)
		{
			(_player.direction) ? _player.x += 1 : _player.x -= 1;
			_player.frameCount = 0;
			_player.frameX++;

			//공격
			if (_player.frameX == 2)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x + 50, _player.y - 20, 30, 30) : atk.rc = RectMakeCenter(_player.x - 50, _player.y - 20, 30, 30);
				(_player.direction) ? atk.xSpeed = 3 : atk.xSpeed = -3;
				atk.zSpeed = 0;
				atk.special = false;
				atk.dmg = 2;
			}

			if (_player.frameX > 5)
			{
				_player.frameX = 0;
				_player.state = IDLE;
			}
		}
		break;
	case ATK2:
		if (_player.frameCount > 3)
		{
			(_player.direction) ? _player.x += 1 : _player.x -= 1;
			_player.frameCount = 0;
			_player.frameX++;

			//공격
			if (_player.frameX == 3)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x + 50, _player.y - 10, 30, 50) : atk.rc = RectMakeCenter(_player.x - 50, _player.y - 10, 30, 50);
				(_player.direction) ? atk.xSpeed = 3 : atk.xSpeed = -3;
				atk.zSpeed = 0;
				atk.special = false;
				atk.dmg = 2;
			}

			if (_player.frameX > 5)
			{
				_player.frameX = 0;
				_player.state = IDLE;
				atk.special = false;
			}
		}
		break;
	case ATK3:
		if (_player.frameCount > 3)
		{
			(_player.direction) ? _player.x += 1 : _player.x -= 1;
			_player.frameCount = 0;
			_player.frameX++;

			//공격
			if (_player.frameX == 3)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x + 60, _player.y + 10, 40, 30) : atk.rc = RectMakeCenter(_player.x - 60, _player.y + 10, 40, 30);
				(_player.direction) ? atk.xSpeed = 3 : atk.xSpeed = -3;
				atk.zSpeed = 0; atk.special = false;
				atk.dmg = 3;

			}

			if (_player.frameX > 6)
			{
				_player.frameX = 0;
				_player.state = IDLE;
			}
		}
		break;
	case ATK4:
		if (_player.frameCount > 3)
		{
			(_player.direction) ? _player.x += 1 : _player.x -= 1;
			_player.frameCount = 0;
			_player.frameX++;

			//공격
			if (_player.frameX == 3 || _player.frameX == 5)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x + 80, _player.y - 10, 30, 70) : atk.rc = RectMakeCenter(_player.x - 80, _player.y - 10, 30, 70);
				(_player.direction) ? atk.xSpeed = 3 : atk.xSpeed = -3;
				atk.zSpeed = 0;
				atk.special = false;
				atk.dmg = 4;
			}

			if (_player.frameX > 8)
			{
				_player.frameX = 0;
				_player.state = IDLE;
			}
		}
		break;
	case DASHATK:
		if (_player.frameX < 7) (_player.direction) ? _player.x += 5 : _player.x -= 5;
		else
		{
			(_player.direction) ? _player.x += 1 : _player.x -= 1;
		}

		if (_player.frameCount > 3)
		{
			_player.frameCount = 0;
			_player.frameX++;
			//공격
			if (_player.frameX == 5)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x + 50, _player.y - 10, 80, 50) : atk.rc = RectMakeCenter(_player.x - 50, _player.y - 10, 80, 50);
				(_player.direction) ? atk.xSpeed = 6 : atk.xSpeed = -6;
				atk.zSpeed = 0;
				atk.special = false;
				atk.dmg = 4;
			}

			if (_player.frameX > 9)
			{
				_player.frameX = 0;
				_player.state = IDLE;
			}
		}
		break;
	case SATK1:
		(_player.direction) ? _player.x += 1 : _player.x -= 1;
		if (_player.frameCount > 2)
		{
			_player.frameCount = 0;
			_player.frameX++;

			//공격
			if (_player.frameX == 5)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x + 50, _player.y - 10, 80, 50) : atk.rc = RectMakeCenter(_player.x - 50, _player.y - 10, 80, 50);
				(_player.direction) ? atk.xSpeed = 10 : atk.xSpeed = -10;
				atk.zSpeed = 0;
				atk.dmg = 8;
				atk.special = false;
			}

			if (_player.frameX > 9)
			{
				_player.frameX = 0;
				_player.state = SATK2;
				_player.grab = true;

			}
		}
		break;
	case SATK2:
		(_player.direction) ? _player.x += 5 : _player.x -= 5;
		if (_player.frameCount > 2)
		{
			_player.frameCount = 0;
			_player.frameX++;
			if (_player.frameX > 7)
			{
				_player.frameX = 0;
				_player.state = SATK3;
				_player.grab = false;
			}

		}
		break;
	case SATK3:
		if (_player.frameCount > 2)
		{
			_player.frameCount = 0;
			_player.frameX++;

			//공격
			if (_player.frameX == 6 || _player.frameX == 8)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x + 50, _player.y - 10, 100, 80) : atk.rc = RectMakeCenter(_player.x - 50, _player.y - 10, 100, 80);
				(_player.direction) ? atk.xSpeed = 0.5 : atk.xSpeed = -0.5;
				atk.zSpeed = 0;
				atk.dmg = 3;
				atk.special = true;
			}

			if (_player.frameX > 9)
			{
				_player.frameX = 0;
				_player.state = SATK4;
			}
		}
		break;
	case SATK4:
		if (_player.frameCount > 3)
		{
			_player.frameCount = 0;
			_player.frameX++;

			//공격
			if (true)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x + 50, _player.y - 10, 100, 80) : atk.rc = RectMakeCenter(_player.x - 50, _player.y - 10, 100, 80);
				(_player.direction) ? atk.xSpeed = 0.5 : atk.xSpeed = -0.5;
				atk.zSpeed = 0;
				atk.dmg = 5;
				atk.special = true;
			}

			if (_player.frameX > 9)
			{
				_player.frameX = 0;
				_player.state = SATK5;
			}
		}
		break;
	case SATK5:
		if (_player.frameCount > 3)
		{
			_player.frameCount = 0;
			_player.frameX++;

			//공격
			if (_player.frameX == 0 || _player.frameX == 2)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x + 50, _player.y - 10, 100, 80) : atk.rc = RectMakeCenter(_player.x - 50, _player.y - 10, 100, 80);
				(_player.direction) ? atk.xSpeed = 0.5 : atk.xSpeed = -0.5;
				atk.zSpeed = 0;
				atk.dmg = 5;
				atk.special = true;
			}

			if (_player.frameX > 8)
			{
				_player.frameX = 0;
				_player.state = IDLE;
				_player.god = false;
			}
		}
		break;
	case S2ATK1:
		(_player.direction) ? _player.x += 2 : _player.x -= 2;
		if (_player.frameCount > 5)
		{
			_player.frameCount = 0;
			_player.frameX++;

			//공격
			if (_player.frameX == 1 || _player.frameX == 4)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x + 50, _player.y - 10, 30, 50) : atk.rc = RectMakeCenter(_player.x - 50, _player.y - 10, 30, 50);
				(_player.direction) ? atk.xSpeed = 5 : atk.xSpeed = -5;
				atk.zSpeed = 0;
				atk.dmg = 2;
				atk.special = false;
			}

			if (_player.frameX > 6)
			{
				_player.frameX = 0;
				_player.state = S2ATK2;
			}
		}
		break;
	case S2ATK2:
		(_player.direction) ? _player.x += 2 : _player.x -= 2;
		if (_player.frameCount > 1)
		{
			_player.frameCount = 0;
			_player.frameX++;

			//공격
			if (_player.frameX == 5 || _player.frameX == 7 || _player.frameX == 9 || _player.frameX == 11)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x + 50, _player.y - 10, 100, 80) : atk.rc = RectMakeCenter(_player.x - 50, _player.y - 10, 100, 80);
				(_player.direction) ? atk.xSpeed = 3 : atk.xSpeed = -3;
				atk.zSpeed = 0;
				atk.dmg = 5;
				atk.special = true;
			}

			if (_player.frameX > 12)
			{
				_player.frameX = 0;
				_player.state = S2ATK3;
			}
		}
		break;
	case S2ATK3:
		if (_player.frameCount > 2)
		{
			_player.frameCount = 0;
			_player.frameX++;

			//공격
			if (_player.frameX == 5 || _player.frameX == 7 || _player.frameX == 9 || _player.frameX == 11 || _player.frameX == 13)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x + 50, _player.y - 50, 80, 200) : atk.rc = RectMakeCenter(_player.x - 50, _player.y - 50, 80, 200);
				(_player.direction) ? atk.xSpeed = 0.5 : atk.xSpeed = -0.5;
				atk.zSpeed = 5;
				atk.dmg = 10;
				atk.special = true;
			}

			if (_player.frameX > 14)
			{
				_player.frameX = 0;
				_player.state = IDLE;
				_player.god = false;
			}
		}
		break;
	case S3READY:
		if (_player.frameCount > 3)
		{
			_player.frameCount = 0;
			_player.frameX++;
			if (_player.frameX >= 4 && _player.frameX <= 7)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x, _player.y - 50, 60, 150) : atk.rc = RectMakeCenter(_player.x, _player.y - 50, 60, 150);
				atk.zSpeed = 0.5;
				atk.xSpeed = 0;
				atk.dmg = 8;
				atk.special = true;
			}
			if (_player.frameX > 12)
			{
				_player.frameX = 0;
				_player.state = S3ATK1;
				_player.grab = true;
			}
		}
		break;
	case S3ATK1:
		(_player.direction) ? _player.x += 10 : _player.x -= 10;
		if (_player.frameCount > 3)
		{
			_player.frameCount = 0;
			_player.frameX++;
			if (true)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x, _player.y, 100, 60) : atk.rc = RectMakeCenter(_player.x, _player.y, 100, 60);
				(_player.direction) ? atk.xSpeed = 5 : atk.xSpeed = -5;
				atk.zSpeed = 0;
				atk.dmg = 5;
				atk.special = true;
			}
			if (_player.frameX > 5)
			{
				_player.frameX = 0;
				_player.grab = false;
				_player.state = S3ATK2;
			}
		}
		break;
	case S3ATK2:
		if (_player.frameCount > 3)
		{
			_player.frameCount = 0;
			_player.frameX++;
			if (_player.frameX > 6)
			{
				_player.frameX = 0;
				_player.state = S3ATK3;
			}
		}
		break;
	case S3ATK3:
		if (_player.frameCount > 3)
		{
			_player.frameCount = 0;
			_player.frameX++;
			if (_player.frameX % 2 == 0)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x, _player.y - 50, 120, 200) : atk.rc = RectMakeCenter(_player.x, _player.y - 50, 120, 200);
				atk.xSpeed = 0;
				atk.zSpeed = 3;
				atk.dmg = 5;
				atk.special = true;
			}
			if (_player.frameX > 15)
			{
				_player.frameX = 0;
				_player.state = S3ATK4;
			}
		}
		break;
	case S3ATK4:
		if (_player.frameCount > 2)
		{
			_player.frameCount = 0;
			_player.frameX++;
			if (true)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x, _player.y - 50, 120, 200) : atk.rc = RectMakeCenter(_player.x, _player.y - 50, 120, 200);
				atk.xSpeed = 0;
				atk.zSpeed = 1;
				atk.special = true;
				atk.dmg = 7;
			}
			if (_player.frameX > 15)
			{
				_player.frameX = 0;
				_player.state = IDLE;
				_player.god = false;
			}
		}
		break;
	case HURT:
		if (_player.frameCount > 1)
		{
			_player.frameCount = 0;
			_player.frameX++;
			if (_player.frameX > 10)
			{
				_player.frameX = 0;
				_player.state = IDLE;
				hurt = false;
			}
		}
		(_player.x_speed > 0) ? (_player.x_speed -= 0.5) : (_player.x_speed += 0.5);
		break;
	case HURT2:
		if (_player.frameCount > 5)
		{
			_player.frameCount = 0;
			_player.frameX++;
			if (abs(_player.x_speed) > 5)
			{
				_player.frameX=0;
			}
			if (_player.frameX > 4)
			{
				_player.frameX = 0;
				_player.state = WAKEUP;
			}
		}
		(_player.x_speed > 0) ? (_player.x_speed -= 0.2) : (_player.x_speed += 0.2);
		break;
	case WAKEUP:
		if (_player.frameCount > 5)
		{
			_player.frameCount = 0;
			_player.frameX++;

			if (_player.frameX > 7)
			{
				_player.frameX = 0;
				_player.state = IDLE;
				hurt = false;
			}
		}
		if (_player.frameX >= 3 && _player.frameX <= 4) (_player.direction) ? _player.x += 6 : _player.x -= 6;
		break;
	case JUMP:
		//이동
		if (_player.z==0)
		{
			_player.z_speed = 0;
			_player.z = 0;
			_player.frameX = 0;
			_player.frameCount = 0;
			_player.state = IDLE;
		}
		//z속도에따른 점프모션변화
		//if (abs(_player.z_speed) >= JUMPSPEED/3 && abs(_player.z_speed) < JUMPSPEED / 3 * 2)
		//{
		//   _player.frameX = 1;
		//}
		//else if (JUMPSPEED >= JUMPSPEED / 3*2)
		//{
		//   _player.frameX = 0;
		//}
		//else
		//{
		_player.frameX = 0;
		//}
		break;
	case JUMPATK:
		if (_player.z == 0)
		{
			_player.z_speed = 0;
			_player.z = 0;
			_player.frameX = 0;
			_player.frameCount = 0;
			_player.state = IDLE;
		}
		if (_player.frameCount > 3)
		{
			_player.frameCount = 0;
			_player.frameX++;
			if (_player.frameX  == 2|| _player.frameX == 3)
			{
				(_player.direction) ? atk.rc = RectMakeCenter(_player.x+50, _player.y - 50, 50, 50) : atk.rc = RectMakeCenter(_player.x-50, _player.y - 50, 50, 50);
				(_player.direction) ? atk.xSpeed = 3 : atk.xSpeed = -3;
				atk.zSpeed = 0;
				atk.dmg = 2;
				atk.special = false;
			}
			if (_player.frameX > 6)
			{
				_player.frameX = 0;
				_player.state = JUMP;
			}
			break;
		}
	}
	_player.z += _player.z_speed;
	_player.z_speed -= 0.5;
	if (_player.z < 0)_player.z = 0;
	_player.x += _player.x_speed;
	if (abs(_player.x_speed) <= 0.5)_player.x_speed = 0;


	foodCount++;
	if (foodCount > 20)
	{
		foodCount = 0;
		_database->SetFood(1);
	}
}
void player::move()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && (_player.state == IDLE || _player.state == JUMP || _player.state == JUMPATK||_player.state==WAKEUP))
	{
		if (_player.state == WAKEUP&&_player.frameX<3)
		{
			_player.direction = false;
		}
		else
		{
			if (_player.state == IDLE) _player.state = RUN;
			_player.x += 5;
			_player.direction = true;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && (_player.state == IDLE || _player.state == JUMP || _player.state == JUMPATK || _player.state == WAKEUP))
	{
		if (_player.state == WAKEUP&&_player.frameX<3)
		{
			_player.direction = true;
		}
		else
		{
			if (_player.state == IDLE) _player.state = RUN;
			_player.x -= 5;
			_player.direction = false;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP) && (_player.state == IDLE || _player.state == RUN || _player.state == JUMP || _player.state == JUMPATK))
	{
		_player.y -= 1;
		if (_player.state == IDLE) _player.state = RUN;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && (_player.state == IDLE || _player.state == RUN || _player.state == JUMP || _player.state == JUMPATK))
	{
		_player.y += 1;
		if (_player.state == IDLE) _player.state = RUN;

	}
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		switch (_player.state)
		{
		case IDLE:
			_player.frameX = 0;
			_player.frameCount = 0;
			_player.state = ATK1;
			break;
		case ATK1:
			_player.frameX = 0;
			_player.frameCount = 0;
			_player.state = ATK2;
			break;
		case ATK2:
			_player.frameX = 0;
			_player.frameCount = 0;
			_player.state = ATK3;
			break;
		case ATK3:
			_player.frameX = 0;
			_player.frameCount = 0;
			_player.state = ATK4;
			break;
		case RUN:
			_player.frameX = 0;
			_player.frameCount = 0;
			_player.state = DASHATK;
			break;
		case JUMP:
			_player.frameX = 0;
			_player.frameCount = 0;
			_player.state = JUMPATK;
		}
	}
	if (KEYMANAGER->isOnceKeyDown('Q') && _player.state == IDLE&&_player.skill1_Use)
	{
		_player.frameX = 0;
		_player.frameCount = 0;
		_player.state = SATK1;
		_player.god = true;
		_player.skill1_Use = false;
		_player.skill1_CoolDown = 5;
	}
	if (KEYMANAGER->isOnceKeyDown('W') && _player.state == IDLE&&_player.skill2_Use)
	{
		_player.frameX = 0;
		_player.frameCount = 0;
		_player.state = S2ATK1;
		_player.god = true;
		_player.skill2_Use = false;
		_player.skill2_CoolDown = 3;
	}
	if (KEYMANAGER->isOnceKeyDown('E') && _player.state == IDLE&&_player.skill3_Use)
	{
		_player.frameX = 0;
		_player.frameCount = 0;
		_player.state = S3READY;
		_player.god = true;
		_player.skill3_Use = false;
		_player.skill3_CoolDown = 8;
	}
	if (KEYMANAGER->isOnceKeyDown('C') && (_player.state == IDLE || _player.state == RUN))
	{
		_player.frameX = 0;
		_player.frameCount = 0;
		_player.state = JUMP;
		_player.z_speed = JUMPSPEED;
		_player.z++;
	}
	if (hurt&&_player.state!=WAKEUP)
	{
		(speacial_hurt) ? _player.state = HURT2 : _player.state = HURT;
	}
	if (_player.y < minY)_player.y = minY;
	if (_player.y > maxY)_player.y = maxY;
	if (_player.x < 0)_player.x = 0;
	if (_player.x > WINSIZEX)_player.x = WINSIZEX;
}	
void player::renderUI()
{
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(250, 250, 255));
	HFONT font = CreateFont(25, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("HY궁서B"));
	SelectObject(getMemDC(), font);
	SetTextAlign(getMemDC(), TA_RIGHT);
	char str[128];
	sprintf(str, "%d", _database->getFood());
	TextOut(getMemDC(), 250, 60, str, strlen(str));

	SetTextAlign(getMemDC(), TA_LEFT);
	sprintf(str, "%d", _database->getSoldier());
	TextOut(getMemDC(), 600, 60, str, strlen(str));

	if (_player.skill1_Use)
	{
		IMAGEMANAGER->frameRender("skillUI", getMemDC(), 20, 635, 0, 0);
	}
	else
	{
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		sprintf(str, "%d",_player.skill1_CoolDown);
		TextOut(getMemDC(), 20, 635, str, strlen(str));
	}
	if (_player.skill2_Use)
	{
		IMAGEMANAGER->frameRender("skillUI", getMemDC(), 114, 635,1, 0);
	}
	else
	{
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		sprintf(str, "%d", _player.skill2_CoolDown);
		TextOut(getMemDC(), 114, 635, str, strlen(str));
	}
	if (_player.skill3_Use)
	{
		IMAGEMANAGER->frameRender("skillUI", getMemDC(), 208, 635, 2, 0);
	}
	else
	{
		SetTextColor(getMemDC(), RGB(255, 0, 0));
		sprintf(str, "%d", _player.skill3_CoolDown);
		TextOut(getMemDC(), 208, 635, str, strlen(str));
	}
	DeleteObject(font);
}
