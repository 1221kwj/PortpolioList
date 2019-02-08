#pragma once

#include "gamenode.h"

class soundTestScene : public gameNode
{
public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	soundTestScene(void);
	~soundTestScene(void);
};

