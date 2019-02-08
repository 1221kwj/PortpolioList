#pragma once

#include "gamenode.h"
#include "player.h"
#include "bullets.h"
#include "hitBox.h"

class gameStudy : public gameNode
{
public:
	player* _player;

	

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	gameStudy(void);
	virtual ~gameStudy(void);
};

