#pragma once

class RenderTargetView
{
public:
	RenderTargetView( UINT width, UINT height, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM );
	~RenderTargetView();

	ID3D11Texture2D*			GetTexture()	{ return texture; }
	ID3D11ShaderResourceView*	GetSRV()		{ return srv; }
	ID3D11RenderTargetView*		GetRTV()		{ return rtv; }
	ID3D11UnorderedAccessView*	GetUAV()		{ return uav; }

private:
	UINT						width;
	UINT						height;

	DXGI_FORMAT					format;

	ID3D11Texture2D*			texture;
	ID3D11ShaderResourceView*	srv;
	ID3D11RenderTargetView*		rtv;
	ID3D11UnorderedAccessView*	uav;
};