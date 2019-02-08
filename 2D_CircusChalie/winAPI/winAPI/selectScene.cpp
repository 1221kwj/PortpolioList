#include "StdAfx.h"
#include "selectScene.h"

selectScene::selectScene(void)
{
}

selectScene::~selectScene(void)
{
}

HRESULT selectScene::init(void)
{
	gameNode::init();

	IMAGEMANAGER->addFrameImage("btnTest", "btnTest.bmp", 200, 120, 1, 2);

	_btnAngleUp = new button;
	_btnAngleUp->init("btnTest", WINSIZEX / 2 + 200, WINSIZEY / 2, PointMake(0, 1),
		PointMake(0, 0), cbAngleUp);

	_btnAngleDown = new button;
	_btnAngleDown->init("btnTest", WINSIZEX / 2 - 200, WINSIZEY / 2, PointMake(0, 1),
		PointMake(0, 0), cbAngleDown);

	return S_OK;
}

void selectScene::release(void)
{
	gameNode::release();

	SAFE_DELETE(_btnAngleUp);
	SAFE_DELETE(_btnAngleDown);
}

void selectScene::update(void)
{
	gameNode::update();

	_btnAngleUp->update();
	_btnAngleDown->update();

	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		SCENEMANAGER->changeScene("starWarsScene");
	}
}

void selectScene::render(void)
{
	_btnAngleUp->render();
	_btnAngleDown->render();
}

void selectScene::cbAngleUp(void)
{
	DATABASE->setElementDataAngle("battle",
		DATABASE->getElementDataAngle("battle") + 0.1f);
}

void selectScene::cbAngleDown(void)
{
	DATABASE->setElementDataAngle("battle",
		DATABASE->getElementDataAngle("battle") - 0.1f);
}

