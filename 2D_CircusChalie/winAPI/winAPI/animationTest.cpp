#include "StdAfx.h"
#include "animationTest.h"

animationTest::animationTest(void)
{
}

animationTest::~animationTest(void)
{
}

HRESULT animationTest::init(void)
{
	gameNode::init();

	//숙제...
	//1. 마계촌 기사 구현해오기.. (마계촌 온라인 아님...)
	//2. 애니메이션매니져 써서 해오기..
	//3. 벌거벗고... 갑옷입고.. 다 해오기..
	//4. 앉아서 던지고, 서서 던지고, 점프하고, 달리면서 점프하고..
	//다 구현해올것...
	//5. 배경 이미지 출력...
	//6. 무기 던질것!!!

	_kkr = IMAGEMANAGER->addFrameImage("kkr", "elephant.bmp", 660, 268, 6, 4, true);

	KEYANIMANAGER->addDefPlayFrameAnimation("ani1", "kkr", 17, true, true);
	
	int arrAni[] = {23, 3, 7, 18, 2, 9};
	KEYANIMANAGER->addArrayFrameAnimation("ani2", "kkr", arrAni, 6, 3, true);

	KEYANIMANAGER->addCoordinateFrameAnimation("ani3", "kkr", 9, 3, 6, true, true);

	/*
	_kkr = IMAGEMANAGER->addFrameImage("kkr", "elephant.bmp", 660, 268, 6, 4, true);

	_ani1 = new animation;
	_ani1->init(_kkr->getWidth(), _kkr->getHeight(),
		_kkr->getFrameWidth(), _kkr->getFrameHeight());
	_ani1->setDefPlayFrame(true, true);
	_ani1->setFPS(17);

	int arrAni[] = {23, 3, 7, 18, 2, 9}; 
	_ani2 = new animation;
	_ani2->init(_kkr->getWidth(), _kkr->getHeight(),
		_kkr->getFrameWidth(), _kkr->getFrameHeight());
	_ani2->setPlayFrame(arrAni, 6, true);
	_ani2->setFPS(3);

	_ani3 = new animation;
	_ani3->init(_kkr->getWidth(), _kkr->getHeight(),
		_kkr->getFrameWidth(), _kkr->getFrameHeight());
	_ani3->setPlayFrame(9, 3, true, true);
	_ani3->setFPS(6);
	*/

	return S_OK;
}

void animationTest::release(void)
{
	gameNode::release();

	//SAFE_DELETE(_ani1);
	//SAFE_DELETE(_ani2);
	//SAFE_DELETE(_ani3);
}

void animationTest::update(void)
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		KEYANIMANAGER->start("ani1");
//		_ani1->start();
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		KEYANIMANAGER->start("ani2");
//		_ani2->start();
	}
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		KEYANIMANAGER->start("ani3");
//		_ani3->start();
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		KEYANIMANAGER->stop("ani1");
		KEYANIMANAGER->stop("ani2");
		KEYANIMANAGER->stop("ani3");
//		_ani1->stop();
//		_ani2->stop();
//		_ani3->stop();
	}

//	_ani1->frameUpdate(TIMEMANAGER->getElapsedTime());
//	_ani2->frameUpdate(TIMEMANAGER->getElapsedTime());
//	_ani3->frameUpdate(TIMEMANAGER->getElapsedTime());

	KEYANIMANAGER->update();
}

void animationTest::render(void)
{
	_kkr->aniRender(getMemDC(), 300, 100, KEYANIMANAGER->findAnimation("ani1"));
	_kkr->aniRender(getMemDC(), 300, 200, KEYANIMANAGER->findAnimation("ani2"));
	_kkr->aniRender(getMemDC(), 300, 300, KEYANIMANAGER->findAnimation("ani3"));
	
	//	_kkr->aniRender(getMemDC(), 300, 100, _ani1);
//	_kkr->aniRender(getMemDC(), 300, 200, _ani2);
//	_kkr->aniRender(getMemDC(), 300, 300, _ani3);
}
