#include "StdAfx.h"
#include "knight.h"


knight::knight(void)
{
}


knight::~knight(void)
{
}

HRESULT knight::init(void)
{
	gameNode::init();

	_direction = KNIGHTDIRECTION_RIGHT_STOP;

	_image = IMAGEMANAGER->addFrameImage("knight", "knight.bmp", 1224, 624, 9, 4, true, RGB(255, 0, 255));

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2 + 200;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	//Ű �ִ� ���..
	int arrRightStop[] = {0};
	KEYANIMANAGER->addArrayFrameAnimation("knightRightStop", "knight", arrRightStop, 1, 4, false);

	int arrLeftStop[] = {9};
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftStop", "knight", arrLeftStop, 1, 4, false);

	int arrRightRun[] = {1, 2, 3, 4, 5, 6};
	KEYANIMANAGER->addArrayFrameAnimation("knightRightRun", "knight", arrRightRun, 6, 10, true);

	int arrLeftRun[] = {10, 11, 12, 13, 14, 15};
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftRun", "knight", arrLeftRun, 6, 10, true);

	int arrRightSit[] = {18};
	KEYANIMANAGER->addArrayFrameAnimation("knightRightSit", "knight", arrRightSit, 1, 10, false);

	int arrLeftSit[] = {27};
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftSit", "knight", arrLeftSit, 1, 10, false);

	int arrRightFire[] = {7, 8};
	KEYANIMANAGER->addArrayFrameAnimation("knightRightFire", "knight", arrRightFire, 2, 20, false, cbRightFire, this);

	int arrLeftFire[] = {16, 17};
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftFire", "knight", arrLeftFire, 2, 20, false, cbLeftFire, this);

	int arrRightSitFire[] = {19, 20};
	KEYANIMANAGER->addArrayFrameAnimation("knightRightSitFire", "knight", arrRightSitFire, 2, 20, false, cbRightSitFire, this);

	int arrLeftSitFire[] = {28, 29};
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftSitFire", "knight", arrLeftSitFire, 2, 20, false, cbLeftSitFire, this);

	int arrRightJump[] = {22, 24, 25};
	KEYANIMANAGER->addArrayFrameAnimation("knightRightJump", "knight", arrRightJump, 2, 3, false, cbRightJump, this);

	int arrLeftJump[] = {31, 33, 34};
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftJump", "knight", arrLeftJump, 2, 3, false, cbLeftJump, this);

	int arrRightRunJump[] = {21, 23};
	KEYANIMANAGER->addArrayFrameAnimation("knightRightRunJump", "knight", arrRightRunJump, 2, 3, false, cbRightRunJump, this);

	int arrLeftRunJump[] = {30, 32};
	KEYANIMANAGER->addArrayFrameAnimation("knightLeftRunJump", "knight", arrLeftRunJump, 2, 3, false, cbLeftRunJump, this);


	_knightMotion = KEYANIMANAGER->findAnimation("knightRightStop");


	_jump = new jump;
	_jump->init();


	//�ָ�����
	//1. �ռ� �����...
	//2. ������ ���� ��� ���콺�� �浹��Ű��....
	//(�浹üũ Ȯ���� ȭ�鿡 �˾Ƽ� ǥ���ϱ�)
	//3. ��Ǫ������ �����ϱ�...


	return S_OK;
}

void knight::release(void)
{
	gameNode::release();

	_jump->release();
	SAFE_DELETE(_jump);
}

