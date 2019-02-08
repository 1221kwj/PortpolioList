#pragma once

#include "gamenode.h"
#include "battle.h"
#include "carrier.h"
#include "space.h"

enum SHIPKIND
{
	SHIPKIND_BATTLE,
	SHIPKIND_CARRIER,
	SHIPKIND_END
};

class shipManager : public gameNode
{
private:
	ship* _ship[SHIPKIND_END];
	ship* _focusShip;

	space* _space;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	shipManager(void);
	~shipManager(void);
};

