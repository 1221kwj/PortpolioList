#include "StdAfx.h"
#include "player.h"

player::player(void) {}
player::~player(void) {}

HRESULT player::init(void)
{
	gameNode::init();

	ZeroMemory(&myPlayer, sizeof(tagPlayer));

	myPlayer.img = IMAGEMANAGER->addFrameImage("player", "walking.bmp", 288, 320, 6, 5, true, RGB(255, 0, 255));
	myPlayer._direction = DIREC_LEFT;
	myPlayer._x = 600;
	myPlayer._y = 600;
	myPlayer._rc = RectMakeCenter(myPlayer._x, myPlayer._y, 36, 36);
	myPlayer.speed = 1.2f;
	myPlayer.frameX = 0;
	myPlayer.frameY = 0;
	myPlayer.life = true;

	item1MaxCount = 1;
	item2MaxCount = 1;
	item3MaxCount = 1;

	enemySetting();
	return S_OK;
}

void player::release(void)
{
	gameNode::release();

}

void player::update(void)
{
	gameNode::update();
	
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && collision(DIREC_LEFT) && myPlayer.life)
	{
		myPlayer._x -= myPlayer.speed;
		myPlayer._direction = DIREC_LEFT;
		if (FRAMECOUNT + myPlayer.frameCount <= GetTickCount())
		{
			++myPlayer.frameX;
			myPlayer.frameCount = GetTickCount();
			if (myPlayer.frameX > myPlayer.img->getMaxFrameX()) myPlayer.frameX = 0;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && collision(DIREC_RIGHT) && myPlayer.life)
	{
		myPlayer._x += myPlayer.speed;
		myPlayer._direction = DIREC_RIGHT;
		if (FRAMECOUNT + myPlayer.frameCount <= GetTickCount())
		{
			++myPlayer.frameX;
			myPlayer.frameCount = GetTickCount();
			if (myPlayer.frameX > myPlayer.img->getMaxFrameX()) myPlayer.frameX = 0;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP) && collision(DIREC_UP) && myPlayer.life)
	{
		myPlayer._y -= myPlayer.speed;
		myPlayer._direction = DIREC_UP;
		if (FRAMECOUNT + myPlayer.frameCount <= GetTickCount())
		{
			++myPlayer.frameX;
			myPlayer.frameCount = GetTickCount();
			if (myPlayer.frameX > myPlayer.img->getMaxFrameX()) myPlayer.frameX = 0;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN) && collision(DIREC_DOWN) && myPlayer.life)
	{
		myPlayer._y += myPlayer.speed;
		myPlayer._direction = DIREC_DOWN;
		if (FRAMECOUNT + myPlayer.frameCount <= GetTickCount())
		{
			++myPlayer.frameX;
			myPlayer.frameCount = GetTickCount();
			if (myPlayer.frameX > myPlayer.img->getMaxFrameX()) myPlayer.frameX = 0;
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _tile->bombs < item1MaxCount)
	{
		for (int x = 0; x < 14; x++)
		{
			for (int y = 0; y < 13; y++)
			{
				if (PtInRect(&_tile->tileMap[x][y].rc, PointMake(myPlayer._x, myPlayer._y)))
				{
					_tile->tileMap[x][y].state = STATE_BOMB;
					++_tile->bombs;
					break;
				}
			}
		}
	}

	if (!myPlayer.life && FRAMECOUNT + myPlayer.frameCount <= GetTickCount())
	{
		++myPlayer.frameX;
		myPlayer.frameCount = GetTickCount();
		if (myPlayer.frameX > myPlayer.img->getMaxFrameX()) myPlayer.frameX = myPlayer.img->getMaxFrameX();
	}

	myPlayer.life = bombCollision();
	myPlayer._rc = RectMakeCenter(myPlayer._x, myPlayer._y, 36, 36);

	itemAcquire();
	enemyCollision();
	
	//enemyMove();

	//if (!myPlayer.life && myPlayer.frameX == myPlayer.img->getMaxFrameX())
	//{
	//	PostMessage(_hWnd, WM_DESTROY, 0, 0);
	//}
}

void player::render(void)
{
	switch (myPlayer._direction)
	{
	case DIREC_LEFT:
		myPlayer.frameY = 0;
		break;
	case DIREC_RIGHT:
		myPlayer.frameY = 1;
		break;
	case DIREC_UP:
		myPlayer.frameY = 2;
		break;
	case DIREC_DOWN:
		myPlayer.frameY = 3;
		break;
	case DIREC_DIE:
		myPlayer.frameY = 4;
		break;
	}
	//RectangleMakeCenter(getMemDC(), myPlayer._x, myPlayer._y, 36, 36);
	myPlayer.img->frameRender(getMemDC(), myPlayer._rc.left - 6, myPlayer._rc.top - 28, myPlayer.frameX, myPlayer.frameY);

	for (int i = 0; i < 4; i++)
	{
		if (!myEnemy[i].life) continue;
		myEnemy[i].img->frameRender(getMemDC(), myEnemy[i]._rc.left - 6, myEnemy[i]._rc.top - 6,
			myEnemy[i].frameX, myEnemy[i].frameY);
	}

}

bool player::collision(DIRECTION direction)
{
	for (int x = 0; x < 14; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			switch (direction)
			{
			case DIREC_LEFT:
				if (IntersectRect(&RectMake(0, 0, 0, 0), &myPlayer._rc, &_tile->tileMap[x][y].rc)
					&& _tile->tileMap[x][y].state != STATE_NULL 
					&& myPlayer._x > _tile->tileMap[x][y].rc.right) return false;
				break;
			case DIREC_RIGHT:
				if (IntersectRect(&RectMake(0, 0, 0, 0), &myPlayer._rc, &_tile->tileMap[x][y].rc)
					&& _tile->tileMap[x][y].state != STATE_NULL 
					&& myPlayer._x < _tile->tileMap[x][y].rc.left) return false;
				break;
			case DIREC_UP:
				if (IntersectRect(&RectMake(0, 0, 0, 0), &myPlayer._rc, &_tile->tileMap[x][y].rc)
					&& _tile->tileMap[x][y].state != STATE_NULL 
					&& myPlayer._y > _tile->tileMap[x][y].rc.bottom) return false;
				break;
			case DIREC_DOWN:
				if (IntersectRect(&RectMake(0, 0, 0, 0), &myPlayer._rc, &_tile->tileMap[x][y].rc)
					&& _tile->tileMap[x][y].state != STATE_NULL
					&& myPlayer._y < _tile->tileMap[x][y].rc.top) return false;
				break;
			}
		}
	}
	return true;
}

