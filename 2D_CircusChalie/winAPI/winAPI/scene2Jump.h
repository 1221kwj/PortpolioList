#pragma once
#include "gameNode.h"
class scene2Jump : public gameNode
{
private:


public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	scene2Jump();
	virtual ~scene2Jump();
};

