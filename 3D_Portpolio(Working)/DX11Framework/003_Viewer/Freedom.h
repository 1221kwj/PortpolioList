#pragma once
#include "Camera.h"

class Freedom : public Camera
{
public:
	Freedom( float moveSpeed = 20.0f, float rotationSpeed = 2.5f );
	~Freedom();

	void Update();

	void SetMoveSpeed( float speed )		{ moveSpeed		= speed; }
	void SetRotationSpeed( float speed )	{ rotationSpeed = speed; }

private:
	float moveSpeed;
	float rotationSpeed;
};