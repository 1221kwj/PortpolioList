#include "stdafx.h"
#include "FbxExporter.h"
#include "Type.h"
#include "Utility.h"

#include "../001_Utilities/Xml.h"
#include "../001_Utilities/BinaryFile.h"

Fbx::FbxExporter::FbxExporter( wstring file )
{
	manager = FbxManager::Create();
	scene	= FbxScene::Create( manager, "" );

	ios = FbxIOSettings::Create( manager, IOSROOT );
	ios->SetBoolProp( IMP_FBX_TEXTURE, true );
	manager->SetIOSettings( ios );

	importer = FbxImporter::Create( manager, "" );

	string	sFile	= String::ToString( file );
	bool	b		= importer->Initialize( sFile.c_str(), -1, ios );
	assert( b == true );

	b = importer->Import( scene );
	assert( b == true );

	converter = new FbxGeometryConverter( manager );
}

Fbx::FbxExporter::~FbxExporter()
{
	SAFE_DELETE( converter );

	ios		->Destroy();
	importer->Destroy();
	scene	->Destroy();
	manager	->Destroy();
}

void Fbx::FbxExporter::ExportMaterial( wstring saveFolder, wstring fileName )
{
	ReadMaterial();

	WriteMaterial( saveFolder, fileName );
}

void Fbx::FbxExporter::ExportMesh( wstring saveFolder, wstring fileName )
{
	ReadBoneData( scene->GetRootNode(), -1, -1 );
	ReadSkinData();

	WriteMeshData( saveFolder, fileName );
}

void Fbx::FbxExporter::GetClipList( vector<wstring>* list )
{
	list->clear();
	for ( int i = 0; i < importer->GetAnimStackCount(); i++ )
	{
		FbxTakeInfo* takeInfo = importer->GetTakeInfo( i );

		string name = takeInfo->mName.Buffer();
		list->push_back( String::ToWString( name ) );
	}
}

void Fbx::FbxExporter::ExportAnimation( wstring saveFolder, wstring fileName, UINT clipNumber )
{
	FbxClip* clip = ReadAnimationData( clipNumber );

	WriteClipData( clip, saveFolder, fileName );
}

void Fbx::FbxExporter::ExportAnimation( wstring saveFolder, wstring fileName, wstring clipName )
{
	FbxClip* clip = ReadAnimationData( clipName );

	WriteClipData( clip, saveFolder, fileName );
}

void Fbx::FbxExporter::ReadMaterial()
{
	int count = scene->GetMaterialCount();

	for ( int i = 0; i < count; i++ )
	{
		FbxSurfaceMaterial* fbxMaterial = scene->GetMaterial( i );

		FbxMaterial* material = new FbxMaterial();
		material->Name = fbxMaterial->GetName();

		if ( fbxMaterial->GetClassId().Is( FbxSurfaceLambert::ClassId ) == true )
		{
			FbxSurfaceLambert* lambert	= ( FbxSurfaceLambert * )fbxMaterial;
			material->Diffuse			= Utility::ToColor( lambert->Diffuse, lambert->DiffuseFactor );
		}

		if ( fbxMaterial->GetClassId().Is( FbxSurfacePhong::ClassId ) == true )
		{
			FbxSurfacePhong* phong	= ( FbxSurfacePhong* )fbxMaterial;
			material->Speulcar		= Utility::ToColor( phong->Specular, phong->SpecularFactor );
			material->SpecularExp	= ( float )phong->Shininess;
		}

		FbxProperty prop;

		prop = fbxMaterial->FindProperty( FbxSurfaceMaterial::sDiffuse );
		material->DiffuseFile = Utility::GetTextureFile( prop );

		prop = fbxMaterial->FindProperty( FbxSurfaceMaterial::sSpecular );
		material->SpecularFile = Utility::GetTextureFile( prop );

		prop = fbxMaterial->FindProperty( FbxSurfaceMaterial::sNormalMap );
		material->NormalMapFile = Utility::GetTextureFile( prop );

		materials.push_back( material );
	}
}

