#include "stdafx.h"
#include "Floor.h"
#include "../BinExport/FbxLoader.h"
#include "../Model/ModelPart.h"
#include "../Model/Elements/ModelMesh.h"
#include "../Model/Elements/ModelMaterial.h"

Floor::Floor()
	: modelFile			( BinModels + L"Meshes/Plane.model" )
	, shaderFile		( Shaders + L"Floor.hlsl" )
	, shader			( NULL )
{
	shader = new Shader( shaderFile );
	floorBuffer = new FloorBuffer();

	FbxLoader::LoadBinary( modelFile, &model );
	model->GetModelPart( 0 )->GetMaterial()->SetShader( shaderFile );

	D3DXMatrixScaling( &world, 20, 20, 20 );
}

Floor::~Floor()
{
	SAFE_DELETE( model );

	SAFE_DELETE( floorBuffer );
	SAFE_DELETE( shader );
}

void Floor::Update()
{
	model->GetModelPart( 0 )->GetMesh()->SetGeometricOffset( world );
	model->GetModelPart( 0 )->Update();
}

void Floor::Render()
{
	floorBuffer->SetPSBuffer( 2 );

	model->GetModelPart( 0 )->Render();
}

void Floor::PostRender( GuiSettings* settings )
{
	if ( settings->bShowEnvironmentWindow == true )
	{
		ImGui::Begin( "Environment", &settings->bShowEnvironmentWindow );
		{
			ImGui::Dummy( ImVec2( 0, 10 ) );
			ImGui::Text( "Floor" );
			ImGui::Separator();
			ImGui::ColorEdit3( "Color", ( float * )&floorBuffer->Data.Color );
		}
		ImGui::End();
	}
}
