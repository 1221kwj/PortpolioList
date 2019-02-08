#include "stdafx.h"
#include "button.h"

button::button() {}
button::~button() {}

HRESULT button::init(void)
{
	_OPENRC = RectMake(573, 479, 135, 35);

	//내 상태 초기화
	_myState = OPENING;

	//동적 할당
	_field = new field;
	_field->init();

	_database = new database;
	_database->init();

	//징집, 수련, 관리 아이콘 초기화----------------------------------------
	ZeroMemory(&_icon, sizeof(_icon));

	_icon[0].buttonImage = IMAGEMANAGER->addImage("soldierButton", "soldierButton.bmp", 60, 60, true, RGB(255, 0, 255));
	_icon[0].activeButtonImage = IMAGEMANAGER->addFrameImage("ActiveSoldierButton", "ActiveSoldierButton.bmp", 900, 60, 15, 1, true, RGB(255, 0, 255));
	_icon[0].x = 680;
	_icon[0].y = 500;
	_icon[0].rc = RectMakeCenter(_icon[0].x, _icon[0].y, 60, 60);

	_icon[1].buttonImage = IMAGEMANAGER->addImage("powerButton", "powerButton.bmp", 60, 60, true, RGB(255, 0, 255));
	_icon[1].activeButtonImage = IMAGEMANAGER->addFrameImage("ActivePowerButton", "ActivePowerButton.bmp", 900, 60, 15, 1, true, RGB(255, 0, 255));
	_icon[1].x = 830;
	_icon[1].y = 350;
	_icon[1].rc = RectMakeCenter(_icon[1].x, _icon[1].y, 60, 60);

	_icon[2].buttonImage = IMAGEMANAGER->addImage("manageButton", "manageButton.bmp", 60, 60, true, RGB(255, 0, 255));
	_icon[2].activeButtonImage = IMAGEMANAGER->addFrameImage("ActiveManageButton", "ActiveManageButton.bmp", 900, 60, 15, 1, true, RGB(255, 0, 255));
	_icon[2].x = 550;
	_icon[2].y = 350;
	_icon[2].rc = RectMakeCenter(_icon[2].x, _icon[2].y, 60, 60);
	//------------------------------------------------------------------------

	//Close버튼 초기화--------------------------------------------------------
	ZeroMemory(&_closeIcon, sizeof(_closeIcon));

	_closeIcon.buttonImage = IMAGEMANAGER->addImage("closeButton", "closeButton.bmp", 96, 28, true, RGB(255, 0, 255));
	_closeIcon.activeButtonImage = IMAGEMANAGER->addImage("ActiveCloseButton", "ActiveCloseButton.bmp", 96, 28, true, RGB(255, 0, 255));
	_closeIcon.collision = false;
	_closeIcon.x = 570;
	_closeIcon.y = 690;
	_closeIcon.rc = RectMakeCenter(_closeIcon.x, _closeIcon.y, 96, 28);
	//------------------------------------------------------------------------

	//이미지 등록----------------------------------------------------------------
	//단일 이미지
	//아이콘과 마우스 충돌 시 이름뒤에 나오는 스크롤
	IMAGEMANAGER->addImage("iconScroll", "iconScroll.bmp", 60, 38, true, RGB(255, 0, 255));
	//초상화
	IMAGEMANAGER->addImage("portrait", "face.bmp", 200, 150, true, RGB(255, 0, 255));
	//상태 창
	IMAGEMANAGER->addImage("state", "state.bmp", 200, 500, true, RGB(255, 0, 255));
	//왼쪽 상단 재화 화면
	IMAGEMANAGER->addImage("moneyIcon", "moneyIcon.bmp", 450, 70, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("ActiveMoneyIcon", "ActiveMoneyIcon.bmp", 450, 70, true, RGB(255, 0, 255));
	//징집 화면-----
	IMAGEMANAGER->addImage("soldierMake", "soldierMake.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("soldierMakeUp", "soldierMakeUp.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("soldierMakeDown", "soldierMakeDown.bmp", 570, 355, true, RGB(255, 0, 255));
	//수련 화면 ----
	IMAGEMANAGER->addImage("powerIdle", "powerIdle.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("powerActiveAttack", "powerActiveAttack.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("powerActiveInt", "powerActiveInt.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("powerAttackUp", "powerAttackUp.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("powerIntup", "powerIntup.bmp", 570, 355, true, RGB(255, 0, 255));
	//관리 화면 ----
	IMAGEMANAGER->addImage("manageIdle", "manageIdle.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("manageActiveCollect", "manageActiveCollect.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("manageActiveTax", "manageActiveTax.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("manageActiveParty", "manageActiveParty.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("collectIdle", "collectIdle.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("collectUp", "collectUp.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("collectDown", "collectDown.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("taxIdle", "taxIdle.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("taxUp", "taxUp.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("taxDown", "taxDown.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("partyIdle", "partyIdle.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("partyUp", "partyUp.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("partyDown", "partyDown.bmp", 570, 355, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("battleStartImage", "battleStartImage.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));

	//프레임 이미지
	//춘하추동 프레임 이미지
	IMAGEMANAGER->addFrameImage("seasonIcon", "season.bmp", 400, 100, 4, 1, true, RGB(255, 0, 255));
	//yes / no 프레임 이미지
	IMAGEMANAGER->addFrameImage("yesIcon", "yes.bmp", 196, 28, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("noIcon", "no.bmp", 196, 28, 2, 1, true, RGB(255, 0, 255));
	//---------------------------------------------------------------------------
	
	
	//렉트
	//휴식 버튼 렉트
	_TURNENDBUTTON = RectMake(440, 55, 80, 36);
	
	//징집 화면 렉트
	_UPBUTTON = RectMake(708, 250, 41, 29);
	_DOWNBUTTON = RectMake(708, 280, 41, 29);
	
	//수련 화면 렉트
	_PHYSICAL = RectMake(380, 310, 110, 110);
	_MENTAL = RectMake(590, 310, 110, 110);

	//관리 화면 렉트
	_COLLECT = RectMake(329, 310, 110, 110);
	_TAX = RectMake(485, 310, 110, 110);
	_PARTY = RectMake(641, 310, 110, 110);

	//yer / no 버튼 렉트
	_OKBUTTON = RectMake(432, 486, 96, 28);
	_CANCELBUTTON = RectMake(553, 486, 96, 28);
	
	
	_BATTLERC = RectMake(200, 200, 100, 100);
	_BOSSRC = RectMake(250, 250, 100, 100);

	ATTACKINFO = RectMake(1077, 234, 50, 25);
	INTINFO = RectMake(1077, 316, 50, 25);
	SOLDIERINFO = RectMake(1077, 398, 50, 25);
	PEOPLEINFO = RectMake(1077, 480, 50, 25);
	FOODINFO = RectMake(1077, 562, 50, 25);
	LOYALTYINFO = RectMake(1077, 643, 50, 25);

	battleStart = false;
	loadingCount = 0;
	loadingFrame = 0;

	return S_OK;
}
void button::release(void)
{
	SAFE_DELETE(_field);
	SAFE_DELETE(_database);
}
void button::update(void)
{
	switch (_myState)
	{
		case OPENING:
			openingState();
			break;
		case TITLE:
			{
				titleState();
				for (int i = 0; i < 3; i++)
				{
					if (buttonCollision(_icon[i].rc))
					{
						_icon[i].collision = true;
					}
					else
					{
						_icon[i].collision = false;
					}
				}
			}
			break;
		case EVENT:
			eventClose();
			break;
		case SOLDIER:
			solState();
			break;
		case POWERUP:
			powerState();
			break;
		case PHISICAL:
			phisicalState();
			break;
		case MENTAL:
			mentalState();
			break;
		case MANAGEMENT:
			manageState();
			break;
		case COLLECT:
			collectState();
			break;
		case TAX:
			taxState();
			break;
		case PARTY:
			partyState();
			break;
		case WOLRDMAP:
			break;
		case BATTLE:
			break;
		case BOSS:
			break;
	}

	if (_database->startEvent) _myState = EVENT;
	if (_database->battleStart) _myState = BATTLE;
	
	_database->update();
	_field->update();
}
void button::render(void)
{
	switch (_myState)
	{
		case OPENING:
			{
			if (PtInRect(&_OPENRC, _ptMouse))
			{
				_field->openingDraw(1);
			}
			else
			{
				_field->openingDraw(0);
			}
			}
			break;
		case TITLE:
			{
				_field->render(_database->getSeason());

				drawUI();

				iconDraw();

				if (buttonCollision(ATTACKINFO))
				{
					_database->introType = TEXT_ATK;
				}
				else if (buttonCollision(INTINFO))
				{
					_database->introType = TEXT_INT;
				}
				else if (buttonCollision(SOLDIERINFO))
				{
					_database->introType = TEXT_SOLIDERS;
				}
				else if (buttonCollision(PEOPLEINFO))
				{
					_database->introType = TEXT_PEOPLE;
				}
				else if (buttonCollision(FOODINFO))
				{
					_database->introType = TEXT_FOODS;
				}
				else if (buttonCollision(LOYALTYINFO))
				{
					_database->introType = TEXT_LOYALTY;
				}
			}
			break;
		case EVENT:
			{
				_field->render(_database->getSeason());

				drawUI();

				iconDraw();

				eventCloseDraw();
			}
			break;
		case SOLDIER:
			{
				_field->render(_database->getSeason());

				drawUI();

				iconDraw();
				
				upDownDraw("soldierMakeUp", "soldierMakeDown", "soldierMake");

				yesNoButton();

				char str[64];
				SetTextAlign(getMemDC(), TA_RIGHT);
				SetBkMode(getMemDC(), TRANSPARENT);
				SetTextColor(getMemDC(), RGB(251, 225, 108));
				HFONT myFont = CreateFont(25, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("HY궁서B"));
				SelectObject(getMemDC(), myFont);

				sprintf(str, "%d", _database->amount);
				TextOut(getMemDC(), 670, 270, str, strlen(str));
				
				sprintf(str, "%d", _database->amount * 7);
				TextOut(getMemDC(), 670, 370, str, strlen(str));

				sprintf(str, "%d", _database->amount * 7);
				TextOut(getMemDC(), 670, 420, str, strlen(str));

				DeleteObject(myFont);
			}
			break;
		case POWERUP:
			{
				_field->render(_database->getSeason());

				drawUI();

				iconDraw();

				if (buttonCollision(_PHYSICAL))
				{
					IMAGEMANAGER->findImage("powerActiveAttack")->render(getMemDC(), 240, 170);
				}
				else if (buttonCollision(_MENTAL))
				{
					IMAGEMANAGER->findImage("powerActiveInt")->render(getMemDC(), 240, 170);
				}
				else
				{
					IMAGEMANAGER->findImage("powerIdle")->render(getMemDC(), 240, 170);
				}
			}
			break;
		case PHISICAL:
			{
				_field->render(_database->getSeason());

				drawUI();

				iconDraw();

				IMAGEMANAGER->findImage("powerAttackUp")->render(getMemDC(), 240, 170);

				yesNoButton();
				
			}
			break;
		case MENTAL:
			{
				_field->render(_database->getSeason());

				drawUI();

				iconDraw();

				IMAGEMANAGER->findImage("powerIntup")->render(getMemDC(), 240, 170);

				yesNoButton();
			}
			break;
		case MANAGEMENT:
			{
				_field->render(_database->getSeason());

				drawUI();

				iconDraw();

				if (buttonCollision(_COLLECT))
				{
					IMAGEMANAGER->findImage("manageActiveCollect")->render(getMemDC(), 240, 170);
				}
				else if (buttonCollision(_TAX))
				{
					IMAGEMANAGER->findImage("manageActiveTax")->render(getMemDC(), 240, 170);
				}
				else if (buttonCollision(_PARTY))
				{
					IMAGEMANAGER->findImage("manageActiveParty")->render(getMemDC(), 240, 170);
				}
				else
				{
					IMAGEMANAGER->findImage("manageIdle")->render(getMemDC(), 240, 170);
				}
			}
			break;
		case COLLECT:
			{
				_field->render(_database->getSeason());

				drawUI();

				iconDraw();

				upDownDraw("collectUp", "collectDown", "collectIdle"); // UP, DOWN, IDLE

				yesNoButton();

				char str[64];
				SetTextAlign(getMemDC(), TA_RIGHT);
				SetBkMode(getMemDC(), TRANSPARENT);
				SetTextColor(getMemDC(), RGB(251, 225, 108));
				HFONT myFont = CreateFont(25, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("HY궁서B"));
				SelectObject(getMemDC(), myFont);

				sprintf(str, "%d", _database->amount);
				TextOut(getMemDC(), 670, 270, str, strlen(str));

				sprintf(str, "%d", -_database->amount / 100);
				TextOut(getMemDC(), 670, 370, str, strlen(str));

				sprintf(str, "%d", -_database->amount / 10);
				TextOut(getMemDC(), 670, 420, str, strlen(str));

				DeleteObject(myFont);
			}
			break;
		case TAX:
			{
				_field->render(_database->getSeason());

				drawUI();

				iconDraw();

				upDownDraw("taxUp", "taxDown", "taxIdle"); // UP, DOWN, IDLE

				yesNoButton();

				char str[64];
				SetTextAlign(getMemDC(), TA_RIGHT);
				SetBkMode(getMemDC(), TRANSPARENT);
				SetTextColor(getMemDC(), RGB(251, 225, 108));
				HFONT myFont = CreateFont(25, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("HY궁서B"));
				SelectObject(getMemDC(), myFont);

				sprintf(str, "%d", _database->amount);
				TextOut(getMemDC(), 670, 270, str, strlen(str));

				sprintf(str, "%d", -_database->amount / 100);
				TextOut(getMemDC(), 670, 370, str, strlen(str));

				sprintf(str, "%d", -_database->amount / 10);
				TextOut(getMemDC(), 670, 420, str, strlen(str));

				DeleteObject(myFont);
			}
			break;
		case PARTY:
			{
				_field->render(_database->getSeason());

				drawUI();

				iconDraw();

				upDownDraw("partyUp", "partyDown", "partyIdle"); // UP, DOWN, IDLE

				yesNoButton();

				char str[64];
				SetTextAlign(getMemDC(), TA_RIGHT);
				SetBkMode(getMemDC(), TRANSPARENT);
				SetTextColor(getMemDC(), RGB(251, 225, 108));
				HFONT myFont = CreateFont(25, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("HY궁서B"));
				SelectObject(getMemDC(), myFont);

				sprintf(str, "%d", _database->amount);
				TextOut(getMemDC(), 670, 270, str, strlen(str));

				sprintf(str, "%d", _database->amount / 100);
				TextOut(getMemDC(), 670, 370, str, strlen(str));

				DeleteObject(myFont);
			}
			break;
		case WOLRDMAP:
			break;
		case BATTLE:
			battleStartLoading();
			break;
		case BOSS:
			break;
	}
	
	_database->render();
}

//유틸리티 : 마우스 + 버튼 충돌
bool button::buttonCollision(RECT rc)
{
	if (PtInRect(&rc, _ptMouse)) return true;
	return false;
}

//아이콘을 그린다.
void button::iconDraw(void)
{
	for (int i = 0; i < 3; i++)
	{
		if (!_icon[i].collision)
		{
			_icon[i].buttonImage->render(getMemDC(), _icon[i].rc.left, _icon[i].rc.top);
			_icon[i].frameX = 0;
		}
		else if (_icon[i].collision)
		{
			IMAGEMANAGER->findImage("iconScroll")->render(getMemDC(), _icon[i].x - 30, _icon[i].y - 70);
			if (i == 0)
			{
				//RGB(251, 225, 108);
				SetTextAlign(getMemDC(), TA_CENTER);
				SetBkMode(getMemDC(), TRANSPARENT);
				SetTextColor(getMemDC(), RGB(0, 0, 0));
				HFONT myFont = CreateFont(18, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("HY궁서B"));
				char str[64] = "징 집";
				SelectObject(getMemDC(), myFont);
				TextOut(getMemDC(), _icon[i].x, _icon[i].y - _icon[i].buttonImage->getHeight(), str, strlen(str));
				DeleteObject(myFont);
			}
			else if (i == 1)
			{
				SetTextAlign(getMemDC(), TA_CENTER);
				SetBkMode(getMemDC(), TRANSPARENT);
				SetTextColor(getMemDC(), RGB(0, 0, 0));
				HFONT myFont = CreateFont(18, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("HY궁서B"));
				char str[64] = "수 련";
				SelectObject(getMemDC(), myFont);
				TextOut(getMemDC(), _icon[i].x, _icon[i].y - _icon[i].buttonImage->getHeight(), str, strlen(str));
				DeleteObject(myFont);
			}
			else if (i == 2)
			{
				SetTextAlign(getMemDC(), TA_CENTER);
				SetBkMode(getMemDC(), TRANSPARENT);
				SetTextColor(getMemDC(), RGB(0, 0, 0));
				HFONT myFont = CreateFont(18, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("HY궁서B"));
				char str[64] = "관 리";
				SelectObject(getMemDC(), myFont);
				TextOut(getMemDC(), _icon[i].x, _icon[i].y - _icon[i].buttonImage->getHeight(), str, strlen(str));
				DeleteObject(myFont);
			}

			_icon[i].activeButtonImage->frameRender(getMemDC(), _icon[i].rc.left, _icon[i].rc.top, _icon[i].frameX, 0);

			if (FRAMECOUNT + _icon[i].frameCount <= GetTickCount())
			{
				_icon[i].frameCount = GetTickCount();
				++_icon[i].frameX;
				if (_icon[i].frameX > _icon[i].activeButtonImage->getMaxFrameX())
				{
					_icon[i].frameX = 0;
				}
			}
		}
	}
}

//이벤트 Close버튼 함수--------------------------------------------------
void button::eventClose(void)
{
	if (_database->startEvent)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (buttonCollision(_closeIcon.rc))
			{
				_database->startEvent = false;
				_myState = TITLE;
			}
		}
	}
}

void button::eventCloseDraw(void)
{
	if (_database->startEvent)
	{
		if (buttonCollision(_closeIcon.rc))
		{
			_closeIcon.activeButtonImage->render(getMemDC(), _closeIcon.rc.left, _closeIcon.rc.top);
		}
		else
		{
			_closeIcon.buttonImage->render(getMemDC(), _closeIcon.rc.left, _closeIcon.rc.top);
		}
	}
}
//----------------------------------------------------------------------

//UI 그리기!!
void button::drawUI(void)
{
	IMAGEMANAGER->findImage("portrait")->render(getMemDC(), 1060, 20);
	IMAGEMANAGER->findImage("state")->render(getMemDC(), 1060, 200);
	
	if (buttonCollision(_TURNENDBUTTON))
	{
		IMAGEMANAGER->findImage("ActiveMoneyIcon")->render(getMemDC(), 140, 35);
	}
	else
	{
		IMAGEMANAGER->findImage("moneyIcon")->render(getMemDC(), 140, 35);
	}

	switch (_database->getSeason())
	{
	case SPRING:
		IMAGEMANAGER->findImage("seasonIcon")->frameRender(getMemDC(), 20, 20, 0, 0);
		break;
	case SUMMER:
		IMAGEMANAGER->findImage("seasonIcon")->frameRender(getMemDC(), 20, 20, 1, 0);
		break;
	case FALL:
		IMAGEMANAGER->findImage("seasonIcon")->frameRender(getMemDC(), 20, 20, 2, 0);
		break;
	case WINTER:
		IMAGEMANAGER->findImage("seasonIcon")->frameRender(getMemDC(), 20, 20, 3, 0);
		break;
	}

	char str[64];
	SetTextAlign(getMemDC(), TA_RIGHT);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(251, 225, 108));
	HFONT myFont = CreateFont(25, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("HY궁서B"));
	SelectObject(getMemDC(), myFont);
	sprintf(str, "%d", _database->getAttack());
	TextOut(getMemDC(), 1240, 235, str, strlen(str));

	sprintf(str, "%d", _database->getInt());
	TextOut(getMemDC(), 1240, 315, str, strlen(str));

	sprintf(str, "%d", _database->getSoldier());
	TextOut(getMemDC(), 1240, 400, str, strlen(str));
	
	sprintf(str, "%d", _database->getPeople());
	TextOut(getMemDC(), 1240, 480, str, strlen(str));
	
	sprintf(str, "%d", _database->getFood());
	TextOut(getMemDC(), 1240, 565, str, strlen(str));

	sprintf(str, "%d", _database->getLoyalty());
	TextOut(getMemDC(), 1240, 645, str, strlen(str));

	sprintf(str, "%d", _database->getMoney());
	TextOut(getMemDC(), 400, 60, str, strlen(str));

	sprintf(str, "%d", _database->getYear());
	TextOut(getMemDC(), 200, 60, str, strlen(str));

	sprintf(str, "%d", _database->getMonth());
	TextOut(getMemDC(), 260, 60, str, strlen(str));

	SetTextAlign(getMemDC(), TA_LEFT);
	SetBkMode(getMemDC(), TRANSPARENT);
	SetTextColor(getMemDC(), RGB(251, 225, 108));
	myFont = CreateFont(15, 0, 0, 0, 1, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1, VARIABLE_PITCH | FF_ROMAN, TEXT("HY궁서B"));
	SelectObject(getMemDC(), myFont);
	
	sprintf(str, "다음 전투까지 %d년 남았습니다.", _database->getNextBattleYear());
	TextOut(getMemDC(), 150, 30, str, strlen(str));

	DeleteObject(myFont);
}

//오프닝 버튼 처리
void button::openingState(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (buttonCollision(_OPENRC))
		{
			_myState = TITLE;
			PlaySound(NULL, 0, 0);
			PlaySound(TEXT("manageBGM.wav"), NULL, SND_LOOP | SND_ASYNC);
		}
	}
}

void button::titleState(void)
{
	for (int i = 0; i < 3; i++)
	{
		if (buttonCollision(_icon[i].rc))
		{
			_database->introType = i + 1;
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (i == 0)
				{
					_myState = SOLDIER;
					break;
				}
				else if (i == 1)
				{
					_myState = POWERUP;
					break;
				}
				else if (i == 2)
				{
					_myState = MANAGEMENT;
					break;
				}
			}
		}
	}

	if (buttonCollision(_TURNENDBUTTON))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_database->endTurn();
		}
	}
}

void button::solState(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		upDownAct();

		if (buttonCollision(_OKBUTTON) && _database->checkPToS())
		{
			_myState = TITLE;
			_database->PToS();
			_database->endTurn();
		}
		else if (buttonCollision(_CANCELBUTTON))
		{
			_myState = TITLE;
			_database->amount = 100;
		}
	}
}

void button::powerState(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (buttonCollision(_PHYSICAL))
		{
			_myState = PHISICAL;
		}
		else if (buttonCollision(_MENTAL))
		{
			_myState = MENTAL;
		}
	}
}

void button::phisicalState(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) )
	{
		if (buttonCollision(_OKBUTTON) && _database->checkAttackUp())
		{
			_myState = TITLE;
			_database->AttackUp();
			_database->endTurn();
		}
		else if (buttonCollision(_CANCELBUTTON))
		{
			_myState = TITLE;
		}
	}
}

void button::mentalState(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON) )
	{
		if (buttonCollision(_OKBUTTON) && _database->checkIntUp())
		{
			_myState = TITLE;
			_database->IntUp();
			_database->endTurn();
		}
		else if (buttonCollision(_CANCELBUTTON))
		{
			_myState = TITLE;
		}
	}
}

