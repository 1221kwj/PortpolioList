#include "StdAfx.h"
#include "animationTestScene.h"


animationTestScene::animationTestScene(void)
{
}


animationTestScene::~animationTestScene(void)
{
}

HRESULT animationTestScene::init(void)
{
	gameNode::init();

	_fat = new frameAnimationTest;
	_fat->init();

	_at = new animationTest;
	_at->init();

	return S_OK;
}

void animationTestScene::release(void)
{
	gameNode::release();

	SAFE_DELETE(_fat);
	SAFE_DELETE(_at);
}

void animationTestScene::update(void)
{
	gameNode::update();

	_fat->update();
	_at->update();
}

void animationTestScene::render(void)
{
	_fat->render();
	_at->render();
}
