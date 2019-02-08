#pragma once

struct TerrainCP
{
	Vector3 Position;
	Vector2 Uv;
	Vector2 BoundsY;

	TerrainCP() {}
	TerrainCP( Vector3 position, Vector2 uv, Vector2 boundsY )
	{
		Position	= position;
		Uv			= uv;
		BoundsY		= boundsY;
	}
};

class Patch
{
public:
	enum class NeighborDir{ Top, Left };

public:
	Patch();
	~Patch();

	void InitPatchData( int patchWidth );

private:
	void BuildCenterIndices();
	void BuildTopEdges();
	void BuildLeftEdges();

	WORD width;

	vector<TerrainCP>			vertices;
	ID3D11Buffer*				vertexBuffer;

	map<WORD, ID3D11Buffer*>	indexBuffer;
	map<WORD, WORD>				indexCount;
	
	map<WORD, ID3D11Buffer*>	centerIndexBuffer;
	map<WORD, WORD>				centerIndexCount;
	
	map<NeighborDir, map<tuple<WORD, WORD>, ID3D11Buffer*>> edgeIbs;
	map<NeighborDir, map<tuple<WORD, WORD>, WORD>>			edgeIndexCount;
};