#pragma once
#include "gameNode.h"
class effect :
	public gameNode
{

private:
	//ȿ�� ���� �̳�.. player���� ��ߵǴϱ� ���߿� enum���� ��. 
	enum
	{
		pAttackEffect = 50,
		eAttackEffect,
		bossAttack1, //��Ÿ
		bossAttack2, //������ �������� ��ų ����Ʈ
	};

	struct tagEffect
	{
		float x, y;
		int frame;
		int currentX;
		bool check;
		bool direction; // true : ������, false : ����
		image* img;
	};

	int num;

	tagEffect pAttack[100];
	tagEffect eAttack[100];
	tagEffect bAttack1[100];
	tagEffect bSkillEffect[100];

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//����Ʈ�� ���ִ� �Լ� 
	//��ǥ���̶�, ��������Ʈ���� �޾ƾ���. enum���� ������.
	//int num �� �̳��� �޴� ����. ���࿡ ��Ŭ�������� ����, ���ڸ� x,y,ENEMYMOVE? �ƴϸ� ���ڸ� ������... �۵��ǰ�.. ?
	//���࿡ x,y�� ������ �� x,y�� ����Ʈ�� ��Ÿ�����ϰ�... 
	//�����ӵ� �� �̳ѿ� �°� �����ؾ��ϴϱ�... �̳��� ����ġ�� �޾Ƽ� �����ӵ� �ٸ��� ����ǰڳ�.. ?
	virtual void makeEffect(float x, float y, int num);

	//����Ʈ�� ���������� �ִϸ��̼� ������ �ö󰡰� ����� �Լ�(���� update�� ���� �˴ϴ�.)
	//����ġ�� �޾Ƽ� 
	virtual void frameWork();

	//����Ʈ�� ���������� �׷��ִ� �Լ�!(���� render�� ���ּ���)
	virtual void draw();

	//����Ʈ x, y���� �޾Ƽ� �����̰� �� �� �ִ� set �Լ�(ī�޶� �̵��Ҷ� �����)
	virtual void pSet(float x, float y);
	virtual void eSet(float x, float y);
	virtual void bSet1(float x, float y);
	virtual void bSet2(float x, float y);

	virtual void removePAttack(int arrNum) { ZeroMemory(&pAttack[arrNum], sizeof(pAttack[arrNum])); }
	virtual void removeEAttack(int arrNum) { ZeroMemory(&eAttack[arrNum], sizeof(eAttack[arrNum])); }
	virtual void removeBAttack1(int arrNum) { ZeroMemory(&bAttack1[arrNum], sizeof(bAttack1[arrNum])); }
	virtual void removeBAttack2(int arrNum) { ZeroMemory(&bSkillEffect[arrNum], sizeof(bSkillEffect[arrNum])); }

public:
	effect();
	~effect();
};