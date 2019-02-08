#include "StdAfx.h"
#include "flame.h"


flame::flame(void)
{
}


flame::~flame(void)
{
}

HRESULT flame::init(const char* imageName, float* x, float* y)
{
	gameNode::init();
	
	_img = IMAGEMANAGER->addFrameImage("flame", "flame.bmp", 432, 297, 9, 1, true, RGB(255, 0, 255));
	_x = x;
	_y = y;
	_rc = RectMakeCenter((int)_x, (int)_y, _img->getFrameWidth(), _img->getFrameHeight());

	_flameCount = 0.0f;

	return S_OK;
}

void flame::release(void)
{
	gameNode::release();
}

void flame::update(void)
{
	gameNode::update();

	if (FLAMECOUNT + _flameCount <= GetTickCount())
	{
		_flameCount = GetTickCount();
		_img->setFrameX(_img->getFrameX() + 1);
		if (_img->getFrameX() >= _img->getMaxFrameX())
		{
			_img->setFrameX(0);
		}
	}

	_rc = RectMakeCenter(*_x, *_y + 180, _img->getFrameWidth(), _img->getFrameHeight());
}

void flame::render(void)
{
	_img->frameRender(getMemDC(), _rc.left, _rc.top, _img->getFrameX(), _img->getFrameY());
}
