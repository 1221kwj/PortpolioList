#pragma once

class DepthStencilView
{
public:
	DepthStencilView( UINT width, UINT height, DXGI_FORMAT format = DXGI_FORMAT_D24_UNORM_S8_UINT );
	~DepthStencilView();

	ID3D11Texture2D* GetTexture() { return texture; }
	ID3D11DepthStencilView* GetDSV() { return dsv; }

private:
	UINT					width;
	UINT					height;

	DXGI_FORMAT				format;

	ID3D11Texture2D*		texture;
	ID3D11DepthStencilView* dsv;
};