#pragma once
#include "gameNode.h"
class circusJump : public gameNode
{
private:
	float _power;
	float _gravity;

	float* _x;
	float* _y;
	float _startX;
	float _startY;

	bool _isJumping;
	bool _isRightLeft;
	bool _stopJump;

public:
	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void jumping(float* x, float* y, float power, float gravity, bool isRightLeft, bool stopJump);

	bool getIsJumping(void) { return _isJumping; }
	bool setIsJumping(bool isJumping) { _isJumping = isJumping; }

	circusJump();
	virtual ~circusJump();
};

