#include "stdafx.h"
#include "enemyChar.h"


enemyChar::enemyChar()
{
	enemyCattle = 1000;

	tagEnemy sTemp;
	ZeroMemory(&sTemp, sizeof(sTemp));
	sTemp.move = true;
	sTemp.life = true;
	sTemp.die = false;
	sTemp.hit = false;
	sTemp.attacking = false;
	sTemp.ATTACK = 50;
	sTemp.HP = 500;
	sTemp.speed = 0.8f;
	sTemp.count = 0;
	sTemp.frameX = 0;
	sTemp.frameY = 0;
	sTemp.charImage = IMAGEMANAGER->addFrameImage("enemy1", "enemy1.bmp", 300, 180, 6, 3, true, RGB(255, 0, 255));
	sTemp.x = -700;// +sTemp.charImage->getFrameWidth() / 2;
	sTemp.y = 400 - sTemp.charImage->getFrameHeight() / 2;
	sTemp.rc = RectMakeCenter(sTemp.x, sTemp.y, sTemp.charImage->getFrameWidth(), sTemp.charImage->getFrameHeight());
	sTemp.hitBox = RectMakeCenter(sTemp.x, sTemp.y, 80, 60);
	enemyCharacter[0] = sTemp;

	ZeroMemory(&sTemp, sizeof(sTemp));
	sTemp.move = true;
	sTemp.life = true;
	sTemp.die = false;
	sTemp.hit = false;
	sTemp.attacking = false;
	sTemp.ATTACK = 60;
	sTemp.HP = 500;
	sTemp.speed = 0.8f;
	sTemp.count = 0;
	sTemp.frameX = 0;
	sTemp.frameY = 0;
	sTemp.charImage = IMAGEMANAGER->addFrameImage("enemy2", "enemy2.bmp", 480, 180, 6, 3, true, RGB(255, 0, 255));
	sTemp.x = -700;// +sTemp.charImage->getFrameWidth() / 2;
	sTemp.y = 400 - sTemp.charImage->getFrameHeight() / 2;
	sTemp.rc = RectMakeCenter(sTemp.x, sTemp.y, sTemp.charImage->getFrameWidth(), sTemp.charImage->getFrameHeight());
	sTemp.hitBox = RectMakeCenter(sTemp.x, sTemp.y, 80, 60);
	enemyCharacter[1] = sTemp;

	ZeroMemory(&sTemp, sizeof(sTemp));
	sTemp.move = true;
	sTemp.life = true;
	sTemp.die = false;
	sTemp.hit = false;
	sTemp.attacking = false;
	sTemp.ATTACK = 70;
	sTemp.HP = 500;
	sTemp.speed = 0.8f;
	sTemp.count = 0;
	sTemp.frameX = 0;
	sTemp.frameY = 0;
	sTemp.charImage = IMAGEMANAGER->addFrameImage("enemy3", "enemy3.bmp", 600, 150, 10, 3, true, RGB(255, 0, 255));
	sTemp.x = -700;// +sTemp.charImage->getFrameWidth() / 2;
	sTemp.y = 400 - sTemp.charImage->getFrameHeight() / 2;
	sTemp.rc = RectMakeCenter(sTemp.x, sTemp.y, sTemp.charImage->getFrameWidth(), sTemp.charImage->getFrameHeight());
	sTemp.hitBox = RectMakeCenter(sTemp.x, sTemp.y, 80, 60);
	enemyCharacter[2] = sTemp;
}


enemyChar::~enemyChar()
{
}
