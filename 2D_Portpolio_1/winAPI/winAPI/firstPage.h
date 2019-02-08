#pragma once
#include "gameNode.h"
#define FRAMECOUNT 50.0f

class firstPage : public gameNode
{
private:
	image* _loadingImage;
	image* _openDoor;
	image* _worldMap;
	image* _worldMapBackButton;
	image* _buttonImage;
	image* _powerupImage;

	bool _firstOn;
	bool _loading;
	bool _doorOpen;
	float _firstCount;
	int state;

	RECT _button;
	RECT _powerup;
	RECT _country[3];

	

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual bool getFirstOn(){ return _firstOn; }
	virtual void setFirstOn(bool push){ _firstOn = push; }
	virtual void setLoading(bool push){ _loading = push; }
	virtual int getState() { return state; }

	firstPage();
	~firstPage();
};

