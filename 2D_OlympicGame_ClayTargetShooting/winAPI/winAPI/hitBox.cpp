#include "stdafx.h"
#include "hitBox.h"


hitBox::hitBox()
{
}


hitBox::~hitBox()
{
}

HRESULT hitBox::init(float x, float y)
{
	gameNode::init();
	
	_hitBox = IMAGEMANAGER->addFrameImage("_hitBox", "target.bmp", 80, 36, 2, 1, true, RGB(255, 0, 255));

	_x = x;
	_y = y;

	_rc = RectMakeCenter(_x, _y, _hitBox->getFrameWidth(), _hitBox->getFrameHeight());

	frameX = 0;
	frameCount = 0;
	return S_OK;
}

void hitBox::release(void)
{
	gameNode::release();

}

void hitBox::update(void)
{
	gameNode::update();

	
	if (frameCount > 0)
	{
		--frameCount;
		if (frameCount == 0) frameX = 0;
	}

	_rc = RectMakeCenter(_x, _y, _hitBox->getFrameWidth(), _hitBox->getFrameHeight());
}

void hitBox::render(void)
{
	_hitBox->frameRender(getMemDC(), _rc.left - 3, _rc.top - 3, frameX, 0);
}

void hitBox::setFrame(int x, int num)
{
	frameX = x;
	frameCount = num;
}
