#pragma once

class ModelData
{
	friend class FbxLoader;
public:
	virtual ~ModelData();

	// ======================================================= //
	void RenderAnimBoneList();
	void SetBoneName( string name, int index );
	int GetAnimBoneCount() { return selectBoneCount; }
	string GetAnimBoneName( int index );
	static void AddBinAnimation( wstring animFile, Model* model );
	// ======================================================= //

private:
	ModelData();

	void OnlyMeshWrite(const string& file);
	static void Write(const string& file, class Model* model);
	static void ReadOnlyMesh( const string& file, class Model** model );
	static void Read(const string& file, class Model** model);
	
	// ======================================================= //
	void ReadAnim( string name, class Model* model );
	void SaveAnimBin( wstring file = L"" );
	void WriteAnim( const wstring& file );
	// ======================================================= //

	void PushMaterialData(class FbxSurfaceMaterial* material, int& number);
	struct BoneData* FindBoneData(const string& boneName);
	int FindBoneIndex(const string& boneName);
	float BoneWeightValidate(struct BoneWeightData* data);
	void BoneWeightNormalize(const UINT& index);
	void SetBlendWeight(struct BlendWeightData* blendWeight, int nIndex, int nBoneIndex, float fWeight);

private:
	string name;
	vector<struct MaterialData*> materialDatas;
	vector<struct MeshData*> meshDatas;
	vector<struct BoneData*> boneDatas;
	vector<struct AnimationData*> animationDatas;
	vector<struct BoneWeightData> meshBoneWeightDatas;

	int selectBoneCount;
};