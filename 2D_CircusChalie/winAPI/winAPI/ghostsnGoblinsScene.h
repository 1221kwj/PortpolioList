#pragma once

#include "gamenode.h"
#include "knight.h"

class ghostsnGoblinsScene : public gameNode
{
private:
	knight* _knight;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	ghostsnGoblinsScene(void);
	~ghostsnGoblinsScene(void);
};

