#include "stdafx.h"
#include "FbxLoader.h"

#include "FbxUtility.h"
#include "FbxData.h"
#include "ModelData.h"

#include "../Utilities/String.h"
#include "../Utilities/Path.h"

void FbxLoader::Convert( wstring fbxFile, wstring saveFile )
{
	ModelData* data = NULL;
	FbxLoader* loader = new FbxLoader();

	string tempFbxFile = String::WStringToString( fbxFile );
	string tempSaveFile = String::WStringToString( saveFile );

	data = loader->Load( tempFbxFile );
	SAFE_DELETE( loader );

	data->OnlyMeshWrite( tempSaveFile );
	SAFE_DELETE( data );
}

void FbxLoader::LoadBinaryOnlyMesh( wstring binFile, Model ** model )
{
	string temp = String::WStringToString( binFile );
	ModelData::ReadOnlyMesh( temp, model );
}

void FbxLoader::LoadBinary( wstring binFile, Model ** model )
{
	string temp = String::WStringToString( binFile );
	ModelData::Read( temp, model );
}

void FbxLoader::WriteBinary( wstring binFile, Model * model )
{
	string temp = String::WStringToString( binFile );
	ModelData::Write( temp, model );
}

ModelData * FbxLoader::LoadFbxAnimation( wstring fbxFile, wstring animName )
{
	ModelData* data = NULL;
	FbxLoader* loader = new FbxLoader();

	string tempFbxFile = String::WStringToString( fbxFile );

	data = loader->Load( tempFbxFile );
	SAFE_DELETE( loader );

	return data;
}

FbxLoader::FbxLoader()
{
	manager = FbxManager::Create();
	assert( manager != NULL );

	scene = FbxScene::Create( manager, "" );
	assert( scene != NULL );
}

FbxLoader::~FbxLoader()
{
	scene->Destroy();
	manager->Destroy();
}

ModelData * FbxLoader::Load( const string & file )
{
	int major, minor, revision;
	FbxManager::GetFileFormatVersion( major, minor, revision );

	FbxIOSettings* ios = FbxIOSettings::Create( manager, IOSROOT );
	ios->SetBoolProp( IMP_FBX_TEXTURE, true );
	manager->SetIOSettings( ios );

	importer = FbxImporter::Create( manager, "" );
	bool check = importer->Initialize( file.c_str(), -1, ios );
	assert( check == true );

	importer->Import( scene );
	converter = new FbxGeometryConverter( manager );
	{
		string name = Path::GetFileNameWithoutExtension( file );

		modelData = new ModelData();
		modelData->name = name;

		ProcessMaterial();
		ProcessNode( scene->GetRootNode(), FbxNodeAttribute::eSkeleton );
		ProcessNode( scene->GetRootNode(), FbxNodeAttribute::eMesh );
		ProcessAnimations();
	}
	SAFE_DELETE( converter );

	ios->Destroy();
	importer->Destroy();

	return modelData;
}

void FbxLoader::ProcessMaterial()
{
	for ( int i = 0; i < scene->GetMaterialCount(); i++ )
	{
		FbxSurfaceMaterial* temp = scene->GetMaterial( i );
		materials.push_back( temp );

		modelData->PushMaterialData( temp, i );
	}
}

void FbxLoader::ProcessNode( FbxNode * node, FbxNodeAttribute::EType type )
{
	FbxNodeAttribute* attribute = node->GetNodeAttribute();
	if ( attribute != NULL )
	{
		FbxNodeAttribute::EType nodeType = attribute->GetAttributeType();
		if ( nodeType == type )
		{
			switch ( nodeType )
			{
			case FbxNodeAttribute::eSkeleton:
				ProcessSkeleton( node );
				break;

			case FbxNodeAttribute::eMesh:
				ProcessMesh( node );
				break;

			case FbxNodeAttribute::eMarker:
			case FbxNodeAttribute::eNurbs:
			case FbxNodeAttribute::ePatch:
			case FbxNodeAttribute::eCamera:
			case FbxNodeAttribute::eLight:
			case FbxNodeAttribute::eNull:
				break;
			}//switch(nodeType)
		}
	}

	for ( int i = 0; i < node->GetChildCount(); i++ )
		ProcessNode( node->GetChild( i ), type );
}

