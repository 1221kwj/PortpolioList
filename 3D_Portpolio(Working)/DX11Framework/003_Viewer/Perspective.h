#pragma once

class Perspective
{
public:
	Perspective
	( 
		float width,
		float height,
		float fov	= XM_PI * 0.25f,
		float zn	= 0.1f,
		float zf	= 1000.0f
	);
	~Perspective();

	void GetMatrix( XMFLOAT4X4* mat );
	void Set
	( 
		float width,
		float height,
		float fov	= XM_PI * 0.25f,
		float zn	= 0.1f,
		float zf	= 1000.0f
	);

private:
	float		width, height;
	float		fov;
	float		aspect;
	float		zn, zf;

	XMFLOAT4X4	projection;
};