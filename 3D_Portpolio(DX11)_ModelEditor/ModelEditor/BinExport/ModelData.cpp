#include "stdafx.h"
#include "ModelData.h"
#include "FbxUtility.h"

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
#include "../Utilities/Path.h"
#include "../Utilities/String.h"

// PUBLIC
void ModelData::RenderAnimBoneList()
{
	D3DDesc desc;
	D3D::GetDesc( &desc );

	ImGui::SetNextWindowPos( ImVec2( desc.Width - 605, 20 ) );
	ImGui::SetNextWindowSize( ImVec2( 300, desc.Height - 25 ) );

	ImGui::Begin( "AnimBoneList" );
	{
		if ( ImGui::Button( "Save", ImVec2( 80, 25 ) ) )
			SaveAnimBin();

		if ( ImGui::CollapsingHeader( name.c_str(), ImGuiTreeNodeFlags_DefaultOpen ) )
		{
			ImGui::Indent();
			for ( int i = 0; i < ( int )boneDatas.size(); ++i )
			{
				if ( ImGui::Selectable( boneDatas[ i ]->name.c_str(), selectBoneCount == i ) )
					selectBoneCount = i;
			}
		}
	}
	ImGui::End();
}

void ModelData::SaveAnimBin( wstring file )
{
	if ( file.length() < 1 )
	{
		D3DDesc desc;
		D3D::GetDesc( &desc );

		function<void( wstring )> func = bind( &ModelData::SaveAnimBin, this, placeholders::_1 );
		Path::SaveFileDialog( file, Path::BinAnimFilter, AnimationFolder, func, desc.Handle );
	}
	else
	{
		file += L".anim";
		WriteAnim( file );
	}
}

void ModelData::WriteAnim( const wstring & file )
{
	BinaryWriter* w = new BinaryWriter();

	wstring tempName = Path::GetFileNameWithoutExtension( file );
	string animName = String::WStringToString( tempName );

	for ( BoneData* boneData : boneDatas )
		for ( KeyFrameData* frame : boneData->keyFrameDatas )
			frame->name = animName;

	for ( AnimationData* animationData : animationDatas )
		animationData->name = animName;

	w->Open( file );
	{
		w->UInt( boneDatas.size() );
		if ( boneDatas.empty() == false )
		{
			for ( BoneData* boneData : boneDatas )
				boneData->WriteOnlyKeyFrame( w );
		}

		w->UInt( animationDatas.size() );
		if ( animationDatas.empty() == false )
		{
			for ( AnimationData* animationData : animationDatas )
				animationData->Write( w );
		}
	}
	w->Close();
	SAFE_DELETE( w );
}

void ModelData::AddBinAnimation( wstring animFile, Model * model )
{
	BinaryReader* r = new BinaryReader();
	r->Open( animFile );
	{
		int boneDataSize = r->UInt();
		if ( boneDataSize > 0 )
		{
			for ( int i = 0; i < boneDataSize; i++ )
			{
				ModelBone* bone = NULL;
				BoneData::ReadOnlyKeyFrame( r, &bone );
				for ( size_t j = 0; j < model->skeleton->bones.size(); j++ )
				{
					if ( model->skeleton->bones[ j ].second->name == bone->GetName() )
					{
						model->skeleton->bones[ j ].second->keyFrames.push_back
						(
							make_pair( bone->keyFrames[ 0 ].first, bone->keyFrames[ 0 ].second )
						);
					}
				}
			}
		}

		int AnimationCount = r->UInt();
		if ( AnimationCount > 0 )
		{
			for ( int i = 0; i < AnimationCount; i++ )
			{
				ModelAnimation* animation = NULL;
				AnimationData::Read( r, &animation );

				if ( model->controller == NULL ) model->controller = new ModelAnimationController();
				model->controller->animations.push_back( make_pair( animation->GetName(), animation ) );
				model->controller->SetCurrentAnimation( animation->startIndex );
				model->controller->Play();
			}
		}
	}
	r->Close();
	SAFE_DELETE( r );
}

string ModelData::GetAnimBoneName( int index )
{
	return boneDatas[ index ]->name;
}


// PRIVATE
ModelData::ModelData()
	: name				( "" )
	, selectBoneCount	( -1 )
{
}

ModelData::~ModelData()
{
	for ( AnimationData* animationData : animationDatas )
		SAFE_DELETE( animationData );

	for ( BoneData* boneData : boneDatas )
		SAFE_DELETE( boneData );

	for ( MeshData* meshData : meshDatas )
		SAFE_DELETE( meshData );

	for ( MaterialData* materialData : materialDatas )
		SAFE_DELETE( materialData );
}

void ModelData::OnlyMeshWrite(const string & file)
{
	BinaryWriter* w = new BinaryWriter();
	wstring temp = String::StringToWString(file);

	w->Open(temp);
	{
		w->String(name);

		w->UInt(materialDatas.size());
		if (materialDatas.empty() == false)
			for ( MaterialData* materialData : materialDatas )
				materialData->Write( w );

		w->UInt(meshDatas.size());
		if (meshDatas.empty() == false)
			for ( MeshData* meshData : meshDatas )
				meshData->Write( w );
		
		w->UInt(boneDatas.size());
		if (boneDatas.empty() == false)
			for ( BoneData* boneData : boneDatas )
				boneData->WriteOnlyBone( w );
	}
	w->Close();
	SAFE_DELETE(w);
}

