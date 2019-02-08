#pragma once

#include "gamenode.h"
#include "animation.h"
#include "jump.h"

#define SPEED 3.0f

enum KNIGHTDIRECTION
{
	KNIGHTDIRECTION_RIGHT_STOP,
	KNIGHTDIRECTION_LEFT_STOP,
	KNIGHTDIRECTION_RIGHT_RUN,
	KNIGHTDIRECTION_LEFT_RUN,
	KNIGHTDIRECTION_RIGHT_SIT,
	KNIGHTDIRECTION_LEFT_SIT,
	KNIGHTDIRECTION_RIGHT_FIRE,
	KNIGHTDIRECTION_LEFT_FIRE,
	KNIGHTDIRECTION_RIGHT_SIT_FIRE,
	KNIGHTDIRECTION_LEFT_SIT_FIRE,
	KNIGHTDIRECTION_RIGHT_JUMP,
	KNIGHTDIRECTION_LEFT_JUMP,
	KNIGHTDIRECTION_RIGHT_RUN_JUMP,
	KNIGHTDIRECTION_LEFT_RUN_JUMP,
};

class knight : public gameNode
{
private:
	KNIGHTDIRECTION _direction;

	image* _image;
	animation* _knightMotion;

	float _x, _y;
	RECT _rc;

	jump* _jump;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	static void cbRightFire(void* obj);
	static void cbLeftFire(void* obj);
	static void cbRightSitFire(void* obj);
	static void cbLeftSitFire(void* obj);
	static void cbRightJump(void* obj);
	static void cbLeftJump(void* obj);
	static void cbRightRunJump(void* obj);
	static void cbLeftRunJump(void* obj);

	void setKnightDirection(KNIGHTDIRECTION kd) {_direction = kd;}
	void setKnightMotion(animation* ani) {_knightMotion = ani;}

	animation* getKnightMotion(void) {return _knightMotion;}

	knight(void);
	~knight(void);
};

