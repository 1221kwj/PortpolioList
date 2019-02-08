#pragma once

#include "stdafx.h"
#include "Component.h"

const wstring TYPENAME_MATERIAL		= L"MATERIAL";
const wstring TYPENAME_MESH			= L"MESH";
const wstring TYPENAME_BONE			= L"BONE";
const wstring TYPENAME_TRANSFORM	= L"TRANSFORM";
// ======================================================================
//								Material Component
// ======================================================================
class ModelMaterials : public Component
{
public:
	ModelMaterials();
	~ModelMaterials();

	UINT						MaterialCount	();
	vector< class Material *>&	Materials		();
	class Material*				MaterialByIndex	( UINT index );
	class Material*				MaterialByName	( wstring name );
	void						AddMaterial		( class Material* m );

private:
	vector<class Material*> materials;
};
// ======================================================================

// ======================================================================
//									Mesh Component
// ======================================================================
class ModelMeshes : public Component
{
public:
	ModelMeshes();
	~ModelMeshes();

	UINT						MeshCount	();
	vector<class ModelMesh *>&	Meshes		();
	class ModelMesh*			MeshByIndex	( UINT index );
	class ModelMesh*			MeshByName	( wstring name );
	void						AddMesh		( class ModelMesh* m );

private:
	vector<class ModelMesh *> meshes;
};
// ======================================================================

// ======================================================================
//								Bone Component
// ======================================================================
class ModelBones : public Component
{
public:
	ModelBones();
	~ModelBones();
	
	UINT						BoneCount	();
	vector<class ModelBone *>&	Bones		();
	class ModelBone*			BoneByIndex	( UINT index );
	class ModelBone*			BoneByName	( wstring name );
	void						AddBone		( class ModelBone* b );
	void						SetRootBone	( class ModelBone* root );
	class ModelBone*			GetRootBone	();

private:
	class ModelBone*			root;
	vector<class ModelBone*>	bones;
};
// ======================================================================

// ======================================================================
//								Transform
// ======================================================================
class Transform : public Component
{
public:
	Transform();
	~Transform();

	void SetScale				( float x, float y, float z );
	void SetScale				( Vector3& scale ); 
	void GetScale				( Vector3* scale );
	
	void SetRotation			( float x, float y, float z ); 
	void SetRotation			( Vector3& rotation ); 
	void SetRotationDegree		( float x, float y, float z );
	void SetRotationDegree		( Vector3& rotation );
	void GetRotation			( Vector3* rotation );
	void GetRotationDegree		( Vector3* rotation );
	
	void SetTranslation			( float x, float y, float z );
	void SetTranslation			( Vector3& translation ); 
	void GetTranslation			( Vector3* translation );

	void GetForward				( Vector3* forward );
	void GetUp					( Vector3* up );
	void GetRight				( Vector3* right );

	void SetWorld				( XMFLOAT4X4& world );
	void GetWorld				( XMFLOAT4X4* world );
	
	void SetLocal				( XMFLOAT4X4& local );
	void GetLocal				( XMFLOAT4X4* local );

	void UpdateWorld			();

private:
	Vector3 Scale;
	Vector3 Rotation;
	Vector3 Translation;

	Vector3 Up;
	Vector3 Right;
	Vector3 Forward;

	XMFLOAT4X4 World;
	XMFLOAT4X4 Local;
};
// ======================================================================