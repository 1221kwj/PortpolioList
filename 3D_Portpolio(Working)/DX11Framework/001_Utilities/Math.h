#pragma once

class Math
{
public:
	static const float EPSILON;

	static float Modulo( float val1, float val2 );

	static float ToRadian( float degree );
	static float ToDegree( float radian );

	static int Random( int r1, int r2 );
	static float Random( float r1, float r2 );

	static float Clamp( float value, float min, float max );

	static void toEulerAngle( const Vector4& q, float& pitch, float& yaw, float& roll );
	static void toEulerAngle( const Vector4& q, Vector3& out );

	static Vector3 QuaternionToEuler( XMVECTOR q );
	
	static Vector4 LookAt( const Vector3& origin, const Vector3& target, const Vector3& up );

	static void LerpMatrix( OUT XMFLOAT4X4& out, const XMFLOAT4X4& m1, const XMFLOAT4X4& m2, float amount );

	static XMFLOAT4X4 IdentityMatrix();
};