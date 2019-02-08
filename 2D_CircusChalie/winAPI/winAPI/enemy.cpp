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
	_rc = RectMakeCenter(position.x, position.y,
		_image->getWidth(), _image->getHeight());

	_pb = new progressBar;
	_pb->init(position.x - _image->getWidth() / 2, 
		position.y - _image->getHeight() / 2 - 12);
	_pb->setGuage(3, 10);

	_rndFireCount = 0;
	_bulletFireCount = 0;

	return S_OK;
}

void enemy::release(void)
{
	gameNode::release();

	SAFE_DELETE(_pb);
}

void enemy::update(void)
{
	gameNode::update();

	move();

	_pb->update();
}

void enemy::render(void)
{
	draw();

	_pb->render();
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
