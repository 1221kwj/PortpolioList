#include "StdAfx.h"
#include "jump.h"

jump::jump(void)
	:_isJumping(false),
	_power(0.0f),
	_gravity(0.0f)
{
}

jump::~jump(void)
{
}

HRESULT jump::init(void)
{
	gameNode::init();
	return S_OK;
}

void jump::release(void)
{
	gameNode::release();
}

void jump::update(void)
{
	gameNode::update();

	if (!_isJumping) return;

	*_y -= _power;
	_power -= _gravity;

	if (_startY < *_y)
	{
		*_y = _startY;
		_isJumping = false;
	}
}

void jump::render(void)
{
}

void jump::jumping(float* x, float* y, float power, float gravity)
{
	if (_isJumping) return;
	_isJumping = true;

	_x = x;
	_y = y;

	_startX = *x;
	_startY = *y;

	_gravity = gravity;
	_power = power;
}
