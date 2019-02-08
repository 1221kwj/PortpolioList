#pragma once
#include "image.h"
#include <map>

struct tagPlayer
{	
	bool move;
	bool life;
	bool die;
	bool attacking;
	bool hit;
	int cost;
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

class playerChar
{
public:
	int allcost;
	int cost;
	int upgradeCost;
	int myCattleHP;
	map<int, tagPlayer> playerCharacter;

public:
	playerChar();
	~playerChar();
};

