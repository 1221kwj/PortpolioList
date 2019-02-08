#include "stdafx.h"
#include "GameRender.h"

GameRender::GameRender()
	: enable	( true )
	, visible	( true )
	, position	( 0.0f, 0.0f, 0.0f )
	, scale		( 1.0f, 1.0f, 1.0f )
	, rotation	( 0.0f, 0.0f, 0.0f )
	, direction	( 0.0f, 0.0f, 1.0f )
	, up		( 0.0f, 1.0f, 0.0f )
	, right		( 1.0f, 0.0f, 0.0f )
{
	rootAxis	= Math::IdentityMatrix();
	world		= Math::IdentityMatrix();
}

GameRender::~GameRender() {}

void GameRender::SetEnable( bool val )
{
	enable = val;

	for ( auto temp : Enabled )
		temp( val );
}

bool GameRender::GetEnable()
{
	return enable;
}

void GameRender::SetVisible( bool val )
{
	visible = val;

	for ( auto temp : Visibled )
		temp( val );
}

bool GameRender::GetVisible()
{
	return visible;
}

void GameRender::SetRootAxis( XMFLOAT4X4 & matrix ) 
{ 
	rootAxis = matrix;
}

void GameRender::SetRootAxisDegree( Vector3 & rotation )
{
	XMMATRIX r = XMMatrixRotationRollPitchYaw( rotation.x, rotation.y, rotation.z  );

	XMStoreFloat4x4( &rootAxis, r );
}

void GameRender::SetRootAxisRadian( Vector3 & rotation )
{
	XMMATRIX r = XMMatrixRotationRollPitchYaw( rotation.x, rotation.y, rotation.z );

	XMStoreFloat4x4( &rootAxis, r );
}

void GameRender::GetRootAxis( XMFLOAT4X4* matrix )
{ 
	*matrix = rootAxis;
}

void GameRender::GetWorld( XMFLOAT4X4* matrix )
{ 
	*matrix = world;
}

void GameRender::SetPosition( Vector3 & vec )
{
	position = vec;

	UpdateWorld();
}

void GameRender::SetPosition( float x, float y, float z ) 
{
	SetPosition( Vector3( x, y, z ) );
}

void GameRender::GetPosition( Vector3* vec )
{
	*vec = position;
}

void GameRender::SetScale( Vector3 & vec )
{
	scale = vec;

	UpdateWorld();
}

void GameRender::SetScale( float x, float y, float z )
{
	SetScale( Vector3( x, y, z ) );
}

void GameRender::GetScale( Vector3* vec )
{
	*vec = scale;
}

void GameRender::SetRotation( Vector3 & vec )
{
	rotation = vec;

	UpdateWorld();
}

void GameRender::SetRotation( float x, float y, float z )
{
	SetRotation( Vector3( x, y, z ) );
}

void GameRender::SetRotationDegree( Vector3 & vec )
{
	Vector3 temp = Vector3
	(
		XMConvertToRadians( vec.x ),
		XMConvertToRadians( vec.y ),
		XMConvertToRadians( vec.z )
	);

	SetRotation( temp );
}

void GameRender::SetRotationDegree( float x, float y, float z )
{
	SetRotationDegree( Vector3( x, y, z ) );
}

void GameRender::GetRotation( Vector3* vec )
{
	*vec = rotation;
}

void GameRender::GetRotationDegree( Vector3* vec )
{
	*vec = Vector3
	(
		XMConvertToDegrees( rotation.x ),
		XMConvertToDegrees( rotation.y ),
		XMConvertToDegrees( rotation.z )
	);
}

void GameRender::GetDirection( Vector3* vec )
{
	*vec = direction;
}

void GameRender::GetUp( Vector3* vec )
{
	*vec = up;
}

void GameRender::GetRight( Vector3* vec )
{
	*vec = right;
}

void GameRender::GetTransformed( XMFLOAT4X4* matrix )
{
	XMMATRIX r = XMLoadFloat4x4( &rootAxis );
	XMMATRIX w = XMLoadFloat4x4( &world );
	XMMATRIX m = r * w;
	
	XMStoreFloat4x4( matrix, m );
}

void GameRender::Update()
{
}

void GameRender::Render()
{
}

void GameRender::UpdateWorld()
{
	XMMATRIX S = XMMatrixScaling				( scale.x	, scale.y	, scale.z	 );
	XMMATRIX R = XMMatrixRotationRollPitchYaw	( rotation.x, rotation.y, rotation.z );
	XMMATRIX T = XMMatrixTranslation			( position.x, position.y, position.z );

	XMStoreFloat4x4( &world, S * R * T );

	direction	= Vector3( world._31, world._32, world._33 );
	up			= Vector3( world._21, world._22, world._23 );
	right		= Vector3( world._11, world._12, world._13 );
}