void ModelData::Write(const string & file, Model * model)
{
	assert(model != NULL);

	BinaryWriter* w = new BinaryWriter();
	wstring temp = String::StringToWString(file);
	w->Open(temp);
	{
		w->String(model->name);

		w->UInt(0);

		w->UInt(model->parts.size());
		if (model->parts.empty() == false)
		{
			for (pair<string, ModelPart*> part : model->parts)
			{
				MeshData::Write(w, part.second->mesh);
				MaterialData::Write(w, part.second->material);
			}
		}

		if (model->skeleton != NULL)
		{
			w->UInt(model->skeleton->bones.size());
			if (model->skeleton->bones.empty() == false)
			{
				for ( pair<string, ModelBone*> bone : model->skeleton->bones )
				{
					BoneData::Write( w, bone.second );
				}
			}
		}
		else w->UInt(0);

		if (model->controller != NULL)
		{
			w->UInt(model->controller->animations.size());
			if (model->controller->animations.empty() == false)
			{
				for ( pair<string, ModelAnimation*> animation : model->controller->animations )
				{
					AnimationData::Write( w, animation.second );
				}
			}
		}
		else w->UInt(0);
	}
	w->Close();
	SAFE_DELETE(w);
}

void ModelData::ReadOnlyMesh( const string & file, Model ** model )
{
	BinaryReader* r = new BinaryReader();
	wstring temp = String::StringToWString( file );

	UINT count = 0;
	r->Open( temp );
	{
		*model = new Model();
		( *model )->name = r->String();

		UINT count = r->UInt();
		ModelMaterial* material = NULL;
		if ( count > 0 )
		{
			for ( UINT i = 0; i < count; i++ )
			{
				MaterialData::Read( r, &material );
			}
		}

		count = r->UInt();
		if ( count > 0 )
		{
			for ( UINT i = 0; i < count; i++ )
			{
				ModelPart* part = new ModelPart();
				MeshData::Read( r, &part->mesh );

				if ( material != NULL )
				{
					part->material = new ModelMaterial( *material );
				}
				else
				{
					ModelMaterial* eachMaterial = NULL;
					MaterialData::Read( r, &eachMaterial );
					part->material = eachMaterial;
				}

				( *model )->parts.push_back( make_pair( part->mesh->name, part ) );
			}
			SAFE_DELETE( material );
		}

		count = r->UInt();
		if ( count > 0 )
		{
			( *model )->skeleton = new ModelSkeleton();

			for ( UINT i = 0; i < count; i++ )
			{
				ModelBone* bone = NULL;
				BoneData::ReadOnlyBone( r, &bone );

				( *model )->skeleton->bones.push_back( make_pair( bone->GetName(), bone ) );
			}
		}
	}
	r->Close();

	SAFE_DELETE( r );
}

void ModelData::Read(const string & file, Model ** model)
{
	BinaryReader* r = new BinaryReader();
	wstring temp = String::StringToWString(file);

	UINT count = 0;
	r->Open(temp);
	{
		*model = new Model();
		(*model)->name = r->String();

		UINT count = r->UInt();
		ModelMaterial* material = NULL;
		if (count > 0)
		{
			for ( UINT i = 0; i < count; i++ )
			{
				MaterialData::Read( r, &material );
			}
		}

		count = r->UInt();
		if (count > 0)
		{
			for (UINT i = 0; i < count; i++)
			{
				ModelPart* part = new ModelPart();
				MeshData::Read(r, &part->mesh);

				if ( material != NULL )
				{
					part->material = new ModelMaterial( *material );
				}
				else
				{
					ModelMaterial* eachMaterial = NULL;
					MaterialData::Read(r, &eachMaterial);
					part->material = eachMaterial;
				}

				(*model)->parts.push_back(make_pair(part->mesh->name, part));
			}
			SAFE_DELETE(material);
		}

		count = r->UInt();
		if (count > 0)
		{
			(*model)->skeleton = new ModelSkeleton();

			for (UINT i = 0; i < count; i++)
			{
				ModelBone* bone = NULL;
				BoneData::Read(r, &bone);

				(*model)->skeleton->bones.push_back(make_pair(bone->GetName(), bone));
			}
		}

		count = r->UInt();
		if (count > 0)
		{
			(*model)->controller = new ModelAnimationController();

			for (UINT i = 0; i < count; i++)
			{
				ModelAnimation* animation = NULL;
				AnimationData::Read(r, &animation);

				(*model)->controller->animations.push_back(make_pair(animation->GetName(), animation));
				(*model)->controller->SetCurrentAnimation(animation->startIndex);
				(*model)->controller->Play();
			}
		}
	}
	r->Close();
	SAFE_DELETE(r);
}

void ModelData::SetBoneName( string name, int index )
{
	boneDatas[ index ]->name = name;
}

