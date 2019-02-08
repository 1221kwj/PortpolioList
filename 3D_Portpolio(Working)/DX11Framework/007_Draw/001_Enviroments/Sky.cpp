#include "stdafx.h"
#include "Sky.h"

#include "../../003_Viewer/Camera.h"

Sky::Sky( wstring cubeFile )
{
	material	= new Material	( Shaders + L"056_CubeSky.fx" );
	sphere		= new MeshSphere( material, 500.0f, 30.0f, 30.0f );

	HRESULT hr = D3DX11CreateShaderResourceViewFromFile
	(
		D3D::GetDevice(),
		cubeFile.c_str(),
		NULL,
		NULL,
		&srv,
		NULL
	);
	assert( SUCCEEDED( hr ) );

	material->GetShader()->GetAsShaderResource( "CubeMap" )->SetResource( srv );
}

Sky::~Sky()
{
	SAFE_DELETE( sphere );
	SAFE_DELETE( material );
}

void Sky::Update()
{
	Vector3 position;
	Context::Get()->GetMainCamera()->GetPosition( &position );

	sphere->SetPosition( position );
}

void Sky::Render()
{
	sphere->Render();
}
