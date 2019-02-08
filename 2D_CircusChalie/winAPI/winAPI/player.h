#pragma once

#include "gamenode.h"
#include "bullets.h"
#include "flame.h"

class player : public gameNode
{
private:
	float _x;
	float _y;
	float _currentHP;
	float _maxHP;

	RECT _rc;

	bullet* _bullet;
	image* _rocket;
	flame* _flame;
	missileM1* _mm1;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void removeMissile(int arrNum);

	inline missileM1* getMissile(void) {return _mm1;}

	inline float getX(void) {return _x;}
	inline float getY(void) {return _y;}

	player(void);
	~player(void);
};

