#include "StdAfx.h"
#include "bullets.h"


bullet::bullet(void)
{
}


bullet::~bullet(void)
{
}

HRESULT bullet::init(int bulletMax, float range)
{
	gameNode::init();

	_range = range;

	for (int i = 0; i < bulletMax; i++)
	{
		tagBullet bullet;
		ZeroMemory(&bullet, sizeof(tagBullet));
		bullet.img = new image;
		bullet.img->init("puck.bmp", 36, 10, 2, 1, true, RGB(255, 0, 255));
		bullet.speed = 1.1f;
		bullet.fire = false;
		_vBullet.push_back(bullet);
	}

	return S_OK;
}

void bullet::release(void)
{
	gameNode::release();

	remove();
}

void bullet::remove(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void bullet::update(void)
{
	gameNode::update();

	move();
}

void bullet::render(void)
{
	draw();
}

void bullet::fire(float x, float y, float angle, float gravity)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->angle = angle;
		_viBullet->gravity = gravity;
		_viBullet->rc = RectMakeCenter(x, y, _viBullet->img->getWidth(), _viBullet->img->getHeight());
		break;
	}
}

//총알 이동
void bullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed + _viBullet->gravity;
		if (_viBullet->gravity > 0) _viBullet->gravity = _viBullet->gravity + 0.0019;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(),
			_viBullet->img->getHeight());

		//사거리 밖으로 나감.!
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet->fire = false;
		}
	}
}

//총알 그리기
void bullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top, 1, 0);
	}
}

RECT bullet::getRC(int num)
{
	if (_vBullet.size() < num) RectMakeCenter(0, 0, 0, 0);
	_viBullet = _vBullet.begin();
	for (int i = 0; i < num; i++) _viBullet++;
	return _viBullet->rc;
}

float bullet::getX(int num)
{
	if (_vBullet.size() < num) _viBullet->x = 0;
	_viBullet = _vBullet.begin();
	for (int i = 0; i < num; ++i) _viBullet++;
	return _viBullet->x;
}

float bullet::getY(int num)
{
	if (_vBullet.size() < num) _viBullet->y = 0;
	_viBullet = _vBullet.begin();
	for (int i = 0; i < num; ++i) _viBullet++;
	return _viBullet->y;
}

bool bullet::getFire(int num)
{
	if (_vBullet.size() < num) _viBullet->fire = true;
	_viBullet = _vBullet.begin();
	for (int i = 0; i < num; ++i) _viBullet++;
	return _viBullet->fire;
}

void bullet::fireTran(int num)
{
	if (_vBullet.size() < num) return;
	_viBullet = _vBullet.begin();
	for (int i = 0; i < num; i++) _viBullet++;
	_viBullet->fire = false;
}