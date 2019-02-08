#include "stdafx.h"
#include "TerrainRender.h"
#include "Patch.h"
#include "Terrain.h"
#include "HeightMap.h"

#include "../../003_Viewer/Frustum.h"

const float TerrainRender::MaxDistance		= 500.0f;
const float TerrainRender::MinDistance		= 20.0f;
const float TerrainRender::MaxTessellation	= 6.0f;
const float TerrainRender::MinTessellation	= 0.0f;

TerrainRender::TerrainRender( Material * material, Terrain * terrain )
	: material	( material )
	, terrain	( terrain )
	, pass		( 1 )
{
	world = Math::IdentityMatrix();

	D3D11_BUFFER_DESC desc;
	desc.Usage					= D3D11_USAGE_DYNAMIC;
	desc.ByteWidth				= ( UINT )sizeof( Buffer );
	desc.BindFlags				= D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags			= D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags				= 0;
	desc.StructureByteStride	= 0;

	HRESULT hr = D3D::GetDevice()->CreateBuffer( &desc, NULL, &cBuffer );
	assert( SUCCEEDED( hr ) );

	frustum = new Frustum( 1000.0f );

	D3DDesc d3dDesc;
	D3D::GetDesc( &d3dDesc );

	r_2d = new Render2D();
	r_2d->SetScale( 200.0f, 200.0f );
	r_2d->SetPosition( Vector2( 0.0f, 0.0f ) );
}

TerrainRender::~TerrainRender()
{
	for ( Patch* patch : patches )
		SAFE_DELETE( patch );

	SAFE_RELEASE( quadPatchVB );
	SAFE_RELEASE( quadPatchIB );

	SAFE_DELETE( frustum );
	SAFE_DELETE( material );

	SAFE_DELETE( r_2d );
}

void TerrainRender::Initialize()
{
	patchVertexRows = ( ( ( UINT )terrain->GetDesc().HeightMapHeight - 1 ) / Terrain::CellsPerPatch ) + 1;
	patchVertexCols = ( ( ( UINT )terrain->GetDesc().HeightMapWidth  - 1 ) / Terrain::CellsPerPatch ) + 1;

	patchVerticesCount	= patchVertexRows * patchVertexCols;
	patchQuadFacesCount = ( patchVertexRows - 1 ) * ( patchVertexCols - 1 );
	
	CalcAllPatchBoundsY();

	BuildQuadPatchVB();
	BuildQuadPatchIB();

	vector<wstring> textures;
	for ( int i = 0; i < 5; i++ )
		textures.push_back( terrain->GetDesc().LayerMapFile[ i ] );
	
	layMapArray		= new TextureArray( textures, 512, 512 );
	layMapArraySRV	= layMapArray->GetSRV();
	heightMapSRV	= terrain->GetHeightMap()->BuildSRV();
	
	r_2d->SRV( heightMapSRV );

	Shader* shader = material->GetShader();
	shader->GetAsShaderResource( "HeightMap" )		->SetResource( heightMapSRV );
	shader->GetAsShaderResource( "LayerMapArray" )	->SetResource( layMapArraySRV );
	//shader->GetAsShaderResource( "BlendMap" )		->SetResource( blendMapSRV );
}

void TerrainRender::Update()
{
	if ( Keyboard::Get()->Down( VK_SPACE ) )
	{
		if ( pass == 1 ) pass = 0;
		else pass = 1;
	}
}

void TerrainRender::Render()
{
	buffer.FogStart			= 15.0f;
	buffer.FogRange			= 175.0f;
	buffer.FogColor			= Vector4( 1.0f, 1.0f, 1.0f, 1.0f );
	buffer.MinDistance		= MinDistance;
	buffer.MaxDistance		= MaxDistance;
	buffer.MinTessellation	= MinTessellation;
	buffer.MaxTessellation	= MaxTessellation;
	buffer.TessCellSpaceU	= 1.0f / terrain->GetDesc().HeightMapWidth;
	buffer.TessCellSpaceV	= 1.0f / terrain->GetDesc().HeightMapHeight;
	buffer.WorldCellSpace	= terrain->GetDesc().CellSpacing;

	frustum->GetPlanes( buffer.WorldFrustumPlanes );

	D3D11_MAPPED_SUBRESOURCE subResource;
	HRESULT hr = D3D::GetDC()->Map( cBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource );
	assert( SUCCEEDED( hr ) );

	memcpy( subResource.pData, &buffer, sizeof( Buffer ) );
	D3D::GetDC()->Unmap( cBuffer, 0 );

	hr = material->GetShader()->GetAsConstantBuffer( "CB_Terrain" )->SetConstantBuffer( cBuffer );
	assert( SUCCEEDED( hr ) );

	UINT stride = ( UINT )sizeof( TerrainCP );
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers	( 0, 1, &quadPatchVB, &stride, &offset );
	D3D::GetDC()->IASetIndexBuffer		( quadPatchIB, DXGI_FORMAT_R16_UINT, 0 );
	D3D::GetDC()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST );

	material->GetShader()->GetAsMatrix( "World" )->SetMatrix( &world._11 );
	material->GetShader()->DrawIndexed( 0, pass, patchQuadFacesCount * 4 );

	r_2d->Render();
}