void Fbx::FbxExporter::WriteMaterial( wstring saveFolder, wstring fileName )
{
	Path::CreateFolders( saveFolder );

	Xml::XMLDocument* document = new Xml::XMLDocument();
	Xml::XMLDeclaration *decl = document->NewDeclaration();
	document->LinkEndChild( decl );

	Xml::XMLElement* root = document->NewElement( "Materials" );
	root->SetAttribute( "xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance" );
	root->SetAttribute( "xmlns:xsd", "http://www.w3.org/2001/XMLSchema" );
	document->LinkEndChild( root );

	for ( FbxMaterial* material : materials )
	{
		Xml::XMLElement* node = document->NewElement( "Material" );
		root->LinkEndChild( node );

		Xml::XMLElement* element = NULL;

		// Wrtie Material Name
		element = document->NewElement( "Name" );
		element->SetText( material->Name.c_str() );
		node->LinkEndChild( element );

		// Write Material - Diffuse Color
		element = document->NewElement( "Diffuse" );
		node->LinkEndChild( element );

		WriteXmlColor( document, element, material->Diffuse );

		// Write Material - Specular Color To Xml
		element = document->NewElement( "Specular" );
		node->LinkEndChild( element );

		WriteXmlColor( document, element, material->Speulcar );

		// Write Material - SpecularExp Value To Xml
		element = document->NewElement( "SpecularExp" );
		element->SetText( material->SpecularExp );
		node->LinkEndChild( element );

		// Write Material - Diffuse Texture File Name To Xml
		element = document->NewElement( "DiffuseFile" );
		CopyTextureFile( material->DiffuseFile, saveFolder );
		element->SetText( material->DiffuseFile.c_str() );
		node->LinkEndChild( element );

		// Write Material - Specular Texture File Name To Xml
		element = document->NewElement( "SpecularFile" );
		CopyTextureFile( material->SpecularFile, saveFolder );
		element->SetText( material->SpecularFile.c_str() );
		node->LinkEndChild( element );

		// Write Material - Normal Texture File Name To Xml
		element = document->NewElement( "NormalMapFile" );
		CopyTextureFile( material->NormalMapFile, saveFolder );
		element->SetText( material->NormalMapFile.c_str() );
		node->LinkEndChild( element );

		SAFE_DELETE( material );
	}

	string file = String::ToString( saveFolder + fileName );
	document->SaveFile( file.c_str() );
}

void Fbx::FbxExporter::ReadBoneData( FbxNode * node, int index, int parent )
{
	FbxNodeAttribute* attribute = node->GetNodeAttribute();

	if ( attribute != NULL )
	{
		FbxNodeAttribute::EType nodeType = attribute->GetAttributeType();

		bool b = false;
		b |= ( nodeType == FbxNodeAttribute::eSkeleton );
		b |= ( nodeType == FbxNodeAttribute::eMesh );
		b |= ( nodeType == FbxNodeAttribute::eNull );
		b |= ( nodeType == FbxNodeAttribute::eMarker );

		if ( b == true )
		{
			FbxBoneData* bone		= new FbxBoneData();
			bone->Index				= index;
			bone->Parent			= parent;
			bone->Name				= node->GetName();
			bone->LocalTransform	= Utility::ToMatrix( node->EvaluateLocalTransform() );
			bone->GlobalTransform	= Utility::ToMatrix( node->EvaluateGlobalTransform() );
			
			node->LclTranslation.Get();
			boneDatas.push_back( bone );

			if ( nodeType == FbxNodeAttribute::eMesh )
			{
				converter->Triangulate( attribute, true, true );

				ReadMeshData( node, index );
			}
		}//if(b)
	}

	for ( int i = 0; i < node->GetChildCount(); i++ )
		ReadBoneData( node->GetChild( i ), ( int )boneDatas.size(), index );
}

UINT Fbx::FbxExporter::GetBoneIndexByName( string name )
{
	for ( UINT i = 0; i < ( UINT )boneDatas.size(); i++ )
	{
		if ( boneDatas[ i ]->Name == name )
			return i;
	}

	return -1;
}