void button::manageState(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (buttonCollision(_COLLECT))
		{
			_myState = COLLECT;
		}
		else if (buttonCollision(_TAX))
		{
			_myState = TAX;
		}
		else if (buttonCollision(_PARTY))
		{
			_myState = PARTY;
		}
	}
}

void button::collectState(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		upDownAct();

		if (buttonCollision(_OKBUTTON) && _database->checkLToF())
		{
			_myState = TITLE;
			_database->LToF();
			_database->endTurn();
		}
		else if (buttonCollision(_CANCELBUTTON))
		{
			_myState = TITLE;
			_database->amount = 100;
		}
	}
}

void button::taxState(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		upDownAct();

		if (buttonCollision(_OKBUTTON) && _database->checkLToM())
		{
			_myState = TITLE;
			_database->LToM();
			_database->endTurn();
		}
		else if (buttonCollision(_CANCELBUTTON))
		{
			_myState = TITLE;
			_database->amount = 100;
		}
	}
}

void button::partyState(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		upDownAct();

		if (buttonCollision(_OKBUTTON) && _database->checkParty())
		{
			_myState = TITLE;
			_database->Party();
			_database->endTurn();
		}
		else if (buttonCollision(_CANCELBUTTON))
		{
			_myState = TITLE;
			_database->amount = 100;
		}
	}
}

