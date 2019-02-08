#include "StdAfx.h"
#include "soundTestScene.h"

soundTestScene::soundTestScene(void)
{
}

soundTestScene::~soundTestScene(void)
{
}

HRESULT soundTestScene::init(void)
{
	gameNode::init();

	SOUNDMANAGER->addSound("�ɱ�", "������-03-�ɱ�-320k.mp3", true, true);

	return S_OK;
}

void soundTestScene::release(void)
{
	gameNode::release();
}

void soundTestScene::update(void)
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SOUNDMANAGER->play("�ɱ�");
	}
}

void soundTestScene::render(void)
{

}
