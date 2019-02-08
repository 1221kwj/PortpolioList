#pragma once

#include "gamenode.h"
#include "opening.h"
#include "firstPage.h"
#include "powerPage.h"
#include "battle01.h"
#include "battle02.h"
#include "battle03.h"

class gameStudy : public gameNode
{
public:
	opening* _opening;
	firstPage* _firstPage;
	battle01* _battle01;
	battle02* _battle02;
	battle03* _battle03;
	powerPage* _power;

	int state;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	gameStudy(void);
	virtual ~gameStudy(void);
};

