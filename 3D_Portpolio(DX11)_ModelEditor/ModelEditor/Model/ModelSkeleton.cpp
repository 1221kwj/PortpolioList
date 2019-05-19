#include "stdafx.h"
#include "ModelSkeleton.h"
#include "ModelAnimationController.h"

#include "./Buffer/ModelBuffer.h"

#include "./Elements/ModelBone.h"
#include "./Elements/ModelKeyFrame.h"
#include "./Elements/ModelAnimation.h"

ModelSkeleton::ModelSkeleton()
	: skinTransforms			( NULL )
	, boneAnimationTransforms	( NULL )
{
	boneBuffer = new BoneBuffer();
}

ModelSkeleton::~ModelSkeleton()
{
	SAFE_DELETE(boneBuffer);

	for ( pair<string, ModelBone*> temp : bones )
		SAFE_DELETE( temp.second );
	bones.clear();
	
	SAFE_DELETE_ARRAY(boneAnimationTransforms);
	SAFE_DELETE_ARRAY(skinTransforms);
}

UINT ModelSkeleton::GetBoneCount() const
{
	if (bones.empty() == true) return 0;
	else return bones.size();
}

D3DXMATRIX ModelSkeleton::GetBoneBindMatrix( string name )
{
	for ( size_t i = 0; i < bones.size(); i++ )
	{
		if ( bones[ i ].first == name )
		{
			if ( bones[ i ].second->GetKeyFrameCount() < 1 )
				return bones[ i ].second->GetBindPoseTransform();
			else
				return boneAnimationTransforms[ i ];
		}
	}
}

const D3DXMATRIX & ModelSkeleton::GetBoneScale() const
{
	return boneBuffer->GetBoneScale();
}

void ModelSkeleton::UpdateAnimation(ModelAnimationController * controller)
{
	ModelAnimation* currentAnimation = controller->GetCurrentAnimation();
	int keyFrame = controller->GetCurrentKeyFrame();

	if (currentAnimation == NULL) return;

	BuildBoneTransforms( controller, currentAnimation->GetName() );
	
	int boneCount = bones.size();
	boneCount = ( boneCount < BoneWeightData::MaxBonesPerMax ) ? boneCount : BoneWeightData::MaxBonesPerMax;

	boneBuffer->SetBoneArray(skinTransforms, boneCount);
	boneBuffer->SetVSBuffer(2);
}

void ModelSkeleton::SetBoneScale( D3DXMATRIX mat )
{
	boneBuffer->SetBoneScale( mat );
}

void ModelSkeleton::SelectedBoneRender( int index, D3DXMATRIX mat )
{
	D3DXMATRIX worldMatrix;
	D3DXMatrixIdentity( &worldMatrix );

	if ( bones[ index ].second->GetKeyFrameCount() < 1 )
		worldMatrix = bones[ index ].second->GetBindPoseTransform() * mat;
	else
		worldMatrix = boneAnimationTransforms[ index ] * mat;

	bones[ index ].second->SphereRender( worldMatrix );
}

void ModelSkeleton::DeleteKeyFrame( string name )
{
	for ( size_t i = 0; i < bones.size(); i++ )
		bones[ i ].second->DeleteKeyFrame( name );
}

void ModelSkeleton::BuildBoneTransforms(ModelAnimationController * controller, const string & name)
{
	if ( skinTransforms == NULL )
		skinTransforms = new D3DXMATRIX[ bones.size() ];

	if ( boneAnimationTransforms == NULL )
		boneAnimationTransforms = new D3DXMATRIX[ bones.size() ];

	int keyFrame = controller->GetCurrentKeyFrame();
	int nextKeyFrame = controller->GetNextKeyFrame();
	float keyframeFactor = controller->GetKeyFrameFactor();
	bool useQuaterniokeyFrames = controller->GetUseQuaternionKeyFrames();

	int index = 0;
	BoneArray::const_iterator it = bones.begin();
	for (; it != bones.end(); ++it)
	{
		ModelBone* bone = it->second;

		D3DXMATRIX matInvBindPose = bone->GetInvBindPoseTransform();
		D3DXMATRIX matBoneReference = bone->GetBoneReferenceTransform();
		D3DXMATRIX matAnimation;
		D3DXMATRIX matParentAnimation;

		D3DXMATRIX matFirstRootTransform;

		ModelKeyFrame* modelKeyFrame = bone->GetKeyFrame(name);

		if ( modelKeyFrame != NULL )
		{
			if ( useQuaterniokeyFrames == true )
			{
				const ModelQuaternionKeyFrame& qKeyFrame1 = modelKeyFrame->GetQuaternionKeyFrame( keyFrame );
				const ModelQuaternionKeyFrame& qKeyFrame2 = modelKeyFrame->GetQuaternionKeyFrame( nextKeyFrame );
				const D3DXQUATERNION& q1 = qKeyFrame1.GetQuaternion();
				const D3DXQUATERNION& q2 = qKeyFrame2.GetQuaternion();
				const D3DXQUATERNION& minus_q2 = -q2;

				D3DXQUATERNION q;

				if ( D3DXQuaternionLengthSq( &( q1 - q2 ) ) > D3DXQuaternionLengthSq( &( q1 + q2 ) ) )
					D3DXQuaternionSlerp( &q, &q1, &minus_q2, keyframeFactor );
				else
					D3DXQuaternionSlerp( &q, &q1, &q2, keyframeFactor );

				D3DXMatrixRotationQuaternion( &matAnimation, &q );

				D3DXVECTOR3 t1 = qKeyFrame1.GetTranslation();
				D3DXVECTOR3 t2 = qKeyFrame2.GetTranslation();


				D3DXVECTOR3 vTranslation;
				D3DXVec3Lerp( &vTranslation, &t1, &t2, keyframeFactor );

				matAnimation._41 = vTranslation.x;
				matAnimation._42 = vTranslation.y;
				matAnimation._43 = vTranslation.z;
			}
			else
				matAnimation = modelKeyFrame->GetKeyFrameTransform( keyFrame );
		}

		int parentBoneIndex = bone->GetParentBoneIndex();
		if (parentBoneIndex < 0)
		{
			D3DXMatrixIdentity(&matParentAnimation);

			// 루트 모션을 첫번째 프레임 값으로 고정
			//matAnimation = modelKeyFrame->GetKeyFrameTransform(0);

			// 루트 모션을 변경하지 않음
			//matAnimation = bone->GetBindPoseTransform();
		}
		else matParentAnimation = boneAnimationTransforms[parentBoneIndex];

		boneAnimationTransforms[index] = matAnimation * matParentAnimation;
		skinTransforms[index] = matInvBindPose *  boneAnimationTransforms[index];

		index++;
	}
}