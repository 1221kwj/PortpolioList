#pragma once

class Mesh
{
public:
	Mesh( Material* material );
	virtual ~Mesh();

	void Render();

public:
	void SetScale( float x, float y, float z );
	void SetScale( Vector3& scale );
	void GetScale( Vector3* scale );

	void SetRotation( float x, float y, float z );
	void SetRotation( Vector3& rotation );
	void GetRotation( Vector3* rotation );

	void SetRotationDegree( float x, float y, float z );
	void SetRotationDegree( Vector3& rotation );
	void GetRotationDegree( Vector3* rotation );

	void SetPosition( float x, float y, float z );
	void SetPosition( Vector3& position );
	void GetPosition( Vector3* position );

	void SetMatrix( XMFLOAT4X4& mat );
	void GetMatrix( XMFLOAT4X4* mat );

	void SetPass( UINT val )	{ pass = val; }
	UINT GetPass()				{ return pass; }


protected:
	virtual void CreateData() = 0;
	void CreateBuffer();

	VTNT* vertices;
	UINT* indices;

	UINT vertexCount;
	UINT indexCount;

private:
	void UpdateWorld();

private:
	UINT			pass;

	Vector3			scale;
	Vector3			rotation;
	Vector3			position;

	Material*		material;
	XMFLOAT4X4		world;

	ID3D11Buffer*	vertexBuffer;
	ID3D11Buffer*	indexBuffer;

};