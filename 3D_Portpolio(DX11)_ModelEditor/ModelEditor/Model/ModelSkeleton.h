#pragma once

class ModelSkeleton
{
	friend class ModelData;
	typedef vector<pair<string, class ModelBone*>> BoneArray;

public:
	virtual ~ModelSkeleton();

	class ModelBone* GetBone(const UINT& index) { return bones[index].second; }
	const BoneArray& GetSkeletonBones() const { return bones; }
	UINT GetBoneCount() const;
	D3DXMATRIX* GetSkinTransforms() { return skinTransforms; }
	D3DXMATRIX* GetBoneAnimationTransforms() { return boneAnimationTransforms; }
	D3DXMATRIX GetBoneBindMatrix( string name );
	const D3DXMATRIX& GetBoneScale() const;

	void UpdateAnimation(class ModelAnimationController* controller);
	void SetBoneScale( D3DXMATRIX mat );
	void SelectedBoneRender( int index, D3DXMATRIX mat );
	void DeleteKeyFrame( string name );

private:
	ModelSkeleton();

	void BuildBoneTransforms(class ModelAnimationController* controller, const string& name);

private:
	class BoneBuffer* boneBuffer;
	
	BoneArray bones;
	D3DXMATRIX* skinTransforms;
	D3DXMATRIX* boneAnimationTransforms;
};

