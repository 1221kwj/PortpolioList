#pragma once
#include "image.h"
#include <map>

struct tagEnemy
{
	bool move;
	bool life;
	bool die;
	bool attacking;
	bool hit;
	int HP;
	int ATTACK;
	int frameX;
	int frameY;
	int count;
	float speed;
	float x;
	float y;
	RECT rc;
	RECT hitBox;
	image* charImage;
};

class enemyChar
{
public:
	int enemyCattle;

public:
	map<int, tagEnemy> enemyCharacter;

	enemyChar();
	~enemyChar();
};

