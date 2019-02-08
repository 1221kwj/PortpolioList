#pragma once

class Terrain
{
public:
	struct InitDesc
	{
		wstring		HeightMap;
		float		HeightScale;
		float		HeightMapWidth;
		float		HeightMapHeight;

		wstring		LayerMapFile[ 5 ];
		wstring		BlendMapFile;
		float		CellSpacing;

		Material*	TerrainMaterial;
	};

public:
	Terrain( InitDesc& desc );
	~Terrain();

	void Update();
	void Render();

	void SetData( UINT row, UINT col, float data );
	float GetData( UINT row, UINT col );

	float GetWidth();
	float GetDepth();

	struct InitDesc& GetDesc()		{ return desc; }

	class HeightMap* GetHeightMap() { return heightMap; }

public:
	static const UINT CellsPerPatch;

private:
	class TerrainRender*	render;
	class HeightMap*		heightMap;

	InitDesc				desc;
};