void FbxLoader::ProcessMesh( FbxNode * node )
{
	FbxNodeAttribute* attribute = node->GetNodeAttribute();
	converter->Triangulate( attribute, true, true );

	FbxMesh* mesh = node->GetMesh();
	assert( mesh != NULL );

	int vertexCount = mesh->GetControlPointsCount();
	assert( vertexCount > 0 );

	modelData->meshBoneWeightDatas.assign( vertexCount, BoneWeightData() );
	ProcessBoneWeights( mesh );

	FbxVector4* controlPoints = mesh->GetControlPoints();

	MeshData* meshData = new MeshData();
	meshData->name = node->GetName();
	meshData->bSkinning = false;

	for ( int i = 0; i < mesh->GetPolygonCount(); i++ )
	{
		for ( int vi = 0; vi < 3; vi++ )
		{
			int vertexIndex = mesh->GetPolygonVertex( i, vi );
			if ( vertexIndex < 0 || vertexIndex >= vertexCount ) continue;
			VertexTextureNormalTangentBlend vertex = VertexTextureNormalTangentBlend();
			BoneWeightData boneWeightData = modelData->meshBoneWeightDatas[ vertexIndex ];
			BlendWeightData blendWeightData = BlendWeightData();

			meshData->bSkinnedModel = !boneWeightData.boneWeights.empty();
			meshData->bSkinning |= boneWeightData.boneWeights.size() > 1;

			if ( meshData->bSkinnedModel )
			{
				for ( int j = 0; j < ( int )boneWeightData.boneWeights.size(); j++ )
				{
					modelData->SetBlendWeight
					(
						&blendWeightData,
						j,
						boneWeightData.boneWeights[ j ].first,
						boneWeightData.boneWeights[ j ].second
					);
				}
			}

			vertex.position = FbxUtility::GetPosition( controlPoints[ vertexIndex ] );
			vertex.uv = FbxUtility::GetUV( mesh, 0, i, vi, vertexIndex );
			vertex.normal = FbxUtility::GetNormal( mesh, i, vi );
			vertex.tangent = D3DXVECTOR3( 0, 0, 0 );
			vertex.biNormal = D3DXVECTOR3( 0, 0, 0 );
			vertex.blendIndices = blendWeightData.blendIndices;
			vertex.blendWeights = blendWeightData.blendWeights;

			meshData->vertices.push_back( vertex );
			meshData->indices.push_back( meshData->indices.size() );
		}//for(vi)
	}//for(i)

	meshData->world = FbxUtility::GetGeometricOffset( node );
	modelData->meshDatas.push_back( meshData );
}

void FbxLoader::ProcessAnimations()
{
	FbxNode* rootNode = scene->GetRootNode();
	if ( rootNode == NULL ) return;

	float frameRate = ( float )FbxTime::GetFrameRate( scene->GetGlobalSettings().GetTimeMode() );

	FbxArray<FbxString *> animationArray;

	FbxDocument* document = dynamic_cast< FbxDocument * >( scene );

	if ( document != NULL )
		document->FillAnimStackNameArray( animationArray );

	for ( int i = 0; i < importer->GetAnimStackCount(); i++ )
	{
		FbxTakeInfo* animationInfo = importer->GetTakeInfo( i );
		string		 animationName = animationInfo->mName.Buffer();
		FbxTimeSpan  span = animationInfo->mLocalTimeSpan;

		double startTime = span.GetStart().GetSecondDouble();
		double endTime = span.GetStop().GetSecondDouble();

		if ( startTime < endTime )
		{
			int keyFrameCount = ( int )( ( endTime - startTime ) * ( double )frameRate );

			AnimationData* animationData = new AnimationData();
			animationData->name = animationName;
			animationData->frameRate = frameRate;
			animationData->keyFrameCount = keyFrameCount;
			animationData->startIndex = i;

			modelData->animationDatas.push_back( animationData );

			ProcessAnimation( rootNode, animationName, frameRate, ( float )startTime, ( float )endTime );
		}
	}

	animationArray.Clear();
}

