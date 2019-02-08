#pragma once
#include "gameNode.h"
class field : public gameNode
{
private:
	image* _seasonTitle;

	image* _openingBG_0; // ��� ��ư
	image* _openingBG_1; // ��� ��ư ���콺���� ������.

	struct blocktag
	{
		float x, y;
		RECT rc;
		bool check;

		int minY;
		int maxY;
	};
public:
	//�� �����ϴ� ���
	blocktag spawnBlock[6];
	//y�� ���� ���
	blocktag changeBlock[4];
	//�� ���
	blocktag goalBlock;

	float cameraX;
	bool lockCamera;

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(int season);

	virtual void openingDraw(int num);
	virtual void moveChangeBlock(float num)
	{
		for (int i = 0; i < 4; i++)

		{
			changeBlock[i].x -= num;
		}
	}
	virtual void moveSpawnBlock(float num)
	{
		for (int i = 0; i < 6; i++)

		{
			spawnBlock[i].x -= num;
		}
	}
	field();
    virtual ~field();
};
