#pragma once

#include "gamenode.h"
#include "frameAnimationTest.h"
#include "animationTest.h"

class animationTestScene : public gameNode
{
private:
	frameAnimationTest* _fat;
	animationTest* _at;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	animationTestScene(void);
	~animationTestScene(void);
};