void button::yesNoButton(void)
{
	if (buttonCollision(_OKBUTTON))
	{
		IMAGEMANAGER->findImage("yesIcon")->frameRender(getMemDC(), _OKBUTTON.left, _OKBUTTON.top, 1, 0);
		
		switch (_myState)
		{
		case SOLDIER:
			if (!_database->checkPToS()) _database->introType = TEXT_NOTENOUGH;
			break;
		case PHISICAL:
			if (!_database->checkAttackUp()) _database->introType = TEXT_NOTENOUGH;
			break;
		case MENTAL:
			if (!_database->checkIntUp()) _database->introType = TEXT_NOTENOUGH;
			break;
		case COLLECT:
			if (!_database->checkLToF()) _database->introType = TEXT_NOTENOUGH;
			break;
		case TAX:
			if (!_database->checkLToM()) _database->introType = TEXT_NOTENOUGH;
			break;
		case PARTY:
			if (!_database->checkParty()) _database->introType = TEXT_NOTENOUGH;
			break;
		}
	}
	else
	{
		IMAGEMANAGER->findImage("yesIcon")->frameRender(getMemDC(), _OKBUTTON.left, _OKBUTTON.top, 0, 0);
	}

	if (buttonCollision(_CANCELBUTTON))
	{
		IMAGEMANAGER->findImage("noIcon")->frameRender(getMemDC(), _CANCELBUTTON.left, _CANCELBUTTON.top, 1, 0);
	}
	else
	{
		IMAGEMANAGER->findImage("noIcon")->frameRender(getMemDC(), _CANCELBUTTON.left, _CANCELBUTTON.top, 0, 0);
	}
}

