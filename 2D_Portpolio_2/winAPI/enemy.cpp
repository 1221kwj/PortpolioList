#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}
HRESULT enemy::init(void)
{
	_effect = new effect;
	_effect->init();
	IMAGEMANAGER->addFrameImage("enemy1Left", "enemy1Left.bmp", 1600, 2400, 6, 9, true, RGB(255, 0, 255)); // 1600, 3200
	IMAGEMANAGER->addFrameImage("enemy1Right", "enemy1Right.bmp", 1600, 2400, 6, 9, true, RGB(255, 0, 255)); 

	IMAGEMANAGER->addFrameImage("enemy2Left", "enemy2Left.bmp", 1600, 2400, 6, 9, true, RGB(255, 0, 255)); // 1600, 3200
	IMAGEMANAGER->addFrameImage("enemy2Right", "enemy2Right.bmp", 1600, 2400, 6, 9, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("boss", "boss.bmp", 4800, 3600, 12, 9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("boss2", "boss2.bmp", 4800, 3600, 12, 9, true, RGB(255, 0, 255));


	ZeroMemory(&_enemy1, sizeof(_enemy1));
	ZeroMemory(&_enemy2, sizeof(_enemy2));
	for (int i = 0; i < 10; i++)
	{
		_enemy1[i].direction = false;//¿ÞÂÊ
		_enemy1[i].state = IDLE;

		_enemy1[i].frameX = 0;
		_enemy1[i].frameCount = 0;

		_enemy1[i].HP = 100000;
		_enemy1[i].life = false;

		_enemy1[i].x = 600;
		_enemy1[i].y = 200 + 40 * i;
		_enemy1[i].z = 0;

		_enemy1[i].xSpeed = 0;
		_enemy1[i].zSpeed = 0;

		_enemy1[i].special_frameCount = 0;
		_enemy1[i].moveType = 0;
		_enemy1[i].moveCount = 0;

		_enemy1[i].atkDelay = 0;
		_enemy1[i].atkXRange = 50;
		_enemy1[i].atkYRange = 10;
		_enemy1[i].atkZRange = 20;

		_enemy1[i].dieCount = 0;

		_enemy2[i].direction = false;//¿ÞÂÊ
		_enemy2[i].state = IDLE;

		_enemy2[i].frameX = 0;
		_enemy2[i].frameCount = 0;

		_enemy2[i].HP = 300000;
		_enemy2[i].life = false;;

		_enemy2[i].x = 500;
		_enemy2[i].y = 200+40*i;
		_enemy2[i].z = 0;

		_enemy2[i].xSpeed = 0;
		_enemy2[i].zSpeed = 0;

		_enemy2[i].special_frameCount = 0;
		_enemy2[i].moveType = 0;
		_enemy2[i].moveCount = 0;

		_enemy2[i].atkDelay = 0;
		_enemy2[i].atkXRange = 50;
		_enemy2[i].atkYRange = 10;
		_enemy2[i].atkZRange = 20;

		_enemy2[i].dieCount = 0;

	}

	startBoss = false;

	boss.HP = 10000000;
	boss.x = 800;
	boss.y = 500;
	boss.z = 0;
	boss.frameX = 0;
	boss.frameCount = 0;
	boss.direction = false;
	boss.life = true;
	boss.xSpeed = 0;
	boss.zSpeed = 0;
	boss.state = B_RUN;
	boss.moveType = BACKPLAYER;
	boss.moveCount = 0;
	boss.atkDelay = 0;
	boss.atkXRange = 0;
	boss.atkYRange = 0;
	boss.atkZRange = 0;
	boss.die = false;
	boss.dieCount = 0;

	return S_OK;
}
void enemy::release(void)
{

}
void enemy::update(void)
{
	move();
	Collision();
	frameWork();
	removeEnemy();
	if (startBoss)
	{
		bossFrameWork();
		bossMove();
		bossCollision();
	}
	_effect->update();
}
void enemy::render(void)
{
	drawEnemy();
	_effect->render();
	_database->damageDraw();
}

void enemy::makeEnemy(int num,int type)
{
	int count = 0;
	//¸÷ »ý¼º
	switch (type)
	{
	case 1:
		for (int i = 0; i < MAXENEMY; i++)
		{
			if (_enemy1[i].life)continue;
			count++;
			_enemy1[i].life = true;
			_enemy1[i].atkDelay = 0;
			_enemy1[i].die = false;
			_enemy1[i].dieCount = 0;
			_enemy1[i].direction = false;
			_enemy1[i].frameCount = 0;
			_enemy1[i].frameX = 0;
			_enemy1[i].HP = 100000;
			_enemy1[i].moveCount = 0;
			_enemy1[i].state = IDLE;
			_enemy1[i].moveType = 0;
			_enemy1[i].xSpeed = 0;
			_enemy1[i].zSpeed = 0;
			_enemy1[i].special_frameCount = 0;
			_enemy1[i].rc = { 0,0,0,0 };
			_enemy1[i].x = rand() % 2 * WINSIZEX;
			_enemy1[i].y = RND->getFromFloatTo(425, 620);
			if (count == num) break;
		}
		break;
		//¸÷2 »ý¼º
	case 2:
		for (int i = 0; i < MAXENEMY; i++)
		{
			if (_enemy2[i].life)continue;
			count++;
			_enemy2[i].life = true;
			_enemy2[i].atkDelay = 0;
			_enemy2[i].die = false;
			_enemy2[i].dieCount = 0;
			_enemy2[i].direction = false;
			_enemy2[i].frameCount = 0;
			_enemy2[i].frameX = 0;
			_enemy2[i].HP = 300000;
			_enemy2[i].moveCount = 0;
			_enemy2[i].state = IDLE;
			_enemy2[i].moveType = 0;
			_enemy2[i].xSpeed = 0;
			_enemy2[i].zSpeed = 0;
			_enemy2[i].special_frameCount = 0;
			_enemy2[i].rc = { 0,0,0,0 };
			_enemy2[i].x = rand() % 2 * WINSIZEX;
			_enemy2[i].y = RND->getFromFloatTo(425, 620);
			if (count == num) break;
		}
		break;
	}
}
void enemy::move(void)
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (!_enemy1[i].life) continue;
		
		_enemy1[i].rc = RectMakeCenter(_enemy1[i].x, _enemy1[i].y, 50, 80);

		_enemy1[i].atkDelay++;
		if (_enemy1[i].atkDelay > 120) _enemy1[i].atkDelay = 120;

		switch (_enemy1[i].state)
		{
		case IDLE:
		{
			(_player->getPlayerX() > _enemy1[i].x) ? (_enemy1[i].direction = true) : (_enemy1[i].direction = false);
			if ((abs(_player->getPlayerX() - _enemy1[i].x) < 50) && (abs(_player->getPlayerY() - _enemy1[i].y) < 10)) _enemy1[i].state = ATK;

			int t = rand() % 1000;
			if (t < 30)
			{
				_enemy1[i].state = RUN;
				_enemy1[i].moveType = TOPLAYER + rand() % 4;
			}
		}
			break;
		case RUN:
			_enemy1[i].moveCount++;
			switch (_enemy1[i].moveType)
			{
			case TOPLAYER:
				if (abs(_player->getPlayerX() - _enemy1[i].x) < 80 && abs(_player->getPlayerY() - _enemy1[i].y) > 3)
				{
					(_player->getPlayerY() > _enemy1[i].y) ? _enemy1[i].y++ : _enemy1[i].y--;
				}
				else
				{
					(_player->getPlayerX() > _enemy1[i].x) ? _enemy1[i].x++ : _enemy1[i].x--;
				}
				if (_enemy1[i].moveCount > 180)
				{
					_enemy1[i].moveCount = 0;
					_enemy1[i].state = IDLE;
				}
				if ((abs(_player->getPlayerX() - _enemy1[i].x) < 50) && (abs(_player->getPlayerY() - _enemy1[i].y) < 10))
				{
					_enemy1[i].state = ATK;
					_enemy1[i].frameX = 0;
					_enemy1[i].frameCount = 0;
				}
				break;
			case BACKPLAYER:
				(_player->getPlayerX() > _enemy1[i].x) ? _enemy1[i].x-- : _enemy1[i].x++;
				_enemy1[i].y--;
				if (_enemy1[i].moveCount > 60)
				{
					_enemy1[i].moveCount = 0;
					_enemy1[i].state = IDLE;
				}
				break;
			case BACKPLAYER2:
				(_player->getPlayerX() > _enemy1[i].x) ? _enemy1[i].x-- : _enemy1[i].x++;
				_enemy1[i].y++;
				if (_enemy1[i].moveCount > 60)
				{
					_enemy1[i].moveCount = 0;
					_enemy1[i].state = IDLE;
				}
				break;
			case SUPERTMOVE:
				if (abs(_player->getPlayerY() - _enemy1[i].y) > 3)
				{
					(_player->getPlayerY() > _enemy1[i].y) ? _enemy1[i].y++ : _enemy1[i].y--;
				}
				if (abs(_player->getPlayerX() - _enemy1[i].x) > 3)
				{
					(_player->getPlayerX() > _enemy1[i].x) ? _enemy1[i].x++ : _enemy1[i].x--;
				}
				if (_enemy1[i].moveCount > 180)
				{
					_enemy1[i].moveCount = 0;
					_enemy1[i].state = IDLE;
				}
				if ((abs(_player->getPlayerX() - _enemy1[i].x) < 50) && (abs(_player->getPlayerY() - _enemy1[i].y) < 10))
				{
					_enemy1[i].state = ATK;
					_enemy1[i].frameX = 0;
					_enemy1[i].frameCount = 0;
				}
			}
			break;
		case ATK:
			if (_enemy1[i].atkDelay < 120)
			{
				_enemy1[i].state = RUN;
				_enemy1[i].moveType = BACKPLAYER + rand() % 2;
			}
			break;
		case HURT1:
			break;
		case HURT2:
			break;
		case S1HURT1:
			break;
		case S1HURT2:
			break;
		case S2HURT1:
			break;
		case S2HURT2:
			break;
		}
		if (_enemy1[i].y < _player->minY)_enemy1[i].y = _player->minY;
		if (_enemy1[i].y > _player->maxY)_enemy1[i].y = _player->maxY;
		if (_enemy1[i].x < 0)_enemy1[i].x = 0;
		if (_enemy1[i].x > WINSIZEX)_enemy1[i].x = WINSIZEX;
	}

	//µÎ¹øÂ°¸÷
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (!_enemy2[i].life) continue;

		_enemy2[i].rc = RectMakeCenter(_enemy2[i].x, _enemy2[i].y, 50, 80);

		_enemy2[i].atkDelay++;
		if (_enemy2[i].atkDelay > 120) _enemy2[i].atkDelay = 120;

		switch (_enemy2[i].state)
		{
		case IDLE:
		{
			(_player->getPlayerX() > _enemy2[i].x) ? (_enemy2[i].direction = true) : (_enemy2[i].direction = false);
			if ((abs(_player->getPlayerX() - _enemy2[i].x) < 50) && (abs(_player->getPlayerY() - _enemy2[i].y) < 10)) _enemy2[i].state = ATK;

			int t = rand() % 1000;
			if (t < 30)
			{
				_enemy2[i].state = RUN;
				_enemy2[i].moveType = TOPLAYER + rand() % 4;
			}
		}
		break;
		case RUN:
			_enemy2[i].moveCount++;
			switch (_enemy2[i].moveType)
			{
			case TOPLAYER:
				if (abs(_player->getPlayerX() - _enemy2[i].x)<80 && abs(_player->getPlayerY() - _enemy1[i].y) > 3)
				{
					(_player->getPlayerY() > _enemy2[i].y) ? _enemy2[i].y++ : _enemy2[i].y--;
				}
				else
				{
					(_player->getPlayerX() > _enemy2[i].x) ? _enemy2[i].x++ : _enemy2[i].x--;
				}
				if (_enemy2[i].moveCount > 180)
				{
					_enemy2[i].moveCount = 0;
					_enemy2[i].state = IDLE;
				}
				if ((abs(_player->getPlayerX() - _enemy2[i].x) < 50) && (abs(_player->getPlayerY() - _enemy2[i].y) < 10))
				{
					_enemy2[i].state = ATK;
					_enemy2[i].frameX = 0;
					_enemy2[i].frameCount = 0;
				}
				break;
			case BACKPLAYER:
				(_player->getPlayerX() > _enemy2[i].x) ? _enemy2[i].x-- : _enemy2[i].x++;
				_enemy2[i].y--;
				if (_enemy2[i].moveCount > 60)
				{
					_enemy2[i].moveCount = 0;
					_enemy2[i].state = IDLE;
				}
				break;
			case BACKPLAYER2:
				(_player->getPlayerX() > _enemy2[i].x) ? _enemy2[i].x-- : _enemy2[i].x++;
				_enemy2[i].y++;
				if (_enemy2[i].moveCount > 60)
				{
					_enemy2[i].moveCount = 0;
					_enemy2[i].state = IDLE;
				}
				break;
			case SUPERTMOVE:
				if (abs(_player->getPlayerY() - _enemy2[i].y) > 3)
				{
					(_player->getPlayerY() > _enemy2[i].y) ? _enemy2[i].y++ : _enemy2[i].y--;
				}
				if (abs(_player->getPlayerX() - _enemy2[i].x) > 3)
				{
					(_player->getPlayerX() > _enemy2[i].x) ? _enemy2[i].x++ : _enemy2[i].x--;
				}
				if (_enemy2[i].moveCount > 180)
				{
					_enemy2[i].moveCount = 0;
					_enemy2[i].state = IDLE;
				}
				if ((abs(_player->getPlayerX() - _enemy2[i].x) < 50) && (abs(_player->getPlayerY() - _enemy2[i].y) < 10))
				{
					_enemy2[i].state = ATK;
					_enemy2[i].frameX = 0;
					_enemy2[i].frameCount = 0;
				}
			}
			break;
		case ATK:
			if (_enemy2[i].atkDelay < 120)
			{
				_enemy2[i].state = RUN;
				_enemy2[i].moveType = BACKPLAYER + rand() % 2;
			}
			break;
		case HURT1:
			break;
		case HURT2:
			break;
		case S1HURT1:
			break;
		case S1HURT2:
			break;
		case S2HURT1:
			break;
		case S2HURT2:
			break;
		}
		if (_enemy2[i].y < _player->minY)_enemy2[i].y = _player->minY;
		if (_enemy2[i].y > _player->maxY)_enemy2[i].y = _player->maxY;
		if (_enemy2[i].x < 0)_enemy2[i].x = 0;
		if (_enemy2[i].x > WINSIZEX)_enemy2[i].x = WINSIZEX;
	}
}
void enemy::frameWork(void)
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (!_enemy1[i].life) continue;
		if (_enemy1[i].die)
		{
			_enemy1[i].dieCount++;
		}
		++_enemy1[i].frameCount;
		switch (_enemy1[i].state)
		{
		case IDLE:
			_enemy1[i].frameCount = 0;
			break;
		case RUN:
			if (_enemy1[i].frameCount > 8)
			{
				_enemy1[i].frameCount = 0;
				_enemy1[i].frameX++;
				{
					if (_enemy1[i].frameX > 5)
					{
						_enemy1[i].frameX = 0;
					}
				}
			}
			break;
		case ATK:
			if (_enemy1[i].frameCount > 8)
			{
				_enemy1[i].frameCount = 0;
				_enemy1[i].frameX++;
				if (_enemy1[i].frameX == 2&&atkCheck(_enemy1[i].atkXRange,_enemy1[i].atkYRange,_enemy1[i].atkZRange,i)&&!_player->getHurt()&&!_player->checkGod())
				{
					_player->OnHurt((_enemy1[i].direction) ? 3 : -3, 0, false);
					_effect->makeEffect(_player->getPlayerX() - 50, _player->getPlayerY() - 100, 51);
					_database->SetSolider(10);
				}
				if (_enemy1[i].frameX > 3)
				{
					_enemy1[i].frameX = 0;
					_enemy1[i].state = IDLE;
					_enemy1[i].atkDelay = 0;
				}
			}
			break;
		case HURT1:
			if (_enemy1[i].frameCount > 15)
			{
				_enemy1[i].frameCount = 0;
				_enemy1[i].frameX++;
				if (_enemy1[i].frameX > 1)
				{
					_enemy1[i].frameX = 0;
					_enemy1[i].state = IDLE;
					if (_enemy1[i].HP < 0) _enemy1[i].state = HURT2;
				}
			}
			if (_enemy1[i].z != 0)
			{
				_enemy1[i].frameX = 0;
				_enemy1[i].state = HURT2;
			}
			break;
		case HURT2:
			if (_enemy1[i].z == 0)
			{
				if (_enemy1[i].frameCount > 8) 
				{
					_enemy1[i].frameCount = 0;
					_enemy1[i].frameX++;

					if (_enemy1[i].die) _enemy1[i].frameX--;

					if (_enemy1[i].frameX == 2)
					{
						if (_enemy1[i].HP < 0) _enemy1[i].die = true;
					}

					if (_enemy1[i].frameX > 3)
					{
						_enemy1[i].frameX = 0;
						_enemy1[i].state = IDLE;
					}
				}
			}
			break;
		case S1HURT1:
			_enemy1[i].special_frameCount++;
			if (_enemy1[i].special_frameCount % 2 == 0)
			{
				_enemy1[i].special_frameCount = 0;
				_enemy1[i].state = S2HURT1;
			}
			if (_enemy1[i].frameCount > 15)
			{
				_enemy1[i].frameCount = 0;
				_enemy1[i].frameX++;
				if (_enemy1[i].frameX > 1)
				{
					_enemy1[i].frameX = 0;
					_enemy1[i].state = IDLE;
					if (_enemy1[i].HP < 0) _enemy1[i].state = S1HURT2;
				}
			}
			if (_enemy1[i].z != 0)
			{
				_enemy1[i].frameX = 0;
				_enemy1[i].state = S1HURT2;
			}
			break;
		case S2HURT1:
			_enemy1[i].special_frameCount++;
			if (_enemy1[i].special_frameCount % 2 == 0)
			{
				_enemy1[i].special_frameCount = 0;
				_enemy1[i].state = S1HURT1;
			}
			if (_enemy1[i].frameCount > 15)
			{
				_enemy1[i].frameCount = 0;
				_enemy1[i].frameX++;
				if (_enemy1[i].frameX > 1)
				{
					_enemy1[i].frameX = 0;
					_enemy1[i].state = IDLE;
					if (_enemy1[i].HP < 0) _enemy1[i].state = S2HURT2;
				}
			}
			if (_enemy1[i].z != 0)
			{
				_enemy1[i].frameX = 0;
				_enemy1[i].state = S2HURT2;
			}
			break;
		case S1HURT2:
			_enemy1[i].special_frameCount++;
			if (_enemy1[i].special_frameCount % 2 == 0)
			{
				_enemy1[i].special_frameCount = 0;
				_enemy1[i].state = S2HURT2;
			}
			if (_enemy1[i].z == 0)
			{
				if (_enemy1[i].frameCount > 8)
				{
					_enemy1[i].frameCount = 0;
					_enemy1[i].frameX++;

					if (_enemy1[i].die) _enemy1[i].frameX--;

					if (_enemy1[i].frameX == 2)
					{
						if (_enemy1[i].HP < 0) _enemy1[i].die = true;
					}

					if (_enemy1[i].frameX > 3)
					{
						_enemy1[i].frameX = 0;
						_enemy1[i].state = IDLE;
					}
				}
			}
			break;
		case S2HURT2:
			_enemy1[i].special_frameCount++;
			if (_enemy1[i].special_frameCount % 2 == 0)
			{
				_enemy1[i].special_frameCount = 0;
				_enemy1[i].state = S1HURT2;
			}
			if (_enemy1[i].z == 0)
			{
				if (_enemy1[i].frameCount > 8)
				{
					_enemy1[i].frameCount = 0;
					_enemy1[i].frameX++;

					if (_enemy1[i].die) _enemy1[i].frameX--;

					if (_enemy1[i].frameX == 2)
					{
						if (_enemy1[i].HP < 0) _enemy1[i].die = true;
					}

					if (_enemy1[i].frameX > 3)
					{
						_enemy1[i].frameX = 0;
						_enemy1[i].state = IDLE;
					}
				}
			}
			break;
		}

		//x¿Í z ¹Ð·Á³²
		_enemy1[i].x += _enemy1[i].xSpeed;
		_enemy1[i].z += _enemy1[i].zSpeed;


		(_enemy1[i].xSpeed>0)?_enemy1[i].xSpeed -= 0.5: _enemy1[i].xSpeed += 0.5;
		_enemy1[i].zSpeed -= 0.4;
		//Á¤Áö
		if (abs(_enemy1[i].xSpeed) <= 0.5) _enemy1[i].xSpeed = 0;
		if (_enemy1[i].z < 0)_enemy1[i].z = 0;
	}

	//µÎ¹øÂ°¸÷
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (!_enemy2[i].life) continue;
		if (_enemy2[i].die)
		{
			_enemy2[i].dieCount++;
		}
		++_enemy2[i].frameCount;
		switch (_enemy2[i].state)
		{
		case IDLE:
			_enemy2[i].frameCount = 0;
			break;
		case RUN:
			if (_enemy2[i].frameCount > 8)
			{
				_enemy2[i].frameCount = 0;
				_enemy2[i].frameX++;
				{
					if (_enemy2[i].frameX > 5)
					{
						_enemy2[i].frameX = 0;
					}
				}
			}
			break;
		case ATK:
			if (_enemy2[i].frameCount > 8)
			{
				_enemy2[i].frameCount = 0;
				_enemy2[i].frameX++;
				if (_enemy2[i].frameX == 2 && atkCheck2(_enemy2[i].atkXRange, _enemy2[i].atkYRange, _enemy2[i].atkZRange, i) && !_player->getHurt() && !_player->checkGod())
				{
					_player->OnHurt((_enemy2[i].direction) ? 5 : -5, 0, true);
					_effect->makeEffect(_player->getPlayerX() - 50, _player->getPlayerY() - 100, 51);
					_database->SetSolider(20);
				}
				if (_enemy2[i].frameX > 3)
				{
					_enemy2[i].frameX = 0;
					_enemy2[i].state = IDLE;
					_enemy2[i].atkDelay = 0;
				}
			}
			break;
		case HURT1:
			if (_enemy2[i].frameCount > 15)
			{
				_enemy2[i].frameCount = 0;
				_enemy2[i].frameX++;
				if (_enemy2[i].frameX > 1)
				{
					_enemy2[i].frameX = 0;
					_enemy2[i].state = IDLE;
					if (_enemy2[i].HP < 0) _enemy2[i].state = HURT2;
				}
			}
			if (_enemy2[i].z != 0)
			{
				_enemy2[i].frameX = 0;
				_enemy2[i].state = HURT2;
			}
			break;
		case HURT2:
			if (_enemy2[i].z == 0)
			{
				if (_enemy2[i].frameCount > 8)
				{
					_enemy2[i].frameCount = 0;
					_enemy2[i].frameX++;

					if (_enemy2[i].die) _enemy2[i].frameX--;

					if (_enemy2[i].frameX == 2)
					{
						if (_enemy2[i].HP < 0) _enemy2[i].die = true;
					}

					if (_enemy2[i].frameX > 3)
					{
						_enemy2[i].frameX = 0;
						_enemy2[i].state = IDLE;
					}
				}
			}
			break;
		case S1HURT1:
			_enemy2[i].special_frameCount++;
			if (_enemy2[i].special_frameCount % 2 == 0)
			{
				_enemy2[i].special_frameCount = 0;
				_enemy2[i].state = S2HURT1;
			}
			if (_enemy2[i].frameCount > 15)
			{
				_enemy2[i].frameCount = 0;
				_enemy2[i].frameX++;
				if (_enemy2[i].frameX > 1)
				{
					_enemy2[i].frameX = 0;
					_enemy2[i].state = IDLE;
					if (_enemy2[i].HP < 0) _enemy2[i].state = S1HURT2;
				}
			}
			if (_enemy2[i].z != 0)
			{
				_enemy2[i].frameX = 0;
				_enemy2[i].state = S1HURT2;
			}
			break;
		case S2HURT1:
			_enemy2[i].special_frameCount++;
			if (_enemy2[i].special_frameCount % 2 == 0)
			{
				_enemy2[i].special_frameCount = 0;
				_enemy2[i].state = S1HURT1;
			}
			if (_enemy2[i].frameCount > 15)
			{
				_enemy2[i].frameCount = 0;
				_enemy2[i].frameX++;
				if (_enemy2[i].frameX > 1)
				{
					_enemy2[i].frameX = 0;
					_enemy2[i].state = IDLE;
					if (_enemy2[i].HP < 0) _enemy2[i].state = S2HURT2;
				}
			}
			if (_enemy2[i].z != 0)
			{
				_enemy2[i].frameX = 0;
				_enemy2[i].state = S2HURT2;
			}
			break;
		case S1HURT2:
			_enemy2[i].special_frameCount++;
			if (_enemy2[i].special_frameCount % 2 == 0)
			{
				_enemy2[i].special_frameCount = 0;
				_enemy2[i].state = S2HURT2;
			}
			if (_enemy2[i].z == 0)
			{
				if (_enemy2[i].frameCount > 8)
				{
					_enemy2[i].frameCount = 0;
					_enemy2[i].frameX++;

					if (_enemy2[i].die) _enemy2[i].frameX--;

					if (_enemy2[i].frameX == 2)
					{
						if (_enemy2[i].HP < 0) _enemy2[i].die = true;
					}

					if (_enemy2[i].frameX > 3)
					{
						_enemy2[i].frameX = 0;
						_enemy2[i].state = IDLE;
					}
				}
			}
			break;
		case S2HURT2:
			_enemy2[i].special_frameCount++;
			if (_enemy2[i].special_frameCount % 2 == 0)
			{
				_enemy2[i].special_frameCount = 0;
				_enemy2[i].state = S1HURT2;
			}
			if (_enemy2[i].z == 0)
			{
				if (_enemy2[i].frameCount > 8)
				{
					_enemy2[i].frameCount = 0;
					_enemy2[i].frameX++;

					if (_enemy2[i].die) _enemy2[i].frameX--;

					if (_enemy2[i].frameX == 2)
					{
						if (_enemy2[i].HP < 0) _enemy2[i].die = true;
					}

					if (_enemy2[i].frameX > 3)
					{
						_enemy2[i].frameX = 0;
						_enemy2[i].state = IDLE;
					}
				}
			}
			break;
		}

		//x¿Í z ¹Ð·Á³²
		_enemy2[i].x += _enemy2[i].xSpeed;
		_enemy2[i].z += _enemy2[i].zSpeed;


		(_enemy2[i].xSpeed>0) ? _enemy2[i].xSpeed -= 0.5 : _enemy2[i].xSpeed += 0.5;
		_enemy2[i].zSpeed -= 0.4;
		//Á¤Áö
		if (abs(_enemy2[i].xSpeed) <= 0.5) _enemy2[i].xSpeed = 0;
		if (_enemy2[i].z < 0)_enemy2[i].z = 0;
	}
}
void enemy::drawEnemy()
{
	/*
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (!_enemy1[i].life)continue;
		(!_enemy1[i].direction) ? (IMAGEMANAGER->frameRender("enemy1Left", getMemDC(), _enemy1[i].rc.left-100, _enemy1[i].rc.top-100-_enemy1[i].z, _enemy1[i].frameX, _enemy1[i].state)) :
			(IMAGEMANAGER->frameRender("enemy1Right", getMemDC(), _enemy1[i].rc.left-100, _enemy1[i].rc.top-100- _enemy1[i].z, 5 - _enemy1[i].frameX, _enemy1[i].state));
		_player->render();
	    // Rectangle(getMemDC(), _enemy1[i].rc.left, _enemy1[i].rc.top, _enemy1[i].rc.right, _enemy1[i].rc.bottom);
		// Rectangle(getMemDC(), _enemy1[i].x-10, _enemy1[i].y-10, _enemy1[i].x+10, _enemy1[i].y+10);
	}
	*/
	int wifer = 0;
	while (wifer < WINSIZEY)
	{
		wifer++;
		for (int i = 0; i < MAXENEMY; i++)
		{
			if (!_enemy1[i].life)continue;
			if (abs(wifer - _enemy1[i].y) <= 1)
			{
				if (!_enemy1[i].die)
				{
					(!_enemy1[i].direction) ? (IMAGEMANAGER->frameRender("enemy1Left", getMemDC(), _enemy1[i].rc.left - 100, _enemy1[i].rc.top - 100 - _enemy1[i].z, _enemy1[i].frameX, _enemy1[i].state)) :
						(IMAGEMANAGER->frameRender("enemy1Right", getMemDC(), _enemy1[i].rc.left - 100, _enemy1[i].rc.top - 100 - _enemy1[i].z, 5 - _enemy1[i].frameX, _enemy1[i].state));
				}
				else if(_enemy1[i].dieCount%2==0)
				{
					(!_enemy1[i].direction) ? (IMAGEMANAGER->frameRender("enemy1Left", getMemDC(), _enemy1[i].rc.left - 100, _enemy1[i].rc.top - 100 - _enemy1[i].z, _enemy1[i].frameX, _enemy1[i].state)) :
						(IMAGEMANAGER->frameRender("enemy1Right", getMemDC(), _enemy1[i].rc.left - 100, _enemy1[i].rc.top - 100 - _enemy1[i].z, 5 - _enemy1[i].frameX, _enemy1[i].state));
				}
			}
		}
		for (int i = 0; i < MAXENEMY; i++)
		{
			if (!_enemy2[i].life)continue;
			if (abs(wifer - _enemy2[i].y) <= 1)
			{

				if (!_enemy2[i].die)
				{
					(!_enemy2[i].direction) ? (IMAGEMANAGER->frameRender("enemy2Left", getMemDC(), _enemy2[i].rc.left - 100, _enemy2[i].rc.top - 100 - _enemy2[i].z, _enemy2[i].frameX, _enemy2[i].state)) :
						(IMAGEMANAGER->frameRender("enemy2Right", getMemDC(), _enemy2[i].rc.left - 100, _enemy2[i].rc.top - 100 - _enemy2[i].z, 5 - _enemy2[i].frameX, _enemy2[i].state));
				}
				else if (_enemy2[i].dieCount % 2 == 0)
				{
					(!_enemy2[i].direction) ? (IMAGEMANAGER->frameRender("enemy2Left", getMemDC(), _enemy2[i].rc.left - 100, _enemy2[i].rc.top - 100 - _enemy2[i].z, _enemy2[i].frameX, _enemy2[i].state)) :
						(IMAGEMANAGER->frameRender("enemy2Right", getMemDC(), _enemy2[i].rc.left - 100, _enemy2[i].rc.top - 100 - _enemy2[i].z, 5 - _enemy2[i].frameX, _enemy2[i].state));
				}
			}
		}
		if (abs(wifer - _player->getPlayerY()) <= 1)
		{
			_player->render();
		}
		if (abs(wifer - boss.y) <= 1&&startBoss)
		{
			bossDraw();
		}

	}
}
void enemy::Collision()
{
	RECT rc;
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (!_enemy1[i].life||_enemy1[i].die) continue;
		if (IntersectRect(&rc, &_player->getAtkRect(), &_enemy1[i].rc))
		{
			if (abs(_player->getPlayerY() - _enemy1[i].y) < 40&&_player->getAtkType())
			{
				_enemy1[i].frameX = 0;
				_enemy1[i].frameCount = 0;
				(!_player->getAtkType()) ? (_enemy1[i].state = HURT1) : (_enemy1[i].state = S1HURT1);
				_enemy1[i].xSpeed = _player->getXSpeed();
				_enemy1[i].zSpeed = _player->getZSpeed();
				_enemy1[i].special_frameCount = 0;
				int Dmg= _player->getDmg();
				_database->makeDamage(_enemy1[i].x, _enemy1[i].rc.top - _enemy1[i].z, 10, 10, Dmg,true);
				_enemy1[i].HP -= Dmg;
			}
			else if (abs(_player->getPlayerY() - _enemy1[i].y) < 20)
			{
				_enemy1[i].frameX = 0;
				_enemy1[i].frameCount = 0;
				(!_player->getAtkType()) ? (_enemy1[i].state = HURT1) : (_enemy1[i].state = S1HURT1);
				_enemy1[i].xSpeed = _player->getXSpeed();
				_enemy1[i].zSpeed = _player->getZSpeed();
				_enemy1[i].special_frameCount = 0;
				_effect->makeEffect(_player->getAtkRect().left+(_player->getAtkRect().right- _player->getAtkRect().left)/2, _player->getAtkRect().top, 50);
				int Dmg = _player->getDmg();
				_database->makeDamage(_enemy1[i].x, _enemy1[i].rc.top - _enemy1[i].z, 10, 10, Dmg,false);
				_enemy1[i].HP -= Dmg;
			}
		}
		if (IntersectRect(&rc, &_player->getPlayerRect(), &_enemy1[i].rc)&&_player->getGrab())
		{
			(_player->getDirection()) ? (_enemy1[i].x = _player->getPlayerX() - 10) : (_enemy1[i].x = _player->getPlayerX() + 10);
			//_enemy1[i].y = _player->getPlayerY();
		}
	}

	for (int i = 0; i < MAXENEMY; i++)
	{
		if (!_enemy2[i].life || _enemy2[i].die) continue;
		if (IntersectRect(&rc, &_player->getAtkRect(), &_enemy2[i].rc))
		{
			if (abs(_player->getPlayerY() - _enemy2[i].y) < 40 && _player->getAtkType())
			{
				_enemy2[i].frameX = 0;
				_enemy2[i].frameCount = 0;
				(!_player->getAtkType()) ? (_enemy2[i].state = HURT1) : (_enemy2[i].state = S1HURT1);
				_enemy2[i].xSpeed = _player->getXSpeed();
				_enemy2[i].zSpeed = _player->getZSpeed();
				_enemy2[i].special_frameCount = 0;
				int Dmg = _player->getDmg();
				_database->makeDamage(_enemy2[i].x, _enemy2[i].rc.top - _enemy2[i].z, 10, 10, Dmg,true);
				_enemy2[i].HP -= Dmg;
				mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
				mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
			}
			else if (abs(_player->getPlayerY() - _enemy2[i].y) < 20)
			{
				_enemy2[i].frameX = 0;
				_enemy2[i].frameCount = 0;
				(!_player->getAtkType()) ? (_enemy2[i].state = HURT1) : (_enemy2[i].state = S1HURT1);
				_enemy2[i].xSpeed = _player->getXSpeed();
				_enemy2[i].zSpeed = _player->getZSpeed();
				_enemy2[i].special_frameCount = 0;
				_effect->makeEffect(_player->getAtkRect().left + (_player->getAtkRect().right - _player->getAtkRect().left) / 2, _player->getAtkRect().top, 50);
				int Dmg = _player->getDmg();
				_database->makeDamage(_enemy2[i].x, _enemy2[i].rc.top - _enemy2[i].z, 10, 10, Dmg,false);
				_enemy2[i].HP -= Dmg;
				mciSendCommand(1, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL);
				mciSendCommand(1, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlay);
			}
		}
		if (IntersectRect(&rc, &_player->getPlayerRect(), &_enemy2[i].rc) && _player->getGrab())
		{
			(_player->getDirection()) ? (_enemy2[i].x = _player->getPlayerX() - 10) : (_enemy2[i].x = _player->getPlayerX() + 10);
			//_enemy2[i].y = _player->getPlayerY();
		}
	}
}
bool enemy::atkCheck(float xRange, float yRange,float zRange,int arrayNum)
{
	if (abs(_player->getPlayerX() - _enemy1[arrayNum].x) < xRange&&abs(_player->getPlayerY() - _enemy1[arrayNum].y) < yRange&&abs(_player->getPlayerZ() - _enemy1[arrayNum].z) < zRange)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool enemy::atkCheck2(float xRange, float yRange, float zRange, int arrayNum)
{
	if (abs(_player->getPlayerX() - _enemy2[arrayNum].x) < xRange&&abs(_player->getPlayerY() - _enemy2[arrayNum].y) < yRange&&abs(_player->getPlayerZ() - _enemy2[arrayNum].z) < zRange)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool enemy::atkCheck3(float xRange, float yRange, float zRange)
{
	if (abs(_player->getPlayerX() - boss.x) < xRange&&abs(_player->getPlayerY() - boss.y) < yRange&&abs(_player->getPlayerZ() - boss.z) < zRange)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void enemy::removeEnemy()
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (_enemy1[i].dieCount > 100)
		{
			_enemy1[i].dieCount = 0;
			_enemy1[i].life = false;
		}
	}
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (_enemy2[i].dieCount > 100)
		{
			_enemy2[i].dieCount = 0;
			_enemy2[i].life = false;
		}
	}
}
void enemy::moveAllEnemy(float num)
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		_enemy1[i].x -= num;
		_enemy2[i].x -= num;
	}
}
bool enemy::CheckEnemy()
{
	for (int i = 0; i < MAXENEMY; i++)
	{
		if (_enemy1[i].life) return false;
		if (_enemy2[i].life)return false;
	}
	return true;
}
void enemy::bossFrameWork()
{
	if (boss.die) boss.state = B_DIE;
	boss.frameCount++;
	switch (boss.state)
	{
	case B_IDLE:
		boss.frameCount = 0;
		boss.frameX = 0;
		break;
	case B_RUN:
		if (boss.frameCount > 5)
		{
			boss.frameCount = 0;
			boss.frameX++;
			if (boss.frameX > 6)
			{
				boss.frameX = 0;
			}
		}
		break;
	case B_FASTRUN:
		if (boss.frameCount > 5)
		{
			boss.frameCount = 0;
			boss.frameX++;
			if (boss.frameX > 5)
			{
				boss.frameX = 0;
			}
			if (boss.direction&&boss.x-_player->getPlayerX()>150)
			{
				boss.state = B_TURN;
				boss.frameX = 0;
			}
			else if (!boss.direction&&boss.x - _player->getPlayerX()<-150)
			{
				boss.state = B_TURN;
				boss.frameX = 0;
			}
			if (atkCheck3(80, 30, 80) && !_player->getHurt() && !_player->checkGod())
			{
				_player->OnHurt((boss.direction) ? 10 : -10, 0, true);
				boss.state = B_IDLE;
				boss.atkDelay = 0;
				_effect->makeEffect(_player->getPlayerX()-50, _player->getPlayerY()-50, 52);
				_database->SetSolider(50);
			}
		}
		break;
	case B_TURN:
		if (boss.frameCount > 20)
		{
			boss.frameCount = 0;
			boss.state = B_FASTRUN;
			(boss.direction) ? boss.direction = false : boss.direction = true;
		}
		break;
	case B_ATK2:
		if (boss.frameCount > 10)
		{
			boss.frameCount = 0;
			boss.frameX++;
			if (boss.frameX == 2 && atkCheck3(60, 60, 30) && !_player->getHurt() && !_player->checkGod())
			{
				_player->OnHurt((boss.direction) ? 10 : -10, 0, false);
				_effect->makeEffect(_player->getPlayerX()-50, _player->getPlayerY()-50, 52);
				_database->SetSolider(20);
			}
			if (boss.frameX > 3)
			{
				boss.frameX = 0;
				boss.state = B_IDLE;
			}
		}
		break;
	case B_DIE:
		if (boss.frameCount > 8)
		{
			boss.frameCount = 0;
			boss.frameX++;
			if (boss.frameX > 7)
			{
				boss.frameX = 0;
				boss.life = false;
			}
		}
		break;
	case B_ATK:
		if (boss.frameCount > 5)
		{
			boss.frameCount = 0;
			boss.frameX++;
			if (boss.frameX == 3 && atkCheck3(80, 80, 100) && !_player->getHurt() && !_player->checkGod())
			{
				_player->OnHurt((boss.direction) ? 10 : -10, 0, true);
				_effect->makeEffect(_player->getPlayerX()-3-50, _player->getPlayerY()-50, 52);
				_database->SetSolider(50);
			}
			if (boss.frameX > 6)
			{
				boss.frameX = 0;
				boss.state = B_IDLE;
				boss.atkDelay = 0;
			}
		}
		break;
	case B_RUN_ATK:
		if (boss.frameCount > 5)
		{
			boss.frameCount = 0;
			boss.frameX++;
			if (boss.frameX > 11)
			{
				boss.frameX = 0;
			}
		}
		break;
	case B_SPEACIAL:
		if (boss.frameCount > 8)
		{
			boss.frameCount = 0;
			boss.frameX++;
			if (boss.frameX > 9)
			{
				boss.frameX = 0;
			}
		}
		break;
	}
}
void enemy::bossMove()
{
	boss.rc = RectMakeCenter(boss.x, boss.y, 120, 120);
	boss.atkDelay++;
	switch (boss.state)
	{
	case B_IDLE:
	{
		(_player->getPlayerX() > boss.x) ? (boss.direction = true) : (boss.direction = false);
		int t = rand() % 1000;
		if (t < 80)
		{
			boss.state = B_RUN;
			boss.moveType = TOPLAYER + rand() % 4;
		}
		//if (abs(_player->getPlayerX() - boss.x) < 60&& abs(_player->getPlayerY() - boss.y) < 50)
		//{
		//	boss.state = B_ATK;
		//	boss.frameX = 0;
		//	boss.frameCount = 0;
		//}
		if (boss.atkDelay > 210)
		{
			boss.state = B_FASTRUN;
		}
	}
		break;
	case B_RUN:
		boss.moveCount++;
		switch (boss.moveType)
		{
		case TOPLAYER:
			(_player->getPlayerX() > boss.x) ? (boss.direction = true) : (boss.direction = false);
			if (abs(_player->getPlayerX() - boss.x) > 80)
			{
				(boss.direction) ? boss.x+=2 : boss.x-=2;
			}
			else if(abs(_player->getPlayerY()-boss.y)>10)
			{
				(_player->getPlayerY() > boss.y) ? boss.y++ : boss.y--;
			}
			if (boss.moveCount > 150)
			{
				boss.moveCount = 0;
				boss.state = B_IDLE;
			}
			break;
		case BACKPLAYER:
			(_player->getPlayerX() > boss.x) ? (boss.direction = true) : (boss.direction = false);
			(_player->getPlayerX() > boss.x) ? boss.x -= 2 : boss.x += 2;
			boss.y--;
			if (boss.moveCount > 30)
			{
				boss.moveCount = 0;
				boss.state = B_IDLE;
			}
			break;
		case BACKPLAYER2:
			(_player->getPlayerX() > boss.x) ? (boss.direction = true) : (boss.direction = false);
			(_player->getPlayerX() > boss.x) ? boss.x -= 2 : boss.x += 2;
			boss.y++;
			if (boss.moveCount > 30)
			{
				boss.moveCount = 0;
				boss.state = B_IDLE;
			}
			break;
		case SUPERTMOVE:
			(_player->getPlayerX() > boss.x) ? (boss.direction = true) : (boss.direction = false);
			if (abs(_player->getPlayerX() - boss.x) > 20)
			{
				(boss.direction) ? boss.x += 2 : boss.x -= 2;
			}
			if (abs(_player->getPlayerY() - boss.y) > 10)
			{
				(_player->getPlayerY() > boss.y) ? boss.y++ : boss.y--;
			}
			if (boss.moveCount > 150)
			{
				boss.moveCount = 0;
				boss.state = B_IDLE;
			}
			break;
		}
		if (abs(_player->getPlayerX() - boss.x) < 60 && abs(_player->getPlayerY() - boss.y) < 50)
		{
			boss.state = B_ATK;
			boss.frameX = 0;
			boss.frameCount = 0;
		}
		break;
	case B_FASTRUN:
		(boss.direction) ? boss.x += 8 : boss.x -= 8;
		(_player->getPlayerY() > boss.y) ? boss.y+=0.5 : boss.y-=0.5;
		break;
	case B_TURN:
		break;
	case B_ATK2:
		break;
	case B_DIE:
		break;
	case B_ATK:
		if (boss.atkDelay < 120)
		{
			boss.state = B_ATK2;
		}
		break;
	case B_RUN_ATK:
		break;
	case B_SPEACIAL:
		break;
	}
	if (boss.y < _player->minY)boss.y = _player->minY;
	if (boss.y > _player->maxY-30)boss.y = _player->maxY-30;
	if (boss.x > WINSIZEX)boss.x = WINSIZEX;
	if (boss.x < 0)boss.x = 0;
	if (boss.HP < 0&&!boss.die)
	{
		boss.die = true;
		boss.state = B_DIE;
		boss.frameX = 0;
		boss.frameCount = 0;
	}
}
void enemy::bossCollision()
{
	RECT rc;
	if (IntersectRect(&rc, &_player->getAtkRect(), &boss.rc))
	{
		if (abs(_player->getPlayerY() - boss.y) < 40 && _player->getAtkType())
		{
			boss.frameX = 0;
			boss.frameCount = 0;
			boss.state = B_IDLE;
			boss.atkDelay = 0;
			boss.xSpeed = _player->getXSpeed()/2;
			int Dmg = _player->getDmg();
			_database->makeDamage(boss.x, boss.rc.top, 10, 10, Dmg, true);
			boss.HP -= Dmg;
		}
		else if (abs(_player->getPlayerY() - boss.y) < 20)
		{
			int Dmg = _player->getDmg();
			_effect->makeEffect(_player->getAtkRect().left + (_player->getAtkRect().right - _player->getAtkRect().left) / 2, _player->getAtkRect().top, 50);
			_database->makeDamage(boss.x, boss.rc.top, 10, 10, Dmg, false);
			boss.HP -= Dmg;
		}
	}
	if (IntersectRect(&rc, &_player->getPlayerRect(), &boss.rc) && _player->getGrab())
	{
		(_player->getDirection()) ? (boss.x = _player->getPlayerX() - 10) : (boss.x = _player->getPlayerX() + 10);
		//_enemy2[i].y = _player->getPlayerY();
	}
}
void enemy::bossDraw()
{
	if (boss.life)
	{
		(boss.direction) ? IMAGEMANAGER->frameRender("boss", getMemDC(), boss.x - 200, boss.y - 220, boss.frameX, boss.state - 1000) :
			IMAGEMANAGER->frameRender("boss2", getMemDC(), boss.x - 200, boss.y - 220, 11 - boss.frameX, boss.state - 1000);
	}
	//Rectangle(getMemDC(), boss.rc.left, boss.rc.top, boss.rc.right, boss.rc.bottom);
}