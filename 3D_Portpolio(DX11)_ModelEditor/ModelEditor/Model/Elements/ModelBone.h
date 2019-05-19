#pragma once

class ModelBone
{
	friend class ModelData;
	friend struct BoneData;
	typedef vector<pair<string, class ModelKeyFrame*>> KeyFrameArray;

public:
	virtual ~ModelBone();

	class ModelKeyFrame* GetKeyFrame(const string& name);

	const D3DXMATRIX& GetBindPoseTransform() const { return matBindPoseTransform; }
	const D3DXMATRIX& GetInvBindPoseTransform() const { return matInvBindPoseTransform; }
	const D3DXMATRIX& GetBoneReferenceTransform() const { return matBoneReferenceTransform; }
	const D3DXMATRIX& GetInvBoneReferenceTransform() const { return matInvBoneReferenceTransform; }

	string GetName() const { return name; }
	int GetParentBoneIndex() const { return parentBoneIndex; }

	void SetBindPoseTransform(const D3DXMATRIX& matBindPoseTransform);
	void SetBoneReferenceTransform(const D3DXMATRIX& matBoneReferenceTransform);
	void SphereRender( D3DXMATRIX mat );

	int GetKeyFrameCount() { return keyFrames.size(); }

	void DeleteKeyFrame( string name );

private:
	ModelBone(const BoneData& data);

private:
	string name;

	int parentBoneIndex;

	D3DXMATRIX matBindPoseTransform;
	D3DXMATRIX matInvBindPoseTransform;
	D3DXMATRIX matBoneReferenceTransform;
	D3DXMATRIX matInvBoneReferenceTransform;

	KeyFrameArray keyFrames;

	class GizmosSphere* sphere;
};
