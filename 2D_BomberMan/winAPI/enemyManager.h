#pragma once

#include "gamenode.h"
#include "minion.h"

class enemyManager : public gameNode
{
private:
	typedef vector<enemy*> VEC_ENEMY;
	typedef vector<enemy*>::iterator VECITER_ENEMY;


public:
	VEC_ENEMY _vMinion;
	VECITER_ENEMY _viMinion;

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void setMinion(void); 
	virtual void removeMinion(int arrNum);


	enemyManager(void);
	~enemyManager(void);
};

