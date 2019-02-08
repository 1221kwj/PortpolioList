#pragma once

#include "gamenode.h"
#include "tile.h"
#include "enemyManager.h"
#include "player.h"
#include "saveLoadTest.h"


class gameStudy : public gameNode
{
public:
	tile* _tile;
	player* _player;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	gameStudy(void);
	virtual ~gameStudy(void);
};

