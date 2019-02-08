#pragma once
#include "gameNode.h"
#include "field.h"
#include "database.h"

#define FRAMECOUNT 100.0f

class button : public gameNode
{
private:
	//�� ���� ����
	PAGESTATE _myState;

	//������ ��Ʈ
	RECT _OPENRC;

	//�޽� ��ư ��Ʈ
	RECT _TURNENDBUTTON;

	//���� ��Ʈ
	RECT _PHYSICAL;
	RECT _MENTAL;
	
	//���� ��Ʈ
	//¡��
	RECT _COLLECT;
	//¡��
	RECT _TAX;
	//��ȸ
	RECT _PARTY;

	//UP, DOWN ��ư ��Ʈ
	RECT _UPBUTTON;
	RECT _DOWNBUTTON;

	//yes / no ��ư
	RECT _OKBUTTON;
	RECT _CANCELBUTTON;

	//CLOSE ��ư
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

	//UI �׸��� �Լ�
	virtual void drawUI(void);

	//������ �׸��� �Լ�
	virtual void iconDraw(void);

	//�̺�Ʈ Close��ư �Լ�
	virtual void eventClose(void);

	//�̺�Ʈ Close��ư �׸���.
	virtual void eventCloseDraw(void);

	//yes / no ��ư�� �׸���
	virtual void yesNoButton(void);

	//UP / DOWN ��ư �浹 �� �ൿ �Լ�
	virtual void upDownAct(void);

	//UP / DOWN ��ư �׸��� �Լ�
	virtual void upDownDraw(char* charName1, char* charName2, char* charName3);

	//���� ���¸� ��´�.
	virtual PAGESTATE getState(void) { return _myState; }
	bool buttonCollision(RECT rc);

	//������ ��ư
	virtual void openingState(void);
	
	//Ÿ��Ʋ ��ư
	virtual void titleState(void);
	
	//¡�� ��ư
	virtual void solState(void);
	
	//���� ��ư
	virtual void powerState(void);
	//���� ����
	virtual void phisicalState(void);
	//å�� ����
	virtual void mentalState(void);

	
	//���� ��ư
	virtual void manageState(void);
	//¡��
	virtual void collectState(void);
	//¡��
	virtual void taxState(void);
	//��ȸ
	virtual void partyState(void);

	//��Ʋ ��ŸƮ �ε� ȭ�� �׸���
	virtual void battleStartLoading(void);

	button();
	virtual ~button();
};

