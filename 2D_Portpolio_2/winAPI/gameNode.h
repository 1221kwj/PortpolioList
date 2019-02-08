#pragma once
#pragma comment(lib,"winmm.lib")
#include "image.h"

static image* _backBuffer = IMAGEMANAGER->addImage("backImage", "backImage.bmp", WINSIZEX, WINSIZEY);
#include "mmsystem.h"
#include "Digitalv.h"
//페이지 상태 enum문
enum PAGESTATE
{
	OPENING = 0,
	TITLE,
	EVENT,
	SOLDIER,
	POWERUP,
	PHISICAL,
	MENTAL,
	MANAGEMENT,
	COLLECT,
	TAX,
	PARTY,
	WOLRDMAP,
	BATTLE,
	BOSS
};

enum SEASON
{
	SPRING = 14,
	SUMMER,
	FALL,
	WINTER
};

enum
{
	DROUGHT = 18,
	TORNADO,
	TYPHOON,
	HEAVYRAIN,
	PLAGUE,
	RICH,
	POOR,
	HEAVYPOOR,
	HEAVYSNOW,
	TEACHER,
	LIBRARY,
	SLOTH,
	THIEF,
	TREASURE,
	REVOLT,
	GAMEOVER
};
//텍스트 띄우기 enum
enum
{
	TEXT_NOTENOUGH=40,
	TEXT_ATK,
	TEXT_INT,
	TEXT_SOLIDERS,
	TEXT_PEOPLE,
	TEXT_FOODS,
	TEXT_LOYALTY,
	TEXT_DAMAGE,
	TEXT_GO
};

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:

	DWORD Sound1, Sound2;
	MCI_OPEN_PARMS      mciOpen;
	MCI_PLAY_PARMS       mciPlay;
	MCI_STATUS_PARMS   mciStatus;
	UINT wDeviceID = 0;

	DWORD LoadWAV(HWND hWnd, LPCTSTR lpszWave)
	{
		DWORD Result;

		mciOpen.lpstrDeviceType = "WaveAudio";
		//WaveAudio 대신 MPEGVideo를 사용하면 mp3 형식을 재생합니다.

		mciOpen.lpstrElementName = lpszWave;

		Result = mciSendCommand(wDeviceID, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpen);

		if (Result)
			return Result;

		wDeviceID = mciOpen.wDeviceID;

		mciPlay.dwCallback = (DWORD)hWnd;

		if (Result)
			return Result;

		return 0;
	}

	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	image* getBackBuffer(void) {return _backBuffer;}
	HDC getMemDC() {return _backBuffer->getMemDC();}
	HDC getHDC() {return _hdc;}

	//메시지 프로시져
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	gameNode(void);
	virtual ~gameNode(void);
};

