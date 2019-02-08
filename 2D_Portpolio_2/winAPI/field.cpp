#include "stdafx.h"
#include "field.h"


field::field() {}

field::~field() {}

HRESULT field::init(void)
{
	_seasonTitle = IMAGEMANAGER->addFrameImage("season", "seasonTitle.bmp", 5120, 720, 4, 1, true, RGB(255, 0, 255));
	_openingBG_0 = IMAGEMANAGER->addFrameImage("openingBG_0", "openingBG_0.bmp", 1280, 720, 1, 1, true, RGB(255, 0, 255));
	_openingBG_1 = IMAGEMANAGER->addFrameImage("openingBG_1", "openingBG_1.bmp", 1280, 720, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("battleBackGround", "battle01.bmp", 11000, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossMap", "bossMap.bmp", 2800, 720, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("battleUI", "battleUI.bmp", 1280, 720, true, RGB(255, 0, 255));
	cameraX = 0;
	lockCamera = true;

	changeBlock[0].x = 1980;
	changeBlock[0].y = WINSIZEY / 2;
	changeBlock[0].check = true;
	changeBlock[0].minY = 600;
	changeBlock[0].maxY = 630;
	changeBlock[0].rc = { 0,0,0,0 };

	changeBlock[1].x = 2690;
	changeBlock[1].y = WINSIZEY / 2;
	changeBlock[1].check = true;
	changeBlock[1].minY = 425;
	changeBlock[1].maxY = 620;
	changeBlock[1].rc = { 0,0,0,0 };

	changeBlock[2].x = 3940;
	changeBlock[2].y = WINSIZEY / 2;
	changeBlock[2].check = true;
	changeBlock[2].minY = 470;
	changeBlock[2].maxY = 620;
	changeBlock[2].rc = { 0,0,0,0 };

	changeBlock[3].x = 7335;
	changeBlock[3].y = WINSIZEY / 2;
	changeBlock[3].check = true;
	changeBlock[3].minY = 425;
	changeBlock[3].maxY = 620;
	changeBlock[3].rc = { 0,0,0,0 };

	spawnBlock[0].x = 1300;
	spawnBlock[0].y = WINSIZEY / 2;
	spawnBlock[0].check = true;

	spawnBlock[1].x = 3520;
	spawnBlock[1].y = WINSIZEY / 2;
	spawnBlock[1].check = true;

	spawnBlock[2].x = 4600;
	spawnBlock[2].y = WINSIZEY / 2;
	spawnBlock[2].check = true;

	spawnBlock[3].x = 6000;
	spawnBlock[3].y = WINSIZEY / 2;
	spawnBlock[3].check = true;

	spawnBlock[4].x = 7960;
	spawnBlock[4].y = WINSIZEY / 2;
	spawnBlock[4].check = true;

	spawnBlock[5].x = 10000;
	spawnBlock[5].y = WINSIZEY / 2;
	spawnBlock[5].check = true;

	goalBlock.x = 10950;
	//goalBlock.x = 200;
	goalBlock.y = WINSIZEY / 2;
	goalBlock.rc = { 0,0,0,0 };
	goalBlock.check = true;
	return S_OK;
}
void field::release(void)
{

}
void field::update(void)
{
	for (int i = 0; i < 4; i++)
	{
		changeBlock[i].rc = RectMakeCenter(changeBlock[i].x, changeBlock[i].y, 10, WINSIZEY);
	}
	for (int i = 0; i < 6; i++)
	{
		spawnBlock[i].rc = RectMakeCenter(spawnBlock[i].x, spawnBlock[i].y, 10, WINSIZEY);
	}
	goalBlock.rc = RectMakeCenter(goalBlock.x, goalBlock.y, 10, WINSIZEY);
}
void field::render(int page)
{
	switch (page)
	{
	case SPRING:
		_seasonTitle->frameRender(getMemDC(), 0, 0, 0, 0);
		break;
	case SUMMER:
		_seasonTitle->frameRender(getMemDC(), 0, 0, 1, 0);
		break;
	case FALL:
		_seasonTitle->frameRender(getMemDC(), 0, 0, 2, 0);
		break;
	case WINTER:
		_seasonTitle->frameRender(getMemDC(), 0, 0, 3, 0);
		break;
	case BATTLE:
		IMAGEMANAGER->findImage("battleBackGround")->render(getMemDC(), 0, 0, cameraX, 0, 1280, 720);
		IMAGEMANAGER->findImage("battleUI")->render(getMemDC());
		break;
	case BOSS:
		IMAGEMANAGER->findImage("bossMap")->render(getMemDC(), 0, 0, cameraX, 0, 1280, 720);
		IMAGEMANAGER->findImage("battleUI")->render(getMemDC());
		break;
		//for (int i = 0; i < 4; i++)
		//{
		//	if (!changeBlock[i].check) continue;
		//	HBRUSH red= CreateSolidBrush(RGB(255, 0, 0));
		//	FillRect(getMemDC(), &changeBlock[i].rc, red);
		//	DeleteObject(red);
		//}
		//for (int i = 0; i < 6; i++)
		//{
		//	if (!spawnBlock[i].check)continue;
		//	HBRUSH blue = CreateSolidBrush(RGB(255, 255, 0));
		//	FillRect(getMemDC(), &spawnBlock[i].rc, blue);
		//  FillRect(getMemDC(), &goalBlock.rc, blue);
		//	DeleteObject(blue);
		//}
	}
}

void field::openingDraw(int num)
{
	switch (num)
	{
	case 0:
		_openingBG_0->frameRender(getMemDC(), 0, 0, 0, 0);
		break;
	case 1:
		_openingBG_1->frameRender(getMemDC(), 0, 0, 0, 0);
		break;
	}


}