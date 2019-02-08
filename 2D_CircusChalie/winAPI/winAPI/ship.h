#pragma once

#include "gamenode.h"

class ship : public gameNode
{
protected:
	image* _img;
	RECT _rc;
	float _x, _y;
	float _speed;
	float _angle;
	float _radius;

public:
	virtual HRESULT init(const char* imageName, int x, int y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void draw(void);
	virtual void defaultDraw(RECT rcFocus);
	virtual void focusDraw(void);

	virtual void move(void);
	virtual void keyControl(void);

	RECT getRect(void) {return _rc;}
	image* getImage(void) {return _img;}

	ship(void);
	virtual ~ship(void);
};

