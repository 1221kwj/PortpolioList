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

	//씬 생성
	SCENEMANAGER->addScene("circusSceneOne", new circusSceneOne);
	SCENEMANAGER->addScene("circusSceneTwo", new circusSceneTwo);
	
	//현재 씬을 _sceneOne으로 설정
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