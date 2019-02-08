#pragma once
#include "gameNode.h"

#define FRAMECOUNT 50.0f
#define BROKENFRAMECOUNT 200.0f
#define BOMBFRAMECOUNT 200.0f
#define BOMBINGFRAMECOUNT 50.0f

class tile : public gameNode
{
private:
	image* _bombImage;
	image* _bombingImage;

	int bombFrameX;
	int bombFrameY;
	int bombCount;
	

	float bombFrameCount;
	float bombingFrameCount;
	int delay;
	

	bool bombing;


public:
	int bombs;
	int bombMaxRange;

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
	
	virtual void mapSet(void);
	virtual void bombSet(void);
	virtual void itemSet(int x, int y);
	virtual void bombCheck(void);
	virtual void itemCollision(void);

	tagTile bombTile[14][13];
	tagItem itemTile[14][13];
	tagTile tileMap[14][13];

	tile();
	virtual ~tile();
};

