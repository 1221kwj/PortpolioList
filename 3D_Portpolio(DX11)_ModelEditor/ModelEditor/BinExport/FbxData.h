#pragma once

struct MaterialData
{
	MaterialData() {}

	string name = "";
	UINT number = 0;

	D3DXCOLOR ambient = D3DXCOLOR( 0, 0, 0, 1 );
	D3DXCOLOR diffuse = D3DXCOLOR( 0, 0, 0, 1 );
	D3DXCOLOR normal = D3DXCOLOR( 0, 0, 0, 1 );
	D3DXCOLOR specular = D3DXCOLOR( 0, 0, 0, 1 );
	D3DXCOLOR emissive = D3DXCOLOR( 0, 0, 0, 1 );
	float shininess = 0.0f;

	string shaderFile = "";
	string ambientFile = "";
	string diffuseFile = "";
	string normalFile = "";
	string specularFile = "";
	string emissiveFile = "";

	void Write( class BinaryWriter* w );
	static void Write( class BinaryWriter* w, class ModelMaterial* material );
	static void Read( class BinaryReader* r, class ModelMaterial** material );
};

struct KeyFrameData
{
	KeyFrameData()
	{
		for ( D3DXMATRIX matrix : transforms )
			D3DXMatrixIdentity( &matrix );
	}

	string name = "";
	vector<D3DXMATRIX> transforms;

	void Write( class BinaryWriter* w );
	static void Write( class BinaryWriter* w, struct KeyFrameData* data, class ModelKeyFrame* keyFrame );
	static void Read( class BinaryReader* r, class ModelKeyFrame** keyFrame );
};

struct BoneWeightData
{
	vector<pair<int, float>> boneWeights;

	static const UINT MaxBonesPerVertex = 4;
	static const UINT MaxBonesPerMax = 100;
};

struct MeshData
{
	MeshData()
	{
		D3DXMatrixIdentity( &world );
	}

	virtual ~MeshData()
	{
		for ( KeyFrameData* keyFrame : keyFrameDatas )
			SAFE_DELETE( keyFrame );
	}

	string name = "";
	//vector<VertexTextureNormalBlend> vertices;
	vector<VertexTextureNormalTangentBlend> vertices;
	vector<UINT> indices;
	vector<struct KeyFrameData *> keyFrameDatas;

	D3DXMATRIX world;
	bool bSkinnedModel = false;
	bool bSkinning = false;

	void Write( class BinaryWriter* w );
	static void Write( class BinaryWriter* w, class ModelMesh* mesh );
	static void Read( class BinaryReader* r, class ModelMesh** mesh );
};

struct BoneData
{
	BoneData()
	{
		D3DXMatrixIdentity( &matBindPoseTransform );
		D3DXMatrixIdentity( &matBoneReferenceTransform );
	}

	virtual ~BoneData()
	{
		for ( struct KeyFrameData* keyFrame : keyFrameDatas )
			SAFE_DELETE( keyFrame );
	}

	string name = "";

	int parentBoneIndex = -1;

	D3DXMATRIX matBindPoseTransform;
	D3DXMATRIX matBoneReferenceTransform;
	vector<struct KeyFrameData*> keyFrameDatas;

	void Write( class BinaryWriter* w );
	void WriteOnlyBone( class BinaryWriter* w );
	void WriteOnlyKeyFrame( class BinaryWriter* w );
	static void Write( class BinaryWriter* w, class ModelBone* bone );
	static void Read( class BinaryReader* r, class ModelBone** bone );
	static void ReadOnlyBone( class BinaryReader* r, class ModelBone** bone );
	static void ReadOnlyKeyFrame( class BinaryReader*r, class ModelBone** bone );
};

struct AnimationData
{
	AnimationData() {}

	string name = "";

	int startIndex = 0;
	int keyFrameCount = 0;
	float frameRate = 0.0f;

	void Write( class BinaryWriter* w );
	static void Write( class BinaryWriter* w, class ModelAnimation* animation );
	static void Read( class BinaryReader* r, class ModelAnimation** animation );
};

struct BlendWeightData
{
	BlendWeightData() {}

	D3DXVECTOR4 blendIndices = D3DXVECTOR4( 0, 0, 0, 0 );
	D3DXVECTOR4 blendWeights = D3DXVECTOR4( 0, 0, 0, 0 );
};