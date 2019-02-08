#include "stdafx.h"
#include "Frustum.h"
#include "Camera.h"
#include "Perspective.h"

Frustum::Frustum( float zFar, Camera * camera, Perspective * perspective )
	: zFar			( zFar )
	, camera		( camera )
	, perspective	( perspective )
{
	if ( camera == NULL )		this->camera		= Context::Get()->GetMainCamera();
	if ( perspective == NULL )	this->perspective	= Context::Get()->GetPerspective();
}

Frustum::~Frustum() {}

void Frustum::Update()
{
	XMFLOAT4X4 V, P;
	camera		->GetMatrix( &V );
	perspective	->GetMatrix( &P );

	XMMATRIX tempV, tempP;
	tempV = XMLoadFloat4x4( &V );
	tempP = XMLoadFloat4x4( &P );

	float zNear = -P._43 / P._33;
	float r		= zFar / ( zFar - zNear );

	P._33 = r;
	P._43 = -r * zNear;

	XMMATRIX matrix = tempV * tempP;
	XMVECTOR tempPlanes[ 6 ];
	
	//Near
	tempPlanes[ 0 ] = XMVectorSet
	(
		XMVectorGetW( matrix.r[ 0 ] ) + XMVectorGetZ( matrix.r[ 0 ] ),
		XMVectorGetW( matrix.r[ 1 ] ) + XMVectorGetZ( matrix.r[ 1 ] ),
		XMVectorGetW( matrix.r[ 2 ] ) + XMVectorGetZ( matrix.r[ 2 ] ),
		XMVectorGetW( matrix.r[ 3 ] ) + XMVectorGetZ( matrix.r[ 3 ] )
	);
	
	//Far
	tempPlanes[ 1 ] = XMVectorSet
	(
		XMVectorGetW( matrix.r[ 0 ] ) - XMVectorGetZ( matrix.r[ 0 ] ),
		XMVectorGetW( matrix.r[ 1 ] ) - XMVectorGetZ( matrix.r[ 1 ] ),
		XMVectorGetW( matrix.r[ 2 ] ) - XMVectorGetZ( matrix.r[ 2 ] ),
		XMVectorGetW( matrix.r[ 3 ] ) - XMVectorGetZ( matrix.r[ 3 ] )
	);
	
	//Left
	tempPlanes[ 2 ] = XMVectorSet
	(
		XMVectorGetW( matrix.r[ 0 ] ) + XMVectorGetX( matrix.r[ 0 ] ),
		XMVectorGetW( matrix.r[ 1 ] ) + XMVectorGetX( matrix.r[ 1 ] ),
		XMVectorGetW( matrix.r[ 2 ] ) + XMVectorGetX( matrix.r[ 2 ] ),
		XMVectorGetW( matrix.r[ 3 ] ) + XMVectorGetX( matrix.r[ 3 ] )
	);
	
	//Right
	tempPlanes[ 3 ] = XMVectorSet
	(
		XMVectorGetW( matrix.r[ 0 ] ) - XMVectorGetX( matrix.r[ 0 ] ),
		XMVectorGetW( matrix.r[ 1 ] ) - XMVectorGetX( matrix.r[ 1 ] ),
		XMVectorGetW( matrix.r[ 2 ] ) - XMVectorGetX( matrix.r[ 2 ] ),
		XMVectorGetW( matrix.r[ 3 ] ) - XMVectorGetX( matrix.r[ 3 ] )
	);

	//Top
	tempPlanes[ 4 ] = XMVectorSet
	(
		XMVectorGetW( matrix.r[ 0 ] ) - XMVectorGetY( matrix.r[ 0 ] ),
		XMVectorGetW( matrix.r[ 1 ] ) - XMVectorGetY( matrix.r[ 1 ] ),
		XMVectorGetW( matrix.r[ 2 ] ) - XMVectorGetY( matrix.r[ 2 ] ),
		XMVectorGetW( matrix.r[ 3 ] ) - XMVectorGetY( matrix.r[ 3 ] )
	);
	
	//Bottom
	tempPlanes[ 5 ] = XMVectorSet
	(
		XMVectorGetW( matrix.r[ 0 ] ) + XMVectorGetY( matrix.r[ 0 ] ),
		XMVectorGetW( matrix.r[ 1 ] ) + XMVectorGetY( matrix.r[ 1 ] ),
		XMVectorGetW( matrix.r[ 2 ] ) + XMVectorGetY( matrix.r[ 2 ] ),
		XMVectorGetW( matrix.r[ 3 ] ) + XMVectorGetY( matrix.r[ 3 ] )
	);

	for ( int i = 0; i < 6; i++ )
		tempPlanes[ i ] = XMVector4Normalize( tempPlanes[ i ] );

	for ( int i = 0; i < 6; i++ )
		XMStoreFloat4( &planes[ i ], tempPlanes[ i ] );
}

