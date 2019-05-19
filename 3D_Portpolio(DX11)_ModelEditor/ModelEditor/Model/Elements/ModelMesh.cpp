#include "stdafx.h"
#include "ModelMesh.h"
#include "ModelMaterial.h"
#include "ModelKeyFrame.h"
#include "ModelBone.h"
#include "../ModelSkeleton.h"
#include "../../BinExport/FbxData.h"

ModelMesh::ModelMesh(const MeshData& data)
	: name			( "" )
	, vertexBuffer	( NULL )
	, indexBuffer	( NULL )
	, vertexData	( NULL )
	, indexData		( NULL )
	, vertexCount	( 0 )
	, indexCount	( 0 )
{
	D3DXMatrixIdentity( &matGeometricOffset );

	name				= data.name;
	matGeometricOffset	= data.world;
	bSkinning			= data.bSkinning;
	bSkinnedModel		= data.bSkinnedModel;

	vertexCount = data.vertices.size();
	vertexData	= new VertexTextureNormalTangentBlend[ vertexCount ];
	memcpy( vertexData, &data.vertices[ 0 ], sizeof( VertexTextureNormalTangentBlend ) * vertexCount );

	indexCount	= data.indices.size();
	indexData	= new UINT[ indexCount ];
	memcpy( indexData, &data.indices[ 0 ], sizeof( UINT ) * indexCount );

	boneIndex = ( int )vertexData[ 0 ].blendIndices.x;

	//if ( bSkinning == true ) boneIndex = -1;
	//else boneIndex = ( int )vertexData[ 0 ].blendIndices.x;

	CreateVertexBuffer();
	CreateIndexBuffer();
}

ModelMesh::~ModelMesh()
{
	SAFE_RELEASE(indexBuffer);
	SAFE_RELEASE(vertexBuffer);

	SAFE_DELETE_ARRAY(indexData);
	SAFE_DELETE_ARRAY(vertexData);
}

ModelKeyFrame * ModelMesh::GetModelKeyFrame(string name)
{
	for (pair<string, ModelKeyFrame*> temp : keyFrames)
	{
		if (temp.first == name) return  temp.second;
	}

	return NULL;
}

void ModelMesh::CreateVertexBuffer()
{
	if (vertexBuffer != NULL) SAFE_RELEASE(vertexBuffer);

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage		= D3D11_USAGE_DEFAULT;
	desc.ByteWidth	= sizeof( VertexTextureNormalTangentBlend ) * vertexCount;
	desc.BindFlags	= D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = vertexData;

	HRESULT hr = D3D::GetDevice()->CreateBuffer(&desc, &subData, &vertexBuffer);
	assert(SUCCEEDED(hr));	
}

void ModelMesh::CreateIndexBuffer()
{
	if (indexBuffer != NULL)
		SAFE_RELEASE(indexBuffer);

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage		= D3D11_USAGE_DEFAULT;
	desc.ByteWidth	= sizeof(UINT) * indexCount;
	desc.BindFlags	= D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subData;
	ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
	subData.pSysMem = indexData;

	HRESULT hr = D3D::GetDevice()->CreateBuffer(&desc, &subData, &indexBuffer);
	assert(SUCCEEDED(hr));
}