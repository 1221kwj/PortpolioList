#pragma once
#include "tile.h"
#include "gamenode.h"

#define FRAMECOUNT 200.0f
#define ENEMYMOVECOUNT 200.0f

class player : public gameNode
{
private:
	int item1MaxCount;
	int item2MaxCount;
	int item3MaxCount;

	
	enum DIRECTION
	{
		DIREC_LEFT,
		DIREC_RIGHT,
		DIREC_UP,
		DIREC_DOWN,
		DIREC_DIE
	};

	struct tagPlayer
	{
		image* img;
		bool life;
		float _x;
		float _y;
		float speed;
		float frameCount;
		int frameX;
		int frameY;
		DIRECTION _direction;
		RECT _rc;
	};

	tagPlayer myPlayer;
	tile* _tile;

	struct tagEnemy
	{
		image* img;
		bool life;
		bool die;
		float _x;
		float _y;
		float speed;
		float frameCount;
		int frameX;
		int frameY;
		DIRECTION _direction;
		RECT _rc;
	};

	tagEnemy myEnemy[4];
public:

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	inline RECT getPlayerRC(void) { return myPlayer._rc; }
	inline float getX(void) {return myPlayer._x;}
	inline float getY(void) { return myPlayer._y; }

	void setAdressTileLink(tile* tile) { _tile = tile; }

	bool collision(DIRECTION direction);
	bool bombCollision();
	void itemAcquire();


	virtual void enemySetting(void);
	//virtual void enemyMove(void);
	virtual void enemyCollision(void);
	//virtual bool ecollision(DIRECTION direction);

	player(void);
	virtual ~player(void);
};

