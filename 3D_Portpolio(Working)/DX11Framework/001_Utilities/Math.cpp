#include "stdafx.h"
#include "Math.h"

const float Math::EPSILON	= 0.000001f;

float Math::Modulo( float val1, float val2 )
{
	while ( val1 - val2 >= 0 )
		val1 -= val2;

	return val1;
}

float Math::ToRadian( float degree ) 
{ 
	return degree * XM_PI / 180.0f;
}

float Math::ToDegree( float radian )
{ 
	return radian * 180.0f / XM_PI;
}

int Math::Random( int r1, int r2 )
{
	return ( int )( rand() % ( r2 - r1 + 1 ) ) + r1;
}

float Math::Random( float r1, float r2 )
{
	float random = ( ( float )rand() ) / ( float )RAND_MAX;
	float diff = r2 - r1;
	float val = random * diff;

	return r1 + val;
}

float Math::Clamp( float value, float min, float max )
{
	value = value > max ? max : value;
	value = value < min ? min : value;

	return value;
}

void Math::toEulerAngle( const Vector4 & q, float & pitch, float & yaw, float & roll )
{
	// pitch (x-axis rotation)
	float sinr = +2.0f * ( q.w * q.x + q.y * q.z );
	float cosr = +1.0f - 2.0f * ( q.x * q.x + q.y * q.y );
	pitch = atan2f( sinr, cosr );

	// yaw (y-axis rotation)
	float sinp = +2.0f * ( q.w * q.y - q.z * q.x );
	if ( fabs( sinp ) >= 1 )
		yaw = ( float )copysign( XM_PI / 2.0f, sinp ); // use 90 degrees if out of range
	else
		yaw = asinf( sinp );

	// roll (z-axis rotation)
	float siny = +2.0f * ( q.w * q.z + q.x * q.y );
	float cosy = +1.0f - 2.0f * ( q.y * q.y + q.z * q.z );
	roll = atan2f( siny, cosy );
}

void Math::toEulerAngle( const Vector4 & q, Vector3 & out )
{
	toEulerAngle( q, out.x, out.y, out.z );
}

Vector3 Math::QuaternionToEuler( XMVECTOR q )
{
	float q0 = XMVectorGetW( q );
	float q1 = XMVectorGetY( q );
	float q2 = XMVectorGetX( q );
	float q3 = XMVectorGetZ( q );

	Vector3 vec3 = Vector3::Zero();
	
	// X - Axis Rotation
	float sinr = 2.0f * ( q0 * q2 + q1 * q3 );
	float cosr = 1.0f - 2.0f * ( q2 * q2 + q1 * q1 );
	vec3.x = atan2f( sinr, cosr );

	// Y - Axis Rotation
	float sinp = +2.0f * ( q0 * q1 - q3 * q2 );
	if ( fabs( sinp ) >= 1 )
	{
		// use 90 degrees if out of range
		vec3.y = ( float )copysign( XM_PI / 2.0f, sinp ); 
	}
	else
	{
		vec3.y = asinf( sinp );
	}

	// Z - Axis Rotation
	float siny = +2.0f * ( q0 * q3 + q2 * q1 );
	float cosy = +1.0f - 2.0f * ( q1 * q1 + q3 * q3 );
	vec3.z = atan2f( siny, cosy );

	return vec3;
}

