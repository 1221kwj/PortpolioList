#include "stdafx.h"
#include "Model.h"

#include "ModelBone.h"
#include "ModelMesh.h"
#include "ModelMeshPart.h"
#include "ModelComponents.h"
// ======================================================================
//									Model
// ======================================================================
void Model::ReadMaterial( wstring folder, wstring file )
{
	ModelMaterials* m = new ModelMaterials;
	Models::LoadMaterial( folder + file, m );

	components.insert( Pair( m->GetTypeName(), m ) ); 
}

void Model::ReadMesh( wstring folder, wstring file )
{
	ModelMeshes* m = new ModelMeshes;
	ModelBones*  b = new ModelBones;
	Models::LoadMesh( folder + file, b, m );

	components.insert( Pair( m->GetTypeName(), m ) );
	components.insert( Pair( b->GetTypeName(), b ) );

	BindingBone();
	BindingMesh();
}

void Model::BindingBone()
{
	ModelBones* m				= GetComponent<ModelBones>( TYPENAME_BONE );
	vector<ModelBone*> bones	= m->Bones();

	m->SetRootBone( bones[ 0 ] );
	
	for ( ModelBone* bone : bones )
	{
		if ( bone->parentIndex > -1 )
		{
			bone->parent = bones[ bone->parentIndex ];
			bone->parent->childs.push_back( bone );
		}
		else
		{
			bone->parent = NULL;
		}
	}
}

void Model::BindingMesh()
{
	ModelMeshes* m				= GetComponent<ModelMeshes>( TYPENAME_MESH );

	vector<ModelMesh*> meshes	= m->Meshes();
	vector<ModelBone*> bones	= GetComponent<ModelBones>( TYPENAME_BONE )->Bones();
	vector<Material*> materials = GetComponent<ModelMaterials>( TYPENAME_MATERIAL )->Materials();

	for ( ModelMesh* mesh : meshes )
	{
		for ( ModelBone* bone : bones )
		{
			if ( mesh->parentBoneIndex == bone->index )
			{
				mesh->parentBone = bone;

				break;
			}
		}

		for ( ModelMeshPart* part : mesh->meshParts )
		{
			for ( Material* material : materials )
			{
				if ( material->Name() == part->materialName )
				{
					part->material = material;

					break;
				}
			}
		}

		mesh->Binding();
	}
}
// ======================================================================

// ======================================================================
//									Models
// ======================================================================
// Load MaterialData
map<wstring, vector<Material *>> Models::materialMap;
void Models::LoadMaterial( wstring file, ModelMaterials* materials )
{
	if ( materialMap.count( file ) < 1 )
		ReadMaterialData( file );

	for ( Material* material : materialMap[ file ] )
	{
		Material* temp = NULL;
		material->Clone( &temp );

		materials->AddMaterial( temp );
	}
}

void Models::ReadMaterialData( wstring file )
{
	vector<Material *> materials;
	
	Xml::XMLDocument* document = new Xml::XMLDocument();

	wstring tempFile = file;
	Xml::XMLError error = document->LoadFile( String::ToString( tempFile ).c_str() );
	assert( error == Xml::XML_SUCCESS );

	Xml::XMLElement* root		= document->FirstChildElement();
	Xml::XMLElement* matNode	= root->FirstChildElement();

	do
	{
		Xml::XMLElement* node = NULL;

		Material* material = new Material();

		node = matNode->FirstChildElement();
		material->Name( String::ToWString( node->GetText() ) );

		node = node->NextSiblingElement();

		Vector4 dxColor = Vector4::Zero();
		Xml::XMLElement* color = node->FirstChildElement();
		dxColor.x	= color->FloatText();

		color		= color->NextSiblingElement();
		dxColor.y	= color->FloatText();

		color		= color->NextSiblingElement();
		dxColor.z	= color->FloatText();

		color		= color->NextSiblingElement();
		dxColor.w	= color->FloatText();
		
		material->SetDiffuse( dxColor );

		node = node->NextSiblingElement();
		wstring diffuseTexture	= String::ToWString( node->GetText() );
		wstring directory		= Path::GetDirectoryName( file );

		if ( diffuseTexture.length() > 0 )
			material->SetDiffuseMap( directory + diffuseTexture );

		node = node->NextSiblingElement();
		wstring specularTexture = String::ToWString( node->GetText() );
		directory				= Path::GetDirectoryName( file );

		if ( specularTexture.length() > 0 )
			material->SetSpecularMap( directory + specularTexture );

		node = node->NextSiblingElement();
		wstring normalMapTexture = String::ToWString( node->GetText() );
		directory				 = Path::GetDirectoryName( file );

		if ( normalMapTexture.length() > 0 )
			material->SetNormalMap( directory + normalMapTexture );

		materials.push_back( material );
		matNode = matNode->NextSiblingElement();
	} while ( matNode != NULL );

	materialMap[ file ] = materials;
}

