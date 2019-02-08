#include "stdafx.h"
#include "Perspective.h"

Perspective::Perspective( float width, float height, float fov, float zn, float zf )
{
	Set( width, height, fov, zn, zf );
}

Perspective::~Perspective()
{
}

void Perspective::GetMatrix( XMFLOAT4X4 * mat )
{
	memcpy( mat, &projection, sizeof( XMFLOAT4X4 ) );
}

void Perspective::Set( float width, float height, float fov, float zn, float zf )
{
	this->width		= width;
	this->height	= height;
	this->fov		= fov;
	this->aspect	= width / height;
	this->zn		= zn;
	this->zf		= zf;

	XMMATRIX temp	= XMMatrixPerspectiveFovLH( fov, aspect, zn, zf );

	XMStoreFloat4x4( &projection, temp );
}
