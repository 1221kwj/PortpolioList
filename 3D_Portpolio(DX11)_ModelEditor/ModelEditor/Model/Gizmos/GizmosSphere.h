#pragma once

#include "stdafx.h"
#include "Gizmos.h"

class GizmosSphere : public Gizmos
{
public:
	GizmosSphere( D3DXCOLOR color )
		: Gizmos( GIZMOSTYPE::SPHERE )
		, vertexData	( NULL )
		, vertexBuffer	( NULL )
		, vertexCount	( 0 )
	{
		// 1. Create Buffer
		float dt = 10.0f * ( ( float )D3DX_PI / 180.0f );
		int posCount = ( 360 / 10 + 1 ) * 3;
		vertexCount = posCount * 2;

		vertexData = new VertexColor[ vertexCount ];
		vector<D3DXVECTOR3> position;

		for ( int i = 0; i < posCount; i++ )
		{
			D3DXVECTOR3 vec1;
			D3DXVECTOR3 vec2;

			if ( i < posCount / 3 )
			{
				vec1.x = cosf( i * dt );
				vec1.y = 0.0f;
				vec1.z = sinf( i * dt );

				vec2.x = cosf( ( i + 1 ) * dt );
				vec2.y = 0.0f;
				vec2.z = sinf( ( i + 1 ) * dt );
			}
			else if ( i >= posCount / 3 && i < posCount * 2 / 3 )
			{
				vec1.x = cosf( i * dt );
				vec1.y = sinf( i * dt );
				vec1.z = 0.0f;

				vec2.x = cosf( ( i + 1 ) * dt );
				vec2.y = sinf( ( i + 1 ) * dt );
				vec2.z = 0.0f;
			}
			else
			{
				vec1.x = 0.0f;
				vec1.y = cosf( i * dt );
				vec1.z = sinf( i * dt );

				vec2.x = 0.0f;
				vec2.y = cosf( ( i + 1 ) * dt );
				vec2.z = sinf( ( i + 1 ) * dt );
			}

			position.push_back( vec1 * 5.0f );
			position.push_back( vec2 * 5.0f );
		}

		for ( UINT i = 0; i < vertexCount; i++ )
		{
			vertexData[ i ].position = position[ i ];
			vertexData[ i ].color = color;
		}

		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof( VertexColor ) * vertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertexData;

		HRESULT hr;
		hr = D3D::GetDevice()->CreateBuffer
		(
			&desc,
			&data,
			&vertexBuffer
		);
		assert( SUCCEEDED( hr ) );

		SAFE_DELETE_ARRAY( vertexData );

		center = D3DXVECTOR3( 0, 0, 0 );
	}

	~GizmosSphere()
	{
		SAFE_RELEASE( vertexBuffer );
	}
	void Update( D3DXMATRIX mat )
	{

	}

	void Render()
	{
		if ( bDepth == false )  States::SetDepthStencil( depthOffState );

		UINT stride = sizeof( VertexColor );
		UINT offset = 0;

		D3D::GetDC()->IASetVertexBuffers( 0, 1, &vertexBuffer, &stride, &offset );
		D3D::GetDC()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_LINELIST );

		worldBuffer->SetVSBuffer( 1 );
		gizmosBuffer->SetPSBuffer( 1 );

		shader->Render();

		D3D::GetDC()->Draw( vertexCount, 0 );

		if ( bDepth == false ) States::SetDepthStencil( depthOnState );
	}

	void SetLocalScale( D3DXVECTOR3 vec )
	{
		D3DXMatrixScaling( &scaleMat, vec.x, vec.y, vec.z );
	}
	void SetLocalRotation( D3DXVECTOR3 vec )
	{
		D3DXQUATERNION q;
		D3DXQuaternionRotationYawPitchRoll( &q, vec.y, vec.x, vec.z );
		D3DXMatrixRotationQuaternion( &rotMat, &q );
	}
	void SetLocalTranslation( D3DXVECTOR3 vec )
	{
		D3DXMatrixTranslation( &transMat, vec.x, vec.y, vec.z );
	}

	D3DXVECTOR3 GetLocalScale() { return scaleVec; }
	D3DXVECTOR3 GetLocalRotation() { return rotVec; }
	D3DXVECTOR3 GetLocalTranslation() { return transVec; }

	void SetLocalTransform( D3DXMATRIX mat ) { world = mat; }
	void SetTransform( D3DXMATRIX mat )
	{
		center.x = mat._41;
		center.y = mat._42;
		center.z = mat._43;

		world = scaleMat * rotMat * transMat;

		D3DXMATRIX worldMatrix;
		D3DXMatrixIdentity( &worldMatrix );

		worldMatrix = world * mat;
		worldBuffer->SetMatrix( worldMatrix );
	}

private:
	VertexColor*	vertexData;
	ID3D11Buffer*	vertexBuffer;
	UINT			vertexCount;
};