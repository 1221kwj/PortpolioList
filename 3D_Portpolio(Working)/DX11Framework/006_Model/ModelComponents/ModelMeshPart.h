#pragma once

class ModelMeshPart
{
public:
	friend class Model;
	friend class Models;
	friend class ModelMesh;

private:
	ModelMeshPart();
	~ModelMeshPart();

	void Binding();
	void Render();

public:
	void Clone( ModelMeshPart** clone );

	void Pass( UINT val )	{ pass = val; }
	UINT Pass()				{ return pass; }

private:
	UINT pass;

	Material*			material;
	wstring				materialName;

	class ModelMesh*	parent;

	vector<VTNTB>		vertices;
	vector<UINT>		indices;

	ID3D11Buffer*		vertexBuffer;
	ID3D11Buffer*		indexBuffer;
};