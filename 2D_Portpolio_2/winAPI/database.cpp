#include "stdafx.h"
#include "database.h"


database::database()
{
}


database::~database()
{
}

HRESULT database::init(void)
{
	srand(time(NULL));
	//_event.num = 0;
	//_event.type = 0;
	_event = 0;

	month = 3;
	year = 200;
	season = SPRING;

	soliders = 800;
	people = 100;
	foods = 500;
	loyalty = 100;
	attack = 10;
	money = 1000;
	intelligence = 10;
	amount = 100;

	startEvent = false;

	scroll.width = 0;
	scroll.x = 300;
	scroll.y = 50;

	scroll2.width = 10;
	scroll2.x = scroll.x - 10;
	scroll2.y = scroll.y - 10;

	stick.width = 0;
	stick.x = scroll2.x + 10;
	stick.y = scroll2.y - 10;

	battleStart = false;
	battlePeriod = RND->getFromIntTo(5, 10);
	battleYear = 205;

	IMAGEMANAGER->addImage("DROUGHT", "DROUGHT.bmp", 520, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TORNADO", "TORNADO.bmp", 520, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TYPHOON", "TYPHOON.bmp", 520, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HEAVYRAIN", "HEAVYRAIN.bmp", 520, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PLAGUE", "PLAGUE.bmp", 520, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RICH", "RICH.bmp", 520, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("POOR", "POOR.bmp", 520, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HEAVYPOOR", "HEAVYPOOR.bmp", 520, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HEAVYSNOW", "HEAVYSNOW.bmp", 520, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TEACHER", "TEACHER.bmp", 520, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("LIBRARY", "LIBRARY.bmp", 520, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("SLOTH", "SLOTH.bmp", 520, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("THIEF", "THIEF.bmp", 520, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TREASURE", "TREASURE.bmp", 520, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("REVOLT", "REVOLT.bmp", 520, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GAMEOVER", "GAMEOVER.bmp", 520, 390, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("scroll", "scroll.bmp", 540, 410, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("stick", "stick.bmp", 15, 430, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("DROUGHT_TEXT", "DROUGHT_TEXT.bmp", 520, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TORNADO_TEXT", "TORNADO_TEXT.bmp", 520, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TYPHOON_TEXT", "TYPHOON_TEXT.bmp", 520, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HEAVYRAIN_TEXT", "HEAVYRAIN_TEXT.bmp", 520, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PLAGUE_TEXT", "PLAGUE_TEXT.bmp", 520, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("RICH_TEXT", "RICH_TEXT.bmp", 520, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("POOR_TEXT", "POOR_TEXT.bmp", 520, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HEAVYPOOR_TEXT", "HEAVYPOOR_TEXT.bmp", 520, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HEAVYSNOW_TEXT", "HEAVYSNOW_TEXT.bmp", 520, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TEACHER_TEXT", "TEACHER_TEXT.bmp", 520, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("LIBRARY_TEXT", "LIBRARY_TEXT.bmp", 520, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("SLOTH_TEXT", "SLOTH_TEXT.bmp", 520, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("THIEF_TEXT", "THIEF_TEXT.bmp", 520, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TREASURE_TEXT", "TREASURE_TEXT.bmp", 520, 200, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("REVOLT_TEXT", "REVOLT_TEXT.bmp", 520, 200, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("Text_NotEnough", "Text_NotEnough.bmp", 171, 22, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Text_Attack", "Text_Attack.bmp", 199, 253, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Text_Foods", "Text_Foods.bmp", 199, 253, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Text_People", "Text_People.bmp", 199, 253, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Text_Soliders", "Text_Soliders.bmp", 199, 253, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Text_Loyalty", "Text_Loyalty.bmp", 199, 253, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Text_Int", "Text_Int.bmp", 199, 253, true, RGB(255, 0, 255));

	ZeroMemory(&_damageImage, sizeof(_damageImage));
	ZeroMemory(&_goImage, sizeof(_goImage));

	//makeDamage(500, 500, 100, 100, 1945);
	//introType = TEXT_DAMAGE;
	introType = TEXT_NOTENOUGH;

	_goImage.x = 1000;
	_goImage.y = 100;
	_goImage.img = IMAGEMANAGER->addFrameImage("goIcon", "goIcon.bmp", 1024, 64, 16, 1, true, RGB(255, 0, 255));

	goSwitch = false;

	return S_OK;
}
void database::release(void)
{

}
void database::update(void)
{
	scrollMove();
	setMax();
	battleSwitch();
	//if (battleStart) 
	frameWork();
}
void database::render(void)
{
	//if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	//{
	//   introType++;
	//}
	//Rectangle(getMemDC(),100, 100, 400, 400);
	//IMAGEMANAGER->render("GAMEOVER", getMemDC(), 100, 100, 0, 0, scroll.width, 390);
	drawEvent();
	textRender();
	renderIntro();
	if (goSwitch) _goImage.img->frameRender(getMemDC(), _goImage.x, _goImage.y, _goImage.frameX, 0);
	//char str[128];
	//wsprintf(str, "%d", introType);
	//TextOut(getMemDC(), 50, 10, str, strlen(str));
	//wsprintf(str, "%d", money);
	//TextOut(getMemDC(), 50, 50, str, strlen(str));
	//wsprintf(str, "%d", foods);
	//TextOut(getMemDC(), 50, 90, str, strlen(str));
	//wsprintf(str, "%d", loyalty);
	//TextOut(getMemDC(), 50, 140, str, strlen(str));
	//wsprintf(str, "%d,%d", year,month);
	//TextOut(getMemDC(), 50, 180, str, strlen(str));
}
void database::scrollMove()
{
	scroll.width += 5;
	if (scroll.width > 520) scroll.width = 520;
	scroll2.width += 5;
	if (scroll2.width > 540)scroll2.width = 540;
	stick.x += 5;
	if (stick.x > 540 + scroll2.x)stick.x = 540 + scroll2.x;
}
void database::setMax()
{
	if (soliders <= 0) soliders = 0;
	if (foods <= 0)foods = 0;
	if (money <= 0)money = 0;
	if (people <= 0)people = 0;
	if (loyalty <= 0)loyalty = 0;
	if (loyalty >= 100)loyalty = 100;
	if (amount <= 0)amount = 0;
}
void database::endTurn()
{
	month++;
	if (month > 12)
	{
		month = 1;
		year++;

		people += people * 0.3;
		//번식
	}
	money += people / 5;
	//매달 세금
	changeSeason();

	if (season == FALL)
	{
		//foods += people * 2;
		foods += people * 0.9;
	}

	int t = rand() % 1000;
	if (t < 100)
	{
		startEvent = true;
		scroll.width = 0;
		scroll2.width = 10;
		stick.x = scroll2.x + 10;
		MakeEvent();
	}
}

void database::battleSwitch()
{
	if (year == battleYear)
	{
		battlePeriod = RND->getFromIntTo(5, 10);
		battleStart = true;
		battleYear = year + battlePeriod;
		startEvent = false;
		PlaySound(NULL, 0, 0);
		PlaySound(TEXT("battleBGM.wav"), NULL, SND_LOOP | SND_ASYNC);
	}
}

void database::MakeEvent()
{
	for (int i = 0; i<1000; i++)
	{
		//뽑는다
		_event = rand() % 14 + DROUGHT;
		if (_event >= DROUGHT && _event <= HEAVYSNOW)
		{
			switch (season)
			{
			case SPRING:
			{
				int p = rand() % 2;
				switch (p)
				{
				case 0:
					_event = DROUGHT;
					break;
				case 1:
					_event = TORNADO;
					break;
				}
			}
			break;
			case SUMMER:
			{
				int p = rand() % 3;
				switch (p)
				{
				case 0:
					_event = TYPHOON;
					break;
				case 1:
					_event = HEAVYRAIN;
					break;
				case 2:
					_event = PLAGUE;
					break;
				}
			}
			break;
			case FALL:
			{
				int p = rand() % 3;
				switch (p)
				{
				case 0:
					_event = RICH;
					break;
				case 1:
					_event = POOR;
					break;
				case 2:
					_event = HEAVYPOOR;
					break;
				}
			}
			break;
			case WINTER:

				_event = HEAVYSNOW;
				break;
			}
			break;
		}
		//나머지는 OK
		else
		{
			break;
		}

	}

	//반란 이벤트
	if (loyalty < 40)
	{
		_event = REVOLT;
	}
	eventCalculation();
}
void database::changeSeason()
{
	if (month > 2 && month < 6)
	{
		season = SPRING;
		if (month == 5) people += RND->getFromIntTo(3, 10);
	}
	else if (month >= 6 && month < 9)
	{
		season = SUMMER;
		if (month == 8) people += RND->getFromIntTo(3, 10);
	}
	else if (month >= 9 && month < 12)
	{
		season = FALL;
		if (month == 11) people += RND->getFromIntTo(3, 10);
	}
	else
	{
		season = WINTER;
		if (month == 2) people += RND->getFromIntTo(3, 10);
	}
}
void database::drawEvent()
{
	if (startEvent)
	{
		IMAGEMANAGER->render("stick", getMemDC(), scroll2.x - 15, scroll2.y - 10);
		IMAGEMANAGER->render("scroll", getMemDC(), scroll2.x, scroll2.y, 0, 0, scroll2.width, 410);
		switch (_event)
		{
		case DROUGHT:
			IMAGEMANAGER->render("DROUGHT", getMemDC(), scroll.x, scroll.y, 0, 0, scroll.width, 390);
			break;
		case TORNADO:
			IMAGEMANAGER->render("TORNADO", getMemDC(), scroll.x, scroll.y, 0, 0, scroll.width, 390);
			break;
		case TYPHOON:
			IMAGEMANAGER->render("TYPHOON", getMemDC(), scroll.x, scroll.y, 0, 0, scroll.width, 390);
			break;
		case HEAVYRAIN:
			IMAGEMANAGER->render("HEAVYRAIN", getMemDC(), scroll.x, scroll.y, 0, 0, scroll.width, 390);
			break;
		case PLAGUE:
			IMAGEMANAGER->render("PLAGUE", getMemDC(), scroll.x, scroll.y, 0, 0, scroll.width, 390);
			break;
		case RICH:
			IMAGEMANAGER->render("RICH", getMemDC(), scroll.x, scroll.y, 0, 0, scroll.width, 390);
			break;
		case POOR:
			IMAGEMANAGER->render("POOR", getMemDC(), scroll.x, scroll.y, 0, 0, scroll.width, 390);
			break;
		case HEAVYPOOR:
			IMAGEMANAGER->render("HEAVYPOOR", getMemDC(), scroll.x, scroll.y, 0, 0, scroll.width, 390);
			break;
		case HEAVYSNOW:
			IMAGEMANAGER->render("HEAVYSNOW", getMemDC(), scroll.x, scroll.y, 0, 0, scroll.width, 390);
			break;
		case TEACHER:
			IMAGEMANAGER->render("TEACHER", getMemDC(), scroll.x, scroll.y, 0, 0, scroll.width, 390);
			break;
		case LIBRARY:
			IMAGEMANAGER->render("LIBRARY", getMemDC(), scroll.x, scroll.y, 0, 0, scroll.width, 390);
			break;
		case SLOTH:
			IMAGEMANAGER->render("SLOTH", getMemDC(), scroll.x, scroll.y, 0, 0, scroll.width, 390);
			break;
		case THIEF:
			IMAGEMANAGER->render("THIEF", getMemDC(), scroll.x, scroll.y, 0, 0, scroll.width, 390);
			break;
		case TREASURE:
			IMAGEMANAGER->render("TREASURE", getMemDC(), scroll.x, scroll.y, 0, 0, scroll.width, 390);
			break;
		case REVOLT:
			IMAGEMANAGER->render("REVOLT", getMemDC(), scroll.x, scroll.y, 0, 0, scroll.width, 390);
			break;
		}
		IMAGEMANAGER->render("stick", getMemDC(), stick.x, stick.y);
	}
}
void database::textRender()
{
	if (startEvent)
	{
		switch (_event)
		{
		case DROUGHT:
			IMAGEMANAGER->render("DROUGHT_TEXT", getMemDC(), 300, 470, 0, 0, scroll.width, 200);
			break;
		case TORNADO:
			IMAGEMANAGER->render("TORNADO_TEXT", getMemDC(), 300, 470, 0, 0, scroll.width, 200);
			break;
		case TYPHOON:
			IMAGEMANAGER->render("TYPHOON_TEXT", getMemDC(), 300, 470, 0, 0, scroll.width, 200);
			break;
		case HEAVYRAIN:
			IMAGEMANAGER->render("HEAVYRAIN_TEXT", getMemDC(), 300, 470, 0, 0, scroll.width, 200);
			break;
		case PLAGUE:
			IMAGEMANAGER->render("PLAGUE_TEXT", getMemDC(), 300, 470, 0, 0, scroll.width, 200);
			break;
		case RICH:
			IMAGEMANAGER->render("RICH_TEXT", getMemDC(), 300, 470, 0, 0, scroll.width, 200);
			break;
		case POOR:
			IMAGEMANAGER->render("POOR_TEXT", getMemDC(), 300, 470, 0, 0, scroll.width, 200);
			break;
		case HEAVYPOOR:
			IMAGEMANAGER->render("HEAVYPOOR_TEXT", getMemDC(), 300, 470, 0, 0, scroll.width, 200);
			break;
		case HEAVYSNOW:
			IMAGEMANAGER->render("HEAVYSNOW_TEXT", getMemDC(), 300, 470, 0, 0, scroll.width, 200);
			break;
		case TEACHER:
			IMAGEMANAGER->render("TEACHER_TEXT", getMemDC(), 300, 470, 0, 0, scroll.width, 200);
			break;
		case LIBRARY:
			IMAGEMANAGER->render("LIBRARY_TEXT", getMemDC(), 300, 470, 0, 0, scroll.width, 200);
			break;
		case SLOTH:
			IMAGEMANAGER->render("SLOTH_TEXT", getMemDC(), 300, 470, 0, 0, scroll.width, 200);
			break;
		case THIEF:
			IMAGEMANAGER->render("THIEF_TEXT", getMemDC(), 300, 470, 0, 0, scroll.width, 200);
			break;
		case TREASURE:
			IMAGEMANAGER->render("TREASURE_TEXT", getMemDC(), 300, 470, 0, 0, scroll.width, 200);
			break;
		case REVOLT:
			IMAGEMANAGER->render("REVOLT_TEXT", getMemDC(), 300, 470, 0, 0, scroll.width, 200);;
			break;
		}
	}
}
void database::eventCalculation()
{
	switch (_event)
	{
	case DROUGHT:
		foods -= (foods / 5);
		loyalty -= 5;
		//식량 20퍼 감소 민심 5 감소
		break;
	case TORNADO:
		people -= (people / 5);
		loyalty -= 10;
		//인구 20퍼 감소 민심 10 감소
		break;
	case TYPHOON:
		people -= (people / 5);
		loyalty -= 10;
		foods -= (foods / 10);
		money -= (money / 10);
		//인구 20퍼감소 민심 10감소 식량 10퍼감소 재화 10퍼감소
		break;
	case HEAVYRAIN:
		foods -= (foods / 5);
		people -= (people / 10);
		loyalty -= 5;
		//음식 20퍼감소 인구 10퍼감소 민심 5 감소
		break;
	case PLAGUE:
		people -= (people / 3);
		loyalty -= 10;
		//인구 3분의 1감소 민심 10감소
		break;
	case RICH:
		foods += people * 2;
		//수확량 2배
		break;
	case POOR:
		foods -= people * 2;
		//수확량만큼 빼기
		break;
	case HEAVYPOOR:
		foods -= people * 4;
		loyalty -= 10;
		//수확량 2배만큼 빼기
		break;
	case HEAVYSNOW:
		foods -= (foods / 5);
		loyalty -= 10;
		people -= (people / 5);
		//식량 20퍼감소, 민심 10감소, 인구수 20퍼감소
		break;
	case TEACHER:
		attack += 2;
		//무력 2증가
		break;
	case LIBRARY:
		intelligence += 2;
		//지력 2 증가
		break;
	case SLOTH:
		attack -= 1;
		intelligence -= 1;
		//무력 1감소 ,지력 1 감소
		break;
	case THIEF:
		money /= 2;
		//재정 반으로
		break;
	case TREASURE:
		money += 1000;
		//1000골드 추가
		break;
	case REVOLT:
		foods = 100;
		loyalty += 20;
		//음식이 100으로 바뀜, 민심 20증가
		break;
	}
}
void database::PToS()
{
	people -= amount;
	soliders += amount;

	money -= amount * 7;
	foods -= amount * 7;

	amount = 100;
}
void database::AttackUp()
{
	attack += rand() % 3;
	money -= 1000;
	foods -= 1000;
}
void database::IntUp()
{
	intelligence += rand() % 3;
	money -= 1000;
	foods -= 1000;
}
void database::Party()
{
	foods -= amount;
	money -= amount;

	loyalty += amount / 100;

	amount = 100;
}
void database::LToM()
{
	money += amount;
	loyalty -= amount / 100;

	foods -= amount / 10;

	amount = 100;
}
void database::LToF()
{
	foods += amount;
	loyalty -= amount / 100;

	money -= amount / 10;

	amount = 100;
}
bool database::checkPToS()
{
	if (money >= amount * 7 && foods >= amount * 7 && people >= amount)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool database::checkAttackUp()
{
	if (money >= 1000 && foods >= 1000)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool database::checkIntUp()
{
	if (money >= 1000 && foods >= 1000)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool database::checkParty()
{
	if (money >= amount  && foods >= amount)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool database::checkLToM()
{
	if (foods >= amount / 10)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool database::checkLToF()
{
	if (money >= amount / 10)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void database::renderIntro()
{
	switch (introType)
	{
	case TEXT_NOTENOUGH:
		IMAGEMANAGER->render("Text_NotEnough", getMemDC(), _ptMouse.x, _ptMouse.y + 10);
		break;
	case TEXT_ATK:
		//IMAGEMANAGER->render("Text_Attack", getMemDC(), 850, 100);
		IMAGEMANAGER->render("Text_Attack", getMemDC(), 850, 200);
		break;
	case TEXT_INT:
		//IMAGEMANAGER->render("Text_Int", getMemDC(), 850, 180);
		IMAGEMANAGER->render("Text_Int", getMemDC(), 850, 280);
		break;
	case TEXT_SOLIDERS:
		//IMAGEMANAGER->render("Text_Soliders", getMemDC(), 850, 260);
		IMAGEMANAGER->render("Text_Soliders", getMemDC(), 850, 360);
		break;
	case TEXT_PEOPLE:
		//IMAGEMANAGER->render("Text_People", getMemDC(), 850, 340);
		IMAGEMANAGER->render("Text_People", getMemDC(), 850, 440);
		break;
	case TEXT_FOODS:
		//IMAGEMANAGER->render("Text_Foods", getMemDC(), 850, 420);
		IMAGEMANAGER->render("Text_Foods", getMemDC(), 850, 520);
		break;
	case TEXT_LOYALTY:
		//IMAGEMANAGER->render("Text_Loyalty", getMemDC(), 850, 500);
		IMAGEMANAGER->render("Text_Loyalty", getMemDC(), 850, 500);
		break;
	}

	introType = 0;
}
void database::damageDraw(void)
{
	for (int i = 0; i < 100; i++)
	{
		if (!_damageImage[i].drawDamage) continue;
		for (int j = 0; j < 5; j++)
		{
			if (!_damageImage[i].perDamage[j].damaeDigit) continue;
			_damageImage[i].img->frameRender(getMemDC(),
				_damageImage[i].perDamage[j].rc.left,
				_damageImage[i].perDamage[j].rc.top,
				_damageImage[i].perDamage[j].frameX, 0);
		}
	}
}
void database::makeDamage(float x, float y, int width, int height, int damage, bool light)
{
	for (int i = 0; i < 100; i++)
	{
		if (_damageImage[i].drawDamage) continue;
		_damageImage[i].drawDamage = true;
		_damageImage[i].skillKind = light;
		if (_damageImage[i].skillKind)
		{
			_damageImage[i].img = IMAGEMANAGER->addFrameImage("skillDamage", "skillDamage.bmp", 190, 16, 10, 1, true, RGB(255, 0, 255));
		}
		else
		{
			_damageImage[i].img = IMAGEMANAGER->addFrameImage("damage", "damage.bmp", 190, 16, 10, 1, true, RGB(255, 0, 255));
		}

		if (damage > 99999)
		{
			damage = 99999;
			for (int j = 0; j < 5; j++)
			{
				_damageImage[i].perDamage[j].frameX = 9;
				_damageImage[i].perDamage[j].damaeDigit = true;
			}
		}
		else if (damage > 9999 && damage <= 99999)
		{
			_damageImage[i].perDamage[0].frameX = damage / 10000;
			_damageImage[i].perDamage[0].damaeDigit = true;

			_damageImage[i].perDamage[1].frameX = (damage % 10000) / 1000;
			_damageImage[i].perDamage[1].damaeDigit = true;

			_damageImage[i].perDamage[2].frameX = (damage % 1000) / 100;
			_damageImage[i].perDamage[2].damaeDigit = true;

			_damageImage[i].perDamage[3].frameX = (damage % 100) / 10;
			_damageImage[i].perDamage[3].damaeDigit = true;

			_damageImage[i].perDamage[4].frameX = damage % 10;
			_damageImage[i].perDamage[4].damaeDigit = true;
		}
		else if (damage > 999 && damage <= 9999)
		{
			_damageImage[i].perDamage[0].frameX = damage / 1000;
			_damageImage[i].perDamage[0].damaeDigit = true;

			_damageImage[i].perDamage[1].frameX = (damage % 1000) / 100;
			_damageImage[i].perDamage[1].damaeDigit = true;

			_damageImage[i].perDamage[2].frameX = (damage % 100) / 10;
			_damageImage[i].perDamage[2].damaeDigit = true;

			_damageImage[i].perDamage[3].frameX = damage % 10;
			_damageImage[i].perDamage[3].damaeDigit = true;
		}
		else if (damage > 99 && damage <= 999)
		{
			_damageImage[i].perDamage[0].frameX = damage / 100;
			_damageImage[i].perDamage[0].damaeDigit = true;

			_damageImage[i].perDamage[1].frameX = (damage % 100) / 10;
			_damageImage[i].perDamage[1].damaeDigit = true;

			_damageImage[i].perDamage[2].frameX = damage % 10;
			_damageImage[i].perDamage[2].damaeDigit = true;
		}
		else if (damage > 9 && damage <= 99)
		{
			_damageImage[i].perDamage[0].frameX = damage / 10;
			_damageImage[i].perDamage[0].damaeDigit = true;

			_damageImage[i].perDamage[1].frameX = damage % 10;
			_damageImage[i].perDamage[1].damaeDigit = true;
		}
		else if (damage > 0 && damage <= 9)
		{
			_damageImage[i].perDamage[0].frameX = damage % 10;
			_damageImage[i].perDamage[0].damaeDigit = true;
		}

		for (int j = 0; j < 5; j++)
		{
			if (!_damageImage[i].perDamage[j].damaeDigit) continue;
			_damageImage[i].perDamage[j].x = (x - width) + j * (_damageImage[i].img->getFrameWidth() - 5);
			_damageImage[i].perDamage[j].y = (y - height);
			_damageImage[i].perDamage[j].rc = RectMakeCenter(
				_damageImage[i].perDamage[j].x, _damageImage[i].perDamage[j].y,
				_damageImage[i].img->getFrameWidth(), _damageImage[i].img->getFrameHeight());
		}

		break;
	}
}
void database::frameWork(void)
{
		if (goSwitch)
		{
			++_goImage.frameCount;
			if (_goImage.frameCount > 3)
			{
				++_goImage.frameX;
				++_goImage.removeTime;
				_goImage.frameCount = 0;
				if (_goImage.frameX > _goImage.img->getMaxFrameX())
				{
					_goImage.frameX = 0;
					if (_goImage.removeTime > 30)
					{
						_goImage.removeTime = 0;
						goSwitch = false;
					}
				}
			}
		}

		for (int i = 0; i < 100; i++)
		{
			if (!_damageImage[i].drawDamage) continue;
			++_damageImage[i].frameCount;
			if (++_damageImage[i].frameCount > 5)
			{
				_damageImage[i].frameCount = 0;
				++_damageImage[i].removeTime;
				for (int j = 0; j < 5; j++)
				{
					if (!_damageImage[i].perDamage[j].damaeDigit) continue;
					//_damageImage[i].perDamage[j].x += 2;
					_damageImage[i].perDamage[j].y -= 2;
					_damageImage[i].perDamage[j].rc = RectMakeCenter(
						_damageImage[i].perDamage[j].x, _damageImage[i].perDamage[j].y,
						_damageImage[i].img->getFrameWidth(), _damageImage[i].img->getFrameHeight());
				}
				if (_damageImage[i].removeTime > 15)
				{
					removeDamage(i);
				}
			}
		}
}