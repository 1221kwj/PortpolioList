#include "stdafx.h"
#include "Terrain.h"
#include "HeightMap.h"
#include "TerrainRender.h"

const UINT Terrain::CellsPerPatch = 64;

Terrain::Terrain( InitDesc & desc )
	: desc( desc )
{
	render = new TerrainRender( desc.TerrainMaterial, this );

	heightMap = new HeightMap
	( 
		( UINT )desc.HeightMapWidth,
		( UINT )desc.HeightMapHeight,
		desc.HeightScale
	);
	heightMap->Load( desc.HeightMap );

	render->Initialize();
}

Terrain::~Terrain()
{
	SAFE_DELETE( heightMap );
	SAFE_DELETE( render );
}

void Terrain::Update() 
{
	render->Update();
}

void Terrain::Render()
{
	render->Render();
}

void Terrain::SetData( UINT row, UINT col, float data )
{
	heightMap->SetData( row, col, data );
}

float Terrain::GetData( UINT row, UINT col )
{
	return heightMap->GetData( row, col );
}

float Terrain::GetWidth()
{
	return ( desc.HeightMapWidth - 1 ) * desc.CellSpacing;
}

float Terrain::GetDepth()
{
	return ( desc.HeightMapHeight - 1 ) * desc.CellSpacing;
}
