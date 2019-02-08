#include "stdafx.h"
#include "000_Systems/APIWindow.h"

int WINAPI WinMain( HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int cmd )
{
	D3DDesc desc;

	desc.AppName		= L"DX11Framework made by WJ";
	desc.Instance		= instance;
	desc.bFullScreen	= false;
	desc.bVsync			= false;
	desc.Handle			= NULL;
	desc.Width			= 1600;
	desc.Height			= 900;
	desc.gpuDescription = L"";

	D3D::SetDesc( desc );

	srand( ( UINT )time( NULL ) );

	APIWindow*	apiWindow	= new APIWindow();
	WPARAM		wParam		= apiWindow->Run();

	SAFE_DELETE( apiWindow );

	return ( int )wParam;
}