void knight::update(void)
{
	gameNode::update();

	//�����޷�
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_direction = KNIGHTDIRECTION_RIGHT_RUN;
		_knightMotion = KEYANIMANAGER->findAnimation("knightRightRun");
		_knightMotion->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_direction = KNIGHTDIRECTION_RIGHT_STOP;
		_knightMotion = KEYANIMANAGER->findAnimation("knightRightStop");
		_knightMotion->start();
	}

	//�޴޷�
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_direction = KNIGHTDIRECTION_LEFT_RUN;
		_knightMotion = KEYANIMANAGER->findAnimation("knightLeftRun");
		_knightMotion->start();
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_direction = KNIGHTDIRECTION_LEFT_STOP;
		_knightMotion = KEYANIMANAGER->findAnimation("knightLeftStop");
		_knightMotion->start();
	}

	//�ɾ�
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		if (_direction == KNIGHTDIRECTION_RIGHT_STOP ||
			_direction == KNIGHTDIRECTION_RIGHT_RUN)
		{
			_direction = KNIGHTDIRECTION_RIGHT_SIT;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightSit");
			_knightMotion->start();
		}
		else if (_direction == KNIGHTDIRECTION_LEFT_STOP ||
			_direction == KNIGHTDIRECTION_LEFT_RUN)
		{
			_direction = KNIGHTDIRECTION_LEFT_SIT;
			_knightMotion = KEYANIMANAGER->findAnimation("knightLeftSit");
			_knightMotion->start();
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (_direction == KNIGHTDIRECTION_RIGHT_SIT)
		{
			_direction = KNIGHTDIRECTION_RIGHT_STOP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightStop");
			_knightMotion->start();
		}
		else if (_direction == KNIGHTDIRECTION_LEFT_SIT)
		{
			_direction = KNIGHTDIRECTION_LEFT_STOP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightLeftStop");
			_knightMotion->start();
		}
	}

	//����
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//���� ����
		if (_direction == KNIGHTDIRECTION_RIGHT_STOP ||
			_direction == KNIGHTDIRECTION_RIGHT_RUN)
		{
			_direction = KNIGHTDIRECTION_RIGHT_FIRE;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightFire");
			_knightMotion->start();
		}
		//���� ����
		else if (_direction == KNIGHTDIRECTION_LEFT_STOP ||
			_direction == KNIGHTDIRECTION_LEFT_RUN)
		{
			_direction = KNIGHTDIRECTION_LEFT_FIRE;
			_knightMotion = KEYANIMANAGER->findAnimation("knightLeftFire");
			_knightMotion->start();
		}
		
		//�ɾƼ� â ������
		if (_direction == KNIGHTDIRECTION_RIGHT_SIT)
		{
			_direction = KNIGHTDIRECTION_RIGHT_SIT_FIRE;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightSitFire");
			_knightMotion->start();
		}
		else if (_direction == KNIGHTDIRECTION_LEFT_SIT)
		{
			_direction = KNIGHTDIRECTION_LEFT_FIRE;
			_knightMotion = KEYANIMANAGER->findAnimation("knightLeftSitFire");
			_knightMotion->start();
		}
	}

	//����
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_jump->jumping(&_x, &_y, 8.1f, 0.4f);
		if (_direction == KNIGHTDIRECTION_RIGHT_STOP)
		{
			_direction = KNIGHTDIRECTION_RIGHT_JUMP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightJump");
			_knightMotion->start();
		}
		else if (_direction == KNIGHTDIRECTION_LEFT_STOP)
		{
			_direction = KNIGHTDIRECTION_LEFT_JUMP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightLeftJump");
			_knightMotion->start();
		}

		else if (_direction == KNIGHTDIRECTION_RIGHT_RUN)
		{
			_direction = KNIGHTDIRECTION_RIGHT_RUN_JUMP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightRightRunJump");
			_knightMotion->start();
		}
		else if (_direction == KNIGHTDIRECTION_LEFT_RUN)
		{
			_direction = KNIGHTDIRECTION_LEFT_RUN_JUMP;
			_knightMotion = KEYANIMANAGER->findAnimation("knightLeftRunJump");
			_knightMotion->start();
		}

	}

	_jump->update();
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());

	switch (_direction)
	{
		case KNIGHTDIRECTION_RIGHT_STOP: case KNIGHTDIRECTION_LEFT_STOP:
		break;
		case KNIGHTDIRECTION_RIGHT_RUN: case KNIGHTDIRECTION_RIGHT_RUN_JUMP:
			_x += SPEED;
			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
		case KNIGHTDIRECTION_LEFT_RUN: case KNIGHTDIRECTION_LEFT_RUN_JUMP:
			_x -= SPEED;
			_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(), _image->getFrameHeight());
		break;
	}

	KEYANIMANAGER->update();
}

void knight::render(void)
{
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _knightMotion);
}

//����������?
void knight::cbRightFire(void* obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_RIGHT_STOP);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightRightStop"));
	k->getKnightMotion()->start();
}

//�޴�����?
void knight::cbLeftFire(void* obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_LEFT_STOP);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightLeftStop"));
	k->getKnightMotion()->start();
}

//�ɾ� �������� ��
void knight::cbRightSitFire(void* obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_RIGHT_SIT);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightRightSit"));
	k->getKnightMotion()->start();
}

//�ɾ� ���ʴ��� ��
void knight::cbLeftSitFire(void* obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_LEFT_SIT);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightLeftSit"));
	k->getKnightMotion()->start();
}

//���� ���ڸ� ����
void knight::cbRightJump(void* obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_RIGHT_STOP);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightRightStop"));
	k->getKnightMotion()->start();
}

//���� ���ڸ� ����
void knight::cbLeftJump(void* obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_LEFT_STOP);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightLeftStop"));
	k->getKnightMotion()->start();
}

//���� �޷� ���� �� ��
void knight::cbRightRunJump(void* obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_RIGHT_RUN);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightRightRun"));
	k->getKnightMotion()->start();
}

//�� �޷� ���� �� ��
void knight::cbLeftRunJump(void* obj)
{
	knight* k = (knight*)obj;

	k->setKnightDirection(KNIGHTDIRECTION_LEFT_RUN);
	k->setKnightMotion(KEYANIMANAGER->findAnimation("knightLeftRun"));
	k->getKnightMotion()->start();
}