void button::upDownAct(void)
{
	if (buttonCollision(_UPBUTTON))
	{
		_database->amount += 100;
	}
	else if (buttonCollision(_DOWNBUTTON))
	{
		_database->amount -= 100;
	}
}

void button::upDownDraw(char* charName1, char* charName2, char* charName3) // UP, DOWN, IDLE
{
	if (buttonCollision(_UPBUTTON))
	{
		IMAGEMANAGER->findImage(charName1)->render(getMemDC(), 240, 175);
	}
	else if (buttonCollision(_DOWNBUTTON))
	{
		IMAGEMANAGER->findImage(charName2)->render(getMemDC(), 240, 175);
	}
	else
	{
		IMAGEMANAGER->findImage(charName3)->render(getMemDC(), 240, 175);
	}
}

void button::battleStartLoading(void)
{
	if (FRAMECOUNT + loadingFrame <= GetTickCount() && !battleStart)
	{
		loadingFrame = GetTickCount();
		++loadingCount;
		IMAGEMANAGER->findImage("battleStartImage")->render(getMemDC());
		if (loadingCount > 50)
		{
			loadingCount = 0;
			battleStart = true;

		}
	}
	if (battleStart)
	{
		(_field->goalBlock.check)? _field->render(BATTLE) : _field->render(BOSS);
	}
}