#include "stdafx.h"
#include "effect.h"

effect::effect()
{
}

effect::~effect()
{
}

HRESULT effect::init(void)
{
	// 구조체 초기화. 
	ZeroMemory(&pAttack, sizeof(pAttack));
	ZeroMemory(&eAttack, sizeof(eAttack));
	ZeroMemory(&bAttack1, sizeof(bAttack1));
	ZeroMemory(&bSkillEffect, sizeof(bSkillEffect));

	return S_OK;
}

void effect::release(void)
{
}

void effect::update(void)
{
	frameWork();
}

void effect::render()
{
	draw();
}

void effect::makeEffect(float x, float y, int num)
{
	switch (num)
	{
	case pAttackEffect:
		for (int i = 0; i < 100; i++)
		{
			if (pAttack[i].check) continue;
			pAttack[i].check = true;
			pAttack[i].img = IMAGEMANAGER->addFrameImage("normalAttackEffect", "normalAttackEffect.bmp",
				448, 64, 7, 1, true, RGB(255, 0, 255));
			pAttack[i].x = x;
			pAttack[i].y = y;
			break;
		}
		break;
	case eAttackEffect:
		for (int i = 0; i < 100; i++)
		{
			if (eAttack[i].check) continue;
			eAttack[i].check = true;
			eAttack[i].img = IMAGEMANAGER->addFrameImage("enemyAttackEffect", "enemyAttackEffect.bmp",
				900, 200, 9, 1, true, RGB(248, 0, 248));
			eAttack[i].x = x;
			eAttack[i].y = y;
			break;
		}
		break;
	case bossAttack1:
		for (int i = 0; i < 100; i++)
		{
			if (bAttack1[i].check) continue;
			bAttack1[i].check = true;
			bAttack1[i].img = IMAGEMANAGER->addFrameImage("bossNormalAttackEffect", "bossNormalAttackEffect.bmp",
				678, 86, 6, 1, true, RGB(255, 0, 255));
			bAttack1[i].x = x;
			bAttack1[i].y = y;
			break;
		}
		break;
	case bossAttack2:
		for (int i = 0; i < 100; i++)
		{
			if (bSkillEffect[i].check) continue;
			bSkillEffect[i].check = true;
			bSkillEffect[i].img = IMAGEMANAGER->addFrameImage("bossSkillEffect", "bossSkillEffect.bmp",
				1974, 433, 6, 1, true, RGB(255, 0, 255));
			bSkillEffect[i].x = x;
			bSkillEffect[i].y = y;
			break;
		}
		break;
	}
}

void effect::draw()
{
	for (int i = 0; i < 100; i++)
	{
		if (!pAttack[i].check) continue;
		pAttack[i].img->frameRender(getMemDC(), pAttack[i].x, pAttack[i].y, pAttack[i].currentX, 0);
	}

	for (int i = 0; i < 100; i++)
	{
		if (!eAttack[i].check) continue;
		eAttack[i].img->frameRender(getMemDC(), eAttack[i].x, eAttack[i].y, eAttack[i].currentX, 0);
	}


	for (int i = 0; i < 100; i++)
	{
		if (!bAttack1[i].check) continue;
		bAttack1[i].img->frameRender(getMemDC(), bAttack1[i].x, bAttack1[i].y, bAttack1[i].currentX, 0);
	}

	for (int i = 0; i < 100; i++)
	{
		if (!bSkillEffect[i].check) continue;
		bSkillEffect[i].img->frameRender(getMemDC(), bSkillEffect[i].x, bSkillEffect[i].y, bSkillEffect[i].currentX, 0);
	}
}

void effect::frameWork()
{
	for (int i = 0; i < 100; i++)
	{
		if (!pAttack[i].check) continue;
		++pAttack[i].frame;
		if (pAttack[i].frame > 2)
		{
			pAttack[i].frame = 0;
			++pAttack[i].currentX;
			if (pAttack[i].currentX > pAttack[i].img->getMaxFrameX())
			{
				pAttack[i].currentX = 0;
				removePAttack(i);
			}
		}
	}

	for (int i = 0; i < 100; i++)
	{
		if (!eAttack[i].check) continue;
		++eAttack[i].frame;
		if (eAttack[i].frame > 2)
		{
			eAttack[i].frame = 0;
			++eAttack[i].currentX;
			if (eAttack[i].currentX > eAttack[i].img->getMaxFrameX())
			{
				eAttack[i].currentX = 0;
				removeEAttack(i);
			}
		}
	}

	for (int i = 0; i < 100; i++)
	{
		if (!bAttack1[i].check) continue;
		++bAttack1[i].frame;
		if (bAttack1[i].frame > 2)
		{
			bAttack1[i].frame = 0;
			++bAttack1[i].currentX;
			if (bAttack1[i].currentX > bAttack1[i].img->getMaxFrameX())
			{
				bAttack1[i].currentX = 0;
				removeBAttack1(i);
			}
		}
	}

	for (int i = 0; i < 100; i++)
	{
		if (!bSkillEffect[i].check) continue;
		++bSkillEffect[i].frame;
		if (bSkillEffect[i].frame > 2)
		{
			bSkillEffect[i].frame = 0;
			++bSkillEffect[i].currentX;
			if (bSkillEffect[i].currentX > bSkillEffect[i].img->getMaxFrameX())
			{
				bSkillEffect[i].currentX = 0;
				removeBAttack2(i);
			}
		}
	}
}

void effect::pSet(float x, float y)
{
	for (int i = 0; i < 100; i++)
	{
		if (!pAttack[i].check) continue;
		pAttack[i].x = x;
		pAttack[i].y = y;
	}
}

void effect::eSet(float x, float y)
{
	for (int i = 0; i < 100; i++)
	{
		if (!eAttack[i].check) continue;
		eAttack[i].x = x;
		eAttack[i].y = y;
	}
}

void effect::bSet1(float x, float y)
{
	for (int i = 0; i < 100; i++)
	{
		if (!bAttack1[i].check) continue;
		bAttack1[i].x = x;
		bAttack1[i].y = y;
	}
}

void effect::bSet2(float x, float y)
{
	for (int i = 0; i < 100; i++)
	{
		if (!bSkillEffect[i].check) continue;
		bSkillEffect[i].x = x;
		bSkillEffect[i].y = y;
	}
}