#pragma once

#include "stdafx.h"
#include "Gizmos.h"

class GizmosCapsule : public Gizmos
{
public:
	GizmosCapsule( D3DXCOLOR color )
		: Gizmos( GIZMOSTYPE:: CAPSULE)
		, vertexData	( NULL )
		, vertexBuffer	( NULL )
		, vertexCount	( 0 )
	{
		center		= D3DXVECTOR3( 0, 0, 0 );
		this->color = color;

		height = 1.0f;
		radius = 1.0f;
		upperCenter = D3DXVECTOR3( 0,  height * 0.5f, 0 );
		downCenter	= D3DXVECTOR3( 0, -height * 0.5f, 0 );

		CreateBuffer();
	}

	~GizmosCapsule()
	{
		SAFE_RELEASE( vertexBuffer );
	}

	void Update( D3DXMATRIX mat )
	{
		D3DXMATRIX worldMatrix;
		D3DXMatrixIdentity( &worldMatrix );

		world = scaleMat * rotMat * transMat;
		worldMatrix = world * mat;
		worldBuffer->SetMatrix( worldMatrix );
	}

	void Render()
	{
		if ( bDepth == false )  States::SetDepthStencil( depthOffState );
		{
			UINT stride = sizeof( VertexColor );
			UINT offset = 0;

			D3D::GetDC()->IASetVertexBuffers( 0, 1, &vertexBuffer, &stride, &offset );
			D3D::GetDC()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_LINELIST );

			worldBuffer->SetVSBuffer( 1 );
			gizmosBuffer->SetPSBuffer( 1 );

			shader->Render();

			D3D::GetDC()->Draw( vertexCount, 0 );
		}
		if ( bDepth == false ) States::SetDepthStencil( depthOnState );
	}

	void SetLocalScale( D3DXVECTOR3 vec )
	{
		scaleVec = vec;
		D3DXMatrixScaling( &scaleMat, vec.x, vec.y, vec.z );
	}
	void SetLocalRotation( D3DXVECTOR3 vec )
	{
		rotVec = vec;
		D3DXVECTOR3 temp = vec * ( float )D3DX_PI / 180.0f;

		D3DXQUATERNION q;
		D3DXQuaternionRotationYawPitchRoll( &q, temp.y, temp.x, temp.z );
		D3DXMatrixRotationQuaternion( &rotMat, &q );
	}
	void SetLocalTranslation( D3DXVECTOR3 vec )
	{
		transVec = vec;
		D3DXMatrixTranslation( &transMat, vec.x, vec.y, vec.z );
	}

	D3DXVECTOR3 GetLocalScale() { return scaleVec; }
	D3DXVECTOR3 GetLocalRotation() { return rotVec; }
	D3DXVECTOR3 GetLocalTranslation() { return transVec; }

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

	D3DXVECTOR3 GetUpperCenter()	{ return upperCenter; }
	D3DXVECTOR3 GetDownCenter()		{ return downCenter; }
	float GetHeight()				{ return height; }
	float GetRadius()				{ return radius; }
	void SetHeight( float height )
	{
		this->height = height;
		upperCenter = D3DXVECTOR3( 0,  height * 0.5f, 0 );
		downCenter	= D3DXVECTOR3( 0, -height * 0.5f, 0 );
		CreateBuffer();
	}
	void SetRadius( float radius )
	{
		this->radius = radius;
		CreateBuffer();
	}

	void CreateBuffer()
	{
		float dt = 15.0f / 180.0f * ( float )D3DX_PI;

		vector<D3DXVECTOR3> pos;
		vector<UINT> index;
		for ( int i = 0; i < 75; i++ )
		{
			D3DXVECTOR3 vec;
			if ( i < 25 )
			{
				vec.x = radius * cosf( i * dt );
				vec.y = 0.0f;
				vec.z = radius * sinf( i * dt );
			}
			else if ( i >= 25 && i < 50 )
			{
				vec.x = 0.0f;
				vec.y = radius * sinf( ( i - 25 ) * dt );
				vec.z = radius * cosf( ( i - 25 ) * dt );
			}
			else
			{
				vec.x = radius * cosf( ( i - 50 ) * dt );
				vec.y = radius * sinf( ( i - 50 ) * dt );
				vec.z = 0.0f;
			}
			pos.push_back( vec );
		}
		vertexCount = 208;
		vertexData = new VertexColor[ vertexCount ];

		int count = 0;
		// upper
		for ( int i = 0; i < 24; i++ )
		{
			vertexData[ count ].position = upperCenter + pos[ i ]; count++;
			vertexData[ count ].position = upperCenter + pos[ i + 1 ]; count++;
		}
		for ( int i = 25; i < 37; i++ )
		{
			vertexData[ count ].position = upperCenter + pos[ i ]; count++;
			vertexData[ count ].position = upperCenter + pos[ i + 1 ]; count++;
		}
		for ( int i = 50; i < 62; i++ )
		{
			vertexData[ count ].position = upperCenter + pos[ i ]; count++;
			vertexData[ count ].position = upperCenter + pos[ i + 1 ]; count++;
		}
		// down
		for ( int i = 0; i < 24; i++ )
		{
			vertexData[ count ].position = downCenter + pos[ i ]; count++;
			vertexData[ count ].position = downCenter + pos[ i + 1 ]; count++;
		}
		for ( int i = 37; i < 49; i++ )
		{
			vertexData[ count ].position = downCenter + pos[ i ]; count++;
			vertexData[ count ].position = downCenter + pos[ i + 1]; count++;
		}
		for ( int i = 62; i < 74; i++ )
		{
			vertexData[ count ].position = downCenter + pos[ i ]; count++;
			vertexData[ count ].position = downCenter + pos[ i + 1 ]; count++;
		}
		// cylinder
		vertexData[ count ].position = upperCenter + pos[ 0 ]; count++;
		vertexData[ count ].position = downCenter + pos[ 0 ]; count++;

		vertexData[ count ].position = upperCenter + pos[ 6 ]; count++;
		vertexData[ count ].position = downCenter + pos[ 6 ]; count++;

		vertexData[ count ].position = upperCenter + pos[ 12 ]; count++;
		vertexData[ count ].position = downCenter + pos[ 12 ]; count++;

		vertexData[ count ].position = upperCenter + pos[ 18 ]; count++;
		vertexData[ count ].position = downCenter + pos[ 18 ];

		for ( int i = 0; i < count + 1; i++ )
		{
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
	}

private:
	VertexColor*  vertexData;
	ID3D11Buffer* vertexBuffer;
	UINT		  vertexCount;

	D3DXVECTOR3 upperCenter;
	D3DXVECTOR3 downCenter;
	D3DXCOLOR	color;
	float height;
	float radius;
};