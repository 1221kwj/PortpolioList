#pragma once
#include "gameNode.h"
#include "playerChar.h"
#include "enemyChar.h"
#include <vector>

#define FRAMECOUNT 50.0f
#define PLAYERCOUNT 140.0f
#define ENEMYCOUNT 5000.0f
#define FRAME 20

class battle03 : public gameNode
{
private:
	enum CATKIND
	{
		KIND_NULL, // 0
		KIND_CAT1,
		KIND_CAT2,
		KIND_CAT3,
		KIND_CAT4,
		KIND_CAT5
	};

	struct tagIcon
	{
		CATKIND _catkind;
		RECT rc;
		int cost;
		int iconFrameY;
		image* icon;
	};

	playerChar* pC;
	enemyChar* eC;

	int rnd;
	int rndCount;
	int buttonFrameX;
	int buttonFrameY;
	int costCountMinus;

	bool _battle03On;
	bool _loading;

	float _battleStart;
	float _playerFrame;
	float _enemyFrame;
	float _randomFrame;
	float _costCount;

	int _loopX;
	int _dLoopX;

	image* _loadingImage;
	image* _map1;
	image* _movingMap3;
	image* _leftButton;
	RECT _leftButtonRC;

	image* _myCattle;
	RECT _myCattleHitBox;

	image* _enemyCattle3;
	tagEnemy _tempEnemy;
	RECT _enemyCattleHitBox;

	tagIcon _icon[5];
	tagPlayer _tempPlayer;

	vector<tagPlayer> _vBattle01P;
	vector<tagPlayer>::iterator _viBattle01P;

	vector<tagEnemy> _vBattle01E;
	vector<tagEnemy>::iterator _viBattle01E;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void costUP(void);

	virtual void playerSelect(void);
	virtual void playerMove(void);

	virtual void enemySelect(void);
	virtual void enemyMove(void);

	virtual bool getBattle03On(){ return _battle03On; }
	virtual void setBattle03On(bool battle03On){ _battle03On = battle03On; }

	battle03();
	virtual ~battle03();
};

