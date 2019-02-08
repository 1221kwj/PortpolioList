#pragma once

class BinaryWriter
{
public:
	BinaryWriter();
	~BinaryWriter();

	void Open( wstring filePath, UINT openOption = CREATE_ALWAYS );
	void Close();

	void Bool	( bool data );
	void Word	( WORD data );
	void Int	( int data );
	void UInt	( UINT data );
	void Float	( float data );
	void Double	( double data );

	void Vec2( const Vector2& data );
	void Vec3( const Vector3& data );
	void Vec4( const Vector4& data );
	void Color3f( const Vector4& data );
	void Color4f( const Vector4& data );
	void Matrix	( const XMFLOAT4X4& data );

	void String	( const string& data );
	void Byte	( void* data, UINT dataSize );

protected:
	HANDLE fileHandle;
	DWORD size;
};

//////////////////////////////////////////////////////////////////////////

class BinaryReader
{
public:
	BinaryReader();
	~BinaryReader();

	void	Open( wstring filePath );
	void	Close();

	bool Bool();
	WORD Word();
	int	Int();
	UINT UInt();
	float Float();
	double Double();

	Vector2	Vec2();
	Vector3	Vec3();
	Vector4	Vec4();
	Vector4	Color3f();
	Vector4	Color4f();
	XMFLOAT4X4 Matrix();

	string String();
	void Byte( void** data, UINT dataSize );

protected:
	HANDLE	fileHandle;
	DWORD	size;
};