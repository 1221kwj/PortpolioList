#pragma once

#include "gamenode.h"

class jump : public gameNode
{
private:
	float _power;
	float _gravity;

	float* _x;
	float* _y;
	float _startX;
	float _startY;

	bool _isJumping;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void jumping(float* x, float* y, float power, float gravity);

	bool getIsJumping(void) {return _isJumping;}

	jump(void);
	virtual ~jump(void);
};

