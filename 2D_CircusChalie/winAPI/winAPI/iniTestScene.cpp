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

	//����...
	//��Ŀ��!!!!
	//��������4�� ����...

	//¼��
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		char str[128];
	
		GetCurrentDirectory(128, str);
		strncat_s(str, 128, "\\�����ħ��.ini", 126);

		WritePrivateProfileString("���ڷ�", "����", "98", str);
		WritePrivateProfileString("���ڷ�", "�ŷ�", "90", str);
		WritePrivateProfileString("���ڷ�", "����", "70", str);
		WritePrivateProfileString("����", "����", "74", str);
		WritePrivateProfileString("�躴��", "����", "11", str);
		WritePrivateProfileString("����", "�ŷ�", "3", str);
		WritePrivateProfileString("����", "ħ��", "108", str);
		WritePrivateProfileString("����", "�ټ�", "12", str);
		WritePrivateProfileString("����", "��Ż", "-12", str);
	}
}

void iniTestScene::render(void)
{

}