void TerrainRender::CalcAllPatchBoundsY()
{
	patchBoundsY.assign( patchQuadFacesCount, Vector2() );

	for ( UINT row = 0; row < patchVertexRows - 1; row++ )
	{
		for ( UINT col = 0; col < patchVertexCols - 1; col++ )
			CalcPatchBounds( row, col );
	}
}

void TerrainRender::CalcPatchBounds( UINT row, UINT col )
{
	UINT x0 = ( col + 0 ) * Terrain::CellsPerPatch;
	UINT x1 = ( col + 1 ) * Terrain::CellsPerPatch;

	UINT y0 = ( row + 0 ) * Terrain::CellsPerPatch;
	UINT y1 = ( row + 1 ) * Terrain::CellsPerPatch;

	float minY = FLT_MAX;
	float maxY = FLT_MIN;

	for ( UINT y = y0; y <= y1; y++ )
	{
		for ( UINT x = x0; x <= x1; x++ )
		{
			minY = min( minY, terrain->GetData( y, x ) );
			maxY = max( maxY, terrain->GetData( y, x ) );
		}
	}

	UINT patchID = row * ( patchVertexCols - 1 ) + col;
	patchBoundsY[ patchID ] = Vector2( minY, maxY );
}

void TerrainRender::BuildQuadPatchVB()
{
	TerrainCP* patchVertices = new TerrainCP[ patchVerticesCount ];
	float halfWidth = 0.5f * ( float )terrain->GetWidth();
	float halfDepth = 0.5f * ( float )terrain->GetDepth();

	float patchWidth = ( float )terrain->GetWidth() / ( float )( patchVertexCols - 1 );
	float patchDepth = ( float )terrain->GetDepth() / ( float )( patchVertexRows - 1 );

	float du = 1.0f / ( float )( patchVertexCols - 1 );
	float dv = 1.0f / ( float )( patchVertexRows - 1 );

	for ( UINT row = 0; row < patchVertexRows; row++ )
	{
		float z = halfDepth - ( float )row * patchDepth;
		for ( UINT col = 0; col < patchVertexCols; col++ )
		{
			float x			= -halfWidth + ( float )col * patchWidth;
			UINT  vertId	= row * patchVertexCols + col;

			patchVertices[ vertId ].Position	= Vector3( x, 0, z );
			patchVertices[ vertId ].Uv			= Vector2( col * du, row * dv );
		}
	}

	for ( UINT row = 0; row < patchVertexRows - 1; row++ )
	{
		for ( UINT col = 0; col < patchVertexCols - 1; col++ )
		{
			UINT patchID	= row * ( patchVertexCols - 1 ) + col;
			UINT vertID		= row * patchVertexCols + col;
			
			patchVertices[ vertID ].BoundsY = patchBoundsY[ patchID ];
		}
	}

	D3D11_BUFFER_DESC desc = { 0 };
	desc.Usage		= D3D11_USAGE_IMMUTABLE;
	desc.ByteWidth	= ( UINT )sizeof( TerrainCP ) * patchVerticesCount;
	desc.BindFlags	= D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = { 0 };
	data.pSysMem = &patchVertices[ 0 ];

	HRESULT hr = D3D::GetDevice()->CreateBuffer( &desc, &data, &quadPatchVB );
	assert( SUCCEEDED( hr ) );

	SAFE_DELETE_ARRAY( patchVertices );
}

void TerrainRender::BuildQuadPatchIB()
{
	vector<WORD> indices;
	for ( WORD row = 0; row < ( WORD )patchVertexRows - 1; row++ )
	{
		for ( WORD col = 0; col < ( WORD )patchVertexCols - 1; col++ )
		{
			indices.push_back( ( row + 0 ) * ( WORD )patchVertexCols + ( col + 0 ) );
			indices.push_back( ( row + 0 ) * ( WORD )patchVertexCols + ( col + 1 ) );
			indices.push_back( ( row + 1 ) * ( WORD )patchVertexCols + ( col + 0 ) );
			indices.push_back( ( row + 1 ) * ( WORD )patchVertexCols + ( col + 1 ) );
		}
	}

	D3D11_BUFFER_DESC desc = { 0 };
	desc.Usage		= D3D11_USAGE_IMMUTABLE;
	desc.ByteWidth	= ( UINT )( sizeof( WORD ) * indices.size() );
	desc.BindFlags	= D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA data = { 0 };
	data.pSysMem = &indices[ 0 ];

	HRESULT hr = D3D::GetDevice()->CreateBuffer( &desc, &data, &quadPatchIB );
	assert( SUCCEEDED( hr ) );
}

