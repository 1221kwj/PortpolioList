#include "StdAfx.h"
#include "carrier.h"


carrier::carrier(void)
{
}


carrier::~carrier(void)
{
}

void carrier::keyControl(void)
{
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_angle += 0.1f;
		if (_angle > PI * 2) _angle -= PI * 2;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_angle -= 0.1f;
		if (_angle < 0) _angle += PI * 2;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		_speed += 0.03f;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		_speed -= 0.03f;
	}
}
