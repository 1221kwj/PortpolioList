#include "stdafx.h"

#include "ModelPart.h"
#include "ModelSkeleton.h"
#include "ModelAnimationController.h"

#include "./Elements/ModelMaterial.h"
#include "./Elements/ModelMesh.h"
#include "./Elements/ModelKeyFrame.h"
#include "./Elements/ModelAnimation.h"
#include "./Elements/ModelBone.h"

#include "./Buffer/ModelBuffer.h"

ModelPart::ModelPart()
	: material	( NULL )
	, mesh		( NULL )
	, bAnimated	( false )
	, bSelected ( false )
{
	D3DXMatrixIdentity( &world );
	D3DXMatrixIdentity( &worldMat );
	D3DXMatrixIdentity( &matAnimationTransform );

	worldBuffer = new WorldBuffer();
	meshBuffer = new MeshBuffer();
}

ModelPart::~ModelPart()
{
	SAFE_DELETE( worldBuffer );
	SAFE_DELETE( meshBuffer );

	SAFE_DELETE( mesh );
	SAFE_DELETE( material );
}

bool ModelPart::GetIsSkinnedModel()
{
	return mesh->GetIsSkinnedModel();
}

string ModelPart::GetName() { return mesh->GetName(); }

void ModelPart::Update( bool isAnimation )
{
	bAnimated = isAnimation;

	D3DXMATRIX matGeometricOffset = mesh->GetGeometricOffset();

	if ( isAnimation == true )
	{
		if ( mesh->GetIsSkinnedModel() == true )
			world = matGeometricOffset * matAnimationTransform;
		else
			world = matGeometricOffset;
	}
	else
		world = matGeometricOffset;

	D3DXMATRIX a = world;

	//world = localMatrix * worldMat;
}

void ModelPart::UpdateAnimation( ModelAnimationController * controller )
{
	if ( controller != NULL )
	{
		ModelAnimation* animation = controller->GetCurrentAnimation();

		if ( animation != NULL )
		{
			ModelKeyFrame* keyFrames = mesh->GetModelKeyFrame( animation->GetName() );

			if ( keyFrames != NULL )
			{
				int keyFrame = controller->GetCurrentKeyFrame();
				matAnimationTransform = keyFrames->GetKeyFrameTransform( keyFrame );
				return;
			}
		}
	}

	D3DXMatrixIdentity( &matAnimationTransform );
}

void ModelPart::UpdateAnimation( ModelSkeleton * skeleton )
{
	if ( skeleton != NULL )
	{
		D3DXMATRIX* skinTransforms = skeleton->GetSkinTransforms();
		if ( skinTransforms != NULL )
		{
			matAnimationTransform = skinTransforms[ mesh->GetBoneIndex() ] * skeleton->GetBoneScale();
			return;
		}
	}

	D3DXMatrixIdentity( &matAnimationTransform );
}

void ModelPart::SetWorld( D3DXMATRIX mat )
{
	mesh->SetGeometricOffset( mat );
}

void ModelPart::Render()
{
	ID3D11Buffer* vertexBuffer	= mesh->GetVertexBuffer();
	ID3D11Buffer* indexBuffer	= mesh->GetIndexBuffer();
	UINT indexCount = mesh->GetIndexCount();

	bool bSkinning = false;
	if ( bAnimated == true )
		bSkinning = mesh->GetIsSkinning();
	//bool bSkinning = true;

	UINT stride = sizeof( VertexTextureNormalTangentBlend );
	UINT offset = 0;

	D3D::GetDC()->IASetVertexBuffers( 0, 1, &vertexBuffer, &stride, &offset );
	D3D::GetDC()->IASetIndexBuffer( indexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	D3D::GetDC()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	worldBuffer->SetMatrix( world );
	worldBuffer->SetVSBuffer( 1 );

	material->SetPSBuffer();

	meshBuffer->SetSkinning( bSkinning );
	meshBuffer->SetVSBuffer( 3 );

	D3D::GetDC()->DrawIndexed( indexCount, 0, 0 );
}

void ModelPart::ImGuiRender( bool bSelected )
{
	ImGui::SetNextWindowPos( ImVec2( 315, 20 ) );
	ImGui::SetNextWindowSize( ImVec2( 300, 250 ) );
	ImGui::SetNextWindowBgAlpha( 0.8f );

	ImGui::Begin( "Material", &bSelected );
	{
		material->ImGuiRender( bSelected );
	}
	ImGui::End();
}
