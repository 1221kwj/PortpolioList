#include "stdafx.h"
#include "ModelClip.h"
#include "ModelBone.h"

#include "../../001_Utilities/BinaryFile.h"

ModelClip::ModelClip( wstring file )
	: playTime	( 0.0f )
	, bRepeat	( false )
	, speed		( 1.0f )
	, bLockRoot	( false )
{
	BinaryReader* r = new BinaryReader();
	r->Open( file );

	name		= String::ToWString( r->String() );
	duration	= r->Float();
	frameRate	= r->Float();
	frameCount	= r->UInt();

	UINT keyframesCount = r->UInt();
	for ( UINT i = 0; i < keyframesCount; i++ )
	{
		ModelKeyframe* keyframe = new ModelKeyframe();
		
		keyframe->boneName		= String::ToWString( r->String() );
		keyframe->duration		= duration;
		keyframe->frameCount	= frameCount;
		keyframe->frameRate		= frameRate;

		UINT size = r->UInt();
		if ( size > 0 )
		{
			keyframe->transforms.assign( size, ModelKeyframe::Transform() );

			void* ptr = ( void * )&keyframe->transforms[ 0 ];
			r->Byte( &ptr, sizeof( ModelKeyframe::Transform ) * size );
		}

		keyframeMap.insert( Pair( keyframe->boneName, keyframe ) );
	}

	r->Close();
	SAFE_DELETE( r );
}

ModelClip::~ModelClip()
{
	for ( Pair keyframe : keyframeMap )
		SAFE_DELETE( keyframe.second );

	keyframeMap.clear();
}

void ModelClip::Reset()
{
	bRepeat		= false;
	speed		= 1.0f;
	playTime	= 0.0f;
}

XMFLOAT4X4 ModelClip::GetKeyframeMatrix( ModelBone * bone, float time )
{
	wstring boneName = bone->Name();
	unordered_map<wstring, ModelKeyframe *>::iterator it;
	if ( ( it = keyframeMap.find( boneName ) ) == keyframeMap.end() )
	{
		XMFLOAT4X4 temp = Math::IdentityMatrix();
		return temp;
	}

	ModelKeyframe* keyframe = keyframeMap.at( boneName );

	playTime += speed * time;
	if ( bRepeat == true )
	{
		if ( playTime >= duration )
		{
			while ( playTime - duration >= 0 )
				playTime -= duration;
		}
	}
	else
	{
		if ( playTime >= duration )
			playTime = duration;
	}

	XMMATRIX globalMat	= XMLoadFloat4x4( &bone->Global() );
	XMMATRIX invGlobal	= XMMatrixInverse( NULL, globalMat );
	XMMATRIX animation	= XMLoadFloat4x4 ( &keyframe->GetInterpolatedMatrix( playTime, bRepeat ) );
	XMMATRIX parent		= XMMatrixIdentity();

	int parentIndex = bone->ParentIndex();

	if ( parentIndex < 0 )
	{
		if ( bLockRoot == true )
			parent = XMMatrixIdentity();
		else
			parent = animation;
	}
	else
	{
		XMMATRIX pGlobalMat = XMLoadFloat4x4( &bone->Parent()->Global() );

		parent = animation * pGlobalMat;
	}

	XMFLOAT4X4 mat = Math::IdentityMatrix();

	XMStoreFloat4x4( &mat, invGlobal * parent );

	return mat;
}

void ModelClip::UpdateKeyframe( ModelBone * bone, float time )
{
	XMFLOAT4X4 animation = GetKeyframeMatrix( bone, time );
	
	bone->Local( animation );
}
