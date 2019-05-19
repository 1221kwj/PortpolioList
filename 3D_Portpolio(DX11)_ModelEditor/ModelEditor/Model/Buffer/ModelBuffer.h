#pragma once
#include "stdafx.h"

class BoneBuffer : public ShaderBuffer
{
public:
	BoneBuffer() : ShaderBuffer( &Data, sizeof( Struct ) )
	{
		D3DXMatrixIdentity( &Data.BoneScale );
		//D3DXMatrixScaling(&Data.BoneScale, 0.05f, 0.05f, 0.05f);

		for ( int i = 0; i < 100; i++ )
		{
			D3DXMatrixIdentity( &Data.BoneArray[ i ] );
		}
	}

	const D3DXMATRIX& GetBoneScale() { return Data.BoneScale; }
	void SetBoneScale( const D3DXMATRIX& boneScale )
	{
		D3DXMatrixTranspose( &Data.BoneScale, &boneScale );
	}

	void SetBoneArray( D3DXMATRIX* matrix, UINT count )
	{
		memcpy( Data.BoneArray, matrix, count * sizeof( D3DXMATRIX ) );

		for ( UINT i = 0; i < count; i++ )
			D3DXMatrixTranspose( &Data.BoneArray[ i ], &Data.BoneArray[ i ] );
	}

	struct Struct
	{
		D3DXMATRIX BoneScale;
		D3DXMATRIX BoneArray[ 100 ];
	} Data;
};

class MaterialBuffer : public ShaderBuffer
{
	friend class ModelMaterial;
public:
	MaterialBuffer() : ShaderBuffer( &Data, sizeof( Struct ) )
	{
		Data.Ambient = D3DXCOLOR( 0, 0, 0, 1 );
		Data.Diffuse = D3DXCOLOR( 0, 0, 0, 1 );
		Data.Normal = D3DXCOLOR( 0, 0, 0, 1 );
		Data.Specular = D3DXCOLOR( 0, 0, 0, 1 );
		Data.Emissive = D3DXCOLOR( 0, 0, 0, 1 );
		Data.Shininess = 0.0f;
	}

	const D3DXCOLOR& GetAmbient() const { return Data.Ambient; }
	const D3DXCOLOR& GetDiffuse() const { return Data.Diffuse; }
	const D3DXCOLOR& GetNormal() const { return Data.Normal; }
	const D3DXCOLOR& GetSpecular() const { return Data.Specular; }
	const D3DXCOLOR& GetEmissive() const { return Data.Emissive; }
	float GetShininess() const { return Data.Shininess; }

	void SetAmbient( const D3DXCOLOR& color ) { Data.Ambient = color; }
	void SetDiffuse( const D3DXCOLOR& color ) { Data.Diffuse = color; }
	void SetNormal( const D3DXCOLOR& color ) { Data.Normal = color; }
	void SetSpecular( const D3DXCOLOR& color ) { Data.Specular = color; }
	void SetEmissive( const D3DXCOLOR& color ) { Data.Emissive = color; }
	void SetShininess( const float& shininess ) { Data.Shininess = shininess; }

	struct Struct
	{
		D3DXCOLOR Ambient;
		D3DXCOLOR Diffuse;
		D3DXCOLOR Normal;
		D3DXCOLOR Specular;
		D3DXCOLOR Emissive;
		float Shininess;

		D3DXVECTOR3 Padding;
	} Data;
};

class MeshBuffer : public ShaderBuffer
{
public:
	MeshBuffer() : ShaderBuffer( &Data, sizeof( Struct ) )
	{
		Data.bSkinning = false;
	}

	void SetSkinning( const bool& isSkinning ) { Data.bSkinning = ( UINT )isSkinning; }

	struct Struct
	{
		UINT		bSkinning;
		D3DXVECTOR3 padding;
	} Data;
};