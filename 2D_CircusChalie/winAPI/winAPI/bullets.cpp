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
		bullet.img->init("bullet.bmp", 12, 12, true, RGB(255, 0, 255));
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

void bullet::fire(float x, float y)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (_viBullet->fire) continue;
		_viBullet->fire = true;
		_viBullet->x = _viBullet->fireX = x;
		_viBullet->y = _viBullet->fireY = y;
		_viBullet->rc = RectMakeCenter(x, y,
			_viBullet->img->getWidth(),
			_viBullet->img->getHeight());
		break;
	}
}

//�Ѿ� �̵�
void bullet::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->getWidth(),
			_viBullet->img->getHeight());

		//��Ÿ� ������ ����.!
		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet->fire = false;
		}
	}
}

//�Ѿ� �׸���
void bullet::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->fire) continue;

		_viBullet->img->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

bulletM1::bulletM1(void)
{
}


bulletM1::~bulletM1(void)
{
}

//�������� ���� �Ѿ� (�򶧸��� ����� �����Ѵ�)
HRESULT bulletM1::init(const char* imageName, 
		int bulletMax, float range)
{
	gameNode::init();

	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bulletM1::release(void)
{
	gameNode::release();

	_vBullet.clear();
}

void bulletM1::update(void)
{
	gameNode::update();

	move();
}

void bulletM1::render(void)
{
	draw();
}

void bulletM1::fire(float x, float y, float angle,
	float speed)
{
	//�߻� ���� ���� �Ѵ�
	if (_bulletMax < _vBullet.size()) return;

	tagBullet bullets;
	ZeroMemory(&bullets, sizeof(tagBullet));

	bullets.img = IMAGEMANAGER->findImage(_imageName);
	bullets.speed = speed;
	bullets.angle = angle;
	bullets.radius = bullets.img->getWidth() / 2;
	bullets.x = bullets.fireX = x;
	bullets.y = bullets.fireY = y;
	bullets.rc = RectMakeCenter(bullets.x, bullets.y,
		bullets.img->getWidth(), bullets.img->getHeight());
	_vBullet.push_back(bullets);
}

void bulletM1::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;
		
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
		_viBullet->img->getWidth(), _viBullet->img->getHeight());
	
		//��Ÿ� ������ ������...
		if (_range < getDistance(_viBullet->fireX,
			_viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			_viBullet = _vBullet.erase(_viBullet++);
		}
		else ++_viBullet;
	}
}

void bulletM1::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->render(getMemDC(), _viBullet->rc.left, _viBullet->rc.top);
	}
}

void bulletM1::removeBullet(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}

missileM1::missileM1(void)
{
}


missileM1::~missileM1(void)
{
}

HRESULT missileM1::init(int bulletMax, float range)
{
	gameNode::init();

	//��Ÿ�
	_range = range;

	//���� �ִ� ����
	_bulletMax = bulletMax;

	return S_OK;
}

void missileM1::release(void)
{
	gameNode::release();

	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		SAFE_DELETE(_viBullet->img);
	}

	_vBullet.clear();
}

void missileM1::update(void)
{
	gameNode::update();

	move();
}

void missileM1::render(void)
{
	draw();
}

//���̾�~~~~!!
void missileM1::fire(float x, float y)
{
	//�ִ� �߻� ���� ����
	if (_bulletMax <= _vBullet.size()) return;

	tagBullet bullet;
	ZeroMemory(&bullet, sizeof(tagBullet));

	bullet.img = new image;
	bullet.img->init("missile.bmp", 416, 62, 13, 1, true, RGB(255, 0, 255));
	bullet.speed = 3.2f;
	bullet.x = bullet.fireX = x;
	bullet.y = bullet.fireY = y;
	bullet.rc = RectMakeCenter(x, y, bullet.img->getFrameWidth(),
		bullet.img->getFrameHeight());
	_vBullet.push_back(bullet);
}

void missileM1::move(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		_viBullet->y -= _viBullet->speed;
		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y, 
			_viBullet->img->getFrameWidth(),
		_viBullet->img->getFrameHeight());

		if (_range < getDistance(_viBullet->fireX, _viBullet->fireY, _viBullet->x, _viBullet->y))
		{
			SAFE_DELETE(_viBullet->img);
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}
}

void missileM1::draw(void)
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		_viBullet->img->frameRender(getMemDC(), _viBullet->rc.left, _viBullet->rc.top,
			_viBullet->img->getFrameX(), 0);

		if (ANICOUNT + _viBullet->count <= GetTickCount())
		{
			_viBullet->count = GetTickCount();
			_viBullet->img->setFrameX(_viBullet->img->getFrameX() + 1);
			if (_viBullet->img->getFrameX() >= _viBullet->img->getMaxFrameX())
			{
				_viBullet->img->setFrameX(0);
			}
		}
	}
}

void missileM1::removeMissile(int arrNum)
{
	_vBullet.erase(_vBullet.begin() + arrNum);
}
