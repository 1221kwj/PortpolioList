#pragma once
// ======================================================================
//									Model
// ======================================================================
class Model
{
public:
	Model();
	~Model();

	void ReadMaterial( wstring folder, wstring file );
	void ReadMesh( wstring folder, wstring file );

	void CopyGlobalBoneTo( vector<XMFLOAT4X4>& transforms );
	void CopyGlobalBoneTo( vector<XMFLOAT4X4>& transforms, XMFLOAT4X4& w );
	
	template <typename T> T* GetComponent( wstring typeName );

private:
	void BindingBone();
	void BindingMesh();

private:
	typedef pair<wstring, class Component*> Pair;
	unordered_map<wstring, class Component*> components;
};

// ======================================================================
//								Models
// ======================================================================
class Models
{
public:
	friend class Model;

public:
	static void Create();
	static void Delete();

private:
	static void LoadMaterial	( wstring file, class ModelMaterials* materials );
	static void ReadMaterialData( wstring file );

	static void LoadMesh	( wstring file, class ModelBones* bones, class ModelMeshes* meshes );
	static void ReadMeshData( wstring file );

private:
	static map<wstring, vector<Material *>> materialMap;

	struct MeshData
	{
		vector<class ModelBone *> Bones;
		vector<class ModelMesh *> Meshes;
	};
	static map<wstring, MeshData> meshDataMap;
};

template<typename T> inline T * Model::GetComponent( wstring typeName )
{
	for ( Pair c : components )
	{
		if ( c.first == typeName )
			return ( T* )c.second;
	}

	return NULL;
}
