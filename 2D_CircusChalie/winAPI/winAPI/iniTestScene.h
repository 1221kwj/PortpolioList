#pragma once

#include "gamenode.h"

class iniTestScene : public gameNode
{
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	iniTestScene(void);
	~iniTestScene(void);
};

