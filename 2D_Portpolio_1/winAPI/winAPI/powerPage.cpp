#include "stdafx.h"
#include "powerPage.h"


powerPage::powerPage()
{
}


powerPage::~powerPage()
{
}

HRESULT powerPage::init(void)
{
	gameNode::init();

	_powerOn = false;
	_loading = false;
	_frameCount = 0.0f;

	_worldMapBackButton = IMAGEMANAGER->addImage("worldMapBackButton", "worldMapBackButton.bmp", 89, 89, true, RGB(255, 0, 255));
	_loadingImage = IMAGEMANAGER->addFrameImage("loading", "loading.bmp", 6400, 600, 8, 1, true, RGB(255, 0, 255));
	_loadingImage->setFrameX(_loadingImage->getMaxFrameX());
	_powerUI = IMAGEMANAGER->addImage("powerUI", "powerupUI.bmp", 800, 600, false, RGB(255, 0, 255));
	
	ZeroMemory(&_powerUpRect, sizeof(_powerUpRect));

	char ptr1[128];
	char ptr2[128];
	for (int i = 0; i < 5; i++)
	{
		sprintf(ptr1, "cat%dpower", (i + 1));
		sprintf(ptr2, "cat%dpower.bmp", (i + 1));
		_powerUpRect[i].img = IMAGEMANAGER->addFrameImage(ptr1, ptr2, 296, 444, 2, 3, true, RGB(255, 0, 255));
		_powerUpRect[i].rc = RectMake(10 + 158 * i, 150, _powerUpRect[i].img->getFrameWidth(), _powerUpRect[i].img->getFrameHeight());
		_powerUpRect[i].frameX = 0;
		_powerUpRect[i].frameY = 0;
	}

	return S_OK;
}

void powerPage::release(void)
{
	gameNode::release();

}

void powerPage::update(void)
{
	gameNode::update();
	
	if (FRAMECOUNT + _frameCount <= GetTickCount())
	{
		_frameCount = GetTickCount();
		if (_loading)
		{
			_loadingImage->setFrameX(_loadingImage->getFrameX() - 1);
			if (_loadingImage->getFrameX() <= 0)
			{
				_loadingImage->setFrameX(0);
				_loading = false;
			}
		}
		else if (!_loading)
		{
			_loadingImage->setFrameX(_loadingImage->getFrameX() + 1);
			if (_loadingImage->getFrameX() >= _loadingImage->getMaxFrameX())
			{
				_loadingImage->setFrameX(_loadingImage->getMaxFrameX());
			}
		}
	}


	for (int i = 0; i < 5; i++)
	{
		if (PtInRect(&_powerUpRect[i].rc, _ptMouse) && !_loading) _powerUpRect[i].frameX = 1;
		else if (!PtInRect(&_powerUpRect[i].rc, _ptMouse) && !_loading) _powerUpRect[i].frameX = 0;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !_loading)
	{
		for (int i = 0; i < 5; i++)
		{
			if (PtInRect(&_powerUpRect[i].rc, _ptMouse) && _powerUpRect[i].frameY < _powerUpRect[i].img->getMaxFrameY())
			{
				++_powerUpRect[i].frameY;
			}
		}
	}

}

void powerPage::render(void)
{
	if (!_loading)
	{
		_powerUI->render(getMemDC());

		for (int i = 0; i < 5; i++)
		{
			_powerUpRect[i].img->frameRender(getMemDC(), _powerUpRect[i].rc.left, _powerUpRect[i].rc.top,
				_powerUpRect[i].frameX, _powerUpRect[i].frameY);
		}

		_worldMapBackButton->render(getMemDC(), 5, 509);


	}
	
	_loadingImage->frameRender(getMemDC(), 0, 0, _loadingImage->getFrameX(), _loadingImage->getFrameY());
}