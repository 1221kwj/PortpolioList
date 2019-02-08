#pragma once

#include "gamenode.h"
#include "ship.h"
#include "button.h"
#include "shipManager.h"

class battle;
class carrier;

class starWarsScene : public gameNode
{
private:
	shipManager* _sm;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	static void callback(void);

	starWarsScene(void);
	virtual ~starWarsScene(void);
};

