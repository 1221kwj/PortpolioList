#pragma once

#include "gamenode.h"
#include "minion.h"
#include "bullets.h"
#include "player.h"

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> VEC_ENEMY;
	typedef vector<enemy*>::iterator VECITER_ENEMY;

private:
	VEC_ENEMY _vMinion;
	VECITER_ENEMY _viMinion;

	bulletM1* _bullet;
	player* _player;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void setMinion(void); 
	virtual void removeMinion(int arrNum);

	virtual void minionBulletFire(void);

	vector<enemy*> getMinion(void) {return _vMinion;}

	void setPlayerAddressLink(player* player) {_player = player;}

	enemyManager(void);
	~enemyManager(void);
};

