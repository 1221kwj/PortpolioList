#pragma once

#include "ship.h"

class carrier : public ship
{
public:
	virtual void keyControl(void);

	carrier(void);
	~carrier(void);
};

