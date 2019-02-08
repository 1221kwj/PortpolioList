#include "stdafx.h"
#include "firstPage.h"

firstPage::firstPage() {}
firstPage::~firstPage() {}

HRESULT firstPage::init(void)
{
	gameNode::init();
	_loadingImage = IMAGEMANAGER->addFrameImage("loading", "loading.bmp", 6400, 600, 8, 1, true, RGB(255, 0, 255));
	_loadingImage->setFrameX(_loadingImage->getMaxFrameX());

	_openDoor = IMAGEMANAGER->addFrameImage("openDoor", "openDoor.bmp", 4000, 600, 5, 1, true, RGB(255, 0, 255));
	
	_worldMap = IMAGEMANAGER->addFrameImage("worldMap", "worldmap.bmp", 3200, 600, 4, 1, false, RGB(255, 0, 255));
	
	_worldMapBackButton = IMAGEMANAGER->addImage("worldMapBackButton", "worldMapBackButton.bmp", 89, 89, true, RGB(255, 0, 255));
	
	_buttonImage = IMAGEMANAGER->addFrameImage("button", "worldmapButton.bmp", 1600, 600, 2, 1, true, RGB(149, 230, 140));
	_button = RectMake(60, 100, 285, 69);

	_powerupImage = IMAGEMANAGER->addFrameImage("powerup", "powerupButton.bmp", 570, 69, 2, 1, true, RGB(149, 230, 140));
	_powerup = RectMake(60, 194, 285, 69);
	
	
	_firstOn = false;
	_loading = false;
	_doorOpen = false;
	state = 0;

	_country[0] = RectMake(52, 427, 30, 30);
	_country[1] = RectMake(288, 355, 30, 30);
	_country[2] = RectMake(428, 300, 30, 30);


	return S_OK;
}

void firstPage::release(void)
{
	gameNode::release();

}

void firstPage::update(void)
{
	gameNode::update();

	if (FRAMECOUNT + _firstCount <= GetTickCount() && !_doorOpen)
	{
		_firstCount = GetTickCount();
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
	
	if (FRAMECOUNT + _firstCount <= GetTickCount() && _doorOpen)
	{
		_firstCount = GetTickCount();
		_openDoor->setFrameX(_openDoor->getFrameX() + 1);
		if (_openDoor->getFrameX() >= _openDoor->getMaxFrameX())
		{
			_openDoor->setFrameX(_openDoor->getMaxFrameX());
		}
	}

	if (PtInRect(&_button, _ptMouse) && !_loading) _buttonImage->setFrameX(1);
	else if (!PtInRect(&_button, _ptMouse) && !_loading) _buttonImage->setFrameX(0);

	if (PtInRect(&_powerup, _ptMouse) && !_loading) _powerupImage->setFrameX(1);
	else if (!PtInRect(&_powerup, _ptMouse) && !_loading) _powerupImage->setFrameX(0);

	
	if (_openDoor->getFrameX() == _openDoor->getMaxFrameX())
	{
		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&_country[i], _ptMouse))
			{
				if (i == 0)
				{
					_worldMap->setFrameX(2);
					break;
				}
				else if (i == 1)
				{
					_worldMap->setFrameX(1);
					break;
				}
				else if (i == 2) 
				{
					_worldMap->setFrameX(3);
					break;
				}
			}
			else if (!PtInRect(&_country[i], _ptMouse))
			{
				_worldMap->setFrameX(0);
			}
		}
	}
	
	
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && !_loading)
	{
		if (PtInRect(&_button, _ptMouse) && !_doorOpen)
		{
			_doorOpen = true;
		}

		if (PtInRect(&_powerup, _ptMouse) && !_doorOpen)
		{
			state = 5;
			_firstOn = false;
			_loading = false;
		}
		
		for (int i = 0; i < 3; i++)
		{
			if (PtInRect(&_country[i], _ptMouse) && _openDoor->getFrameX() == _openDoor->getMaxFrameX())
			{
				_firstOn = false;
				_doorOpen = false;
				if (i == 0)
				{
					state = 3;
					break;
				}
				else if (i == 1)
				{
					state = 2;
					break;
				}
				else if (i == 2)
				{
					state = 4;
					break;
				}
			}
		}
	}

}

void firstPage::render(void)
{
	if (!_loading)
	{
		_worldMap->frameRender(getMemDC(), 0, 0, _worldMap->getFrameX(), _worldMap->getFrameY());
		_openDoor->frameRender(getMemDC(), 0, 0, _openDoor->getFrameX(), _openDoor->getFrameY());
		if (_openDoor->getFrameX() < _openDoor->getMaxFrameX())
		{
			_buttonImage->frameRender(getMemDC(), 0, 0, _buttonImage->getFrameX(), _buttonImage->getFrameY());
			_powerupImage->frameRender(getMemDC(), _powerup.left, _powerup.top,
				_powerupImage->getFrameX(), _powerupImage->getFrameY());
		}
		_worldMapBackButton->render(getMemDC(), 5, 509);
		
	}

	_loadingImage->frameRender(getMemDC(), 0, 0, _loadingImage->getFrameX(), _loadingImage->getFrameY());
}
