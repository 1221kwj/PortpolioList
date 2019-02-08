#pragma once
#include "gameNode.h"
#include "field.h"
#include "database.h"

#define FRAMECOUNT 100.0f

class button : public gameNode
{
private:
	//내 현재 상태
	PAGESTATE _myState;

	//오프닝 렉트
	RECT _OPENRC;

	//휴식 버튼 렉트
	RECT _TURNENDBUTTON;

	//수련 렉트
	RECT _PHYSICAL;
	RECT _MENTAL;
	
	//관리 렉트
	//징수
	RECT _COLLECT;
	//징세
	RECT _TAX;
	//연회
	RECT _PARTY;

	//UP, DOWN 버튼 렉트
	RECT _UPBUTTON;
	RECT _DOWNBUTTON;

	//yes / no 버튼
	RECT _OKBUTTON;
	RECT _CANCELBUTTON;

	//CLOSE 버튼
	RECT _CLOSEBUTTON;

	RECT ATTACKINFO;
	RECT INTINFO;
	RECT SOLDIERINFO;
	RECT PEOPLEINFO;
	RECT FOODINFO;
	RECT LOYALTYINFO;

	RECT _BATTLERC;
	RECT _BOSSRC;

	struct tagIcon
	{
		image* buttonImage;
		image* activeButtonImage;
		bool collision;
		int frameX;
		float x, y;
		float frameCount;
		RECT rc;
	};

	tagIcon _icon[3];

	tagIcon _closeIcon;

	
	int loadingCount;
	float loadingFrame;

public:
	bool battleStart;
	field* _field;
	database* _database;

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//UI 그리는 함수
	virtual void drawUI(void);

	//아이콘 그리는 함수
	virtual void iconDraw(void);

	//이벤트 Close버튼 함수
	virtual void eventClose(void);

	//이벤트 Close버튼 그린다.
	virtual void eventCloseDraw(void);

	//yes / no 버튼을 그린다
	virtual void yesNoButton(void);

	//UP / DOWN 버튼 충돌 시 행동 함수
	virtual void upDownAct(void);

	//UP / DOWN 버튼 그리는 함수
	virtual void upDownDraw(char* charName1, char* charName2, char* charName3);

	//현재 상태를 얻는다.
	virtual PAGESTATE getState(void) { return _myState; }
	bool buttonCollision(RECT rc);

	//오프닝 버튼
	virtual void openingState(void);
	
	//타이틀 버튼
	virtual void titleState(void);
	
	//징집 버튼
	virtual void solState(void);
	
	//수련 버튼
	virtual void powerState(void);
	//무력 수련
	virtual void phisicalState(void);
	//책략 수련
	virtual void mentalState(void);

	
	//관리 버튼
	virtual void manageState(void);
	//징수
	virtual void collectState(void);
	//징세
	virtual void taxState(void);
	//연회
	virtual void partyState(void);

	//배틀 스타트 로딩 화면 그린다
	virtual void battleStartLoading(void);

	button();
	virtual ~button();
};

