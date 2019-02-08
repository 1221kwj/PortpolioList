#pragma once
#include "gameNode.h"
#define FRAMECOUNT 200.0f

class opening : public gameNode
{
private:
	image* _openPage;
	float _openCount;
	int state;
	bool _open;

	RECT _startButton;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	virtual bool getOpen(){ return _open; }
	virtual int getState() { return state; }
	virtual void setState(int push) { state = push; }
	
	opening();
	virtual ~opening();
};

