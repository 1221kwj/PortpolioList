#pragma once

class HeightMap
{
public:
	HeightMap( UINT width, UINT height, float maxHeight );
	~HeightMap();

	void Load( wstring file );

	UINT GetWidth()			{ return width; }
	UINT GetHeight()		{ return height; }
	float GetMaxHeight()	{ return maxHeight; }

	void SetData( UINT row, UINT col, float data );
	float GetData( UINT row, UINT col );

	bool InBounds( int row, int col );

	void Smooth();
	float Average( int row, int col );

	ID3D11ShaderResourceView* BuildSRV();

private:
	float*	datas;
	UINT	width;
	UINT	height;

	float	maxHeight;
};