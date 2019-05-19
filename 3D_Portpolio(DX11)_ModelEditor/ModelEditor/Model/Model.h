#pragma once

class Model
{
	friend class FbxLoader;
	friend class ModelData;
	friend class UserInterface;

public:
	virtual ~Model();

	void Update();
	void Render();
	void ImGuiBoneRender();
	void ImGuiAnimRender();

	class ModelAnimationController* GetAnimController() { return controller; }
	
	UINT GetModelPartSize() { return parts.size(); }
	
	class ModelPart* GetModelPart(UINT index) { return parts[index].second; }
	
	string GetName() { return name; }
	
	class ModelSkeleton* GetSkeleton() { return skeleton; }
	string GetBoneName( int index );

	bool GetIsConnectBoneButton() { return connectBoneCheck; }
	int GetCurBoneNum() { return selectBoneCount; }

	void ImGuiWorldTransform();

private:
	Model();

private:
	void AddAnimation( wstring file = L"" );

	string name;

	vector<pair<string, class ModelPart*>> parts;
	class ModelSkeleton* skeleton;
	class ModelAnimationController* controller;
	vector<class Gizmos*> colliderList;
	
	D3DXVECTOR3 worldPosition;
	D3DXVECTOR3 worldScale;
	D3DXVECTOR3 worldRotation;
	D3DXMATRIX worldMat;
	D3DXMATRIX world;
	
	float angle;
	float moveSpeed;

	int selectBoneCount;
	int selectedAnim;
	int gizmosType;

	bool connectBoneCheck;

	D3DXVECTOR3 scaleVec;
	D3DXVECTOR3 rotVec;
	D3DXVECTOR3 transVec;
	float height;
	float radius;

	int selectGizmosCount = -1;
	char selectGizmosName[ MAX_PATH ];
};