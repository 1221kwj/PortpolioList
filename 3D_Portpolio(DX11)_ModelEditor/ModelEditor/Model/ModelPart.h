#pragma once

class ModelPart
{
	friend class ModelData;

public:
	virtual ~ModelPart();

	bool GetIsSkinnedModel();
	class ModelMaterial* GetMaterial() { return material; }
	class ModelMesh* GetMesh() { return mesh; }

	string GetName();

	void Update( bool isAnimation = false );
	void UpdateAnimation(class ModelAnimationController* controller);
	void UpdateAnimation( class ModelSkeleton* skeleton );

	void SetWorld( D3DXMATRIX mat );

	void Render();
	void ImGuiRender( bool bSelected );

private:
	ModelPart();

private:
	class WorldBuffer*		worldBuffer;
	class MeshBuffer*		meshBuffer;
	class ModelMaterial*	material;
	class ModelMesh*		mesh;

	bool bAnimated;
	bool bSelected;

	D3DXMATRIX matAnimationTransform;
	D3DXMATRIX world;
	D3DXMATRIX worldMat;
};