#include "stdafx.h"
#include "ModelEditor.h"

#include "../007_Draw/001_Enviroments/Sky.h"
#include "../007_Draw/001_Enviroments/Terrain.h"
#include "../007_Draw/001_Enviroments/HeightMap.h"

ModelEditor::ModelEditor()
{
	sky = new Sky( Textures + L"Sky/SnowSky.dds" );

	// Create Terrain
	{
		Terrain::InitDesc desc =
		{
			Textures + L"Landscape/terrain.raw",
			50.0f,
			2049, 2049,
			// LayerMapFile[ 5 ]
			{
				Textures + L"Landscape/grass.dds"		,
				Textures + L"Landscape/darkdirt.dds"	,
				Textures + L"Landscape/stone.dds"		,
				Textures + L"Landscape/lightdirt.dds"	,
				Textures + L"Landscape/snow.dds"		,
			},
			Textures + L"Landscape/blend.dds",
			0.5f,
		};
		desc.TerrainMaterial = new Material( Shaders + L"060_Terrain.fx" );

		terrain = new Terrain( desc );
	}
}

ModelEditor::~ModelEditor()
{
	SAFE_DELETE( sky );
	SAFE_DELETE( terrain );
}

void ModelEditor::Update()
{
	terrain->Update();
}

void ModelEditor::PreRender()
{
}

void ModelEditor::Render()
{
	//sky		->Render();
	terrain	->Render();
}

void ModelEditor::PostRender()
{

}

void ModelEditor::ResizeScreen()
{

}
