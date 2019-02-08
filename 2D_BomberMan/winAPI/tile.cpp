#include "stdafx.h"
#include "tile.h"

tile::tile() {}
tile::~tile() {}

HRESULT tile::init(void)
{
	gameNode::init();

	IMAGEMANAGER->addFrameImage("object", "object.bmp", 144, 96, 3, 2, true, RGB(255, 0, 255));
	
	_bombImage = IMAGEMANAGER->addFrameImage("bombImage", "bomb.bmp", 96, 96, 2, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bombingImage", "bombing.bmp", 96, 240, 2, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("itemImage", "item.bmp", 192, 96, 4, 2, false, RGB(255, 0, 255));

	mapSet();
	bombSet();

	bombFrameCount = 0.0f;
	bombFrameX = 0;
	bombFrameY = 0;
	bombCount = 0;
	bombMaxRange = 1;
	delay = 0;

	bombs = 0;

	bombing = false;
	return S_OK;
}

void tile::release(void)
{
	gameNode::release();
}

void tile::update(void)
{
	gameNode::update();
	
	for (int x = 0; x < 14;x++)
	{
		for (int y = 0; y < 13; y++)
		{
			switch (tileMap[x][y].state)
			{
			case STATE_BROKEN:
				if (BROKENFRAMECOUNT + tileMap[x][y].frameCount <= GetTickCount())
				{
					tileMap[x][y].frameY = 1;
					++tileMap[x][y].frameX;
					tileMap[x][y].frameCount = GetTickCount();
					if (tileMap[x][y].frameX > tileMap[x][y].img->getMaxFrameX())
					{
						tileMap[x][y].frameX = tileMap[x][y].img->getMaxFrameX();
						int rndNum = 0;// RND->getInt(10);
						if (rndNum == 0) itemSet(x, y);
						tileMap[x][y].state = STATE_NULL;
					}
				}
				break;
			case STATE_BOMB:
				if (BOMBFRAMECOUNT + tileMap[x][y].frameCount <= GetTickCount())
				{
					++bombFrameX;
					tileMap[x][y].frameCount = GetTickCount();
					if (bombFrameX > _bombImage->getMaxFrameX())
					{
						bombFrameX = 0;
						++bombCount;
						if (bombCount > 6)
						{
							bombCount = 0;
							--bombs;
							bombing = true;
							tileMap[x][y].state = STATE_BOMBING;
						}
					}
				}
				break;
			case STATE_BOMBING:
				if (FRAMECOUNT + tileMap[x][y].frameCount <= GetTickCount())
				{
					++delay;
					tileMap[x][y].frameCount = GetTickCount();
					if (delay > 1)
					{
						delay = 0;
						tileMap[x][y].state = STATE_NULL;
					}
				}
				break;
			}

			if (BOMBINGFRAMECOUNT + bombTile[x][y].frameCount <= GetTickCount() && bombTile[x][y].state == STATE_BOMBING)
			{
				bombTile[x][y].frameCount = GetTickCount();
				++bombTile[x][y].delay;
				if (bombTile[x][y].delay > 1)
				{
					bombTile[x][y].delay = 0;
					bombTile[x][y].state = STATE_NULL;
				}
			}
		}
	}

	bombCheck();
	itemCollision();
}

void tile::render(void)
{
	for (int x = 0; x < 14; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			switch (tileMap[x][y].state)
			{
			case STATE_NULL:
				continue;
			case STATE_BOMB:
				_bombImage->frameRender(getMemDC(), tileMap[x][y].rc.left, tileMap[x][y].rc.top, bombFrameX, 0);
				break;
			case STATE_BOMBING:
				continue;
			case STATE_STAND:
				tileMap[x][y].frameX = 0;
				tileMap[x][y].frameY = 0;
				tileMap[x][y].img->frameRender(getMemDC(), tileMap[x][y].rc.left, tileMap[x][y].rc.top,
					tileMap[x][y].frameX, tileMap[x][y].frameY);
				break;
			case STATE_BREAK:
				tileMap[x][y].frameX = 0;
				tileMap[x][y].frameY = 1;
				tileMap[x][y].img->frameRender(getMemDC(), tileMap[x][y].rc.left, tileMap[x][y].rc.top,
					tileMap[x][y].frameX, tileMap[x][y].frameY);
				break;
			case STATE_BROKEN:
				tileMap[x][y].img->frameRender(getMemDC(), tileMap[x][y].rc.left, tileMap[x][y].rc.top,
					tileMap[x][y].frameX, tileMap[x][y].frameY);
				break;
			}
		}
	}

	for (int x = 0; x < 14; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			if (itemTile[x][y].life)
			{
				itemTile[x][y].img->frameRender(getMemDC(), itemTile[x][y].rc.left, itemTile[x][y].rc.top,
					itemTile[x][y].frameX, itemTile[x][y].frameY);
			}
		}
	}

	for (int x = 0; x < 14; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			if (bombTile[x][y].state == STATE_BOMBING)
			{
				bombTile[x][y].img->frameRender(getMemDC(), bombTile[x][y].rc.left, bombTile[x][y].rc.top,
					bombTile[x][y].frameX, bombTile[x][y].frameY);
			}
		}
	}

	
}

