#include "StdAfx.h"
#include "ship.h"

ship::ship(void)
{
}

ship::~ship(void)
{
}

HRESULT ship::init(const char* imageName, int x, int y)
{
	gameNode::init();

	_img = IMAGEMANAGER->findImage(imageName);
	_x = x;
	_y = y;
	_angle = 0.0f;
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	_speed = 0.0f;
	_radius = _img->getFrameWidth() / 2;

	return S_OK;
}

void ship::release(void)
{
	gameNode::release();
}

void ship::update(void)
{
	gameNode::update();

	//keyControl();
	move();
}

void ship::render(void)
{
	draw();
}

//일반 드로우..
void ship::draw(void)
{
	_img->frameRender(getMemDC(), _rc.left, _rc.top);
}

//포커스이면..
void ship::focusDraw(void)
{
	char str[128];

	//좌표
	sprintf(str, "좌표 x : %d, y : %d", _rc.left, _rc.top);
	TextOut(getMemDC(), 800, 10, str, strlen(str));

	//각도
	sprintf(str, "각도 : %d도", int(_angle * 180.0f / PI));
	TextOut(getMemDC(), 800, 30, str, strlen(str));

	//스피드
	sprintf(str, "스피드 : %.2f", _speed);
	TextOut(getMemDC(), 800, 50, str, strlen(str));

	_img->frameRender(getMemDC(), WINSIZEX / 2 - _img->getFrameWidth() / 2,
		WINSIZEY / 2 - _img->getFrameHeight() / 2);
}

//포커스가 아니면...
void ship::defaultDraw(RECT rcFocus)
{
	RECT rcSour;
	RECT rcTemp;

	int x, y;

	rcSour.left = rcFocus.left - ((WINSIZEX / 2) - (rcFocus.right - rcFocus.left) / 2);
	rcSour.top = rcFocus.top - ((WINSIZEY / 2) - (rcFocus.bottom - rcFocus.top) / 2);
	rcSour.right = rcFocus.left + WINSIZEX;
	rcSour.bottom = rcFocus.top + WINSIZEY;

	if (!(IntersectRect(&rcTemp, &_rc, &rcSour))) return;

	x = _rc.left - rcSour.left;
	y = _rc.top - rcSour.top;

	_img->frameRender(getMemDC(), x, y);
}

void ship::move(void)
{
	int frame;
	float angle;

	angle = _angle + PI_16;
	if (angle >= PI * 2) angle -= PI * 2;

	frame = int(angle / PI_8);
	_img->setFrameX(frame);

	float elpasedTime = TIMEMANAGER->getElapsedTime();
	float moveSpeed = elpasedTime * 100;

	_x += cosf(_angle) * _speed * moveSpeed;
	_y += -sinf(_angle) * _speed * moveSpeed;

	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void ship::keyControl(void)
{
}

