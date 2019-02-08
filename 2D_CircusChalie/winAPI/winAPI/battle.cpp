#include "StdAfx.h"
#include "battle.h"

battle::battle(void)
{
}

battle::~battle(void)
{
}

HRESULT battle::init(const char* imageName, int x, int y)
{
	ship::init(imageName, x, y);

	this->setAngle(DATABASE->getElementDataAngle("battle"));

	render();

	return S_OK;
}

void battle::keyControl(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_angle += 0.1f;
		if (_angle > PI * 2) _angle -= PI * 2;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_angle -= 0.1f;
		if (_angle < 0) _angle += PI * 2;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_speed += 0.03f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_speed -= 0.03f;
	}
}

/*
HRESULT battle::init(void)
{
	gameNode::init();

	return S_OK;
}

void battle::release(void)
{
	gameNode::release();
}

void battle::update(void)
{
	gameNode::update();
}

void battle::render(void)
{

}
*/