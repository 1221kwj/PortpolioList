#pragma once

#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backImage", "backImage.bmp", WINSIZEX, WINSIZEY);

enum STATE
{
	STATE_NULL,
	STATE_BOMB,
	STATE_BOMBING,
	STATE_STAND,
	STATE_BREAK,
	STATE_BROKEN
};

enum ITEM
{
	ITEM_NULL,
	ITEM1,
	ITEM2,
	ITEM3
};

struct tagTile
{
	image* img;
	float x, y;
	float frameCount;
	int delay;
	int frameX;
	int frameY;
	RECT rc;
	STATE state;
};

struct tagItem
{
	image* img;
	int frameX;
	int frameY;
	bool life;
	float x, y;
	RECT rc;
	ITEM kindItem;
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	image* getBackBuffer(void) {return _backBuffer;}
	HDC getMemDC() {return _backBuffer->getMemDC();}
	HDC getHDC() {return _hdc;}

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode(void);
	virtual ~gameNode(void);
};

