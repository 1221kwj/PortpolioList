#pragma once

#include "gamenode.h"
#include "frameAnimation.h"

class frameAnimationTest : public gameNode
{
private:
	image* _villagers;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	static void xFrameFinish(void);
	static void yFrameFinish(void);

	frameAnimationTest(void);
	~frameAnimationTest(void);
};

