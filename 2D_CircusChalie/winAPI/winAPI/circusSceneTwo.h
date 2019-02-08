#pragma once
#include "gameNode.h"
#include "animation.h"

enum LINEPDIRECTION
{
	RIGHT_STOP,
	LEFT_STOP,
	RIGHT_RUN,
	LEFT_RUN,
	RIGHT_JUMP,
	LEFT_JUMP
};


class circusSceneTwo : public gameNode
{
private:
	float _x, _y;
	
	RECT _rc;

	image* _playerImage;
	
	animation* _playerMotion;

	LINEPDIRECTION _playerDirect;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void setPlayerDirection(LINEPDIRECTION d) { _playerDirect = d; }
	virtual void setPlayerMotion(animation* a) { _playerMotion = a; }

	virtual animation* getPlayerMotion(void) { return _playerMotion; }

	circusSceneTwo();
	virtual ~circusSceneTwo();
};

