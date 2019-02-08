#include "stdafx.h"
#include "GameAnimModel.h"

#include "../ModelComponents/ModelClip.h"
#include "../ModelComponents/ModelTweener.h"
#include "../ModelComponents/ModelComponents.h"

GameAnimModel::GameAnimModel( wstring matFolder, wstring matFile, wstring meshFolder, wstring meshFile )
	: GameModel
	( 
		matFolder, 
		matFile, 
		meshFolder, 
		meshFile
	)
{
	tweener = new ModelTweener();

	modelBones = model->GetComponent<ModelBones>( L"Bone" );
}

GameAnimModel::~GameAnimModel()
{
	for ( ModelClip* clip : clips )
		SAFE_DELETE( clip );

	SAFE_DELETE( tweener );
}

void GameAnimModel::Update()
{
	__super::Update();

	CalcPosition();

	for ( UINT i = 0; i < modelBones->BoneCount(); i++ )
	{
		ModelBone* bone = modelBones->BoneByIndex( i );

		tweener->UpdateBlending( bone, Time::Delta() );
	}
}

UINT GameAnimModel::AddClip( wstring file, float startTime )
{
	ModelClip* clip = new ModelClip( file );
	clips.push_back( clip );

	return ( UINT )clips.size() - 1;
}

void GameAnimModel::LockRoot( UINT index, bool val )
{
	clips[ index ]->LockRoot( val );
}

void GameAnimModel::Repeat( UINT index, bool val )
{
	clips[ index ]->Repeat( val );
}

void GameAnimModel::Speed( UINT index, float val )
{
	clips[ index ]->Speed( val );
}

void GameAnimModel::Play( UINT index, bool bRepeat, float blendTime, float speed, float startTime )
{
	tweener->Play( clips[ index ], bRepeat, blendTime, speed, startTime );
}
