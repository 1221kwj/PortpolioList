#include "stdafx.h"

#include "ModelBone.h"
#include "ModelKeyFrame.h"

#include "../Gizmos/GizmosSphere.h"

#include "../../BinExport/FbxData.h"

ModelBone::ModelBone(const BoneData& data)
	: name( "" )
{
	D3DXMatrixIdentity(&matBindPoseTransform);
	D3DXMatrixIdentity(&matInvBindPoseTransform);
	D3DXMatrixIdentity(&matBoneReferenceTransform);
	D3DXMatrixIdentity(&matInvBoneReferenceTransform);

	this->name = data.name;
	this->parentBoneIndex = data.parentBoneIndex;

	SetBindPoseTransform(data.matBindPoseTransform);
	SetBoneReferenceTransform(data.matBoneReferenceTransform);

	sphere = new GizmosSphere( D3DXCOLOR( 1, 0, 0, 1 ) );
	sphere->SetRefBoneName( this->name );
}

ModelBone::~ModelBone()
{
	for (pair<string, ModelKeyFrame*> temp : keyFrames)
		SAFE_DELETE(temp.second);
}

void ModelBone::SetBindPoseTransform(const D3DXMATRIX & matBindPoseTransform)
{
	this->matBindPoseTransform = matBindPoseTransform;
	D3DXMatrixInverse(&this->matInvBindPoseTransform, NULL, &this->matBindPoseTransform);
}

void ModelBone::SetBoneReferenceTransform(const D3DXMATRIX & matBoneReferenceTransform)
{
	this->matBoneReferenceTransform = matBoneReferenceTransform;
	D3DXMatrixInverse(&this->matInvBoneReferenceTransform, NULL, &this->matBoneReferenceTransform);
}

void ModelBone::SphereRender( D3DXMATRIX mat )
{
	sphere->SetDepthState( false );
	sphere->SetTransform( mat );
	sphere->Render();
}

ModelKeyFrame * ModelBone::GetKeyFrame(const string & name)
{
	for (pair<string, ModelKeyFrame*> temp : keyFrames)
	{
		if ( temp.first == name )
		{
			return temp.second;
		}
	}

	return NULL;
}

void ModelBone::DeleteKeyFrame( string name )
{
	for ( size_t i = 0; i < keyFrames.size(); i++ )
	{
		if ( keyFrames[ i ].first == name )
		{
			SAFE_DELETE( keyFrames[ i ].second );
			keyFrames.erase( keyFrames.begin() + i );
		}
	}
}
