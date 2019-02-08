#pragma once
#include "gameNode.h"
#include "circusJump.h"
#include "animation.h"

enum LIONPDIRECT
{
	DIRECT_PLAYER_RIGHT_STOP,
	DIRECT_PLAYER_RIGHT_RUN,
	DIRECT_PLAYER_LEFT_STOP,
	DIRECT_PLAYER_LEFT_RUN,
	DIRECT_PLAYER_RIGHT_STOP_JUMP,
	DIRECT_PLAYER_RIGHT_RUN_JUMP,
	DIRECT_PLAYER_LEFT_STOP_JUMP,
	DIRECT_PLAYER_LEFT_RUN_JUMP,
	DIRECT_PLAYER_WINPAUSE,
};

enum LIONDIRECT
{
	DIRECT_LION_RIGHT_STOP,
	DIRECT_LION_RIGHT_RUN,
	DIRECT_LION_RIGHT_STOP_JUMP,
	DIRECT_LION_RIGHT_RUN_JUMP,
	DIRECT_LION_HURT,
};

class circusSceneOne : public gameNode
{
private:
	image* _playerImage;
	image* _lionImage;
	image* _backGroundCenter;
	image* _backGroundUp;

	float _x;
	float _y;

	RECT _rc;
	RECT _stage1WinTable;

	circusJump* _jump;

	LIONPDIRECT _playerDirect;
	LIONDIRECT _lionDirect;

	animation* _playerMotion;
	animation* _lionMotion;

	int _mapCount;

	struct tagBackGround
	{
		float x, y;
		image* img;
		image* underImg;
		bool set;
		RECT fireRect;
	};

	typedef vector<tagBackGround> arrBackGround;

	arrBackGround _vBackGD;
	tagBackGround _addBackGD;

	int _frameX;
	float _frameCount;

	struct tagFireRing
	{
		float x, y;
		int selectRing;
		image* left;
		image* right;
		RECT rc;
		RECT hitBox1;
		RECT hitBox2;
		bool appear;
	};

	typedef vector<tagFireRing> arrFireRing;

	arrFireRing _largeFireRing;
	tagFireRing _addlargeFireRing;

	bool _opening;
	bool _ending;
	float _openingCount;
	int _count;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void frameWork(void);

	virtual void setFireRing(void);
	virtual void moveFireRing(void);
	virtual void collision(void);

	virtual void setPlayerDirection(LIONPDIRECT d) { _playerDirect = d; }
	virtual void setLionDirection(LIONDIRECT d) { _lionDirect = d; }
	
	virtual void setPlayerMotion(animation* a) { _playerMotion = a; }
	virtual void setLionMotion(animation* a) { _lionMotion = a; }

	virtual animation* getPlayerMotion(void) { return _playerMotion; }
	virtual animation* getLionMotion(void) { return _lionMotion; }

	static void cbRightStopJump(void* obj);
	static void cbRightJump(void* obj);
	static void cbHurtMotion(void* obj);

	circusSceneOne();
	virtual ~circusSceneOne();
};

