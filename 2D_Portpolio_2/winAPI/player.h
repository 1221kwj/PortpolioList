#pragma once
#include "gameNode.h"
#define JUMPSPEED 10.0f
#include "database.h"
class player :
	public gameNode
{
	database* _database;
	enum
	{
		START = 0,
		IDLE,
		RUN,
		ATK1,
		ATK2,
		ATK3,
		ATK4,
		DASHATK,
		SATK1,
		SATK2,
		SATK3,
		SATK4,
		SATK5,
		S2ATK1,
		S2ATK2,
		S2ATK3,
		S3READY,
		S3ATK1,
		S3ATK2,
		S3ATK3,
		S3ATK4,
		HURT,
		HURT2,
		WAKEUP,
		JUMP,
		JUMPATK
	};
	struct playertag
	{
		float x;
		float y;
		float z;

		//점프 외에 공중으로 뜨는 속도
		float z_speed;

		//넉백
		float x_speed;

		//스킬 사용상태일때 무적처리
		bool god;
		//잡는 판정 키기
		bool grab;

		int frameCount;
		int frameX;
		int state;
		bool direction;

		int skill1_CoolDown;
		bool skill1_Use;
		int skill1Count;
		int skill2_CoolDown;
		bool skill2_Use;
		int skill2Count;
		int skill3_CoolDown;
		bool skill3_Use;
		int skill3Count;

		RECT rc;
	};
	playertag _player;

	struct attacktag
	{
		//스킬뎀지
		int dmg;

		//x,z넉백속도
		float xSpeed;
		float zSpeed;

		RECT rc;

		bool special;
	};
	attacktag atk;
	void CheckSkill();
	void frameWork();
	void move();

	int foodCount;
public:

	bool debug;

	bool hurt;
	bool speacial_hurt;
	bool hurtDirection;

	float minY;
	float maxY;
	bool getHurt() { return hurt; }
	void OnHurt(float xSpeed,float zSpeed,bool speacial)
	{
		hurt = true;
		_player.frameX = 0;
		_player.frameCount = 0;
		_player.x_speed = xSpeed;
		_player.z_speed = zSpeed;
		(_player.x_speed < 0) ? _player.direction = true : _player.direction = false;
		(speacial) ? speacial_hurt = true : speacial_hurt = false;
	}
	bool setHurtDirection(bool direction) { hurtDirection = direction; }
	bool checkGod() { return _player.god; }
	RECT getAtkRect()
	{
		return atk.rc;
	}
	void setPlayerX()
	{
		_player.x = WINSIZEX / 2;
	}
	void setPlayer2X(int num)
	{
		_player.x = num;
	}
	float getPlayerX()
	{
		return _player.x;
	}
	float getPlayerY()
	{
		return _player.y;
	}
	float getPlayerZ()
	{
		return _player.z;
	}
	float getXSpeed()
	{
		return atk.xSpeed;
	}
	float getZSpeed()
	{
		return atk.zSpeed;
	}
	bool getAtkType()
	{
		return atk.special;
	}
	int getDmg()
	{
		return (getAtkType()) ? atk.dmg*_database->getInt()*_database->getSoldier() / 1000 * RND->getFromIntTo(900, 1100) :
			atk.dmg*_database->getAttack()*_database->getSoldier() / 1000 * RND->getFromIntTo(900, 1100);

		//return (getAtkType()) ? _database->getInt() : _database->getInt();
	}
	bool getGrab()
	{
		return _player.grab;
	}
	bool getDirection()
	{
		return _player.direction;
	}
	RECT getPlayerRect()
	{
		return _player.rc;
	}
	void setAddressDatabaseLink(database* database) { _database = database; }
	void renderUI();
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	player();
	virtual ~player();
};