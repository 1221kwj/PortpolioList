#include "stdafx.h"
#include "FbxData.h"

#include "../Model/Model.h"
#include "../Model/ModelPart.h"
#include "../Model/ModelSkeleton.h"
#include "../Model/ModelAnimationController.h"
#include "../Model/Elements/ModelMaterial.h"
#include "../Model/Elements/ModelMesh.h"
#include "../Model/Elements/ModelKeyFrame.h"
#include "../Model/Elements/ModelBone.h"
#include "../Model/Elements/ModelAnimation.h"

#include "../Utilities/BinaryFile.h"

void MaterialData::Write( BinaryWriter * w )
{
	w->UInt( number );
	w->Color4f( ambient );
	w->Color4f( diffuse );
	w->Color4f( normal );
	w->Color4f( specular );
	w->Color4f( emissive );
	w->Float( shininess );

	w->String( name );
	w->String( shaderFile );
	w->String( ambientFile );
	w->String( diffuseFile );
	w->String( normalFile );
	w->String( specularFile );
	w->String( emissiveFile );
}

void MaterialData::Write( BinaryWriter * w, ModelMaterial * material )
{
	MaterialData data = MaterialData();

	data.number = material->number;
	data.ambient = material->GetAmbient();
	data.diffuse = material->GetDiffuse();
	data.normal = material->GetNormal();
	data.specular = material->GetSpecular();
	data.emissive = material->GetEmissive();
	data.shininess = material->GetShininess();

	data.name = material->name;
	data.shaderFile = material->shaderFile;
	data.ambientFile = material->ambientFile;
	data.diffuseFile = material->diffuseFile;
	data.normalFile = material->normalFile;
	data.specularFile = material->specularFile;
	data.emissiveFile = material->emissiveFile;

	data.Write( w );
}

void MaterialData::Read( BinaryReader * r, ModelMaterial ** material )
{
	MaterialData data = MaterialData();

	data.number = r->UInt();
	data.ambient = r->Color4f();
	data.diffuse = r->Color4f();
	data.normal = r->Color4f();
	data.specular = r->Color4f();
	data.emissive = r->Color4f();
	data.shininess = r->Float();

	data.name = r->String();
	data.shaderFile = r->String();
	data.ambientFile = r->String();
	data.diffuseFile = r->String();
	data.normalFile = r->String();
	data.specularFile = r->String();
	data.emissiveFile = r->String();

	*material = new ModelMaterial( data );
}

void KeyFrameData::Write( BinaryWriter * w )
{
	w->String( name );
	w->UInt( transforms.size() );

	if ( transforms.empty() == false )
		w->Byte( &transforms[ 0 ], sizeof( D3DXMATRIX ) * transforms.size() );
}

void KeyFrameData::Write( BinaryWriter * w, KeyFrameData* data, ModelKeyFrame * keyFrame )
{
	data->name = keyFrame->name;

	for ( pair<D3DXMATRIX, ModelQuaternionKeyFrame> temp : keyFrame->quaternionKeyFrames )
		data->transforms.push_back( temp.first );
}

void KeyFrameData::Read( BinaryReader * r, ModelKeyFrame ** keyFrame )
{
	KeyFrameData data = KeyFrameData();

	data.name = r->String();

	UINT count = r->UInt();
	if ( count > 0 )
	{
		data.transforms.assign( count, D3DXMATRIX() );
		void* ptr = ( void* )&( data.transforms[ 0 ] );
		r->Byte( &ptr, sizeof( D3DXMATRIX ) * count );

		( *keyFrame ) = new ModelKeyFrame( data );
	}
}

