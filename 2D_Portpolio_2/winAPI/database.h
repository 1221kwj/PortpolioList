#pragma once
#include "gameNode.h"
class database :
	public gameNode
{
private:
	//enum
	//{
	//   SPRING = 8,
	//   SUMMER,
	//   FALL,
	//   WINTER
	//};
	//struct eventtag
	//{
	//   int num;
	//   //무슨 이벤트인지
	//   int type;
	//   //무슨 계절에 맞는 타입인지
	//   //0 : 모든 계절 1 : 봄 2 : 여름 3 : 가을 4 :겨울
	//};
	//eventtag _event;


	//1개 데미지 이미지에 들어갈 내용
	struct tagDamageDraw
	{
		//띄우고자 할 자리수
		bool damaeDigit;
		//데미지 프레임 X
		int frameX;
		//데미지 위치
		float x, y;
		//데미지 렉트
		RECT rc;
	};

	//적마다 띄울 데미지 구조체
	struct tagDamage
	{
		//true : 라이트닝 스킬 공격, false : 일반 공격
		bool skillKind;
		//프레임 시간 조절
		int frameCount;
		//지워야 할 시간
		int removeTime;
		//데미지 띄울 것인가
		bool drawDamage;
		//데미지 이미지
		image* img;
		//1개 데미지 이미지
		tagDamageDraw perDamage[5];
	};

	tagDamage _damageImage[100];

	//go 이미지 구조체
	struct tagGo
	{
		//이미지 프레임 X
		int frameX;
		//지워야 할 시간
		int removeTime;
		//프레임 조절
		int frameCount;
		//좌표
		float x, y;
		//이미지
		image* img;
	};

	tagGo _goImage;


	int battlePeriod;
	//전투 주기 : 랜덤으로 15~25년 랜덤으로

	int battleYear;
	//전투 예정 년도 : 전투한 해 + 전투주기

	int _event;

	int season;
	int year;
	int month;
	//계절,연도,월

	int soliders;
	//병사수

	int people;
	//백성수

	int foods;
	//식량

	int loyalty;
	//민심

	int money;
	//재화

	int attack;
	int intelligence;
	//플레이어 무력/지력


	//스크롤 관련 변수들
	struct scrolltag
	{
		int width;
		int x;
		int y;
	};
	scrolltag scroll;
	//그림
	scrolltag scroll2;
	//스크롤
	scrolltag stick;
	//봉


	void scrollMove();
	//스크롤 움직이는 함수
	void MakeEvent();
	//이벤트 뽑는 함수
	void setMax();
	//수치가 최소,최대로 벌어지지않게 설정

	//계절 바꾸기
	void changeSeason();

	//이벤트 그리기
	void drawEvent();

	//이벤트 텍스트 출력
	void textRender();

	//이벤트 수 처리하는 함수
	void eventCalculation();

	//전투 개시 함수
	void battleSwitch();
public:

	bool startEvent;
	//button 에서 켜주세요!!

	bool battleStart;
	//전투 시작 -> 전투 시작 변수를 버튼에서 받아 전투화면으로 넘어감

	//고 스위치
	bool goSwitch;

	int amount;
	//변동수치  버튼으로 늘렸다가 줄였다

	inline int getYear() { return year; }
	//년도를 얻는다

	inline int getMoney() { return money; }
	//돈 수치를 얻는다 

	inline int getSeason() { return season; }
	//계절을 얻는다

	inline int getAttack() { return attack; }
	//무력 수치를 얻는다

	inline int getInt() { return intelligence; }
	//지력 수치를 얻는다

	inline int getFood() { return foods; }
	//군미 수치를 얻는다

	inline int getLoyalty() { return loyalty; }
	//민심 수치를 얻는다

	inline int getPeople() { return people; }
	//백성수를 얻는다

	inline int getSoldier() { return soliders; }
	//군사수를 얻는다

	void SetFood(int num) { foods -= num; }
	//식량을 깎는다

	void SetSolider(int num) { soliders -= num; }
	//군사를 깎는다

	inline int getNextBattleYear() { return (battleYear - year); }

	void endTurn();
	//턴(한달)을 넘긴다

	//징집
	void PToS();
	//People To Soliders

	//수련
	void AttackUp();
	void IntUp();
	//플레이어스탯증가 

	//관리
	void Party();
	//Foods To Loyalty 식량 -> 민심
	//Money To Loyalty 재화 -> 민심

	void LToM();
	//Loyalty To Money 민심 -> 재화
	void LToF();
	//Loyalty To Foods 민심 -> 식량

	//눌렀을때 돈이 되는지 확인하는 각자의 함수
	bool checkPToS();
	bool checkAttackUp();
	bool checkIntUp();
	bool checkParty();
	bool checkLToM();
	bool checkLToF();

	//마우스가 충돌했을때 설명창 랜더하는 함수
	//type는 어떤 텍스트를 출력할지 switch로 결정
	int introType;
	void renderIntro();

	//데미지 그린다.
	void damageDraw(void);

	//데미지 만든다. (데미지 띄울 위치(x, y, 너비, 높이), 데미지)
	void makeDamage(float x, float y, int width, int height, int damage, bool light);

	//데미지를 지운다.
	void removeDamage(int arrNum) { ZeroMemory(&_damageImage[arrNum], sizeof(_damageImage[arrNum])); }

	//프레임 작동
	void frameWork(void);

	int getMonth() { return month; }
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	database();
	virtual ~database();
};