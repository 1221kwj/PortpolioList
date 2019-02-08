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

	_opening = new opening;
	_opening->init();

	_firstPage = new firstPage;
	_firstPage->init();

	_power = new powerPage;
	_power->init();

	_battle01 = new battle01;
	_battle01->init();

	_battle02 = new battle02;
	_battle02->init();

	_battle03 = new battle03;
	_battle03->init();

	return S_OK;
}

void gameStudy::release(void)
{
	gameNode::release();

	SAFE_DELETE(_opening);
	SAFE_DELETE(_firstPage);
	SAFE_DELETE(_battle01);
	SAFE_DELETE(_battle02);
	SAFE_DELETE(_battle03);
}

void gameStudy::update(void)
{
	gameNode::update();
	
	if (_opening->getOpen()) state = 0;
	else if (!_opening->getOpen() && !_firstPage->getFirstOn() && state == 0)
	{
		_firstPage->setFirstOn(true);
		_firstPage->setLoading(true);
		state = 1;
	}
	
	if (!_opening->getOpen() && !_firstPage->getFirstOn() && state == 1)
	{
		state = _firstPage->getState();
		if (state == 2)
		{
			_battle01->setBattle01On(true);
		}
		else if (state == 3)
		{
			_battle02->setBattle02On(true);
		}
		else if (state == 4)
		{
			_battle03->setBattle03On(true);
		}
		else if (state == 5)
		{
			_power->setPowerOn(true);
			_power->setLoading(true);
		}
	}

	switch (state)
	{
	case 0:
		_opening->update();
		break;
	case 1:
		_firstPage->update();
		break;
	case 2:
		_battle01->update();
		break;
	case 3:
		_battle02->update();
		break;
	case 4:
		_battle03->update();
		break;
	case 5:
		_power->update();
	}
	

}

void gameStudy::render(void)
{
	IMAGEMANAGER->findImage("backImage")->render(getMemDC());
	
	switch (state)
	{
	case 0:
		if (_opening->getOpen()) _opening->render();
		break;
	case 1:
		if (_firstPage->getFirstOn()) _firstPage->render();
		break;
	case 2:
		if (_battle01->getBattle01On()) _battle01->render();
		break;
	case 3:
		if (_battle02->getBattle02On()) _battle02->render();
		break;
	case 4:
		if (_battle03->getBattle03On()) _battle03->render();
		break;
	case 5:
		if (_power->getPowerOn()) _power->render();
	}
	

	this->getBackBuffer()->render(getHDC(), 0, 0);
}