void Fbx::FbxExporter::ReadMeshData( FbxNode * node, int parentBone )
{
	FbxMesh* mesh = node->GetMesh();

	vector<FbxVertex *> vertices;
	for ( int p = 0; p < mesh->GetPolygonCount(); p++ )
	{
		int vertexInPolygon = mesh->GetPolygonSize( p );
		assert( vertexInPolygon == 3 );

		for ( int vi = vertexInPolygon - 1; vi >= 0; vi-- )
		{
			FbxVertex* vertex = new FbxVertex();

			int cpIndex = mesh->GetPolygonVertex( p, vi );
			vertex->ControlPoint = cpIndex;

			XMVECTOR	vec			= XMVectorZero();
			XMMATRIX	mat			= XMMatrixIdentity();
			FbxVector4	position	= mesh->GetControlPointAt( cpIndex );

			vec = XMLoadFloat3( &Utility::ToVector3( position ) );
			mat = XMLoadFloat4x4( &Utility::Negative() );
			vec = XMVector3TransformCoord( vec, mat );
			XMStoreFloat3( &vertex->Vertex.Position, vec );
			
			FbxVector4 normal;
			vec = XMVectorZero();
			mesh->GetPolygonVertexNormal( p, vi, normal );
			normal.Normalize();
			vec = XMLoadFloat3( &Utility::ToVector3( normal ) );
			vec = XMVector3TransformCoord( vec, mat );
			vec = XMVector3Normalize( vec );
			XMStoreFloat3( &vertex->Vertex.Normal, vec );

			vertex->MaterialName = Utility::GetMaterialName( mesh, p, cpIndex );

			int uvIndex = mesh->GetTextureUVIndex( p, vi );
			vertex->Vertex.Uv = Utility::GetUv( mesh, cpIndex, uvIndex );

			vertices.push_back( vertex );
		}//for(vi)

		UINT index0 = ( UINT )vertices.size() - 3;
		UINT index1 = ( UINT )vertices.size() - 2;
		UINT index2 = ( UINT )vertices.size() - 1;

		Vector3 p0 = vertices[ index0 ]->Vertex.Position;
		Vector3 p1 = vertices[ index1 ]->Vertex.Position;
		Vector3 p2 = vertices[ index2 ]->Vertex.Position;

		Vector3 uv0 = vertices[ index0 ]->Vertex.Uv;
		Vector3 uv1 = vertices[ index1 ]->Vertex.Uv;
		Vector3 uv2 = vertices[ index2 ]->Vertex.Uv;

		Vector3 e0 = p1 - p0;
		Vector3 e1 = p2 - p0;

		float u0 = uv1.x - uv0.x;
		float u1 = uv2.x - uv0.x;
		float v0 = uv1.y - uv0.y;
		float v1 = uv2.y - uv0.y;
		float r  = 1.0f / ( u0 * v1 - v0 * u1 );

		Vector3 tangent;
		tangent.x = r * ( v1 * e0.x - v0 * e1.x );
		tangent.y = r * ( v1 * e0.y - v0 * e1.y );
		tangent.z = r * ( v1 * e0.z - v0 * e1.z );

		vertices[ index0 ]->Vertex.Tangent += tangent;
		vertices[ index1 ]->Vertex.Tangent += tangent;
		vertices[ index2 ]->Vertex.Tangent += tangent;
	}//for(p)

	for ( UINT i = 0; i < vertices.size(); i++ )
	{
		XMVECTOR n		= XMLoadFloat3( &vertices[ i ]->Vertex.Normal );
		XMVECTOR t		= XMLoadFloat3( &vertices[ i ]->Vertex.Tangent );
		XMVECTOR temp	= XMVectorSubtract( t, n * XMVectorGetX( XMVector3Dot( n, t ) ) );
		
		temp = XMVector3Normalize( temp );

		XMStoreFloat3( &vertices[ i ]->Vertex.Tangent, temp );
	}

	FbxMeshData* meshData	= new FbxMeshData();
	meshData->Name			= node->GetName();
	meshData->ParentBone	= parentBone;
	meshData->Vertices		= vertices;
	meshData->Mesh			= mesh;

	meshDatas.push_back( meshData );
}