void FbxLoader::ProcessAnimation( FbxNode * node, const string & animationName, float frameRate, float start, float stop )
{
	FbxNodeAttribute* nodeAttribute = node->GetNodeAttribute();
	if ( nodeAttribute != NULL )
	{
		switch ( nodeAttribute->GetAttributeType() )
		{
			case FbxNodeAttribute::eSkeleton:
			{
				if ( modelData->boneDatas.empty() == true ) break;

				string boneName = node->GetName();

				BoneData* boneData = modelData->FindBoneData( boneName );
				if ( boneData == NULL ) break;

				KeyFrameData* keyFrameData = new KeyFrameData();
				keyFrameData->name = animationName;

				double time = 0;
				while ( time <= ( double )stop )
				{
					FbxTime animationTime;
					animationTime.SetSecondDouble( time );

					D3DXMATRIX localTransform = FbxUtility::GetLocalTransformFromCurrentTake( node, animationTime );
					keyFrameData->transforms.push_back( localTransform );

					time += 1.0f / frameRate;
				}
				boneData->keyFrameDatas.push_back( keyFrameData );
			}
			break;

			case FbxNodeAttribute::eMesh:
			{
				MeshData* mesh = NULL;

				for ( MeshData* tempMesh : modelData->meshDatas )
				{
					string modelName = node->GetName();
					if ( modelName == tempMesh->name )
					{
						mesh = tempMesh;
						break;
					}
				}

				if ( mesh == NULL ) break;

				KeyFrameData* keyFrameData = new KeyFrameData();
				keyFrameData->name = animationName;

				double time = 0;
				while ( time <= ( double )stop )
				{
					FbxTime animationTime;
					animationTime.SetSecondDouble( time );

					D3DXMATRIX matAbsoluteTransform = FbxUtility::GetAbsoluteTransformFromCurrentTake( node, animationTime );
					keyFrameData->transforms.push_back( matAbsoluteTransform );

					time += 1.0f / frameRate;
				}
				mesh->keyFrameDatas.push_back(keyFrameData);
			}
			break;
		}
	}

	for ( int i = 0; i < node->GetChildCount(); ++i )
	{
		ProcessAnimation( node->GetChild( i ), animationName, frameRate, start, stop );
	}
}

void FbxLoader::ProcessSkeleton( FbxNode * node )
{
	FbxSkeleton* fbxSkeleton = node->GetSkeleton();

	if ( fbxSkeleton == NULL ) return;

	int parentBoneIndex = -1;
	FbxNode* parentNode = node->GetParent();

	if ( parentNode != NULL )
	{
		string boneName = parentNode->GetName();
		parentBoneIndex = modelData->FindBoneIndex( boneName );
	}


	string boneName = node->GetName();

	BoneData* boneData = new BoneData();
	boneData->name = boneName;
	boneData->parentBoneIndex = parentBoneIndex;

	modelData->boneDatas.push_back( boneData );
}

void FbxLoader::ProcessBoneWeights( FbxMesh * mesh )
{
	if ( modelData->boneDatas.empty() == true ) return;

	for ( int i = 0; i < mesh->GetDeformerCount(); ++i )
	{
		FbxDeformer* deformer = mesh->GetDeformer( i );
		if ( deformer == NULL ) continue;

		if ( deformer->GetDeformerType() == FbxDeformer::eSkin )
		{
			FbxSkin* skin = ( FbxSkin * )deformer;
			if ( skin == NULL ) continue;

			ProcessBoneWeights( skin );
		}
	}
}

void FbxLoader::ProcessBoneWeights( FbxSkin * skin )
{
	FbxCluster::ELinkMode linkMode = FbxCluster::eNormalize;

	int clusterCount = skin->GetClusterCount();
	for ( int i = 0; i < clusterCount; i++ )
	{
		FbxCluster* cluster = skin->GetCluster( i );
		if ( cluster == NULL ) continue;

		linkMode = cluster->GetLinkMode();

		FbxNode* pLinkNode = cluster->GetLink();
		if ( pLinkNode == NULL ) continue;

		string lineNodeName = pLinkNode->GetName();
		int nBoneIndex = modelData->FindBoneIndex( lineNodeName );

		if ( nBoneIndex < 0 ) continue;


		BoneData* boneData = modelData->boneDatas[ nBoneIndex ];

		FbxAMatrix matClusterTransformMatrix;
		FbxAMatrix matClusterLinkTransformMatrix;

		cluster->GetTransformMatrix( matClusterTransformMatrix );
		cluster->GetTransformLinkMatrix( matClusterLinkTransformMatrix );

		boneData->matBindPoseTransform = FbxUtility::ToMatrix( matClusterLinkTransformMatrix );
		boneData->matBoneReferenceTransform = FbxUtility::ToMatrix( matClusterTransformMatrix );

		int* indices = cluster->GetControlPointIndices();
		double* weights = cluster->GetControlPointWeights();

		for ( int j = 0; j < cluster->GetControlPointIndicesCount(); j++ )
		{
			modelData->meshBoneWeightDatas[ indices[ j ] ].boneWeights.push_back( make_pair( nBoneIndex, ( float )weights[ j ] ) );
		}
	}

	switch ( linkMode )
	{
	case FbxCluster::eNormalize:
	{
		for ( UINT i = 0; i < modelData->meshBoneWeightDatas.size(); i++ )
			modelData->BoneWeightNormalize( i );
	}
	break;

	case FbxCluster::eAdditive:
	case FbxCluster::eTotalOne:
		break;
	}
}