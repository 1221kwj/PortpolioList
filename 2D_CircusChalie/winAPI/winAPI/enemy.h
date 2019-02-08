#pragma once

#include "gamenode.h"
#include "progressBar.h"

class enemy : public gameNode
{
protected:
	image* _image;
	RECT _rc;

	progressBar* _pb;

	float _rndFireCount;
	float _bulletFireCount;

public:
	virtual HRESULT init(void);
	virtual HRESULT init(const char* imageName, POINT position);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void draw(void);
	virtual void move(void);

	virtual bool bulletCountFire(void);

	inline RECT getRect(void) {return _rc;} 

	enemy(void);
	virtual ~enemy(void);
};