void Fbx::FbxExporter::ReadSkinData()
{
	for ( FbxMeshData* meshData : meshDatas )
	{
		FbxMesh* mesh = meshData->Mesh;

		int deformerCount = mesh->GetDeformerCount();

		vector<FbxBoneWeights> boneWeights;
		boneWeights.assign( mesh->GetControlPointsCount(), FbxBoneWeights() );

		for ( int i = 0; i < deformerCount; i++ )
		{
			FbxDeformer* deformer = mesh->GetDeformer( i, FbxDeformer::eSkin );

			FbxSkin* skin = reinterpret_cast< FbxSkin * >( deformer );
			if ( skin == NULL ) continue;

			for ( int clusterIndex = 0; clusterIndex < skin->GetClusterCount(); clusterIndex++ )
			{
				FbxCluster* cluster = skin->GetCluster( clusterIndex );
				assert( cluster->GetLinkMode() == FbxCluster::eNormalize );

				string linkName = cluster->GetLink()->GetName();
				UINT boneIndex	= GetBoneIndexByName( linkName );

				FbxAMatrix transform;
				FbxAMatrix linkTransform;

				cluster->GetTransformMatrix		( transform );
				cluster->GetTransformLinkMatrix	( linkTransform );

				boneDatas[ boneIndex ]->LocalTransform	= Utility::ToMatrix( transform );
				boneDatas[ boneIndex ]->GlobalTransform = Utility::ToMatrix( linkTransform );

				for ( int indexCount = 0; indexCount < cluster->GetControlPointIndicesCount(); indexCount++ )
				{
					int		temp	= cluster->GetControlPointIndices()[ indexCount ];
					double* weights = cluster->GetControlPointWeights();

					boneWeights[ temp ].AddWeights( boneIndex, ( float )weights[ indexCount ] );
				}
			}//for(clusterIndex)
		}//for(deformer)

		for ( UINT i = 0; i < boneWeights.size(); i++ )
			boneWeights[ i ].Normalize();

		for ( FbxVertex* vertex : meshData->Vertices )
		{
			int cpIndex = vertex->ControlPoint;

			FbxBlendWeight weights;
			boneWeights[ cpIndex ].GetBlendWeights( weights );
			vertex->Vertex.BlendIndices = weights.Indices;
			vertex->Vertex.BlendWeights = weights.Weights;
		}

		for ( int i = 0; i < scene->GetMaterialCount(); i++ )
		{
			FbxSurfaceMaterial* material = scene->GetMaterial( i );
			string materialName = material->GetName();

			vector<FbxVertex *> gather;
			for ( FbxVertex* temp : meshData->Vertices )
			{
				if ( temp->MaterialName == materialName )
					gather.push_back( temp );
			}
			if ( gather.size() < 1 ) continue;

			FbxMeshPartData* meshPart = new FbxMeshPartData();
			meshPart->MaterialName = materialName;

			for ( FbxVertex* temp : gather )
			{
				VTNTB vertex;
				vertex = temp->Vertex;

				meshPart->Vertices.push_back( vertex );
				meshPart->Indices.push_back( ( UINT )meshPart->Indices.size() );
			}
			meshData->MeshParts.push_back( meshPart );
		}
	}//for(MeshData)
}

void Fbx::FbxExporter::WriteMeshData( wstring saveFolder, wstring fileName )
{
	Path::CreateFolder( saveFolder );
	
	BinaryWriter* w = new BinaryWriter();
	w->Open( saveFolder + fileName );

	w->UInt( ( UINT )boneDatas.size() );
	for ( FbxBoneData* bone : boneDatas )
	{
		w->Int		( bone->Index );
		w->String	( bone->Name );
		w->Int		( bone->Parent );

		w->Matrix	( bone->LocalTransform );
		w->Matrix	( bone->GlobalTransform );

		SAFE_DELETE( bone );
	}

	w->UInt( ( UINT )meshDatas.size() );
	for ( FbxMeshData* meshData : meshDatas )
	{
		w->String( meshData->Name );
		w->Int( meshData->ParentBone );

		w->UInt( ( UINT )meshData->MeshParts.size() );
		for ( FbxMeshPartData* part : meshData->MeshParts )
		{
			w->String( part->MaterialName );

			w->UInt( ( UINT )part->Vertices.size() );
			w->Byte( &part->Vertices[ 0 ], sizeof( VTNTB ) * ( UINT )part->Vertices.size() );

			w->UInt( ( UINT )part->Indices.size() );
			w->Byte( &part->Indices[ 0 ], sizeof( UINT ) * ( UINT )part->Indices.size() );

			SAFE_DELETE( part );
		}

		SAFE_DELETE( meshData );
	}

	w->Close();
	SAFE_DELETE( w );
}

void Fbx::FbxExporter::WriteXmlColor( Xml::XMLDocument * document, Xml::XMLElement * element, Vector4 & color )
{
	Xml::XMLElement* r = document->NewElement( "R" );
	r->SetText( color.x );
	element->LinkEndChild( r );

	Xml::XMLElement* g = document->NewElement( "G" );
	g->SetText( color.y );
	element->LinkEndChild( g );

	Xml::XMLElement* b = document->NewElement( "B" );
	b->SetText( color.z );
	element->LinkEndChild( b );

	Xml::XMLElement* a = document->NewElement( "A" );
	a->SetText( color.w );
	element->LinkEndChild( a );
}

