#include "StdAfx.h"
#include "ghostsnGoblinsScene.h"

ghostsnGoblinsScene::ghostsnGoblinsScene(void)
{
}

ghostsnGoblinsScene::~ghostsnGoblinsScene(void)
{
}

HRESULT ghostsnGoblinsScene::init(void)
{
	gameNode::init();

	IMAGEMANAGER->addImage("bgStage1", "bgStage1.bmp", WINSIZEX, WINSIZEY);

	_knight = new knight;
	_knight->init();

	return S_OK;
}

void ghostsnGoblinsScene::release(void)
{
	gameNode::release();

	_knight->release();
	SAFE_DELETE(_knight);
}

void ghostsnGoblinsScene::update(void)
{
	gameNode::update();

	_knight->update();
}

void ghostsnGoblinsScene::render(void)
{
	IMAGEMANAGER->findImage("bgStage1")->render(getMemDC());

	_knight->render();
}
