#include "StdAfx.h"
#include "starWarsScene.h"
#include "battle.h"
#include "carrier.h"

starWarsScene::starWarsScene(void)
{
}

starWarsScene::~starWarsScene(void)
{
}

HRESULT starWarsScene::init(void)
{
	gameNode::init();

	IMAGEMANAGER->addImage("bgSpace", "bgSpace.bmp", 1000, 1000);
	IMAGEMANAGER->addFrameImage("battle", "battle.bmp", 1536, 79, 16, 1, true); 
	IMAGEMANAGER->addFrameImage("carrier", "carrier.bmp", 1984, 97, 16, 1, true, RGB(255, 255, 0)); 
	IMAGEMANAGER->addFrameImage("btnTest", "btnTest.bmp", 200, 120, 1, 2);

	_sm = new shipManager;
	_sm->init();


	return S_OK;
}


void starWarsScene::release(void)
{
	gameNode::release();

	_sm->release();
	SAFE_DELETE(_sm);
}

void starWarsScene::update(void)
{
	gameNode::update();

	_sm->update();
}

void starWarsScene::render(void)
{
	_sm->render();
}