void Fbx::FbxExporter::CopyTextureFile( OUT string & textureFile, wstring & saveFolder )
{
	if ( textureFile.length() < 1 )
		return;

	wstring file		= String::ToWString( textureFile );
	wstring fileName	= Path::GetFileName( file );

	if ( Path::ExistFile( textureFile ) == true )
		CopyFile( file.c_str(), ( saveFolder + fileName ).c_str(), FALSE );

	textureFile = String::ToString( fileName );
}

Fbx::FbxClip* Fbx::FbxExporter::ReadAnimationData( wstring name )
{
	UINT number = -1;
	for ( int i = 0; i < importer->GetAnimStackCount(); i++ )
	{
		FbxTakeInfo* takeInfo = importer->GetTakeInfo( i );
		wstring compare = String::ToWString( takeInfo->mName.Buffer() );

		if ( name == compare )
		{
			number = i;

			break;
		}
	}

	if ( number != -1 )
		return ReadAnimationData( number );

	return NULL;
}

Fbx::FbxClip* Fbx::FbxExporter::ReadAnimationData( UINT index )
{
	UINT stackCount = ( UINT )importer->GetAnimStackCount();
	assert( index < stackCount );


	FbxTime::EMode mode = scene->GetGlobalSettings().GetTimeMode();
	float frameRate = ( float )FbxTime::GetFrameRate( mode );

	FbxClip* clip = new FbxClip();
	clip->FrameRate = frameRate;

	FbxTakeInfo* takeInfo = importer->GetTakeInfo( index );
	clip->Name = takeInfo->mName.Buffer();

	FbxTimeSpan span = takeInfo->mLocalTimeSpan;
	FbxTime tempDuration = span.GetDuration();

	int start		= ( int )span.GetStart().GetFrameCount();
	int stop		= ( int )span.GetStop().GetFrameCount();
	float duration	= ( float )tempDuration.GetMilliSeconds();

	if ( start < stop )
		ReadKeyframeData( clip, scene->GetRootNode(), start, stop );

	clip->Duration = duration;
	clip->FrameCount = ( stop - start ) + 1;

	return clip;
}

void Fbx::FbxExporter::ReadKeyframeData( Fbx::FbxClip * clip, FbxNode * node, int start, int stop )
{
	FbxNodeAttribute* attribute = node->GetNodeAttribute();

	if ( attribute != NULL )
	{
		FbxNodeAttribute::EType nodeType = attribute->GetAttributeType();
		if ( nodeType == FbxNodeAttribute::eSkeleton )
		{
			FbxKeyframe* keyframe = new FbxKeyframe();
			keyframe->BoneName = node->GetName();

			for ( int i = start; i <= stop; i++ )
			{
				FbxTime animationTime;
				animationTime.SetFrame( i );

				FbxAMatrix	matrix		= node->EvaluateLocalTransform( animationTime );
				XMMATRIX	transform	= XMLoadFloat4x4( &Utility::ToMatrix( matrix ) );

				FbxKeyframeData data;
				data.Time = ( float )animationTime.GetMilliSeconds();
				XMVECTOR Scale, Rotation, Translation;
				XMMatrixDecompose( &Scale, &Rotation, &Translation, transform );

				XMStoreFloat3( &data.Scale		, Scale );
				XMStoreFloat4( &data.Rotation	, Rotation );
				XMStoreFloat3( &data.Translation, Translation );

				keyframe->Transforms.push_back( data );
			}

			clip->Keyframes.push_back( keyframe );
		}//if(nodeType)
	}

	for ( int i = 0; i < node->GetChildCount(); i++ )
		ReadKeyframeData( clip, node->GetChild( i ), start, stop );
}

void Fbx::FbxExporter::WriteClipData( FbxClip * clip, wstring saveFolder, wstring fileName )
{
	Path::CreateFolder( saveFolder );

	BinaryWriter* w = new BinaryWriter();
	w->Open( saveFolder + fileName );

	w->String	( clip->Name );
	w->Float	( clip->Duration );
	w->Float	( clip->FrameRate );
	w->UInt		( clip->FrameCount );

	w->UInt( ( UINT )clip->Keyframes.size() );
	for ( FbxKeyframe* keyframe : clip->Keyframes )
	{
		w->String( keyframe->BoneName );

		w->UInt( ( UINT )keyframe->Transforms.size() );
		w->Byte( &keyframe->Transforms[ 0 ], sizeof( FbxKeyframeData ) * ( UINT )keyframe->Transforms.size() );

		SAFE_DELETE( keyframe );
	}

	w->Close();
	SAFE_DELETE( w );
}