void tile::mapSet(void)
{
	ZeroMemory(&tileMap, sizeof(tileMap));

	for (int x = 0; x < 14; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			tileMap[x][y].img = IMAGEMANAGER->findImage("object");
			tileMap[x][y].x = 24 + 48 * x;
			tileMap[x][y].y = 72 + 48 * y;
			tileMap[x][y].rc = RectMakeCenter(tileMap[x][y].x, tileMap[x][y].y, 48, 48);
		}
	}

	for (int x = 0; x < 14; x++)
	{
		tileMap[x][0].state = STATE_STAND;
		tileMap[x][12].state = STATE_STAND;
	}

	for (int y = 0; y < 13; y++)
	{
		tileMap[0][y].state = STATE_STAND;
		tileMap[13][y].state = STATE_STAND;
	}

	for (int x = 1; x < 13; x++) for (int y = 1; y < 12; y++) tileMap[x][y].state = STATE_BREAK;

	tileMap[1][1].state = STATE_NULL;
	tileMap[2][1].state = STATE_NULL;
	tileMap[3][1].state = STATE_NULL;
	tileMap[10][1].state = STATE_NULL;
	tileMap[11][1].state = STATE_NULL;
	tileMap[12][1].state = STATE_NULL;

	tileMap[1][2].state = STATE_NULL;
	tileMap[6][2].state = STATE_NULL;
	tileMap[7][2].state = STATE_NULL;
	tileMap[12][2].state = STATE_NULL;
	
	tileMap[1][3].state = STATE_NULL;
	tileMap[3][3].state = STATE_NULL;
	tileMap[4][3].state = STATE_NULL;
	tileMap[6][3].state = STATE_NULL;
	tileMap[7][3].state = STATE_NULL;
	tileMap[9][3].state = STATE_NULL;
	tileMap[10][3].state = STATE_NULL;
	tileMap[12][3].state = STATE_NULL;
	
	tileMap[3][4].state = STATE_NULL;
	tileMap[10][4].state = STATE_NULL;
	
	tileMap[3][8].state = STATE_NULL;
	tileMap[10][8].state = STATE_NULL;
	
	tileMap[1][9].state = STATE_NULL;
	tileMap[3][9].state = STATE_NULL;
	tileMap[4][9].state = STATE_NULL;
	tileMap[6][9].state = STATE_NULL;
	tileMap[7][9].state = STATE_NULL;
	tileMap[9][9].state = STATE_NULL;
	tileMap[10][9].state = STATE_NULL;
	tileMap[12][9].state = STATE_NULL;
	
	tileMap[1][10].state = STATE_NULL;
	tileMap[6][10].state = STATE_NULL;
	tileMap[7][10].state = STATE_NULL;
	tileMap[12][10].state = STATE_NULL;
	
	tileMap[1][11].state = STATE_NULL;
	tileMap[2][11].state = STATE_NULL;
	tileMap[3][11].state = STATE_NULL;
	tileMap[10][11].state = STATE_NULL;
	tileMap[11][11].state = STATE_NULL;
	tileMap[12][11].state = STATE_NULL;

	tileMap[2][2].state = STATE_STAND;
	tileMap[3][2].state = STATE_STAND;
	tileMap[4][2].state = STATE_STAND;
	tileMap[9][2].state = STATE_STAND;
	tileMap[10][2].state = STATE_STAND;
	tileMap[11][2].state = STATE_STAND;

	tileMap[2][3].state = STATE_STAND;
	tileMap[2][2].state = STATE_STAND;
	
	tileMap[2][4].state = STATE_STAND;
	tileMap[4][4].state = STATE_STAND;
	tileMap[9][4].state = STATE_STAND;
	tileMap[11][4].state = STATE_STAND;

	tileMap[6][5].state = STATE_STAND;
	tileMap[7][5].state = STATE_STAND;

	tileMap[2][6].state = STATE_STAND;
	tileMap[4][6].state = STATE_STAND;
	tileMap[9][6].state = STATE_STAND;
	tileMap[11][6].state = STATE_STAND;

	tileMap[6][7].state = STATE_STAND;
	tileMap[7][7].state = STATE_STAND;

	tileMap[2][8].state = STATE_STAND;
	tileMap[4][8].state = STATE_STAND;
	tileMap[9][8].state = STATE_STAND;
	tileMap[11][8].state = STATE_STAND;

	tileMap[2][9].state = STATE_STAND;
	tileMap[11][9].state = STATE_STAND;

	tileMap[2][10].state = STATE_STAND;
	tileMap[3][10].state = STATE_STAND;
	tileMap[4][10].state = STATE_STAND;
	tileMap[9][10].state = STATE_STAND;
	tileMap[10][10].state = STATE_STAND;
	tileMap[11][10].state = STATE_STAND;

	ZeroMemory(&itemTile, sizeof(itemTile));
	
	for (int x = 0; x < 14; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			itemTile[x][y].img = IMAGEMANAGER->findImage("itemImage");
			itemTile[x][y].x = tileMap[x][y].x;
			itemTile[x][y].y = tileMap[x][y].y;
			itemTile[x][y].rc = tileMap[x][y].rc;
		}
	}

}

