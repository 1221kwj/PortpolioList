#include "stdafx.h"
#include "MeshSphere.h"

MeshSphere::MeshSphere( Material* material, float radius, UINT stackCount, UINT sliceCount )
	: Mesh		( material )
	, radius	( radius )
	, stackCount( stackCount )
	, sliceCount( sliceCount )
{
}

MeshSphere::~MeshSphere()
{
}

void MeshSphere::CreateData()
{
	vector<VTNT> vertices;
	vertices.push_back( VTNT
	(
		0.0f, radius, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	) );

	float phiStep	= XM_PI / stackCount;
	float thetaStep = 2.0f * XM_PI / sliceCount;

	for ( UINT i = 1; i <= stackCount - 1; i++ )
	{
		float phi = i * phiStep;

		for ( UINT j = 0; j <= sliceCount; j++ )
		{
			float theta = j * thetaStep;

			XMVECTOR p = XMVectorSet
			(
				( radius * sinf( phi ) * cosf( theta ) ),
				( radius * cosf( phi ) ),
				( radius * sinf( phi ) * sinf( theta ) ),
				1.0f
			);

			XMVECTOR t = XMVectorSet
			(
				( -radius * sinf( phi ) * sinf( theta ) ),
				0.0f,
				( radius * sinf( phi ) * cosf( theta ) ),
				1.0f
			);

			t = XMVector3Normalize( t );

			XMVECTOR n = XMVector3Normalize( p );

			float u = theta / ( XM_PI * 2.0f );
			float v = phi / XM_PI;

			vertices.push_back( VTNT
			(
				XMVectorGetX( p ), XMVectorGetY( p ), XMVectorGetZ( p ),
				u, v,
				XMVectorGetX( n ), XMVectorGetY( n ), XMVectorGetZ( n ),
				XMVectorGetX( t ), XMVectorGetY( t ), XMVectorGetZ( t )
			) );
		}
	}

	vertices.push_back( VTNT
	(
		0.0f, -radius, 0.0f,
		0.0f, 1.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f
	) );

	this->vertices = new VTNT[ vertices.size() ];

	vertexCount = vertices.size();
	copy
	(
		vertices.begin(),
		vertices.end(),
		stdext::checked_array_iterator<VTNT*>( this->vertices, vertexCount )
	);

	vector<UINT> indices;
	for ( UINT i = 1; i <= sliceCount; i++ )
	{
		indices.push_back( 0 );
		indices.push_back( i + 1 );
		indices.push_back( i );
	}

	UINT baseIndex = 1;
	UINT ringVertexCount = sliceCount + 1;
	for ( UINT i = 0; i < stackCount - 2; i++ )
	{
		for ( UINT j = 0; j < sliceCount; j++ )
		{
			indices.push_back( baseIndex + ( i + 0 ) * ringVertexCount + ( j + 0 ) );
			indices.push_back( baseIndex + ( i + 0 ) * ringVertexCount + ( j + 1 ) );
			indices.push_back( baseIndex + ( i + 1 ) * ringVertexCount + ( j + 0 ) );

			indices.push_back( baseIndex + ( i + 1 ) * ringVertexCount + ( j + 0 ) );
			indices.push_back( baseIndex + ( i + 0 ) * ringVertexCount + ( j + 1 ) );
			indices.push_back( baseIndex + ( i + 1 ) * ringVertexCount + ( j + 1 ) );
		}
	}

	UINT southPoleIndex = vertices.size() - 1;
	baseIndex = southPoleIndex - ringVertexCount;

	for ( UINT i = 0; i < sliceCount; i++ )
	{
		indices.push_back( southPoleIndex );
		indices.push_back( baseIndex + i );
		indices.push_back( baseIndex + i + 1 );
	}

	this->indices = new UINT[ indices.size() ];
	indexCount = indices.size();
	copy
	(
		indices.begin(),
		indices.end(),
		stdext::checked_array_iterator<UINT*>( this->indices, indexCount )
	);
}
