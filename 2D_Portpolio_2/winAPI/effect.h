#pragma once
#include "gameNode.h"
class effect :
	public gameNode
{

private:
	//효과 종류 이넘.. player에도 써야되니까 나중에 enum으로 뺌. 
	enum
	{
		pAttackEffect = 50,
		eAttackEffect,
		bossAttack1, //평타
		bossAttack2, //위에서 떨어지는 스킬 이펙트
	};

	struct tagEffect
	{
		float x, y;
		int frame;
		int currentX;
		bool check;
		bool direction; // true : 오른쪽, false : 왼쪽
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

	//이펙트를 켜주는 함수 
	//좌표값이랑, 무슨이펙트인지 받아야함. enum으로 만들어보기.
	//int num 은 이넘을 받는 숫자. 만약에 적클래스에서 쓸때, 인자를 x,y,ENEMYMOVE? 아니면 숫자를 넣으면... 작동되게.. ?
	//만약에 x,y를 받으면 그 x,y에 이펙트가 나타나야하고... 
	//프레임도 그 이넘에 맞게 동작해야하니까... 이넘을 스위치로 받아서 프레임도 다르게 진행되겠네.. ?
	virtual void makeEffect(float x, float y, int num);

	//이펙트가 켜져있으면 애니메이션 프레임 올라가게 만드는 함수(만들어서 update에 쓰면 됩니다.)
	//스위치로 받아서 
	virtual void frameWork();

	//이펙트가 켜져있으면 그려주는 함수!(만들어서 render에 써주세요)
	virtual void draw();

	//이펙트 x, y값을 받아서 움직이게 할 수 있는 set 함수(카메라 이동할때 써야함)
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