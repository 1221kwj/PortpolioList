#pragma once

class TerrainRender
{
public:
	TerrainRender( Material* material, class Terrain* terrain );
	~TerrainRender();

	void Initialize();
	void Update();
	void Render();

public:
	static const float MaxDistance;
	static const float MinDistance;
	static const float MaxTessellation;
	static const float MinTessellation;

private:
	void CalcAllPatchBoundsY();
	void CalcPatchBounds( UINT row, UINT col );
	void BuildQuadPatchVB();
	void BuildQuadPatchIB();

	void CreateBlendMap();
	void SmoothBlendMap( vector<Vector4>& colors );

private:
	XMFLOAT4X4					world;
	ID3D11Buffer*				cBuffer;

	class Terrain*				terrain;

	ID3D11Buffer*				quadPatchVB;
	ID3D11Buffer*				quadPatchIB;

	vector<class Patch*>		patches;

	TextureArray*				layMapArray;
	ID3D11ShaderResourceView*	layMapArraySRV;
	ID3D11ShaderResourceView*	blendMapSRV;
	ID3D11ShaderResourceView*	heightMapSRV;

	UINT						patchVerticesCount;
	UINT						patchQuadFacesCount;
	UINT						patchVertexRows;
	UINT						patchVertexCols;

	Material*					material;
	vector<Vector2>				patchBoundsY;

	vector<VertexColor>			bvVertices;
	vector<WORD>				bvIndices;
	ID3D11Buffer*				bvVertexBuffer;
	ID3D11Buffer*				bvIndexBuffer;

	UINT						aabbCount;
	UINT						pass;

	class Frustum*				frustum;

	Render2D*					r_2d;

private:
	struct Buffer
	{
		Vector4 FogColor;
		
		float	FogStart;
		float	FogRange;

		float	MinDistance;
		float	MaxDistance;
		float	MinTessellation;
		float	MaxTessellation;

		float	TessCellSpaceU;
		float	TessCellSpaceV;
		float	WorldCellSpace;

		Vector2 TessScale = Vector2( 66.0f, 66.0f );
		float	Padding;

		Vector4 WorldFrustumPlanes[ 6 ];
	} buffer;
};