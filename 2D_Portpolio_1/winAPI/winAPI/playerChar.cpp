#include "stdafx.h"
#include "playerChar.h"


playerChar::playerChar()
{	
	tagPlayer sTemp;
	
	allcost = 100;
	cost = 0;
	upgradeCost = 40;
	myCattleHP = 1000;

	ZeroMemory(&sTemp, sizeof(sTemp));
	sTemp.move = true;
	sTemp.attacking = false;
	sTemp.life = true;
	sTemp.hit = false;
	sTemp.die = false;
	sTemp.ATTACK = 60;
	sTemp.HP = 1000;
	sTemp.speed =0.8f;
	sTemp.count = 0;
	sTemp.frameX = 0;
	sTemp.frameY = 0;
	sTemp.charImage = IMAGEMANAGER->addFrameImage("cat1", "cat1.bmp", 300, 180, 6, 3, true, RGB(255, 0, 255));
	sTemp.x = 650 - sTemp.charImage->getFrameWidth() / 2;
	sTemp.y = 400 - sTemp.charImage->getFrameHeight() / 2;
	sTemp.rc = RectMakeCenter(sTemp.x, sTemp.y, sTemp.charImage->getFrameWidth(), sTemp.charImage->getFrameHeight());
	sTemp.hitBox = RectMakeCenter(sTemp.x, sTemp.y, 150, 90);
	playerCharacter[0] = sTemp;

	ZeroMemory(&sTemp, sizeof(sTemp));
	sTemp.move = true;
	sTemp.attacking = false;
	sTemp.life = true;
	sTemp.hit = false;
	sTemp.die = false;
	sTemp.ATTACK = 70;
	sTemp.HP = 1000;
	sTemp.speed = 0.8f;
	sTemp.count = 0;
	sTemp.frameX = 0;
	sTemp.frameY = 0;
	sTemp.charImage = IMAGEMANAGER->addFrameImage("cat2", "cat2.bmp", 408, 180, 6, 3, true, RGB(255, 0, 255));
	sTemp.x = 650 - sTemp.charImage->getFrameWidth() / 2;
	sTemp.y = 400 - sTemp.charImage->getFrameHeight() / 2;
	sTemp.rc = RectMakeCenter(sTemp.x, sTemp.y, sTemp.charImage->getFrameWidth(), sTemp.charImage->getFrameHeight());
	sTemp.hitBox = RectMakeCenter(sTemp.x, sTemp.y, 150, 90);
	playerCharacter[1] = sTemp;

	ZeroMemory(&sTemp, sizeof(sTemp));
	sTemp.move = true;
	sTemp.life = true;
	sTemp.hit = false;
	sTemp.die = false;
	sTemp.attacking = false;
	sTemp.ATTACK = 80;
	sTemp.HP = 1000;
	sTemp.speed = 0.8f;
	sTemp.count = 0;
	sTemp.frameX = 0;
	sTemp.frameY = 0;
	sTemp.charImage = IMAGEMANAGER->addFrameImage("cat3", "cat3.bmp", 600, 270, 6, 3, true, RGB(255, 0, 255));
	sTemp.x = 650 - sTemp.charImage->getFrameWidth() / 2;
	sTemp.y = 400 - sTemp.charImage->getFrameHeight() / 2;
	sTemp.rc = RectMakeCenter(sTemp.x, sTemp.y, sTemp.charImage->getFrameWidth(), sTemp.charImage->getFrameHeight());
	sTemp.hitBox = RectMakeCenter(sTemp.x, sTemp.y, 150, 90);
	playerCharacter[2] = sTemp;

	ZeroMemory(&sTemp, sizeof(sTemp));
	sTemp.move = true;
	sTemp.attacking = false;
	sTemp.life = true;
	sTemp.hit = false;
	sTemp.die = false;
	sTemp.ATTACK = 100;
	sTemp.HP = 1500;
	sTemp.speed = 1.5f;
	sTemp.count = 0;
	sTemp.frameX = 0;
	sTemp.frameY = 0;
	sTemp.charImage = IMAGEMANAGER->addFrameImage("cat4", "cat4.bmp", 600, 270, 4, 3, true, RGB(255, 0, 255));
	sTemp.x = 650 - sTemp.charImage->getFrameWidth() / 2;
	sTemp.y = 400 - sTemp.charImage->getFrameHeight() / 2;
	sTemp.rc = RectMakeCenter(sTemp.x, sTemp.y, sTemp.charImage->getFrameWidth(), sTemp.charImage->getFrameHeight());
	sTemp.hitBox = RectMakeCenter(sTemp.x, sTemp.y, 150, 90);
	playerCharacter[3] = sTemp;
}


playerChar::~playerChar()
{
}
