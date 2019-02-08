#pragma once
#include "gameNode.h"
class hitBox : public gameNode
{
private:
	float _x;
	float _y;

	int frameX;
	int frameCount;

	RECT _rc;

	image* _hitBox;

public:
	virtual HRESULT init(float x, float y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void setFrame(int x, int num);
	
	virtual RECT getRC() { return _rc; }
	virtual float getX() { return _x; }
	virtual float getY() { return _y; }
	virtual void setX(float x) { _x = x; }
	virtual void setY(float y) { _y = y; }

	hitBox();
	virtual ~hitBox();
};

