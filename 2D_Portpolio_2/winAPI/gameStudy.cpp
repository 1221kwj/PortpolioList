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

	IMAGEMANAGER->addImage("mouseCursor", "mouseCursor.bmp", 25, 30, true, RGB(255, 0, 255));
	_button = new button;
	_button->init();

	_player = new player;
	_player->init();
	_player->setAddressDatabaseLink(_button->_database);

	_enemy = new enemy;
	_enemy->init();
	_enemy->setAddressPlayerLink(_player);
	_enemy->setAddressDatabaseLink(_button->_database);

	SetCursor(NULL);
	ShowCursor(FALSE);

	
	return S_OK;
}

void gameStudy::release(void)
{
	gameNode::release();

	SAFE_DELETE(_button);

	SAFE_DELETE(_player);

	SAFE_DELETE(_enemy);
}

void gameStudy::update(void)
{
	gameNode::update();

	if (_button) _button->update();
	if (_button->getState() == BATTLE && _button->battleStart)
	{
		_player->update();
		_enemy->update();
		CameraMove();
	}
}

void gameStudy::render(void)
{
	IMAGEMANAGER->findImage("backImage")->render(getMemDC());
	
	//TIMEMANAGER->render(getMemDC());
	if (_button) _button->render();
	if (_button->getState() == BATTLE && _button->battleStart)
	{
		_enemy->render();
	}
	//Rectangle(getMemDC(), 100, 100, 200, 200);
	//char str[128];
	//sprintf(str, "%f", _button->_field->cameraX);
	//TextOut(getMemDC(), 20, 20, str, strlen(str));
	//
	//char str2[128];
	//sprintf(str2, "%f",_player->getPlayerX());
	//TextOut(getMemDC(), 20, 40, str2, strlen(str2));


	IMAGEMANAGER->render("mouseCursor", getMemDC(), _ptMouse.x-5, _ptMouse.y-8);
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

void gameStudy::CameraMove()
{

	if (!_enemy->startBoss)
	{
		if (_button->_field->cameraX<10990 - WINSIZEX&&_player->getPlayerX()>WINSIZEX / 2 && !_button->_field->lockCamera)
		{
			_button->_field->cameraX += _player->getPlayerX() - WINSIZEX / 2;
			_enemy->moveAllEnemy(_player->getPlayerX() - WINSIZEX / 2);
			_button->_field->moveChangeBlock(_player->getPlayerX() - WINSIZEX / 2);
			_button->_field->moveSpawnBlock(_player->getPlayerX() - WINSIZEX / 2);
			_button->_field->goalBlock.x -= _player->getPlayerX() - WINSIZEX / 2;
			_player->setPlayerX();
		}
		if (_enemy->CheckEnemy())
		{
			_button->_field->lockCamera = false;
			_button->_database->goSwitch = true;
		}
	}
	else
	{

	}
	for (int i = 0; i < 4; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_button->_field->changeBlock[i].rc, &_player->getPlayerRect()) && _button->_field->changeBlock[i].check)
		{
			_player->minY = _button->_field->changeBlock[i].minY;
			_player->maxY = _button->_field->changeBlock[i].maxY;
			_button->_field->changeBlock[i].check = false;
		}
	}
	for (int i = 0; i < 6; i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_button->_field->spawnBlock[i].rc, &_player->getPlayerRect()) && _button->_field->spawnBlock[i].check)
		{
			_button->_field->spawnBlock[i].check = false;
			_button->_field->lockCamera = true;
			switch (i)
			{
			case 0:
				_enemy->makeEnemy(10, 1);
				break;
			case 1:
				_enemy->makeEnemy(5, 1);
				_enemy->makeEnemy(3, 2);
				break;
			case 2:
				_enemy->makeEnemy(10, 1);
				_enemy->makeEnemy(3, 2);
				break;
			case 3:
				_enemy->makeEnemy(10, 1);
				_enemy->makeEnemy(5, 2);
				break;
			case 4:
				_enemy->makeEnemy(7, 1);
				_enemy->makeEnemy(7, 2);
				break;
			case 5:
				_enemy->makeEnemy(10, 1);
				_enemy->makeEnemy(7, 2);
				break;
			case 6:
				_enemy->makeEnemy(10, 1);
				_enemy->makeEnemy(10, 2);
				break;
			}
		}
	}
	RECT rc;
	if (IntersectRect(&rc, &_player->getPlayerRect(), &_button->_field->goalBlock.rc)&&_button->_field->goalBlock.check)
	{
		_enemy->startBoss = true;
		_button->_field->cameraX = 0;
		_button->_field->goalBlock.check = false;
		_player->setPlayer2X(100);
		_player->maxY = 580;
		_player->minY = 380;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("bossBGM.wav"), NULL, SND_LOOP | SND_ASYNC);
	}
}