void MeshData::Write( BinaryWriter * w )
{
	for ( size_t i = 0; i < indices.size() / 3; i++ )
	{
		UINT index0 = indices[ i * 3 + 0 ];
		UINT index1 = indices[ i * 3 + 1 ];
		UINT index2 = indices[ i * 3 + 2 ];

		D3DXVECTOR3 p0 = vertices[ index0 ].position;
		D3DXVECTOR3 p1 = vertices[ index1 ].position;
		D3DXVECTOR3 p2 = vertices[ index2 ].position;

		D3DXVECTOR3 e0 = p1 - p0;
		D3DXVECTOR3 e1 = p2 - p0;

		D3DXVECTOR2 uv0 = vertices[ index0 ].uv;
		D3DXVECTOR2 uv1 = vertices[ index1 ].uv;
		D3DXVECTOR2 uv2 = vertices[ index2 ].uv;

		float u0 = uv1.x - uv0.x;
		float u1 = uv2.x - uv0.x;
		float v0 = uv1.y - uv0.y;
		float v1 = uv2.y - uv0.y;

		float r = 1.0f / ( u0 * v1 - v0 * u1 );

		D3DXVECTOR3 tangent;
		tangent.x = r * ( v1 * e0.x - v0 * e1.x );
		tangent.y = r * ( v1 * e0.y - v0 * e1.y );
		tangent.z = r * ( v1 * e0.z - v0 * e1.z );

		D3DXVECTOR3 biNormal;
		biNormal.x = r * ( -u1 * e0.x + u0 * e1.x );
		biNormal.y = r * ( -u1 * e0.y + u0 * e1.y );
		biNormal.z = r * ( -u1 * e0.z + u0 * e1.z );

		vertices[ index0 ].tangent += tangent;
		vertices[ index1 ].tangent += tangent;
		vertices[ index2 ].tangent += tangent;

		vertices[ index0 ].biNormal += biNormal;
		vertices[ index1 ].biNormal += biNormal;
		vertices[ index2 ].biNormal += biNormal;
	}

	for ( size_t i = 0; i < vertices.size(); i++ )
	{
		D3DXVECTOR3 n = vertices[ i ].normal;
		D3DXVECTOR3 t = vertices[ i ].tangent;

		vertices[ i ].tangent = ( t - n * D3DXVec3Dot( &n, &t ) );
		D3DXVec3Normalize( &vertices[ i ].tangent, &vertices[ i ].tangent );
		D3DXVec3Normalize( &vertices[ i ].biNormal, &vertices[ i ].biNormal );
	}

	w->String( name );

	w->UInt( vertices.size() );
	if ( vertices.empty() == false )
		w->Byte( &vertices[ 0 ], sizeof( VertexTextureNormalTangentBlend ) * vertices.size() );

	w->UInt( indices.size() );
	if ( indices.empty() == false )
		w->Byte( &indices[ 0 ], sizeof( UINT ) * indices.size() );

	w->Matrix( world );
	w->Bool( bSkinnedModel );
	w->Bool( bSkinning );
}

void MeshData::Write( BinaryWriter * w, ModelMesh * mesh )
{
	MeshData data = MeshData();

	data.name = mesh->name;

	UINT count = mesh->vertexCount;
	data.vertices.assign( count, VertexTextureNormalTangentBlend() );
	memcpy( &data.vertices[ 0 ], mesh->vertexData, sizeof( VertexTextureNormalTangentBlend ) * count );

	count = mesh->indexCount;
	data.indices.assign( count, UINT() );
	memcpy( &data.indices[ 0 ], mesh->indexData, sizeof( UINT ) * count );

	data.world = mesh->matGeometricOffset;
	data.bSkinnedModel = mesh->bSkinnedModel;
	data.bSkinning = mesh->bSkinning;
	data.Write( w );
}

void MeshData::Read( BinaryReader * r, ModelMesh ** mesh )
{
	MeshData data = MeshData();

	data.name = r->String();

	UINT count = r->UInt();
	if ( count > 0 )
	{
		data.vertices.assign( count, VertexTextureNormalTangentBlend() );
		void* ptr = ( void* )&( data.vertices[ 0 ] );
		r->Byte( &ptr, sizeof( VertexTextureNormalTangentBlend ) * count );
	}

	count = r->UInt();
	if ( count > 0 )
	{
		data.indices.assign( count, UINT() );
		void* ptr = ( void* )&( data.indices[ 0 ] );
		r->Byte( &ptr, sizeof( UINT ) * count );
	}

	data.world			= r->Matrix();
	data.bSkinnedModel	= r->Bool();
	data.bSkinning		= r->Bool();

	*mesh = new ModelMesh( data );
}

