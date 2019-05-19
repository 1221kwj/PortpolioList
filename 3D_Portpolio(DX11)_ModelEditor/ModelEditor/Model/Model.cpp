#include "../stdafx.h"

#include "Model.h"
#include "ModelPart.h"
#include "ModelSkeleton.h"
#include "ModelAnimationController.h"

#include "./Elements/ModelMaterial.h"
#include "./Elements/ModelMesh.h"
#include "./Elements/ModelKeyFrame.h"
#include "./Elements/ModelBone.h"
#include "./Elements/ModelAnimation.h"

#include "./Gizmos/Gizmos.h"
#include "./Gizmos/GizmosCapsule.h"
#include "./Gizmos/GizmosSphere.h"

#include "../BinExport/FbxLoader.h"
#include "../BinExport/ModelData.h"

Model::Model()
	: name				( "" )
	, skeleton			( NULL )
	, controller		( NULL )
	, worldPosition		( 0.0f, 0.0f, 0.0f )
	, worldRotation		( 0.0f, 0.0f, 0.0f )
	, worldScale		( 1.0f, 1.0f, 1.0f )
	, angle				( 0.0f )
	, moveSpeed			( 10.0f )
	, selectBoneCount	( -1 )
	, selectedAnim		( -1 )
	, connectBoneCheck  ( false )
	, gizmosType		( 0 )
	, scaleVec			( 1, 1, 1 )
	, rotVec			( 0, 0, 0 )
	, transVec			( 0, 0, 0 )
	, height			( 0 )
	, radius			( 0 )
	, selectGizmosName  ( "" )
{
	D3DXMatrixIdentity( &worldMat );
}

Model::~Model()
{
	SAFE_DELETE( controller );
	SAFE_DELETE( skeleton );

	for ( pair<string, ModelPart*> part : parts )
		SAFE_DELETE( part.second );
}

void Model::Update()
{
	
}

void Model::Render()
{
	bool isAnimated = false;

	if ( controller != NULL )
	{
		isAnimated = controller->GetAnimationCount() > 0;

		if ( isAnimated == true )
		{
			controller->Update();

			if ( skeleton != NULL )
				skeleton->UpdateAnimation( controller );

			for ( pair<string, ModelPart*> part : parts )
			{
				if ( part.second->GetIsSkinnedModel() == true )
					part.second->UpdateAnimation( skeleton );
				else
					part.second->UpdateAnimation( controller );
			}
		}
	}

	for ( pair<string, ModelPart*> part : parts )
		part.second->Update( isAnimated );

	for ( Gizmos* collider : colliderList )
	{
		string boneName = collider->GetRefBoneName();
		collider->Update( skeleton->GetBoneBindMatrix( boneName ) * worldMat );
	}


	for ( Gizmos* collider : colliderList )
		collider->Render();

	for ( pair<string, ModelPart*> part : parts )
		part.second->Render();

	if ( selectBoneCount > -1 ) 
		skeleton->SelectedBoneRender( selectBoneCount, worldMat );
}