void ModelData::ReadAnim( string name, Model * model )
{
	int animCount = this->animationDatas.size();
	
	for ( int i = 0; i < animCount; i++ )
	{
		int boneCount = model->skeleton->GetBoneCount();
		//int boneCount = this->boneDatas.size();
		
		for ( int j = 0; j < boneCount; j++ )
		{
			if ( j < ( int )this->boneDatas.size() )
			{
				int keyFrameDataCount = this->boneDatas[ j ]->keyFrameDatas.size();

				ModelKeyFrame* newKeyFrame = NULL;

				for ( int k = 0; k < keyFrameDataCount; k++ )
				{
					this->boneDatas[ j ]->keyFrameDatas[ k ]->name = name;
					newKeyFrame = new ModelKeyFrame( ( *this->boneDatas[ j ]->keyFrameDatas[ k ] ) );
				}

				model->skeleton->bones[ j ].second->keyFrames.push_back( make_pair( name, newKeyFrame ) );
			}
		}

		this->animationDatas[ i ]->name = name;
		ModelAnimation* anim = new ModelAnimation( ( *this->animationDatas[ i ] ) );
		if ( model->controller == NULL ) model->controller = new ModelAnimationController();
		model->controller->animations.push_back( make_pair( name, anim ) );
		model->controller->SetCurrentAnimation( anim->startIndex );
		model->controller->Stop();
	}
}



void ModelData::PushMaterialData(FbxSurfaceMaterial * material, int & number)
{
	MaterialData* data = new MaterialData();

	data->number	= number;
	data->name		= material->GetName();
	data->ambient	= FbxUtility::GetMaterialProperty(material, FbxSurfaceMaterial::sAmbient, FbxSurfaceMaterial::sAmbientFactor, &data->ambientFile);
	data->diffuse	= FbxUtility::GetMaterialProperty(material, FbxSurfaceMaterial::sDiffuse, FbxSurfaceMaterial::sDiffuseFactor, &data->diffuseFile);
	data->normal	= FbxUtility::GetMaterialProperty( material, FbxSurfaceMaterial::sNormalMap, FbxSurfaceMaterial::sNormalMap, &data->normalFile );
	data->specular	= FbxUtility::GetMaterialProperty(material, FbxSurfaceMaterial::sSpecular, FbxSurfaceMaterial::sSpecularFactor, &data->specularFile);
	data->emissive	= FbxUtility::GetMaterialProperty(material, FbxSurfaceMaterial::sEmissive, FbxSurfaceMaterial::sEmissiveFactor, &data->emissiveFile);

	FbxProperty shininessProp = material->FindProperty(FbxSurfaceMaterial::sShininess);
	if ( shininessProp.IsValid() == true )
	{
		data->shininess = ( float )shininessProp.Get<FbxDouble>();
	}

	data->shaderFile = "0";

	materialDatas.push_back(data);
}

BoneData* ModelData::FindBoneData(const string & boneName)
{
	for (BoneData* boneData : boneDatas)
	{
		if (boneData->name == boneName) return boneData;
	}
	return NULL;
}

int ModelData::FindBoneIndex(const string & boneName)
{
	int index = 0;
	for (BoneData* boneData : boneDatas)
	{
		if (boneData->name == boneName) return index;
		index++;
	}
	return -1;
}

float ModelData::BoneWeightValidate(BoneWeightData * data)
{
	float totalWeight = 0.0f;

	vector<pair<int, float>>::iterator iter = data->boneWeights.begin();
	for (int i = 0; iter != data->boneWeights.end();)
	{
		if ( i >= ( int )BoneWeightData::MaxBonesPerVertex )
		{
			iter = data->boneWeights.erase( iter );
		}
		else
		{
			totalWeight += iter->second;
			i++; iter++;
		}
	}

	return totalWeight;
}

void ModelData::BoneWeightNormalize(const UINT & index)
{
	BoneWeightData* data = &meshBoneWeightDatas[index];

	float totalWeight = BoneWeightValidate(data);
	float ratio = 1.0f / totalWeight;

	vector<pair<int, float>>::iterator iter = data->boneWeights.begin();
	for ( ; iter != data->boneWeights.end(); iter++ )
	{
		iter->second *= ratio;
	}
}

void ModelData::SetBlendWeight(BlendWeightData * blendWeight, int nIndex, int nBoneIndex, float fWeight)
{
	switch ( nIndex )
	{
		case 0:
		{
			( *blendWeight ).blendIndices.x = ( float )nBoneIndex;
			( *blendWeight ).blendWeights.x = fWeight;
		}
		break;

		case 1:
		{
			( *blendWeight ).blendIndices.y = ( float )nBoneIndex;
			( *blendWeight ).blendWeights.y = fWeight;
		}
		break;

		case 2:
		{
			( *blendWeight ).blendIndices.z = ( float )nBoneIndex;
			( *blendWeight ).blendWeights.z = fWeight;
		}
		break;

		case 3:
		{
			( *blendWeight ).blendIndices.w = ( float )nBoneIndex;
			( *blendWeight ).blendWeights.w = fWeight;
		}
		break;
	}
}