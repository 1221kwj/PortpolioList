#include "StdAfx.h"
#include "gameStudy.h"


gameStudy::gameStudy(void)
{
}

gameStudy::~gameStudy(void)
{
}

HRESULT gameStudy::init(void)
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("backGround", "backGround.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_player = new player;
	_player->init();


	return S_OK;
}

void gameStudy::release(void)
{
	gameNode::release();

	SAFE_DELETE(_player);
	
	
}

void gameStudy::update(void)
{
	gameNode::update();
	

	if (_player)_player->update();
}

void gameStudy::render(void)
{
	IMAGEMANAGER->findImage("backImage")->render(getMemDC());
	IMAGEMANAGER->findImage("backGround")->render(getMemDC(), 0, 0);

	if (_player) _player->render();
	
	

	this->getBackBuffer()->render(getHDC(), 0, 0);
}