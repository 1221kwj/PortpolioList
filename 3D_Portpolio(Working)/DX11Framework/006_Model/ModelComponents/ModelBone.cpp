#include "stdafx.h"
#include "ModelBone.h"
#include "ModelComponents.h"

ModelBone::ModelBone() : parent( NULL )
{
	Transform* trans = new Transform();
	components.insert( pair<wstring, Component*>( trans->GetTypeName(), trans ) );
}

ModelBone::~ModelBone()
{
	for ( Pair c : components )
		SAFE_DELETE( c.second );
}

int ModelBone::Index()
{
	return index;
}

int ModelBone::ParentIndex()
{
	return parentIndex;
}

ModelBone * ModelBone::Parent()
{
	return parent;
}

UINT ModelBone::ChildCount()
{
	return ( UINT )childs.size();
}

ModelBone * ModelBone::Child( UINT index )
{
	return childs[ index ];
}

vector<ModelBone*>& ModelBone::GetChilds()
{
	return childs;
}

wstring ModelBone::Name()
{
	return name;
}

XMFLOAT4X4 & ModelBone::Local()
{
	return local;
}

void ModelBone::Local( XMFLOAT4X4 & matrix )
{
	local = matrix;
}

XMFLOAT4X4 & ModelBone::Global()
{
	return global;
}

void ModelBone::Global( XMFLOAT4X4 & matrix )
{
	global = matrix;
}

void ModelBone::Clone( ModelBone ** clone )
{
	ModelBone* bone		= new ModelBone();
	bone->index			= index;
	bone->name			= name;
	bone->parentIndex	= parentIndex;
	bone->local			= local;
	bone->global		= global;

	XMMATRIX lclMat = XMLoadFloat4x4( &local );

	XMVECTOR scale, rotation, translation;
	XMMatrixDecompose( &scale, &rotation, &translation, lclMat );

	Vector3 vScale			= Vector3	::Zero();
	Vector3 vRotation		= Math		::QuaternionToEuler( rotation );
	Vector3 vTranslation	= Vector3	::Zero();
	
	XMStoreFloat3( &vScale, scale );
	XMStoreFloat3( &vTranslation, translation );

	Transform* trans = bone->GetComponent<Transform>( TYPENAME_TRANSFORM );
	trans->SetScale			( vScale );
	trans->SetRotation		( vRotation );
	trans->SetTranslation	( vTranslation );

	*clone = bone;
}