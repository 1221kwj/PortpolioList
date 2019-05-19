#pragma once

class ModelMesh
{
	friend class ModelData;
	friend struct MeshData;

	typedef vector<pair<string, class ModelKeyFrame*>> KeyFrameArray;

public:
	virtual ~ModelMesh();

	int GetBoneIndex() const { return boneIndex; }
	string GetName() const { return name; }
	class ModelKeyFrame* GetModelKeyFrame(string name);

	ID3D11Buffer* GetVertexBuffer() { return vertexBuffer; }
	ID3D11Buffer* GetIndexBuffer() { return indexBuffer; }

	UINT GetIndexCount() const { return indexCount; }
	bool GetIsSkinning() const { return bSkinning; }
	void SetIsSkinning( bool skinning ) { bSkinning = skinning; }
	bool GetIsSkinnedModel() const { return bSkinnedModel; }

	const D3DXMATRIX& GetGeometricOffset() const { return matGeometricOffset; }

	void SetBoneIndex( const int& boneIndex ) { this->boneIndex = boneIndex; }
	void SetGeometricOffset( const D3DXMATRIX& mat ) { this->matGeometricOffset = mat; }

private:
	ModelMesh( const MeshData& data );

	void CreateVertexBuffer();
	void CreateIndexBuffer();

private:
	string name;
	int boneIndex;

	bool bSkinnedModel;
	bool bSkinning;

	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	struct VertexTextureNormalTangentBlend* vertexData;
	UINT* indexData;

	UINT vertexCount, indexCount;

	D3DXMATRIX matGeometricOffset;
	KeyFrameArray keyFrames;
};