void Frustum::GetPlanes( OUT Vector4 * plane )
{
	XMFLOAT4X4 V, P, FM;
	camera		->GetMatrix( &V );
	perspective	->GetMatrix( &P );

	XMMATRIX XV, XP, M;
	XV	= XMLoadFloat4x4( &V );
	XP	= XMLoadFloat4x4( &P );
	M	= XMMatrixMultiply( XV, XP );
	
	XMStoreFloat4x4( &FM, M );
	
	XMVECTOR vPlane[ 6 ];

	// Left
	vPlane[ 0 ] = XMVectorSet
	(
		FM._14 + FM._11,
		FM._24 + FM._21,
		FM._34 + FM._31,
		FM._44 + FM._41
	);

	// Right
	vPlane[ 1 ] = XMVectorSet
	(
		FM._14 - FM._11,
		FM._24 - FM._21,
		FM._34 - FM._31,
		FM._44 - FM._41
	);
	
	// Bottom
	vPlane[ 2 ] = XMVectorSet
	(
		FM._14 + FM._12,
		FM._24 + FM._22,
		FM._34 + FM._32,
		FM._44 + FM._42
	);
	
	// Top
	vPlane[ 3 ] = XMVectorSet
	(
		FM._14 - FM._12,
		FM._24 - FM._22,
		FM._34 - FM._32,
		FM._44 - FM._42
	);

	// Near
	vPlane[ 4 ] = XMVectorSet
	(
		FM._13,
		FM._23,
		FM._33,
		FM._43
	);

	// Far
	vPlane[ 5 ] = XMVectorSet
	(
		FM._14 - FM._13,
		FM._24 - FM._23,
		FM._34 - FM._33,
		FM._44 - FM._43
	);

	for ( int i = 0; i < 6; i++ )
		vPlane[ i ] = XMVector4Normalize( vPlane[ i ] );

	for ( int i = 0; i < 6; i++ )
		XMStoreFloat4( &plane[ i ], vPlane[ i ] );
}

bool Frustum::ContainPoint( Vector3 & position )
{
	XMVECTOR pos = XMLoadFloat3( &position );

	for ( int i = 0; i < 6; i++ )
	{
		XMVECTOR plane = XMLoadFloat4( &planes[ i ] );
		if ( XMVectorGetX( XMPlaneDotCoord( plane, pos ) ) < 0.0f )
			return false;
	}

	return true;
}

