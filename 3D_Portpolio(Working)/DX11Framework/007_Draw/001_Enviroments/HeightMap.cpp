#include "stdafx.h"
#include "HeightMap.h"

HeightMap::HeightMap( UINT width, UINT height, float maxHeight )
	: width		( width )
	, height	( height )
	, maxHeight	( maxHeight )
{
	datas = new float[ width * height ];
}

HeightMap::~HeightMap()
{
	SAFE_DELETE_ARRAY( datas );
}

void HeightMap::Load( wstring file )
{
	BinaryReader* r = new BinaryReader();
	r->Open( file );

	BYTE* temp = new BYTE[ width * height ];
	r->Byte( ( void** )&temp, width * height );

	r->Close();
	SAFE_DELETE( r );

	for ( int i = 0; i < ( int )( width * height ); i++ )
	{
		datas[ i ] = ( ( float )temp[ i ] / 255.0f ) * maxHeight;
	}

	Smooth();
}

void HeightMap::SetData( UINT row, UINT col, float data )
{
	if ( InBounds( row, col ) == false ) return;

	datas[ row * height + col ] = data;
}

float HeightMap::GetData( UINT row, UINT col )
{
	if ( InBounds( row, col ) == false ) return 0.0f;

	return datas[ row * height + col ];
}

bool HeightMap::InBounds( int row, int col )
{
	return ( row >= 0 && row < ( int )height ) && ( col >= 0 && col < ( int )width );
}

void HeightMap::Smooth()
{
	float* dest = new float[ width * height ];

	for ( int row = 0; row < height; row++ )
	{
		for ( int col = 0; col < width; col++ )
		{
			dest[ row * height + col ] = Average( ( int )row, ( int )col );
		}
	}

	memcpy( datas, dest, sizeof( float ) * width * height );
	SAFE_DELETE_ARRAY( dest );
}

float HeightMap::Average( int row, int col )
{
	float average	= 0.0f;
	int   sum		= 0;

	for ( int m = row - 1; m <= row + 1; m++ )
	{
		for ( int n = col - 1; n <= col + 1; n++ )
		{
			if ( InBounds( m, n ) == true )
			{
				average += datas[ m * height + n ];
				sum++;
			}
		}
	}

	return average / ( float )sum;
}

ID3D11ShaderResourceView * HeightMap::BuildSRV()
{
	D3D11_TEXTURE2D_DESC desc = { 0 };
	desc.ArraySize			= 1;
	desc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
	desc.Format				= DXGI_FORMAT_R32_FLOAT;
	desc.SampleDesc.Count	= 1;
	desc.SampleDesc.Quality = 0;
	desc.Width				= width;
	desc.Height				= height;
	desc.MipLevels			= 1;
	desc.MiscFlags			= 0;
	desc.Usage				= D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA data = { 0 };
	data.pSysMem			= datas;
	data.SysMemPitch		= sizeof( float ) * width;
	data.SysMemSlicePitch	= sizeof( float ) * width * height;

	ID3D11Texture2D* map;
	HRESULT hr = D3D::GetDevice()->CreateTexture2D( &desc, &data, &map );
	assert( SUCCEEDED( hr ) );

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory( &srvDesc, sizeof( D3D11_SHADER_RESOURCE_VIEW_DESC ) );
	srvDesc.Format						= desc.Format;
	srvDesc.ViewDimension				= D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip	= 0;
	srvDesc.Texture2D.MipLevels			= -1;

	ID3D11ShaderResourceView* srv;
	hr = D3D::GetDevice()->CreateShaderResourceView( map, &srvDesc, &srv );
	assert( SUCCEEDED( hr ) );

	SAFE_RELEASE( map );

	return srv;
}
