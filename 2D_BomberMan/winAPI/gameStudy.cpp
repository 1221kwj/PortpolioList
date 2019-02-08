#include "StdAfx.h"
#include "gameStudy.h"


gameStudy::gameStudy(void) {}

gameStudy::~gameStudy(void) {}

HRESULT gameStudy::init(void)
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("backGround", "backGround.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	_tile = new tile;
	_tile->init();

	_player = new player;
	_player->init();
	
	_player->setAdressTileLink(_tile);

	return S_OK;
}

void gameStudy::release(void)
{
	gameNode::release();

	SAFE_DELETE(_tile);
	SAFE_DELETE(_player);
}

void gameStudy::update(void)
{
	gameNode::update();

	if (_player) _player->update();
	if (_tile) _tile->update();
}

void gameStudy::render(void)
{
	IMAGEMANAGER->findImage("backImage")->render(getMemDC());
	IMAGEMANAGER->findImage("backGround")->render(getMemDC());
	
	if (_tile) _tile->render();
	if (_player) _player->render();
	

	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);
}