bool Frustum::ContainRect( float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize )
{
	for ( int i = 0; i< 6; i++ )
	{
		XMVECTOR tempPlane	= XMVectorZero();
		XMVECTOR tempVector = XMVectorZero();

		tempPlane	= XMLoadFloat4( &planes[ i ] );

		tempVector	= XMVectorSet( xCenter - xSize, yCenter - ySize, zCenter - zSize, 1.0f );
		if ( XMVectorGetX( XMPlaneDotCoord( tempPlane, tempVector ) ) >= 0.0f ) continue;

		tempVector	= XMVectorSet( xCenter + xSize , yCenter - ySize, zCenter - zSize, 1.0f );
		if ( XMVectorGetX( XMPlaneDotCoord( tempPlane, tempVector ) ) >= 0.0f ) continue;
		
		tempVector	= XMVectorSet( xCenter - xSize, yCenter + ySize, zCenter - zSize, 1.0f );
		if ( XMVectorGetX( XMPlaneDotCoord( tempPlane, tempVector ) ) >= 0.0f ) continue;

		tempVector	= XMVectorSet( xCenter - xSize, yCenter - ySize, zCenter + zSize, 1.0f );
		if ( XMVectorGetX( XMPlaneDotCoord( tempPlane, tempVector ) ) >= 0.0f ) continue;

		tempVector	= XMVectorSet( xCenter + xSize, yCenter + ySize, zCenter - zSize, 1.0f );
		if ( XMVectorGetX( XMPlaneDotCoord( tempPlane, tempVector ) ) >= 0.0f ) continue;
		
		tempVector	= XMVectorSet( xCenter + xSize, yCenter - ySize, zCenter + zSize, 1.0f );
		if ( XMVectorGetX( XMPlaneDotCoord( tempPlane, tempVector ) ) >= 0.0f ) continue;

		tempVector	= XMVectorSet( xCenter - xSize, yCenter + ySize, zCenter + zSize, 1.0f );
		if ( XMVectorGetX( XMPlaneDotCoord( tempPlane, tempVector ) ) >= 0.0f ) continue;
		
		tempVector	= XMVectorSet( xCenter + xSize, yCenter + ySize, zCenter + zSize, 1.0f );
		if ( XMVectorGetX( XMPlaneDotCoord( tempPlane, tempVector ) ) >= 0.0f ) continue;

		return false;
	}

	return true;
}

bool Frustum::ContainRect( Vector3 center, Vector3 size )
{
	return ContainRect( center.x, center.y, center.z, size.x, size.y, size.z );
}

bool Frustum::ContainCube( Vector3 & center, float radius )
{
	for ( int i = 0; i < 6; i++ )
	{
		XMVECTOR plane = XMLoadFloat4( &planes[ i ] );
		XMVECTOR check = XMVectorZero();

		check = XMVectorSet( center.x - radius, center.y - radius, center.z - radius, 1.0f );
		if ( XMVectorGetX( XMPlaneDotCoord( plane, check ) ) >= 0.0f ) continue;

		check = XMVectorSet( center.x + radius, center.y - radius, center.z - radius, 1.0f );
		if ( XMVectorGetX( XMPlaneDotCoord( plane, check ) ) >= 0.0f ) continue;

		check = XMVectorSet( center.x - radius, center.y + radius, center.z - radius, 1.0f );
		if ( XMVectorGetX( XMPlaneDotCoord( plane, check ) ) >= 0.0f ) continue;

		check = XMVectorSet( center.x + radius, center.y + radius, center.z - radius, 1.0f );
		if ( XMVectorGetX( XMPlaneDotCoord( plane, check ) ) >= 0.0f ) continue;

		check = XMVectorSet( center.x - radius, center.y - radius, center.z + radius, 1.0f );
		if ( XMVectorGetX( XMPlaneDotCoord( plane, check ) ) >= 0.0f ) continue;

		check = XMVectorSet( center.x + radius, center.y - radius, center.z + radius, 1.0f );
		if ( XMVectorGetX( XMPlaneDotCoord( plane, check ) ) >= 0.0f ) continue;
		
		check = XMVectorSet( center.x - radius, center.y + radius, center.z + radius, 1.0f );
		if ( XMVectorGetX( XMPlaneDotCoord( plane, check ) ) >= 0.0f ) continue;
		
		check = XMVectorSet( center.x + radius, center.y + radius, center.z + radius, 1.0f );
		if ( XMVectorGetX( XMPlaneDotCoord( plane, check ) ) >= 0.0f ) continue;
		
		return false;
	}

	return true;
}