bool player::bombCollision()
{
	for (int x = 0; x < 14; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			if (IntersectRect(&RectMake(0, 0, 0, 0), &myPlayer._rc, &_tile->tileMap[x][y].rc)
				&& _tile->bombTile[x][y].state == STATE_BOMBING)
			{
				myPlayer.life = false;
				myPlayer._direction = DIREC_DIE;
				return myPlayer.life;
				break;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (IntersectRect(&RectMake(0, 0, 0, 0), &myPlayer._rc, &myEnemy[i]._rc)
			&& myEnemy[i].life)
		{
			myPlayer.life = false;
			myPlayer._direction = DIREC_DIE;
			return myPlayer.life;
		}
	}

	return myPlayer.life;
}

void player::itemAcquire()
{
	for (int x = 0; x < 14; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			if (IntersectRect(&RectMake(0, 0, 0, 0), &myPlayer._rc, &_tile->itemTile[x][y].rc)
				&& _tile->itemTile[x][y].life)
			{
				switch (_tile->itemTile[x][y].kindItem)
				{
				case ITEM1:
					_tile->bombMaxRange += 1;
					if (_tile->bombMaxRange > 5) _tile->bombMaxRange = 5;
					break;
				case ITEM2:
					++item1MaxCount;
					if (item1MaxCount > 5) item1MaxCount = 5;
					break;
				case ITEM3:
					myPlayer.speed += 0.3;
					if (myPlayer.speed > 2.5f) myPlayer.speed = 2.5f;
					break;
				}
				_tile->itemTile[x][y].life = false;
				_tile->itemTile[x][y].kindItem = ITEM_NULL;
				break;
			}
		}
	}
}

void player::enemySetting(void)
{
	ZeroMemory(&myEnemy, sizeof(myEnemy));

	for (int i = 0; i < 4; i++)
	{
		myEnemy[i].img = IMAGEMANAGER->addFrameImage("monster", "monster.bmp", 240, 144, 5, 3, true, RGB(255, 0, 255));
		myEnemy[i].life = true;
		myEnemy[i].speed = 1.2f;
	}

	myEnemy[0].frameX = 0;
	myEnemy[0].frameY = 0;
	myEnemy[0]._x = 168;
	myEnemy[0]._y = 216;
	myEnemy[0]._rc = RectMakeCenter(myEnemy[0]._x, myEnemy[0]._y, 36, 36);

	myEnemy[1].frameX = 0;
	myEnemy[1].frameY = 1;
	myEnemy[1]._x = 504;
	myEnemy[1]._y = 216;
	myEnemy[1]._rc = RectMakeCenter(myEnemy[1]._x, myEnemy[1]._y, 36, 36);

	myEnemy[2].frameX = 0;
	myEnemy[2].frameY = 2;
	myEnemy[2]._x = 168;
	myEnemy[2]._y = 504;
	myEnemy[2]._rc = RectMakeCenter(myEnemy[2]._x, myEnemy[2]._y, 36, 36);

	myEnemy[3].frameX = 0;
	myEnemy[3].frameY = 0;
	myEnemy[3]._x = 504;
	myEnemy[3]._y = 504;
	myEnemy[3]._rc = RectMakeCenter(myEnemy[3]._x, myEnemy[3]._y, 36, 36);
}