Vector4 Math::LookAt( const Vector3 & origin, const Vector3 & target, const Vector3 & up )
{
	XMVECTOR tempO	= XMLoadFloat3( &origin );
	XMVECTOR tempT	= XMLoadFloat3( &target );
	XMVECTOR tempU	= XMLoadFloat3( &up );
	XMVECTOR f		= XMVectorSubtract( tempO, tempT );
	
	f = XMVector3Normalize( f );

	XMVECTOR s = XMVector3Cross( tempU, f );
	s = XMVector3Normalize( s );

	XMVECTOR u = XMVector3Cross( f, s );

	float zz = 1.0f + XMVectorGetX( s ) + XMVectorGetY( u ) + XMVectorGetZ( f );
	float fd = 2.0f * sqrtf( zz );

	Vector4 result = Vector4::Zero();

	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;

	if ( zz > Math::EPSILON )
	{
		result.w = 0.25f * fd;
		result.x = ( XMVectorGetY( f ) - XMVectorGetZ( u ) ) / fd;
		result.y = ( XMVectorGetZ( s ) - XMVectorGetX( f ) ) / fd;
		result.z = ( XMVectorGetX( u ) - XMVectorGetY( s ) ) / fd;
	}
	else if ( XMVectorGetX( s ) > XMVectorGetY( u ) && XMVectorGetX( s ) > XMVectorGetZ( f ) )
	{
		fd = 2.0f * sqrtf( 1.0f + XMVectorGetX( s ) - XMVectorGetY( u ) - XMVectorGetZ( f ) );
		
		result.w = ( XMVectorGetY( f ) - XMVectorGetZ( u ) ) / fd;
		result.x = 0.25f * fd;
		result.y = ( XMVectorGetX( u ) + XMVectorGetY( s ) ) / fd;
		result.z = ( XMVectorGetZ( s ) + XMVectorGetX( f ) ) / fd;
	}
	else if ( XMVectorGetY( u ) > XMVectorGetZ( f ) )
	{
		fd = 2.0f * sqrtf( 1.0f + XMVectorGetY( u ) - XMVectorGetX( s ) - XMVectorGetZ( f ) );
		
		result.w = ( XMVectorGetZ( s ) - XMVectorGetX( f ) ) / fd;
		result.x = ( XMVectorGetX( u ) - XMVectorGetY( s ) ) / fd;
		result.y = 0.25f * fd;
		result.z = ( XMVectorGetY( f ) + XMVectorGetZ( u ) ) / fd;
	}
	else
	{
		fd = 2.0f * sqrtf( 1.0f + XMVectorGetZ( f ) - XMVectorGetX( s ) - XMVectorGetY( u ) );
		
		result.w = ( XMVectorGetX( u ) - XMVectorGetY( s ) ) / fd;
		result.x = ( XMVectorGetZ( s ) + XMVectorGetX( f ) ) / fd;
		result.y = ( XMVectorGetY( f ) + XMVectorGetZ( u ) ) / fd;
		result.z = 0.25f * fd;
	}

	return result;
}

void Math::LerpMatrix( OUT XMFLOAT4X4& out, const XMFLOAT4X4& m1, const XMFLOAT4X4& m2, float amount )
{
	out._11 = m1._11 + ( m2._11 - m1._11 ) * amount;
	out._12 = m1._12 + ( m2._12 - m1._12 ) * amount;
	out._13 = m1._13 + ( m2._13 - m1._13 ) * amount;
	out._14 = m1._14 + ( m2._14 - m1._14 ) * amount;

	out._21 = m1._21 + ( m2._21 - m1._21 ) * amount;
	out._22 = m1._22 + ( m2._21 - m1._22 ) * amount;
	out._23 = m1._23 + ( m2._21 - m1._23 ) * amount;
	out._24 = m1._24 + ( m2._21 - m1._24 ) * amount;

	out._31 = m1._31 + ( m2._31 - m1._31 ) * amount;
	out._32 = m1._32 + ( m2._31 - m1._32 ) * amount;
	out._33 = m1._33 + ( m2._31 - m1._33 ) * amount;
	out._34 = m1._34 + ( m2._31 - m1._34 ) * amount;

	out._41 = m1._41 + ( m2._41 - m1._41 ) * amount;
	out._42 = m1._42 + ( m2._42 - m1._42 ) * amount;
	out._43 = m1._43 + ( m2._43 - m1._43 ) * amount;
	out._44 = m1._44 + ( m2._44 - m1._44 ) * amount;
}

XMFLOAT4X4 Math::IdentityMatrix()
{
	XMFLOAT4X4	iden;
	XMMATRIX	temp = XMMatrixIdentity();

	XMStoreFloat4x4( &iden, temp );
	
	return iden;
}