#pragma once

#include "gamenode.h"
#include <vector>

struct tagBullet
{
	image* img;
	RECT rc;
	int radius;
	float speed;
	float x, y;
	float fireX, fireY;
	float gravity;
	float angle;
	int count;
	bool fire;
};

class bullet : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;

public:
	virtual HRESULT init(int bulletMax, float range);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void fire(float x, float y, float angle, float gravity);
	virtual void move(void);
	virtual void remove(void);
	virtual void draw(void);
	virtual float getX(int num);
	virtual float getY(int num);
	virtual bool getFire(int num);
	virtual RECT getRC(int num);
	virtual int getsize() { return _vBullet.size(); }
	virtual void fireTran(int num);
	

	bullet(void);
	virtual ~bullet(void);
};