void BoneData::Write( BinaryWriter * w )
{
	w->String( name );
	w->Int( parentBoneIndex );
	w->Matrix( matBindPoseTransform );
	w->Matrix( matBoneReferenceTransform );

	w->UInt( keyFrameDatas.size() );
	if ( keyFrameDatas.empty() == false )
	{
		for ( KeyFrameData* data : keyFrameDatas )
			data->Write( w );
	}
}

void BoneData::WriteOnlyBone( BinaryWriter * w )
{
	w->String( name );
	w->Int( parentBoneIndex );
	w->Matrix( matBindPoseTransform );
	w->Matrix( matBoneReferenceTransform );
}

void BoneData::WriteOnlyKeyFrame( BinaryWriter * w )
{
	w->String( name );
	
	w->UInt(keyFrameDatas.size());
	if (keyFrameDatas.empty() == false)
	{
		for (KeyFrameData* data : keyFrameDatas)
			data->Write(w);
	}
}

void BoneData::Write( BinaryWriter * w, ModelBone * bone )
{
	BoneData data = BoneData();

	data.name = bone->name;
	data.parentBoneIndex = bone->parentBoneIndex;
	data.matBindPoseTransform = bone->matBindPoseTransform;
	data.matBoneReferenceTransform = bone->matBoneReferenceTransform;

	for ( pair<string, ModelKeyFrame*> keyFrame : bone->keyFrames )
	{
		KeyFrameData* keyFrameData = new KeyFrameData();
		KeyFrameData::Write( w, keyFrameData, keyFrame.second );

		data.keyFrameDatas.push_back( keyFrameData );
	}

	data.Write( w );

	for ( KeyFrameData* temp : data.keyFrameDatas )
		SAFE_DELETE( temp );

	data.keyFrameDatas.clear();
}

void BoneData::Read( BinaryReader * r, ModelBone ** bone )
{
	BoneData data = BoneData();

	data.name = r->String();
	data.parentBoneIndex = r->Int();
	data.matBindPoseTransform = r->Matrix();
	data.matBoneReferenceTransform = r->Matrix();

	( *bone ) = new ModelBone( data );

	UINT count = r->UInt();
	if (count > 0)
	{
		for (UINT i = 0; i < count; i++)
		{
			ModelKeyFrame* keyFrame = NULL;
			KeyFrameData::Read(r, &keyFrame);
	
			(*bone)->keyFrames.push_back(make_pair(keyFrame->GetAnimationName(), keyFrame));
		}
	}
}

void BoneData::ReadOnlyBone( BinaryReader * r, ModelBone ** bone )
{
	BoneData data = BoneData();

	data.name = r->String();
	data.parentBoneIndex = r->Int();
	data.matBindPoseTransform = r->Matrix();
	data.matBoneReferenceTransform = r->Matrix();

	( *bone ) = new ModelBone( data );
}

void BoneData::ReadOnlyKeyFrame( BinaryReader * r, ModelBone ** bone )
{
	BoneData data = BoneData();
	data.name = r->String();

	( *bone ) = new ModelBone( data );

	UINT count = r->UInt();
	if (count > 0)
	{
		for (UINT i = 0; i < count; i++)
		{
			ModelKeyFrame* keyFrame = NULL;
			KeyFrameData::Read(r, &keyFrame);
	
			(*bone)->keyFrames.push_back(make_pair(keyFrame->GetAnimationName(), keyFrame));
		}
	}
}

void AnimationData::Write( BinaryWriter * w )
{
	w->String( name );
	w->Int( keyFrameCount );
	w->Float( frameRate );
	w->Int( startIndex );
}

void AnimationData::Write( BinaryWriter * w, ModelAnimation * animation )
{
	AnimationData data = AnimationData();

	data.name = animation->name;
	data.keyFrameCount = animation->keyFrameCount;
	data.frameRate = animation->frameRate;
	data.startIndex = animation->startIndex;

	data.Write( w );
}

void AnimationData::Read( BinaryReader * r, ModelAnimation ** animation )
{
	AnimationData data = AnimationData();

	data.name = r->String();
	data.keyFrameCount = r->Int();
	data.frameRate = r->Float();
	data.startIndex = r->Int();

	( *animation ) = new ModelAnimation( data );
}
