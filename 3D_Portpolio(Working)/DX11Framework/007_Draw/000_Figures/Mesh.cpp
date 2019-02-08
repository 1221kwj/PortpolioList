#include "stdafx.h"
#include "Mesh.h"

Mesh::Mesh( Material* material )
	: pass			( 0 )
	, position		( 0.0f, 0.0f, 0.0f )
	, scale			( 1.0f, 1.0f, 1.0f )
	, rotation		( 0.0f, 0.0f, 0.0f )
	, vertices		( NULL )
	, indices		( NULL )
	, vertexBuffer	( NULL )
	, indexBuffer	( NULL )
	, material		( material )
{
	world = Math::IdentityMatrix();
}

Mesh::~Mesh()
{
	SAFE_DELETE_ARRAY( vertices );
	SAFE_DELETE_ARRAY( indices );

	SAFE_RELEASE( vertexBuffer );
	SAFE_RELEASE( indexBuffer );
}

void Mesh::Render()
{
	if ( vertexBuffer == NULL && indexBuffer == NULL )
	{
		CreateData();
		CreateBuffer();
	}

	UINT stride = sizeof( VTNT );
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers	( 0, 1, &vertexBuffer, &stride, &offset );
	D3D::GetDC()->IASetIndexBuffer		( indexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	D3D::GetDC()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	material->GetShader()->GetAsMatrix( "World" )->SetMatrix( &world._11 );
	material->GetShader()->DrawIndexed( 0, pass, indexCount );
}

void Mesh::CreateBuffer()
{
	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage		= D3D11_USAGE_DEFAULT;
		desc.ByteWidth	= sizeof( VTNT ) * vertexCount;
		desc.BindFlags	= D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = D3D::GetDevice()->CreateBuffer( &desc, &data, &vertexBuffer );
		assert( SUCCEEDED( hr ) );
	}

	//Create Index Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage		= D3D11_USAGE_DEFAULT;
		desc.ByteWidth	= sizeof( UINT ) * indexCount;
		desc.BindFlags	= D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = indices;

		HRESULT hr = D3D::GetDevice()->CreateBuffer( &desc, &data, &indexBuffer );
		assert( SUCCEEDED( hr ) );
	}
}

void Mesh::UpdateWorld()
{
	XMMATRIX S, R, T;
	S = XMMatrixScaling( scale.x, scale.y, scale.z );
	R = XMMatrixRotationRollPitchYaw( rotation.x, rotation.y, rotation.z );
	T = XMMatrixTranslation( position.x, position.y, position.z );

	XMStoreFloat4x4( &world, S * R * T );
}

void Mesh::SetScale( float x, float y, float z )
{
	SetScale( Vector3( x, y, z ) );
}

void Mesh::SetScale( Vector3 & scale )
{
	this->scale = scale;

	UpdateWorld();
}

void Mesh::GetScale( Vector3 * scale )
{
	*scale = this->scale;
}

void Mesh::SetRotation( float x, float y, float z )
{
	SetRotation( Vector3( x, y, z ) );
}

void Mesh::SetRotation( Vector3 & rotation )
{
	this->rotation = rotation;
}

void Mesh::GetRotation( Vector3 * rotation )
{
	*rotation = this->rotation;
}

void Mesh::SetRotationDegree( float x, float y, float z )
{
	SetRotationDegree( Vector3( x, y, z ) );
}

void Mesh::SetRotationDegree( Vector3 & rotation )
{
	this->rotation = Vector3
	(
		XMConvertToRadians( rotation.x ),
		XMConvertToRadians( rotation.y ),
		XMConvertToRadians( rotation.z )
	);
}

void Mesh::GetRotationDegree( Vector3 * rotation )
{
	*rotation = Vector3
	(
		XMConvertToDegrees( this->rotation.x ),
		XMConvertToDegrees( this->rotation.y ),
		XMConvertToDegrees( this->rotation.z )
	);
}

void Mesh::SetPosition( float x, float y, float z )
{
	SetPosition( Vector3( x, y, z ) );
}

void Mesh::SetPosition( Vector3 & position )
{
	this->position = position;

	UpdateWorld();
}

void Mesh::GetPosition( Vector3 * position )
{
	*position = this->position;
}

void Mesh::SetMatrix( XMFLOAT4X4 & mat )
{
	world = mat;
}

void Mesh::GetMatrix( XMFLOAT4X4 * mat )
{
	*mat = world;
}
