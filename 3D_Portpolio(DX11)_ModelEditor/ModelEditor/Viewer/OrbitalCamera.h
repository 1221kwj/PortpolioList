#pragma once
#include "Camera.h"

class OrbitalCamera : public Camera
{
public:
	OrbitalCamera( float moveSpeed = 20, float rotationSpeed = 2.5f );
	~OrbitalCamera();

	void Update();

private:
	float moveSpeed;
	float rotationSpeed;
};