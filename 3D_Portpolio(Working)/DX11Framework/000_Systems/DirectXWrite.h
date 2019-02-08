#pragma once

struct FontBrushDesc;
struct FontTextDesc;

class DirectXWrite
{
public:
	static void Create();
	static void Delete();

	static DirectXWrite*		Get();
	static ID2D1DeviceContext*	GetDC() { return deviceContext; }

	static void CreateSurface();
	static void DeleteSurface();

private:
	DirectXWrite();
	~DirectXWrite();

public:
	static void RenderText
	(
		wstring				text,
		RECT				rect,
		float				size	= 20.0f,
		wstring				font	= L"µ¸¿òÃ¼",
		Vector4				color	= Vector4( 0.0f, 0.0f, 0.0f, 1.0f ),
		DWRITE_FONT_WEIGHT	weight	= DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE	style	= DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH stretch = DWRITE_FONT_STRETCH_NORMAL
	);

private:
	static DirectXWrite*			instance;

	ID2D1Factory1*					factory;
	static IDWriteFactory*			writeFactory;

	ID2D1Device*					device;
	static ID2D1DeviceContext*		deviceContext;

	static ID2D1Bitmap1*			targetBitmap;
	static IDXGISurface*			dxgiSurface;

	static vector<FontBrushDesc>	fontBrush;
	static vector<FontTextDesc>		fontText;
};

struct FontBrushDesc
{
	Vector4					Color;
	ID2D1SolidColorBrush*	Brush = NULL;

	bool operator==( const FontBrushDesc& val )
	{
		return	Color.x == val.Color.x &&
				Color.y == val.Color.y &&
				Color.z == val.Color.z &&
				Color.w == val.Color.w;
	}
};

struct FontTextDesc
{
	wstring				Font;
	float				FontSize;

	DWRITE_FONT_WEIGHT	Weight;
	DWRITE_FONT_STYLE	Style;
	DWRITE_FONT_STRETCH Stretch;

	IDWriteTextFormat*	Format = NULL;

	bool operator==( const FontTextDesc& val )
	{
		bool b			= true;
		b &= Font		== val.Font;
		b &= FontSize	== val.FontSize;
		b &= Weight		== val.Weight;
		b &= Style		== val.Style;
		b &= Stretch	== val.Stretch;

		return b;
	}
};