#include "stdafx.h"
#include "DirectXWrite.h"

DirectXWrite*			DirectXWrite::instance		= NULL;
IDWriteFactory*			DirectXWrite::writeFactory	= NULL;
ID2D1DeviceContext*		DirectXWrite::deviceContext = NULL;

ID2D1Bitmap1*			DirectXWrite::targetBitmap	= NULL;
IDXGISurface*			DirectXWrite::dxgiSurface	= NULL;

vector<FontBrushDesc>	DirectXWrite::fontBrush;
vector<FontTextDesc>	DirectXWrite::fontText;

// ======================================================================
//							SINGLETON 
// ======================================================================
void DirectXWrite::Create()
{
	assert( instance == NULL );

	instance = new DirectXWrite();
}

void DirectXWrite::Delete()
{
	assert( instance != NULL );

	SAFE_DELETE( instance );
}

DirectXWrite * DirectXWrite::Get()
{
	return instance;
}

// ======================================================================
//						DirectXWrite Class
// ======================================================================
DirectXWrite::DirectXWrite()
{
	HRESULT hr;
	
	hr = DWriteCreateFactory
	(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof( IDWriteFactory ),
		( IUnknown ** )&writeFactory
	);
	assert( SUCCEEDED( hr ) );

	D2D1_FACTORY_OPTIONS option;
	option.debugLevel = D2D1_DEBUG_LEVEL_NONE;
	hr = D2D1CreateFactory( D2D1_FACTORY_TYPE_MULTI_THREADED, &factory );
	assert( SUCCEEDED( hr ) );

	IDXGIDevice* dxgiDevice;
	hr = D3D::GetDevice()->QueryInterface( &dxgiDevice );
	assert( SUCCEEDED( hr ) );

	hr = factory->CreateDevice( dxgiDevice, &device );
	assert( SUCCEEDED( hr ) );

	hr = device->CreateDeviceContext( D2D1_DEVICE_CONTEXT_OPTIONS_ENABLE_MULTITHREADED_OPTIMIZATIONS, &deviceContext );
	assert( SUCCEEDED( hr ) );

	CreateSurface();

	SAFE_RELEASE( dxgiDevice );
}

DirectXWrite::~DirectXWrite()
{
	DeleteSurface();

	SAFE_RELEASE( factory );
	SAFE_RELEASE( writeFactory );

	SAFE_RELEASE( deviceContext );
	SAFE_RELEASE( device );
}

void DirectXWrite::CreateSurface()
{
	HRESULT hr = D3D::GetSwapChain()->GetBuffer( 0, __uuidof( IDXGISurface ), ( void ** )&dxgiSurface );
	assert( SUCCEEDED( hr ) );

	D2D1_BITMAP_PROPERTIES1 bp;
	bp.pixelFormat.format		= DXGI_FORMAT_R8G8B8A8_UNORM;
	bp.pixelFormat.alphaMode	= D2D1_ALPHA_MODE_IGNORE;
	bp.dpiX						= 96;
	bp.dpiY						= 96;
	bp.bitmapOptions			= D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
	bp.colorContext				= NULL;

	hr = deviceContext->CreateBitmapFromDxgiSurface( dxgiSurface, &bp, &targetBitmap );
	assert( SUCCEEDED( hr ) );

	deviceContext->SetTarget( targetBitmap );
}
void DirectXWrite::DeleteSurface()
{
	deviceContext->SetTarget( NULL );

	for ( FontBrushDesc desc : fontBrush )
		SAFE_RELEASE( desc.Brush );
	
	fontBrush.clear();

	for ( FontTextDesc desc : fontText )
		SAFE_RELEASE( desc.Format );
	
	fontText.clear();


	SAFE_RELEASE( targetBitmap );
	SAFE_RELEASE( dxgiSurface );
}

void DirectXWrite::RenderText
( 
	wstring					text,
	RECT					rect,
	float					size,
	wstring					font,
	Vector4					color,
	DWRITE_FONT_WEIGHT		weight,
	DWRITE_FONT_STYLE		style,
	DWRITE_FONT_STRETCH		stretch
)
{
	FontBrushDesc brushDesc;
	brushDesc.Color = color;

	FontBrushDesc* findBrush = NULL;
	for ( FontBrushDesc& desc : fontBrush )
	{
		if ( desc == brushDesc )
		{
			findBrush = &desc;
			break;
		}
	}
	
	if ( findBrush == NULL )
	{
		D2D1::ColorF colorF = D2D1::ColorF( color.x, color.y, color.z );
		deviceContext->CreateSolidColorBrush( colorF, &brushDesc.Brush );

		fontBrush.push_back( brushDesc );
		findBrush = &brushDesc;
	}

	FontTextDesc textDesc;
	textDesc.Font		= font;
	textDesc.FontSize	= size;
	textDesc.Stretch	= stretch;
	textDesc.Style		= style;
	textDesc.Weight		= weight;

	FontTextDesc* findText = NULL;
	for ( FontTextDesc& desc : fontText )
	{
		if ( desc == textDesc )
		{
			findText = &desc;
			break;
		}
	}

	if ( findText == NULL )
	{
		writeFactory->CreateTextFormat
		(
			textDesc.Font.c_str(),
			NULL,
			textDesc.Weight,
			textDesc.Style,
			textDesc.Stretch,
			textDesc.FontSize,
			L"ko",
			&textDesc.Format
		);

		fontText.push_back( textDesc );
		findText = &textDesc;
	}

	D2D1_RECT_F rectF;
	rectF.left		= ( float )rect.left;
	rectF.right		= ( float )rect.right;
	rectF.top		= ( float )rect.top;
	rectF.bottom	= ( float )rect.bottom;

	deviceContext->DrawTextW( text.c_str(), ( UINT32 )text.size(), findText->Format, rectF, findBrush->Brush );
}