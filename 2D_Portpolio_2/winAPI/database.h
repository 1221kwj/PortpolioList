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
	//   //���� �̺�Ʈ����
	//   int type;
	//   //���� ������ �´� Ÿ������
	//   //0 : ��� ���� 1 : �� 2 : ���� 3 : ���� 4 :�ܿ�
	//};
	//eventtag _event;


	//1�� ������ �̹����� �� ����
	struct tagDamageDraw
	{
		//������ �� �ڸ���
		bool damaeDigit;
		//������ ������ X
		int frameX;
		//������ ��ġ
		float x, y;
		//������ ��Ʈ
		RECT rc;
	};

	//������ ��� ������ ����ü
	struct tagDamage
	{
		//true : ����Ʈ�� ��ų ����, false : �Ϲ� ����
		bool skillKind;
		//������ �ð� ����
		int frameCount;
		//������ �� �ð�
		int removeTime;
		//������ ��� ���ΰ�
		bool drawDamage;
		//������ �̹���
		image* img;
		//1�� ������ �̹���
		tagDamageDraw perDamage[5];
	};

	tagDamage _damageImage[100];

	//go �̹��� ����ü
	struct tagGo
	{
		//�̹��� ������ X
		int frameX;
		//������ �� �ð�
		int removeTime;
		//������ ����
		int frameCount;
		//��ǥ
		float x, y;
		//�̹���
		image* img;
	};

	tagGo _goImage;


	int battlePeriod;
	//���� �ֱ� : �������� 15~25�� ��������

	int battleYear;
	//���� ���� �⵵ : ������ �� + �����ֱ�

	int _event;

	int season;
	int year;
	int month;
	//����,����,��

	int soliders;
	//�����

	int people;
	//�鼺��

	int foods;
	//�ķ�

	int loyalty;
	//�ν�

	int money;
	//��ȭ

	int attack;
	int intelligence;
	//�÷��̾� ����/����


	//��ũ�� ���� ������
	struct scrolltag
	{
		int width;
		int x;
		int y;
	};
	scrolltag scroll;
	//�׸�
	scrolltag scroll2;
	//��ũ��
	scrolltag stick;
	//��


	void scrollMove();
	//��ũ�� �����̴� �Լ�
	void MakeEvent();
	//�̺�Ʈ �̴� �Լ�
	void setMax();
	//��ġ�� �ּ�,�ִ�� ���������ʰ� ����

	//���� �ٲٱ�
	void changeSeason();

	//�̺�Ʈ �׸���
	void drawEvent();

	//�̺�Ʈ �ؽ�Ʈ ���
	void textRender();

	//�̺�Ʈ �� ó���ϴ� �Լ�
	void eventCalculation();

	//���� ���� �Լ�
	void battleSwitch();
public:

	bool startEvent;
	//button ���� ���ּ���!!

	bool battleStart;
	//���� ���� -> ���� ���� ������ ��ư���� �޾� ����ȭ������ �Ѿ

	//�� ����ġ
	bool goSwitch;

	int amount;
	//������ġ  ��ư���� �÷ȴٰ� �ٿ���

	inline int getYear() { return year; }
	//�⵵�� ��´�

	inline int getMoney() { return money; }
	//�� ��ġ�� ��´� 

	inline int getSeason() { return season; }
	//������ ��´�

	inline int getAttack() { return attack; }
	//���� ��ġ�� ��´�

	inline int getInt() { return intelligence; }
	//���� ��ġ�� ��´�

	inline int getFood() { return foods; }
	//���� ��ġ�� ��´�

	inline int getLoyalty() { return loyalty; }
	//�ν� ��ġ�� ��´�

	inline int getPeople() { return people; }
	//�鼺���� ��´�

	inline int getSoldier() { return soliders; }
	//������� ��´�

	void SetFood(int num) { foods -= num; }
	//�ķ��� ��´�

	void SetSolider(int num) { soliders -= num; }
	//���縦 ��´�

	inline int getNextBattleYear() { return (battleYear - year); }

	void endTurn();
	//��(�Ѵ�)�� �ѱ��

	//¡��
	void PToS();
	//People To Soliders

	//����
	void AttackUp();
	void IntUp();
	//�÷��̾������ 

	//����
	void Party();
	//Foods To Loyalty �ķ� -> �ν�
	//Money To Loyalty ��ȭ -> �ν�

	void LToM();
	//Loyalty To Money �ν� -> ��ȭ
	void LToF();
	//Loyalty To Foods �ν� -> �ķ�

	//�������� ���� �Ǵ��� Ȯ���ϴ� ������ �Լ�
	bool checkPToS();
	bool checkAttackUp();
	bool checkIntUp();
	bool checkParty();
	bool checkLToM();
	bool checkLToF();

	//���콺�� �浹������ ����â �����ϴ� �Լ�
	//type�� � �ؽ�Ʈ�� ������� switch�� ����
	int introType;
	void renderIntro();

	//������ �׸���.
	void damageDraw(void);

	//������ �����. (������ ��� ��ġ(x, y, �ʺ�, ����), ������)
	void makeDamage(float x, float y, int width, int height, int damage, bool light);

	//�������� �����.
	void removeDamage(int arrNum) { ZeroMemory(&_damageImage[arrNum], sizeof(_damageImage[arrNum])); }

	//������ �۵�
	void frameWork(void);

	int getMonth() { return month; }
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	database();
	virtual ~database();
};