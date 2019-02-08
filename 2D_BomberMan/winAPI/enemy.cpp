#include "StdAfx.h"
#include "enemy.h"

enemy::enemy(void)
{
}

enemy::~enemy(void)
{
}

HRESULT enemy::init(void)
{
	gameNode::init();

	return S_OK;
}

HRESULT enemy::init(const char* imageName, POINT position)
{
	gameNode::init();

	_image = IMAGEMANAGER->findImage(imageName);
	_rc = RectMakeCenter(position.x, position.y, 36, 36);

	_rndFireCount = 0;
	_bulletFireCount = 0;

	return S_OK;
}

void enemy::release(void)
{
	gameNode::release();
}

void enemy::update(void)
{
	gameNode::update();

	move();
}

void enemy::render(void)
{
	draw();
}

void enemy::draw(void)
{
	_image->render(getMemDC(), _rc.left, _rc.top);
}

void enemy::move(void)
{

}

//½ð´Ù!!
bool enemy::bulletCountFire(void)
{
	if (_rndFireCount + _bulletFireCount <= GetTickCount())
	{
		_bulletFireCount = GetTickCount();
		_rndFireCount = RND->getFromFloatTo(80.0f, 120.0f);
		return true;
	}
	return false;
}
