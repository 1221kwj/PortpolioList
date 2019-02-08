#pragma once
#include "gameNode.h"
#include "playerChar.h"
#define FRAMECOUNT 50.0f

class powerPage : public gameNode
{
private:
	struct tagPowerUp
	{
		RECT rc;
		image* img;
		int frameX;
		int frameY;
	};

	bool _powerOn;
	bool _loading;
	int _state;
	float _frameCount;

	image* _loadingImage;
	image* _worldMapBackButton;
	image* _powerUI;
	playerChar* _playerState;

	tagPowerUp _powerUpRect[5];

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual bool getPowerOn(){ return _powerOn; }
	virtual void setPowerOn(bool powerOn) { _powerOn = powerOn; }
	virtual void setLoading(bool loading) { _loading = loading; }
	virtual int getState() { return _state; }

	powerPage();
	virtual ~powerPage();
};

