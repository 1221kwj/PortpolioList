#pragma once
// ================================================================================================
//											2D VECTOR
// ================================================================================================
struct Vector2 : public XMFLOAT2
{
public:
	Vector2() {};
	Vector2( CONST FLOAT* pf ) 
	{
		#ifdef D3DX10_DEBUG
				if ( !pf ) return;
		#endif
		x = pf[ 0 ];
		y = pf[ 1 ];
	}

	Vector2( CONST XMFLOAT2& other )					{ x = other.x	; y = other.y	; }
	Vector2( FLOAT _x, FLOAT _y )						{ x = _x		; y = _y		; }

	operator FLOAT* ()									{ return ( FLOAT* )&x; }
	operator CONST FLOAT* () const						{ return ( CONST FLOAT* )&x; }

	Vector2& operator += ( CONST Vector2& other )		{ x += other.x	; y += other.y	; return *this; }
	Vector2& operator -= ( CONST Vector2& other )		{ x -= other.x	; y -= other.y	; return *this; }
	Vector2& operator *= ( FLOAT other )				{ x *= other	; y *= other	; return *this; }
	Vector2& operator /= ( FLOAT other )				{ FLOAT inv = 1.0f / other; x *= inv; y *= inv; return *this; }

	Vector2 operator + () const							{ return *this; }
	Vector2 operator - () const							{ return Vector2( -x, -y ); }

	Vector2 operator + ( const Vector2& other )	const	{ return Vector2( x + other.x, y + other.y ); }
	Vector2 operator - ( const Vector2& other )	const	{ return Vector2( x - other.x, y - other.y ); }
	Vector2 operator * ( FLOAT other ) const			{ return Vector2( x * other, y * other ); }
	Vector2 operator / ( FLOAT other ) const			{ FLOAT inv = 1.0f / other;  return Vector2( x * inv, y * inv ); }

	BOOL operator == ( const Vector2& other ) const		{ return x == other.x && y == other.y; }
	BOOL operator != ( const Vector2& other ) const		{ return x != other.x && y != other.y; }

	static Vector2 Zero()								{ return Vector2( 0.0f, 0.0f ); }
};

// ================================================================================================
//											3D VECTOR
// ================================================================================================
struct Vector3 : public XMFLOAT3
{
public:
	Vector3() {};
	Vector3( CONST FLOAT* pf )
	{
		#ifdef D3DX10_DEBUG
				if ( !pf ) return;
		#endif
				x = pf[ 0 ];
				y = pf[ 1 ];
				z = pf[ 2 ];
	}

	Vector3( CONST XMFLOAT3& other )					{ x = other.x	; y = other.y	; z = other.z	; }
	Vector3( FLOAT _x, FLOAT _y, FLOAT _z )				{ x = _x		; y = _y		; z = _z		; };

	operator FLOAT* ( )									{ return ( FLOAT* )&x; }
	operator CONST FLOAT* ( ) const						{ return ( CONST FLOAT* )&x; }

	Vector3& operator += ( CONST Vector3& other )		{ x += other.x	; y += other.y	; z += other.z	; return *this; }
	Vector3& operator -= ( CONST Vector3& other )		{ x -= other.x	; y -= other.y	; z -= other.z	; return *this; }
	Vector3& operator *= ( FLOAT other )				{ x *= other	; y *= other	; z *= other	; return *this; }
	Vector3& operator /= ( FLOAT other )				{ FLOAT inv = 1.0f / other; x *= inv; y *= inv; z *= inv; return *this; }

	Vector3 operator + () const							{ return *this; }
	Vector3 operator - () const							{ return Vector3( -x, -y, -z ); }

	Vector3 operator + ( const Vector3& other )	const	{ return Vector3( x + other.x, y + other.y, z + other.z ); }
	Vector3 operator - ( const Vector3& other )	const	{ return Vector3( x - other.x, y - other.y, z - other.z ); }
	Vector3 operator * ( FLOAT other ) const			{ return Vector3( x * other, y * other, z * other ); }
	Vector3 operator / ( FLOAT other ) const			{ FLOAT inv = 1.0f / other;  return Vector3( x * inv, y * inv, z * inv ); }

	BOOL operator == ( const Vector3& other ) const		{ return x == other.x && y == other.y && z == other.z; }
	BOOL operator != ( const Vector3& other ) const		{ return x != other.x && y != other.y && z != other.z; }

	static Vector3 Zero()								{ return Vector3( 0.0f, 0.0f, 0.0f ); }
};

// ================================================================================================
//											4D VECTOR
// ================================================================================================
struct Vector4 : public XMFLOAT4
{
public:
	Vector4() {}
	Vector4( CONST FLOAT* pf )
	{
		#ifdef D3DX10_DEBUG
				if ( !pf ) return;
		#endif
				x = pf[ 0 ];
				y = pf[ 1 ];
				z = pf[ 2 ];
				w = pf[ 3 ];
	}
	Vector4( CONST XMFLOAT4& other )					{ x = other.x	; y = other.y	; z = other.z	; w = other.w	; }
	Vector4( FLOAT _x, FLOAT _y, FLOAT _z, FLOAT _w )	{ x = _x		; y = _y		; z = _z		; w = _w		; };

	operator FLOAT* ( )									{ return ( FLOAT* )&x; }
	operator CONST FLOAT* ( ) const						{ return ( CONST FLOAT* )&x; }

	Vector4& operator += ( CONST Vector4& other ) 		{ x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
	Vector4& operator -= ( CONST Vector4& other ) 		{ x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
	Vector4& operator *= ( FLOAT other ) 				{ x *= other; y *= other; z *= other; w *= other; return *this; }
	Vector4& operator /= ( FLOAT other ) 				{ FLOAT inv = 1.0f / other; x *= inv; y *= inv; z *= inv; w *= inv; return *this; }

	Vector4 operator + ()								{ return *this; }
	Vector4 operator - ()								{ return Vector4( -x, -y, -z, -w ); }

	Vector4 operator + ( CONST Vector4& other ) const	{ return Vector4( x + other.x, y + other.y, z + other.z, w + other.w ); }
	Vector4 operator - ( CONST Vector4& other ) const	{ return Vector4( x - other.x, y - other.y, z - other.z, w - other.w ); }
	Vector4 operator * ( FLOAT other )					{ return Vector4( x * other, y * other, z * other, w * other ); }
	Vector4 operator / ( FLOAT other )					{ FLOAT inv = 1.0f / other;  return Vector4( x * inv, y * inv, z * inv, w * inv ); }

	BOOL operator == ( const Vector4& other ) const		{ return x == other.x && y == other.y && z == other.z && w == other.w; }
	BOOL operator != ( const Vector4& other ) const		{ return x != other.x && y != other.y && z != other.z && w != other.w; }

	static Vector4 Zero()								{ return Vector4( 0.0f, 0.0f, 0.0f, 0.0f ); }
	static Vector4 ColorZero()							{ return Vector4( 0.0f, 0.0f, 0.0f, 1.0f ); }
};