void Model::ImGuiBoneRender()
{
	for ( UINT i = 0; i < skeleton->GetBoneCount(); i++ )
	{
		string label = skeleton->GetBone( i )->GetName().c_str();
		if ( ImGui::Selectable( label.c_str(), selectBoneCount == i ) )
			selectBoneCount = i;
	}

	if ( ImGui::IsMouseClicked( 1 ) && selectBoneCount > -1 &&
		( ImGui::GetMousePos().x > 5 && ImGui::GetMousePos().x < 305 ) &&
		( ImGui::GetMousePos().y > 280 && ImGui::GetMousePos().y < 480 ) )
		ImGui::OpenPopup( "AddComponents" );


	if ( ImGui::BeginPopup( "AddComponents" ) )
	{
		if ( ImGui::MenuItem( "AddCapsule" ) )
		{
			GizmosCapsule* cap = new GizmosCapsule( D3DXCOLOR( 0, 1, 0, 1 ) );
			cap->SetName( "DefaultCapsule" );
			cap->SetRefBoneName( skeleton->GetBone( selectBoneCount )->GetName() );
			cap->SetTransform( skeleton->GetBone( selectBoneCount )->GetBindPoseTransform() * worldMat );
			height = cap->GetHeight();
			radius = cap->GetRadius();
			colliderList.push_back( cap );
		}

		if ( ImGui::MenuItem( "AddSphere" ) )
		{

		}

		ImGui::EndPopup();
	}

	ImGui::SetNextWindowPos( ImVec2( 315, 280 ) );
	ImGui::SetNextWindowSize( ImVec2( 300, 400 ) );

	//static int selectGizmosCount = -1;
	//static char selectGizmosName[ MAX_PATH ];

	ImGui::Begin( "Transform" );
	{
		ImGui::BeginChild( "ColliderList", ImVec2( 280, 100 ), true );
		{
			for ( size_t i = 0; i < colliderList.size(); i++ )
			{
				bool colliderCheck = ( selectGizmosCount == i );
				if ( ImGui::Selectable( colliderList[ i ]->GetName().c_str(), &colliderCheck ) )
					selectGizmosCount = i;
			}
		}
		ImGui::EndChild();

		if ( selectGizmosCount > -1 )
		{
			gizmosType	= ( int )colliderList[ selectGizmosCount ]->GetType();
			scaleVec	= colliderList[ selectGizmosCount ]->GetLocalScale();
			rotVec		= colliderList[ selectGizmosCount ]->GetLocalRotation();
			transVec	= colliderList[ selectGizmosCount ]->GetLocalTranslation();

			if ( colliderList[ selectGizmosCount ]->GetType() == GIZMOSTYPE::CAPSULE )
			{
				height = ( ( GizmosCapsule* )colliderList[ selectGizmosCount ] )->GetHeight();
				radius = ( ( GizmosCapsule* )colliderList[ selectGizmosCount ] )->GetRadius();
			}
		}

		if ( ImGui::Button( "Change" ) )
			colliderList[ selectGizmosCount ]->SetName( selectGizmosName ); 
		
		ImGui::SameLine(); ImGui::PushItemWidth( ImGui::GetContentRegionAvailWidth() );
		ImGui::InputText( "ChangeName : ", selectGizmosName, MAX_PATH ); 
		ImGui::Separator();

		switch ( gizmosType )
		{
			case 0:
			{
				ImGui::BulletText( "Component Type : " );
				ImGui::Separator();

				ImGui::BulletText( "Scale" );
				ImGui::InputFloat3( "S", scaleVec, 3 );
				ImGui::Separator();

				ImGui::BulletText( "Rotation" );
				ImGui::InputFloat3( "R", rotVec, 3 );
				ImGui::Separator();

				ImGui::BulletText( "Translation" );
				ImGui::InputFloat3( "T", transVec, 3 );
			}
			break;

			case 1:
			{

			}
			break;

			case 2:
			{
				ImGui::BulletText( "Component Type : CAPSULE" );
				ImGui::Separator();

				ImGui::BulletText( "Scale" );
				ImGui::InputFloat3( "S", scaleVec, 3 );
				ImGui::Separator();

				ImGui::BulletText( "Rotation" );
				ImGui::InputFloat3( "R", rotVec, 3 );
				ImGui::Separator();

				ImGui::BulletText( "Translation" );
				ImGui::InputFloat3( "T", transVec, 3 );
				ImGui::Separator();

				ImGui::BulletText( "Height : " ); ImGui::SameLine();
				ImGui::InputFloat( "H", &height, 0, 0, 3 );

				ImGui::BulletText( "Radius : " ); ImGui::SameLine();
				ImGui::InputFloat( "D", &radius, 0, 0, 3 );
				ImGui::Text( "¡Ø Radius Unit - Degree" );

				( ( GizmosCapsule* )colliderList[ selectGizmosCount ] )->SetLocalScale( scaleVec );
				( ( GizmosCapsule* )colliderList[ selectGizmosCount ] )->SetLocalRotation( rotVec );
				( ( GizmosCapsule* )colliderList[ selectGizmosCount ] )->SetLocalTranslation( transVec );
				( ( GizmosCapsule* )colliderList[ selectGizmosCount ] )->SetTransform( skeleton->GetBone( selectBoneCount )->GetBindPoseTransform() * worldMat );
				( ( GizmosCapsule* )colliderList[ selectGizmosCount ] )->SetRadius( radius );
				( ( GizmosCapsule* )colliderList[ selectGizmosCount ] )->SetHeight( height );
			}
			break;
		}
	}
	ImGui::End();
}

