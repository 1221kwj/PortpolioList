#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
	: position	( 0.0f, 0.0f, 0.0f )
	, rotation	( 0.0f, 0.0f )
	, forward	( 0.0f, 0.0f, 1.0f )
	, right		( 1.0f, 0.0f, 0.0f )
	, up		( 0.0f, 1.0f, 0.0f )

{
	matRotation = Math::IdentityMatrix();
	matView		= Math::IdentityMatrix();

	Move();
	Rotation();
}

Camera::~Camera()
{
}

Vector3 Camera::Direction( Viewport * vp, Perspective * perspective )
{
	Vector2 screenSize	( 0.0f, 0.0f );
	Vector2 point		( 0.0f, 0.0f );
	Vector3 mouse		( 0.0f, 0.0f, 0.0f );
	Vector3 dir			( 0.0f, 0.0f, 0.0f );
	
	screenSize.x = vp->GetWidth();
	screenSize.y = vp->GetHeight();

	Mouse::Get()->GetPosition( &mouse );
	
	//Inv Viewport
	{
		point.x = ( ( 2.0f * mouse.x ) / screenSize.x ) - 1.0f;
		point.y = ( ( ( 2.0f * mouse.y ) / screenSize.y ) - 1.0f ) * -1.0f;
	}

	//Inv Projection
	{
		XMFLOAT4X4 projection;
		perspective->GetMatrix( &projection );

		point.x = point.x / projection._11;
		point.y = point.y / projection._22;
	}

	//Inv View
	{
		XMVECTOR tempDir	= XMVectorZero();
		XMMATRIX tempMat	= XMLoadFloat4x4( &matView );
		XMMATRIX invView	= XMMatrixInverse( NULL, tempMat );
		
		tempDir = XMVector3TransformNormal( XMVectorSet( point.x, point.y, 1.0f, 1.0f ), invView );
		tempDir = XMVector3Normalize( tempDir );

		XMStoreFloat3( &dir, tempDir );
	}

	return dir;
}

void Camera::Move()
{
	View();
}

void Camera::Rotation()
{
	XMMATRIX X, Y, temp;
	X = XMMatrixRotationX( rotation.x );
	Y = XMMatrixRotationY( rotation.y );

	temp = X * Y;
	
	XMVECTOR originF = XMVectorSet( 0.0f, 0.0f, 1.0f, 0.0f );
	XMVECTOR originR = XMVectorSet( 1.0f, 0.0f, 0.0f, 0.0f );
	XMVECTOR originU = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
	
	XMVECTOR tempF, tempR, tempU;
	tempF = XMVector3TransformNormal( originF, temp );
	tempR = XMVector3TransformNormal( originR, temp );
	tempU = XMVector3TransformNormal( originU, temp );

	XMStoreFloat3( &forward	, tempF );
	XMStoreFloat3( &right	, tempR );
	XMStoreFloat3( &up		, tempU );
}

void Camera::View()
{
	XMVECTOR eyePosition	= XMLoadFloat3( &position );
	XMVECTOR focusPosition	= XMLoadFloat3( &( position + forward ) );
	XMVECTOR upVector		= XMLoadFloat3( &up );
	XMMATRIX temp			= XMMatrixLookAtLH( eyePosition, focusPosition, upVector );

	XMStoreFloat4x4( &matView, temp );
}
