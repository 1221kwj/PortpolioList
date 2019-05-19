#pragma once

#include "stdafx.h"
#include "GizmosBuffer.h"

enum class GIZMOSTYPE
{
	NONE = 0,
	SPHERE,
	CAPSULE,
};

class Gizmos
{
public:
	Gizmos( GIZMOSTYPE type )
		: shader		( NULL )
		, bDepth		( true )
		, name			( "" )
		, refBoneName	( "" )
		, depthOffState ( NULL )
		, depthOnState	( NULL )
	{
		this->type = type;

		center		= D3DXVECTOR3( 0, 0, 0 );
		scaleVec	= D3DXVECTOR3( 1, 1, 1 );
		rotVec		= D3DXVECTOR3( 0, 0, 0 );
		transVec	= D3DXVECTOR3( 0, 0, 0 );


		D3DXMatrixIdentity( &world );
		D3DXMatrixIdentity( &bindMat );
		D3DXMatrixIdentity( &scaleMat );
		D3DXMatrixIdentity( &rotMat );
		D3DXMatrixIdentity( &transMat );
		
		D3D11_DEPTH_STENCIL_DESC depthDesc;
		States::GetDepthStencilDesc( &depthDesc );
		States::CreateDepthStencil( &depthDesc, &depthOnState );

		depthDesc.DepthEnable = false;
		States::CreateDepthStencil( &depthDesc, &depthOffState );

		shader = new Shader( Shaders + L"GizmosShader.hlsl" );

		worldBuffer		= new WorldBuffer;
		gizmosBuffer	= new GizmosBuffer;
	}

	virtual ~Gizmos()
	{
		SAFE_RELEASE( depthOnState );
		SAFE_RELEASE( depthOffState );

		SAFE_DELETE( gizmosBuffer );
		SAFE_DELETE( worldBuffer );
		SAFE_DELETE( shader );
	}

	virtual void Render() = 0;
	virtual void Update( D3DXMATRIX mat )					= 0;
	virtual void SetLocalScale( D3DXVECTOR3 vec )			= 0;
	virtual void SetLocalRotation( D3DXVECTOR3 vec )		= 0;
	virtual void SetLocalTranslation( D3DXVECTOR3 vec )		= 0;
	virtual D3DXVECTOR3 GetLocalScale() = 0;
	virtual D3DXVECTOR3 GetLocalRotation() = 0;
	virtual D3DXVECTOR3 GetLocalTranslation() = 0;
	virtual void SetTransform( D3DXMATRIX mat )				= 0;
	
	void SetName( string name )				{ this->name = name; }
	void SetCenter( D3DXVECTOR3 vec )		{ center = vec; }
	void SetColiision( bool bCollision )	{ gizmosBuffer->SetCollision( bCollision ); }
	void SetRefBoneName( string name )		{ refBoneName	= name; }
	string GetRefBoneName()					{ return refBoneName; }
	string GetName()						{ return name; }
	void SetDepthState( bool bDepth )		{ this->bDepth	= bDepth; }
	GIZMOSTYPE GetType()					{ return type; }

protected:
	D3DXVECTOR3					center;
	D3DXVECTOR3					scaleVec;
	D3DXVECTOR3					rotVec;
	D3DXVECTOR3					transVec;
	D3DXMATRIX					world;
	D3DXMATRIX					bindMat;
	D3DXMATRIX					scaleMat;
	D3DXMATRIX					rotMat;
	D3DXMATRIX					transMat;
	string						name;
	string						refBoneName;
	bool						bDepth;
	GIZMOSTYPE					type;

	Shader*						shader;

	WorldBuffer*				worldBuffer;
	GizmosBuffer*				gizmosBuffer;

	ID3D11DepthStencilState*	depthOffState;
	ID3D11DepthStencilState*	depthOnState;
};