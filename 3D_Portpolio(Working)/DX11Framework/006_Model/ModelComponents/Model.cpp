#include "stdafx.h"
#include "Model.h"
#include "ModelBone.h"
#include "ModelMesh.h"
#include "ModelComponents.h"

Model::Model() {}
Model::~Model()
{
	for ( Pair c : components )
		SAFE_DELETE( c.second );

	components.clear();
}

void Model::CopyGlobalBoneTo( vector<XMFLOAT4X4>& transforms )
{
	XMFLOAT4X4 w = Math::IdentityMatrix();

	CopyGlobalBoneTo( transforms, w );
}

void Model::CopyGlobalBoneTo( vector<XMFLOAT4X4>& transforms, XMFLOAT4X4 & w )
{
	ModelBones* m = GetComponent<ModelBones>( L"Bone" );
	size_t s = m->BoneCount();

	transforms.clear();
	transforms.assign( s, XMFLOAT4X4() );

	for ( UINT i = 0; i < ( UINT )s; i++ )
	{
		ModelBone* bone = m->BoneByIndex( i );

		if ( bone->Parent() != NULL )
		{
			int		 index	= bone->parent->index;
			XMMATRIX local	= XMLoadFloat4x4( &bone->local );
			XMMATRIX trans	= XMLoadFloat4x4( &transforms[ index ] );
			XMMATRIX mat	= local * trans;
			
			XMStoreFloat4x4( &transforms[ i ], mat );
		}
		else
		{
			XMMATRIX local	= XMLoadFloat4x4( &bone->local );
			XMMATRIX world	= XMLoadFloat4x4( &w );
			XMMATRIX mat	= local * world;

			XMStoreFloat4x4( &transforms[ i ], mat );
		}
	}
}

// ======================================================================
//								Models
// ======================================================================
void Models::Create()
{
}

void Models::Delete()
{
	for ( pair<wstring, vector<Material *>> temp : materialMap )
	{
		for ( Material* material : temp.second )
			SAFE_DELETE( material );
	}
	materialMap.clear();

	for ( pair<wstring, MeshData> temp : meshDataMap )
	{
		MeshData data = temp.second;

		for ( ModelBone* bone : data.Bones )
			SAFE_DELETE( bone );

		for ( ModelMesh* mesh : data.Meshes )
			SAFE_DELETE( mesh );
	}

	meshDataMap.clear();
}
