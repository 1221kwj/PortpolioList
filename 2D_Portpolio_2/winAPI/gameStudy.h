#pragma once

#include "gamenode.h"
#include "button.h"
#include "player.h"
#include "enemy.h"
class gameStudy : public gameNode
{
	

	button* _button;
	player* _player;
	enemy* _enemy;
	virtual void CameraMove();
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	gameStudy(void);
	virtual ~gameStudy(void);
};

