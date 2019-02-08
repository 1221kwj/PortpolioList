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

	SOUNDMANAGER->addSound("粒望", "彌熱⑷-03-粒望-320k.mp3", true, true);

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
		SOUNDMANAGER->play("粒望");
	}
}

void soundTestScene::render(void)
{

}
