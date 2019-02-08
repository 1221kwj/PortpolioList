#pragma once

#include "gamenode.h"
#include "bullets.h"
#include "hitBox.h"

class player : public gameNode
{
private:
	float _x;
	float _y;

	int count;
	int frameX;
	int frameY;
	int frameCount;
	int leftRight;
	int score;
	int endingCounting;

	float firstTime;
	float lastTime;
	float myTime;
	bool gameClear;
	bool gameOver;

	RECT _rc;

	image* _character;
	hitBox* _hitBox1;
	hitBox* _hitBox2;
	bullet* _bullet;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	virtual void hitBoxMoving();
	virtual void hitBoxCollision();

	player(void);
	~player(void);
};

