#pragma once
#include "gameNode.h"
#include "player.h"
#include "database.h"
#include "effect.h"
#define MAXENEMY 10
class enemy : public gameNode
{
private:
	player* _player;
	database* _database;
	effect* _effect;
	enum
	{
		IDLE = 0,
		RUN,
		ATK,
		HURT1,
		HURT2,
		S1HURT1,
		S2HURT1,
		S1HURT2,
		S2HURT2,
	};

	enum
	{
		TOPLAYER=100,
		BACKPLAYER,
		BACKPLAYER2,
		SUPERTMOVE,

	};
	enum
	{
		B_IDLE=1000,
		B_RUN,
		B_FASTRUN,
		B_TURN,
		B_ATK2,
		B_DIE,
		B_ATK,
		B_RUN_ATK,
		B_SPEACIAL
	};
	struct tagEnemy
	{
		float x, y,z;
		int HP;

		int moveType;
		int moveCount;

		int atkDelay;
		int atkXRange;
		int atkYRange;
		int atkZRange;

		int dieCount;
		bool die;

		int special_frameCount;
		int frameCount;
		int frameX;
		int state;

		bool direction;
		bool life;

		float xSpeed;
		float zSpeed;


		RECT rc;
	};
	tagEnemy _enemy1[MAXENEMY];
	tagEnemy _enemy2[MAXENEMY];
	tagEnemy boss;
	virtual void frameWork(void);
	virtual void move(void);
	virtual void drawEnemy();
	virtual void Collision();
	virtual bool atkCheck(float xRange, float yRange, float zRange,int arrayNum);
	virtual bool atkCheck2(float xRange, float yRange, float zRange, int arrayNum);
	virtual bool atkCheck3(float xRange, float yRange, float zRange);
	virtual void removeEnemy();

	virtual void bossFrameWork();
	virtual void bossDraw();
	virtual void bossMove();
	virtual void bossCollision();
public:
	bool startBoss;
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void setAddressPlayerLink(player* player) { _player = player; }
	virtual void setAddressDatabaseLink(database* database) { _database = database; }
	virtual void moveAllEnemy(float num);
	virtual void makeEnemy(int num, int type);
	virtual bool CheckEnemy();
	enemy();
	virtual ~enemy();
};

