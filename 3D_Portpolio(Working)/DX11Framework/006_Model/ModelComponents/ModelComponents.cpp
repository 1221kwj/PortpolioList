#include "stdafx.h"

#include "ModelComponents.h"
#include "ModelMesh.h"
#include "ModelBone.h"

// ======================================================================
//								Material Component
// ======================================================================
ModelMaterials::ModelMaterials()
{
	SetTypeName	( TYPENAME_MATERIAL );
	SetTypeID	( COMPONENTTYPEID::TYPEID_MATERIAL );
}

ModelMaterials::~ModelMaterials()
{
	for ( Material* m : materials )
		SAFE_DELETE( m );

	materials.clear();
}

UINT ModelMaterials::MaterialCount()
{ 
	return ( UINT )materials.size();
}

vector<Material*>& ModelMaterials::Materials()
{ 
	return materials;
}

Material* ModelMaterials::MaterialByIndex( UINT index )
{ 
	return materials[ index ];
}

Material * ModelMaterials::MaterialByName( wstring name )
{
	for ( Material* material : materials )
	{
		if ( material->Name() == name )
			return material;
	}

	return NULL;
}

void ModelMaterials::AddMaterial( Material * m )
{
	materials.push_back( m );
}
// ======================================================================

// ======================================================================
//									Mesh Component
// ======================================================================
ModelMeshes::ModelMeshes()
{
	SetTypeName	( TYPENAME_MESH );
	SetTypeID	( COMPONENTTYPEID::TYPEID_MESH );
}

ModelMeshes::~ModelMeshes()
{
	for ( ModelMesh* mesh : meshes )
		SAFE_DELETE( mesh );

	meshes.clear();
}

UINT ModelMeshes::MeshCount()
{
	return ( UINT )meshes.size();
}

vector<class ModelMesh*>& ModelMeshes::Meshes()
{
	return meshes;
}

ModelMesh * ModelMeshes::MeshByIndex( UINT index )
{
	return meshes[ index ];
}

ModelMesh * ModelMeshes::MeshByName( wstring name )
{
	for ( ModelMesh* mesh : meshes )
	{
		if ( mesh->Name() == name )
			return mesh;
	}

	return NULL;
}

void ModelMeshes::AddMesh( ModelMesh * m )
{
	meshes.push_back( m );
}
// ======================================================================

// ======================================================================
//								Bone Component
// ======================================================================

ModelBones::ModelBones()
{
	SetTypeName	( TYPENAME_BONE );
	SetTypeID	( COMPONENTTYPEID::TYPEID_BONE );
}

ModelBones::~ModelBones()
{
	for ( ModelBone* b : bones )
		SAFE_DELETE( b );

	bones.clear();
}

UINT ModelBones::BoneCount()
{
	return ( UINT )bones.size();
}

vector<ModelBone*>& ModelBones::Bones()
{
	return bones;
}

ModelBone * ModelBones::BoneByIndex( UINT index )
{
	return bones[ index ];
}

ModelBone * ModelBones::BoneByName( wstring name )
{
	for ( ModelBone* bone : bones )
	{
		if ( bone->Name() == name )
			return bone;
	}

	return NULL;
}

void ModelBones::AddBone( ModelBone * b )
{
	bones.push_back( b );
}

void ModelBones::SetRootBone( ModelBone * root )
{
	this->root = root;
}

ModelBone * ModelBones::GetRootBone()
{
	return root;
}
// ======================================================================

// ======================================================================
//								Transform
// ======================================================================

Transform::Transform() 
	: Scale			( 1.0f, 1.0f, 1.0f )
	, Rotation		( 0.0f, 0.0f, 0.0f )
	, Translation	( 0.0f, 0.0f, 0.0f )
	, Up			( 0.0f, 1.0f, 0.0f )
	, Right			( 1.0f, 0.0f, 0.0f )
	, Forward		( 0.0f, 0.0f, 1.0f )

{
	World = Math::IdentityMatrix();
	Local = Math::IdentityMatrix();

	SetTypeName	( TYPENAME_TRANSFORM );
	SetTypeID	( COMPONENTTYPEID::TYPEID_TRANSFORM );
}

Transform::~Transform()
{
}

void Transform::SetScale( float x, float y, float z )
{
	SetScale( Vector3( x, y, z ) );
}

void Transform::SetScale( Vector3& scale )
{
	Scale = scale; 
	
	UpdateWorld();
}

void Transform::GetScale( Vector3* scale )
{
	*scale = Scale;
}

void Transform::SetRotation( float x, float y, float z )
{
	SetRotation( Vector3( x, y, z ) );
}

void Transform::SetRotation( Vector3& rotation )
{
	Rotation = rotation;

	UpdateWorld();
}

void Transform::SetRotationDegree( float x, float y, float z )
{
	SetRotationDegree( Vector3( x, y, z ) );
}

void Transform::SetRotationDegree( Vector3& rotation )
{
	Vector3 temp = Vector3
	(
		XMConvertToRadians( rotation.x ),
		XMConvertToRadians( rotation.y ),
		XMConvertToRadians( rotation.z )
	);

	SetRotation( temp );
}

void Transform::GetRotation( Vector3* rotation )
{
	*rotation = Rotation;
}

void Transform::GetRotationDegree( Vector3* rotation )
{
	*rotation = Vector3
	(
		XMConvertToDegrees( Rotation.x ),
		XMConvertToDegrees( Rotation.y ),
		XMConvertToDegrees( Rotation.z )
	);
}

void Transform::SetTranslation( Vector3& translation )
{
	Translation = translation;

	UpdateWorld();
}

void Transform::SetTranslation( float x, float y, float z )
{
	SetTranslation( Vector3( x, y, z ) );
}

void Transform::GetTranslation( Vector3* translation )
{
	*translation = Translation;
}

void Transform::GetForward( Vector3* forward )
{
	*forward = Forward;
}

void Transform::GetUp( Vector3* up )
{
	*up = Up;
}

void Transform::GetRight( Vector3* right )
{
	*right = Right;
}

void Transform::SetWorld( XMFLOAT4X4& world )
{
	World = world;
}

void Transform::GetWorld( XMFLOAT4X4* world )
{
	*world = World;
}

void Transform::SetLocal( XMFLOAT4X4& local )
{
	Local = local;
}

void Transform::GetLocal(XMFLOAT4X4* local)
{
	*local = Local;
}

void Transform::UpdateWorld()
{
	XMMATRIX S = XMMatrixScaling( Scale.x, Scale.y, Scale.z );
	XMMATRIX R = XMMatrixRotationRollPitchYaw( Rotation.x, Rotation.y, Rotation.z );
	XMMATRIX T = XMMatrixTranslation( Translation.x, Translation.y, Translation.z );

	XMStoreFloat4x4( &Local, S * R * T );

	Forward = Vector3( Local._31, Local._32, Local._33 );
	Up		= Vector3( Local._21, Local._22, Local._23 );
	Right	= Vector3( Local._11, Local._12, Local._13 );
}