void Model::ImGuiAnimRender()
{
	if ( ImGui::Button( "AddAnim", ImVec2( 80, 25 ) ) ) AddAnimation(); ImGui::SameLine();
	bool bDelete = ImGui::Button( "Delete", ImVec2( 80, 25 ) );
	bool bPlay = ImGui::Button( "Play", ImVec2( 80, 25 ) ); ImGui::SameLine();
	bool bPause = ImGui::Button( "Pause", ImVec2( 80, 25 ) ); ImGui::SameLine();
	bool bStop = ImGui::Button( "Stop", ImVec2( 80, 25 ) );

	int count = 0;
	int curFrame = 0;
	int totalFrame = 0;

	if ( controller == NULL ) count = 0;
	else count = controller->GetAnimationCount();

	if ( controller != NULL )
	{
		curFrame = controller->GetCurrentKeyFrame();
		totalFrame = controller->GetCurrentTotalKeyFrame();
	}
	
	ImGui::PushItemWidth( ImGui::GetContentRegionAvailWidth() );
	if ( ImGui::SliderInt( "Frame", &curFrame, 0, totalFrame ) )
	{
		if ( controller != NULL )
		{
			if ( curFrame < totalFrame ) 
				controller->SetCurrentKeyFrame( curFrame );
			else if ( curFrame >= totalFrame )
				controller->SetCurrentKeyFrame( totalFrame );
			else if ( curFrame <= 0 )
				controller->SetCurrentKeyFrame( 0 );
		}
	}
	
	if ( ImGui::BeginChild( "Animations" ), ImVec2( 280, 200 ), true )
	{
		for ( int i = 0; i < count; i++ )
		{
			char temp[ MAX_PATH ];
			sprintf_s( temp, "%d. ", i + 1 );
			string label = temp + controller->GetAnimation( i )->GetName();
			if ( ImGui::Selectable( label.c_str(), selectedAnim == i ) ) selectedAnim = i;
		}
		ImGui::EndChild();
	}

	if ( selectedAnim >= 0 )
	{
		if ( bDelete )
		{
			skeleton->DeleteKeyFrame( controller->GetAnimation( selectedAnim )->GetName() );
			controller->DeleteAnimation( selectedAnim );
			selectedAnim = -1;
		}

		if ( bPlay )
		{
			controller->SetCurrentAnimation( selectedAnim );
			controller->Play();
		}
	}

	if ( bPause && controller != NULL )	controller->Pause();
	if ( bStop && controller != NULL )	controller->Stop();
}

string Model::GetBoneName( int index )
{
	return skeleton->GetBone( index )->GetName();
}

void Model::ImGuiWorldTransform()
{
	//ImGui::Indent();
	ImGui::InputFloat3( "POSITION", worldPosition, 3 );
	ImGui::InputFloat3( "ROTATION", worldRotation, 3 );
	ImGui::InputFloat3( "SCALE", worldScale, 3 );

	D3DXMATRIX T, R, S;
	D3DXQUATERNION q;
	D3DXMatrixTranslation( &T, worldPosition.x, worldPosition.y, worldPosition.z );
	D3DXMatrixScaling( &S, worldScale.x, worldScale.y, worldScale.z );

	D3DXQuaternionRotationYawPitchRoll
	( 
		&q, 
		worldRotation.y * ( float )D3DX_PI / 180.0f,
		worldRotation.x * ( float )D3DX_PI / 180.0f,
		worldRotation.z * ( float )D3DX_PI / 180.0f
	);
	D3DXMatrixRotationQuaternion( &R, &q );

	worldMat = S * R * T;

	if ( controller != NULL )
		skeleton->SetBoneScale( worldMat );

	for ( pair<string, ModelPart*> part : parts )
	{
		part.second->SetWorld( worldMat );
	}

	//for ( size_t i = 0; i < parts.size(); i++ )
	//	parts[ i ].second->SetWorld( worldMat );
}

void Model::AddAnimation( wstring file )
{
	if ( file.length() < 1 )
	{
		D3DDesc desc;
		D3D::GetDesc( &desc );

		function<void( wstring )> func = bind( &Model::AddAnimation, this, placeholders::_1 );
		Path::OpenFileDialog( L"", Path::BinAnimFilter, AnimationFolder, func, desc.Handle );
	}
	else
		ModelData::AddBinAnimation( file, this );
}