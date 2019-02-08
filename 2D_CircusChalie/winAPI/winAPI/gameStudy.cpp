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

	//�� ����
	SCENEMANAGER->addScene("circusSceneOne", new circusSceneOne);
	SCENEMANAGER->addScene("circusSceneTwo", new circusSceneTwo);
	
	//���� ���� _sceneOne���� ����
	SCENEMANAGER->changeScene("circusSceneOne");
	
	return S_OK;
}

void gameStudy::release(void)
{
	gameNode::release();
}

void gameStudy::update(void)
{
	gameNode::update();
	SCENEMANAGER->update();
}

void gameStudy::render(void)
{
	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());
	this->getBackBuffer()->render(getHDC(), 0, 0);
}