void tile::bombSet(void)
{
	ZeroMemory(&bombTile, sizeof(bombTile));
	
	for (int x = 0; x < 14; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			bombTile[x][y].img = IMAGEMANAGER->findImage("bombingImage");
			bombTile[x][y].x = tileMap[x][y].x;
			bombTile[x][y].y = tileMap[x][y].y;
			bombTile[x][y].rc = tileMap[x][y].rc;
		}
	}
}

void tile::bombCheck(void)
{
	for (int x = 0; x < 14; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			if (tileMap[x][y].state != STATE_BOMBING) continue;
			if (tileMap[x][y].state == STATE_BOMBING)
			{
				for (int i = x - 1; i > x - bombMaxRange - 1; i--)
				{
					if (tileMap[i][y].state == STATE_STAND)
					{
						bombTile[i + 1][y].state = STATE_BOMBING;
						bombTile[i + 1][y].frameX = 1;
						bombTile[i + 1][y].frameY = 2;
						break;
					}
					bombTile[i][y].state = STATE_BOMBING;
					bombTile[i][y].frameX = 0;
					bombTile[i][y].frameY = 2;

					if (tileMap[i][y].state == STATE_BREAK || tileMap[i][y].state == STATE_BROKEN)
					{
						bombTile[i][y].state = STATE_BOMBING;
						bombTile[i][y].frameX = 1;
						bombTile[i][y].frameY = 2;
						tileMap[i][y].state = STATE_BROKEN;
						break;
					}

					if (i == x - bombMaxRange) bombTile[i][y].frameX = 1;
				}

				for (int i = x + 1; i < x + bombMaxRange + 1; i++)
				{
					if (tileMap[i][y].state == STATE_STAND)
					{
						bombTile[i - 1][y].state = STATE_BOMBING;
						bombTile[i - 1][y].frameX = 1;
						bombTile[i - 1][y].frameY = 1;
						break;
					}
					bombTile[i][y].state = STATE_BOMBING;
					bombTile[i][y].frameX = 0;
					bombTile[i][y].frameY = 1;

					if (tileMap[i][y].state == STATE_BREAK || tileMap[i][y].state == STATE_BROKEN)
					{
						bombTile[i][y].state == STATE_BOMBING;
						bombTile[i][y].frameX = 1;
						bombTile[i][y].frameY = 1;
						tileMap[i][y].state = STATE_BROKEN;
						break;
					}

					if (i == x + bombMaxRange) bombTile[i][y].frameX = 1;
				}

				for (int i = y - 1; i > y - bombMaxRange - 1; i--)
				{
					if (tileMap[x][i].state == STATE_STAND)
					{
						bombTile[x][i + 1].state = STATE_BOMBING;
						bombTile[x][i + 1].frameX = 1;
						bombTile[x][i + 1].frameY = 3;
						break;
					}
					bombTile[x][i].state = STATE_BOMBING;
					bombTile[x][i].frameX = 0;
					bombTile[x][i].frameY = 3;

					if (tileMap[x][i].state == STATE_BREAK || tileMap[x][i].state == STATE_BROKEN)
					{
						bombTile[x][i].state = STATE_BOMBING;
						bombTile[x][i].frameX = 1;
						bombTile[x][i].frameY = 3;
						tileMap[x][i].state = STATE_BROKEN;
						break;
					}

					if (i == y - bombMaxRange) bombTile[x][i].frameX = 1;
				}

				for (int i = y + 1; i < y + bombMaxRange + 1; i++)
				{
					if (tileMap[x][i].state == STATE_STAND)
					{
						bombTile[x][i - 1].state = STATE_BOMBING;
						bombTile[x][i - 1].frameX = 1;
						bombTile[x][i - 1].frameY = 4;
						break;
					}
					bombTile[x][i].state = STATE_BOMBING;
					bombTile[x][i].frameX = 0;
					bombTile[x][i].frameY = 4;

					if (tileMap[x][i].state == STATE_BREAK || tileMap[x][i].state == STATE_BROKEN)
					{
						bombTile[x][i].state = STATE_BOMBING;
						bombTile[x][i].frameX = 1;
						bombTile[x][i].frameY = 4;
						tileMap[x][i].state = STATE_BROKEN;
						break;
					}

					if (i == y + bombMaxRange) bombTile[x][i].frameX = 1;
				}
				bombTile[x][y].state = STATE_BOMBING;
				bombTile[x][y].frameX = 0;
				bombTile[x][y].frameY = 0;
				break;
			}
		}
	}
}

void tile::itemSet(int x, int y)
{
	itemTile[x][y].life = true;
	itemTile[x][y].kindItem = ITEM(RND->getInt(3) + 1);
	itemTile[x][y].frameY = 0;
	itemTile[x][y].frameX = int(itemTile[x][y].kindItem) - 1;
}

void tile::itemCollision(void)
{
	for (int x = 0; x < 14; x++)
	{
		for (int y = 0; y < 13; y++)
		{
			if (IntersectRect(&RectMake(0, 0, 0, 0), &bombTile[x][y].rc, &itemTile[x][y].rc)
				&& bombTile[x][y].state == STATE_BOMBING && itemTile[x][y].life && tileMap[x][y].state == STATE_NULL)
			{
				itemTile[x][y].life = false;
				itemTile[x][y].kindItem = ITEM_NULL;
			}
		}
	}
}