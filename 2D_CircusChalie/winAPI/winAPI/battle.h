#pragma once

#include "ship.h"

class battle : public ship
{
public:
	virtual HRESULT init(const char* imageName, int x, int y);
	virtual void keyControl(void);

	void setAngle(float angle) {_angle = angle;}

	battle(void);
	~battle(void);
};

