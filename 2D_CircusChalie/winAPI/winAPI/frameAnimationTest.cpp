#include "StdAfx.h"
#include "frameAnimationTest.h"


frameAnimationTest::frameAnimationTest(void)
{
}


frameAnimationTest::~frameAnimationTest(void)
{
}

HRESULT frameAnimationTest::init(void)
{
	gameNode::init();

	_villagers = IMAGEMANAGER->addFrameImage("villagers", "villagers.bmp", 768, 768, 12, 8, true);

	return S_OK;
}

void frameAnimationTest::release(void)
{
	gameNode::release();
}

void frameAnimationTest::update(void)
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		FRAMEANIMANAGER->animationXFrame(_villagers, 8, 0.1, false, xFrameFinish);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		FRAMEANIMANAGER->animationYFrame(_villagers, 5, 0.1, false, yFrameFinish);
	}

	FRAMEANIMANAGER->update();
}

void frameAnimationTest::render(void)
{
	_villagers->frameRender(getMemDC(), 100, 100);
}

void frameAnimationTest::xFrameFinish(void)
{
//	MessageBox(_hWnd, "맨날 잊어먹어 version2.0!!!!", "빙신들아!! 저질실력!!!", MB_OK);
}

void frameAnimationTest::yFrameFinish(void)
{
//	MessageBox(_hWnd, "취업 못할꺼임!!!!", "숨쉬지마!!!", MB_OK);
}


