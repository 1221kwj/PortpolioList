#include "stdafx.h"
#include "opening.h"


opening::opening() {}
opening::~opening() {}

HRESULT opening::init(void)
{
	gameNode::init();
	_openPage = IMAGEMANAGER->addFrameImage("openPage", "openingImage.bmp", 5600, 600, 7, 1, false, RGB(255, 0, 255));
	ZeroMemory(&_startButton, sizeof(_startButton));
	_startButton = RectMake(240, 420, 320, 60);
	
	_open = true;
	state = 0;
	_openCount = 0.0f;
	return S_OK;
}

void opening::release(void)
{
	gameNode::release();

}

void opening::update(void)
{
	gameNode::update();

	if (FRAMECOUNT + _openCount <= GetTickCount() && _open)
	{
		_openCount = GetTickCount();
		_openPage->setFrameX(_openPage->getFrameX() + 1);
		if (_openPage->getFrameX() >= _openPage->getMaxFrameX() - 1)
		{
			_openPage->setFrameX(_openPage->getMaxFrameX() - 1);
		}
	}

	if (PtInRect(&_startButton, _ptMouse) && _openPage->getFrameX() >= _openPage->getMaxFrameX() - 1)
	{
		_openPage->setFrameX(_openPage->getFrameX() + 1);
	}
	else if (!PtInRect(&_startButton, _ptMouse) && _openPage->getFrameX() >= _openPage->getMaxFrameX() - 1)
	{
		_openPage->setFrameX(_openPage->getMaxFrameX() - 1);
	}


	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _open)
	{
		if (PtInRect(&_startButton, _ptMouse))
		{
			_open = false;
			state = 1;
		}
	}
	
}

void opening::render(void)
{
	_openPage->frameRender(getMemDC(), 0, 0, _openPage->getFrameX(), _openPage->getFrameY());
}