// Load MeshData
map<wstring, Models::MeshData> Models::meshDataMap;
void Models::LoadMesh( wstring file, class ModelBones* bones, class ModelMeshes* meshes )
{
	if ( meshDataMap.count( file ) < 1 )
		ReadMeshData( file );

	MeshData data = meshDataMap[ file ];
	for ( size_t i = 0; i < data.Bones.size(); i++ )
	{
		ModelBone* bone = NULL;
		data.Bones[ i ]->Clone( &bone );

		bones->AddBone( bone );
	}

	for ( size_t i = 0; i < data.Meshes.size(); i++ )
	{
		ModelMesh* mesh = NULL;
		data.Meshes[ i ]->Clone( &mesh );

		meshes->AddMesh( mesh );
	}
}

void Models::ReadMeshData( wstring file )
{
	BinaryReader* r = new BinaryReader();
	r->Open( file );

	vector<ModelBone *> bones;
	vector<ModelMesh *> meshes;

	UINT count = 0;
	count = r->UInt();

	for ( UINT i = 0; i < count; i++ )
	{
		ModelBone* bone		= new ModelBone();

		bone->index			= r->Int();
		bone->name			= String::ToWString( r->String() );
		bone->parentIndex	= r->Int();

		Transform* trans	= bone->GetComponent<Transform>( TYPENAME_TRANSFORM );
		trans->SetLocal		( r->Matrix() );
		trans->SetWorld		( r->Matrix() );

		bone->local			= r->Matrix();
		bone->global		= r->Matrix();

		bones.push_back( bone );
	}

	count = r->UInt();
	for ( UINT i = 0; i < count; i++ )
	{
		ModelMesh* mesh			= new ModelMesh();
		mesh->name				= String::ToWString( r->String() );
		mesh->parentBoneIndex	= r->Int();

		UINT partCount = r->UInt();
		for ( UINT k = 0; k < partCount; k++ )
		{
			ModelMeshPart* meshPart = new ModelMeshPart();
			meshPart->parent		= mesh;
			meshPart->materialName	= String::ToWString( r->String() );

			//VertexData
			{
				UINT count = r->UInt();
				meshPart->vertices.assign( count, VTNTB() );

				void* ptr = ( void * )&( meshPart->vertices[ 0 ] );
				r->Byte( &ptr, sizeof( VTNTB ) * count );
			}

			//IndexData
			{
				UINT count = r->UInt();
				meshPart->indices.assign( count, UINT() );

				void* ptr = ( void * )&( meshPart->indices[ 0 ] );
				r->Byte( &ptr, sizeof( UINT ) * count );
			}

			mesh->meshParts.push_back( meshPart );
		}//for(k)

		meshes.push_back( mesh );
	}//for(i)

	r->Close();
	SAFE_DELETE( r );


	MeshData data;
	data.Bones.assign	( bones.begin()	, bones.end()	);
	data.Meshes.assign	( meshes.begin(), meshes.end()	);

	meshDataMap[ file ] = data;
}
// ======================================================================