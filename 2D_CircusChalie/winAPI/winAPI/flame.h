#pragma once

#include "gamenode.h"

#define FLAMECOUNT 3.0f

class flame : public gameNode
{
private:
	image* _img;
	float* _x;
	float* _y;
	RECT _rc;

	float _flameCount;

public:
	virtual HRESULT init(const char* imageName, float* x, float* y);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	flame(void);
	virtual ~flame(void);
};

