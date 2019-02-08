#include "StdAfx.h"
#include "iniTestScene.h"

iniTestScene::iniTestScene(void)
{
}

iniTestScene::~iniTestScene(void)
{
}

HRESULT iniTestScene::init(void)
{
	gameNode::init();

	return S_OK;
}

void iniTestScene::release(void)
{
	gameNode::release();
}

void iniTestScene::update(void)
{
	gameNode::update();

	//숙제...
	//써커스!!!!
	//스테이지4개 구현...

	//쩌장
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		char str[128];
	
		GetCurrentDirectory(128, str);
		strncat_s(str, 128, "\\장수돌침대.ini", 126);

		WritePrivateProfileString("조자룡", "무력", "98", str);
		WritePrivateProfileString("조자룡", "매력", "90", str);
		WritePrivateProfileString("조자룡", "지력", "70", str);
		WritePrivateProfileString("장패", "무력", "74", str);
		WritePrivateProfileString("김병지", "무력", "11", str);
		WritePrivateProfileString("지윤", "매력", "3", str);
		WritePrivateProfileString("지현", "침묵", "108", str);
		WritePrivateProfileString("성하", "근성", "12", str);
		WritePrivateProfileString("반장", "멘탈", "-12", str);
	}
}

void iniTestScene::render(void)
{

}