//void player::enemyMove(void)
//{
//	for (int x = 0; x < 14; x++)
//	{
//		for (int y = 0; y < 13; y++)
//		{
//			for (int i = 0; i < 4; i++)
//			{
//				if (ENEMYMOVECOUNT + myEnemy[i].frameCount <= GetTickCount())
//				{
//					myEnemy[i].frameCount = GetTickCount();
//					//if (IntersectRect(&RectMake(0, 0, 0, 0), &_tile->tileMap[x][y].rc, &myEnemy[i]._rc)) continue;
//					DIRECTION direction;
//					direction = DIRECTION(RND->getInt(4));
//					switch (direction)
//					{
//					case DIREC_LEFT:
//						myEnemy[i]._x -= myEnemy[i].speed;
//						break;
//					case DIREC_RIGHT:
//						myEnemy[i]._x += myEnemy[i].speed;
//						break;
//					case DIREC_UP:
//						myEnemy[i]._y -= myEnemy[i].speed;
//						break;
//					case DIREC_DOWN:
//						myEnemy[i]._y += myEnemy[i].speed;
//						break;
//					}
//					myEnemy[i]._rc = RectMakeCenter(myEnemy[i]._x, myEnemy[i]._y, 36, 36);
//				}
//			}
//		}
//	}
//}

void player::enemyCollision(void)
{
	for (int x = 0; x < 14; x++)
	{
		for (int y = 0; y < 14; y++)
		{
			for (int i = 0; i < 4; i++)
			{
				if (IntersectRect(&RectMake(0, 0, 0, 0), &_tile->bombTile[x][y].rc, &myEnemy[i]._rc)
					&_tile->bombTile[x][y].state == STATE_BOMBING)
				{
					myEnemy[i].die = true;
				}
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (myEnemy[i].die && myEnemy[i].frameCount + FRAMECOUNT <= GetTickCount())
		{
			myEnemy[i].frameCount = GetTickCount();
			++myEnemy[i].frameX;
			if (myEnemy[i].frameX > myEnemy[i].img->getMaxFrameX())
			{
				myEnemy[i].frameX = myEnemy[i].img->getMaxFrameX();
				myEnemy[i].life = false;
			}
		}
	}
}

//bool player::ecollision(DIRECTION direction)
//{
//	for (int x = 0; x < 14; x++)
//	{
//		for (int y = 0; y < 13; y++)
//		{
//			for (int i = 0; i < 4; i++)
//			{
//				switch (direction)
//				{
//				case DIREC_LEFT:
//					if (IntersectRect(&RectMake(0, 0, 0, 0), &myPlayer._rc, &_tile->tileMap[x][y].rc)
//						&& _tile->tileMap[x][y].state != STATE_NULL
//						&& myPlayer._x > _tile->tileMap[x][y].rc.right) return false;
//					break;
//				case DIREC_RIGHT:
//					if (IntersectRect(&RectMake(0, 0, 0, 0), &myPlayer._rc, &_tile->tileMap[x][y].rc)
//						&& _tile->tileMap[x][y].state != STATE_NULL
//						&& myPlayer._x < _tile->tileMap[x][y].rc.left) return false;
//					break;
//				case DIREC_UP:
//					if (IntersectRect(&RectMake(0, 0, 0, 0), &myPlayer._rc, &_tile->tileMap[x][y].rc)
//						&& _tile->tileMap[x][y].state != STATE_NULL
//						&& myPlayer._y > _tile->tileMap[x][y].rc.bottom) return false;
//					break;
//				case DIREC_DOWN:
//					if (IntersectRect(&RectMake(0, 0, 0, 0), &myPlayer._rc, &_tile->tileMap[x][y].rc)
//						&& _tile->tileMap[x][y].state != STATE_NULL
//						&& myPlayer._y < _tile->tileMap[x][y].rc.top) return false;
//					break;
//				}
//			}
//		}
//	}
//	return true;
//}