void TerrainRender::CreateBlendMap()
{
	HeightMap* heightMap = terrain->GetHeightMap();
	vector<Vector4> colors;
	for ( UINT y = 0; y < heightMap->GetHeight(); y++ )
	{
		for ( UINT x = 0; x < heightMap->GetWidth(); x++ )
		{
			float elivation = terrain->GetData( y, x );

			Vector4 color = Vector4( 0, 0, 0, 0 );
			if ( elivation > heightMap->GetMaxHeight() * ( 0.05f + Math::Random( -0.05f, 0.05f ) ) )
				color.x = elivation / heightMap->GetMaxHeight() + Math::Random( -0.05f, 0.05f );

			if ( elivation > heightMap->GetMaxHeight() * ( 0.04f + Math::Random( -0.15f, 0.15f ) ) )
				color.y = elivation / heightMap->GetMaxHeight() + Math::Random( -0.05f, 0.05f );

			if ( elivation > heightMap->GetMaxHeight() * ( 0.75f + Math::Random( -0.1f, 0.1f ) ) )
				color.z = elivation / heightMap->GetMaxHeight() + Math::Random( -0.05f, 0.05f );

			colors.push_back( color );
		}
	}
	
	SmoothBlendMap( colors );
	SmoothBlendMap( colors );

	vector<UINT> colors8b( colors.size() );
	const float f = 255.0f;

	vector<Vector4>::iterator it = colors.begin();
	for ( UINT i = 0; it != colors.end(); it++, i++ )
	{
		colors8b[ i ] = ( ( UINT )( ( f * it->w ) ) << 24 )
					  + ( ( UINT )( ( f * it->z ) ) << 16 )
					  + ( ( UINT )( ( f * it->y ) ) << 8  )
					  + ( ( UINT )( ( f * it->x ) ) << 0  );
	}

	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM; // DXGI_FORMAT_R32G32B32A32_FLOAT

	ID3D11Texture2D* texture = 0;
	//   Create Blend Texture2D
	{
		UINT _width		= terrain->GetHeightMap()->GetWidth();
		UINT _height	= terrain->GetHeightMap()->GetHeight();

		D3D11_TEXTURE2D_DESC desc = { 0 };
		desc.Width				= _width;
		desc.Height				= _height;
		desc.MipLevels			= 1;
		desc.ArraySize			= 1;
		desc.Format				= format;
		desc.SampleDesc.Count	= 1;
		desc.SampleDesc.Quality = 0;
		desc.Usage				= D3D11_USAGE_DEFAULT;
		desc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem			= &colors8b[ 0 ];
		data.SysMemPitch		= _width * ( UINT )sizeof( UINT );
		data.SysMemSlicePitch	= _width * _height * ( UINT )sizeof( UINT );

		HRESULT hr = D3D::GetDevice()->CreateTexture2D( &desc, &data, &texture );
		assert( SUCCEEDED( hr ) );
	}

	// Create Shader Resource View (To . blendMapSRV)
	{
		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		desc.Format						= format;
		desc.ViewDimension				= D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MostDetailedMip	= 0;
		desc.Texture2D.MipLevels		= 1;

		HRESULT hr = D3D::GetDevice()->CreateShaderResourceView( texture, &desc, &blendMapSRV );
		assert( SUCCEEDED( hr ) );
	}

	SAFE_RELEASE( texture );
	colors.clear();
	colors8b.clear();
}

void TerrainRender::SmoothBlendMap( vector<Vector4>& colors )
{
	for ( UINT y = 0; y < terrain->GetHeightMap()->GetHeight(); y++ )
	{
		for ( UINT x = 0; x < terrain->GetHeightMap()->GetWidth(); x++ )
		{
			Vector4 sum = colors[ x + y * terrain->GetHeightMap()->GetHeight() ];
			UINT	num = 0;

			for ( UINT y1 = y - 1; y1 < y + 2; y1++ )
			{
				for ( UINT x1 = x - 1; x1 < x + 1; x1++ )
				{
					if ( terrain->GetHeightMap()->InBounds( y1, x1 ) == false ) continue;

					sum += colors[ x1 + y1 * terrain->GetHeightMap()->GetHeight() ];
					num++;
				}
			}

			sum /= ( float )num;
			colors[ x + y * terrain->GetHeightMap()->GetHeight() ] = sum;
		}
	}
}
