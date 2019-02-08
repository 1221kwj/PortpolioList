#include "stdafx.h"
#include "Render2D.h"

Render2D::Render2D( wstring shaderFile )
	: position	( 0.0f, 0.0f )
	, scale		( 0.0f, 0.0f )
{
	String::Replace( &shaderFile, Shaders, L"" );

	wstring file = L"";
	
	if ( shaderFile.length() > 1 )
	{
		file = Shaders + shaderFile;
	}
	else
	{
		file = Shaders + L"055_Render2D.fx";
	}

	shader = new Shader( file, true );

	//Create Ortho Matrix
	{
		D3DDesc desc;
		D3D::GetDesc( &desc );

		XMMATRIX orthoMat = XMMatrixOrthographicOffCenterLH
		(
			0, desc.Width, 0, desc.Height, -1, 1
		);
		
		XMStoreFloat4x4( &orthographic, orthoMat );
	}

	//Create Vertex Buffer
	{
		VertexTexture* vertices = new VertexTexture[ 6 ];
		vertices[ 0 ].Position = Vector3( -0.5f, -0.5f, 0.0f );
		vertices[ 1 ].Position = Vector3( -0.5f,  0.5f, 0.0f );
		vertices[ 2 ].Position = Vector3(  0.5f, -0.5f, 0.0f );
		vertices[ 3 ].Position = Vector3(  0.5f, -0.5f, 0.0f );
		vertices[ 4 ].Position = Vector3( -0.5f,  0.5f, 0.0f );
		vertices[ 5 ].Position = Vector3(  0.5f,  0.5f, 0.0f );

		vertices[ 0 ].Uv = Vector2( 0.0f, 1.0f );
		vertices[ 1 ].Uv = Vector2( 0.0f, 0.0f );
		vertices[ 2 ].Uv = Vector2( 1.0f, 1.0f );
		vertices[ 3 ].Uv = Vector2( 1.0f, 1.0f );
		vertices[ 4 ].Uv = Vector2( 0.0f, 0.0f );
		vertices[ 5 ].Uv = Vector2( 1.0f, 0.0f );


		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage		= D3D11_USAGE_DEFAULT;
		desc.ByteWidth	= sizeof( VertexTexture ) * 6;
		desc.BindFlags	= D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = D3D::GetDevice()->CreateBuffer( &desc, &data, &vertexBuffer );
		assert( SUCCEEDED( hr ) );

		SAFE_DELETE_ARRAY( vertices );
	}
	
	XMMATRIX viewMat = XMMatrixLookAtLH
	(
		XMLoadFloat3( &( Vector3( 0.0f, 0.0f, -1.0f ) ) ),
		XMLoadFloat3( &( Vector3( 0.0f, 0.0f,  0.0f ) ) ),
		XMLoadFloat3( &( Vector3( 0.0f, 1.0f,  0.0f ) ) )
	);

	XMStoreFloat4x4( &view, viewMat );

	shader->GetAsMatrix( "View" )		->SetMatrix( &view._11 );
	shader->GetAsMatrix( "Projection" )	->SetMatrix( &orthographic._11 );

	UpdateWorld();
}

Render2D::~Render2D()
{
	SAFE_DELETE( shader );

	SAFE_RELEASE( vertexBuffer );
}

void Render2D::SetPosition( float x, float y )
{
	SetPosition( Vector2( x, y ) );
}

void Render2D::SetPosition( Vector2 vec )
{
	position = vec;

	UpdateWorld();
}

void Render2D::SetScale( float x, float y )
{
	SetScale( Vector2( x, y ) );
}

void Render2D::SetScale( Vector2 vec )
{
	scale = vec;

	UpdateWorld();
}

void Render2D::Update()
{
}

void Render2D::Render()
{
	UINT stride = sizeof( VertexTexture );
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers( 0, 1, &vertexBuffer, &stride, &offset );
	D3D::GetDC()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	shader->Draw( 0, 0, 6 );
}

void Render2D::SRV( ID3D11ShaderResourceView * srv )
{
	shader->GetAsShaderResource( "Map" )->SetResource( srv );
}

void Render2D::UpdateWorld()
{
	XMMATRIX S, T, W;
	S = XMMatrixScaling( scale.x, scale.y, 1.0f );
	T = XMMatrixTranslation
	(
		position.x + scale.x * 0.5f,
		position.y + scale.y * 0.5f,
		0
	);

	W = S * T;

	XMFLOAT4X4 worldMat;
	XMStoreFloat4x4( &worldMat, W );
	
	shader->GetAsMatrix( "World" )->SetMatrix( &worldMat._11 );
}
