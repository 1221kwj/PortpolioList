#include "stdafx.h"
#include "circusJump.h"


circusJump::circusJump()
	:_isJumping(false),
	_power(0.0f),
	_gravity(0.0f),
	_isRightLeft(false),
	_stopJump(false)
{
}


circusJump::~circusJump()
{
}

HRESULT circusJump::init(void)
{
	gameNode::init();

	return S_OK;
}

void circusJump::release(void)
{
	gameNode::release();



}

void circusJump::update(void)
{
	gameNode::update();

	if (!_isJumping) return;

	*_y -= _power;
	_power -= _gravity;
	
	//if (!_stopJump)
	//{
	//	if (_isRightLeft)
	//	{
	//		*_x += 2.3;
	//	}
	//	else *_x -= 2.3;
	//}
	

	if (_startY < *_y)
	{
		*_y = _startY;
		_isJumping = false;
	}

}

void circusJump::render(void)
{

}

void circusJump::jumping(float* x, float* y, float power, float gravity, bool isRightLeft, bool stopJump)
{
	if (_isJumping) return;
	_isJumping = true;

	_isRightLeft = isRightLeft;
	_stopJump = stopJump;
	_x = x;
	_y = y;

	_startX = *x;
	_startY = *y;

	_gravity = gravity;
	_power = power;
}