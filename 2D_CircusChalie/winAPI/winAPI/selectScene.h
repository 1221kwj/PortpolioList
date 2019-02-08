#pragma once

#include "gamenode.h"
#include "button.h"

class selectScene : public gameNode
{
private:
	button* _btnAngleUp;
	button* _btnAngleDown;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	static void cbAngleUp(void);
	static void cbAngleDown(void);


	selectScene(void);
	~selectScene(void);
};

