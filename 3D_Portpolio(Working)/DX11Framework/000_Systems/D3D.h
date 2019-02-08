#pragma once

struct D3DDesc
{
	wstring		AppName;
	HINSTANCE	Instance;
	HWND		Handle;
	float		Width;
	float		Height;
	bool		bVsync;
	bool		bFullScreen;
	wstring		gpuDescription;
};

class D3D
{
public:
	static D3D* Get();
	static void Create();
	static void Delete();

	static ID3D11Device*		GetDevice()		{ return device; }
	static ID3D11DeviceContext* GetDC()			{ return deviceContext; }
	static IDXGISwapChain*		GetSwapChain()	{ return swapChain; }

	static void GetDesc( D3DDesc* desc )		{ *desc = d3dDesc; }
	static void SetDesc( D3DDesc& desc )		{ d3dDesc = desc; }

private:
	D3D();
	~D3D();

	void SetGpuInfo();
	void CreateSwapChainAndDevice();
	void CreateBackBuffer( float width, float height );

	void DeleteBackBuffer();

public:
	void SetRenderTarget( ID3D11RenderTargetView* rtv = NULL, ID3D11DepthStencilView* dsv = NULL );
	void Clear( XMFLOAT4 color = XMFLOAT4( 0.3f, 0.3f, 0.4f, 1.0f ), ID3D11RenderTargetView* rtv = NULL, ID3D11DepthStencilView* dsv = NULL );
	void Present();

	void ResizeScreen( float width, float height );

private:
	static D3D*					instance;
	static D3DDesc				d3dDesc;
	static ID3D11Device*		device;
	static ID3D11DeviceContext* deviceContext;
	static IDXGISwapChain*		swapChain;

	ID3D11Debug*				debugDevice;
	ID3D11Texture2D*			backBuffer;
	ID3D11DepthStencilView*		depthStencilView;
	ID3D11RenderTargetView*		renderTargetView;

	UINT						gpuMemorySize;
	UINT						denominator;
	UINT						numerator;
};