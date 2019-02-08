#include "stdafx.h"
#include "Shader.h"

// ======================================================================
//							  Pass Struct
// ======================================================================
void Shader::Pass::Draw( UINT vertexCount, UINT startVertexLocation )
{
	BeginDraw();
	{
		D3D::GetDC()->Draw( vertexCount, startVertexLocation );
	}
	EndDraw();
}

void Shader::Pass::DrawIndexed( UINT indexCount, UINT startIndexLocation, INT baseVertexLocation )
{
	BeginDraw();
	{
		D3D::GetDC()->DrawIndexed
		(
			indexCount,
			startIndexLocation,
			baseVertexLocation
		);
	}
	EndDraw();
}

void Shader::Pass::DrawInstanced( UINT vertexCountPerInstance, UINT instanceCount, UINT startVertexLocation, UINT startInstanceLocation )
{
	BeginDraw();
	{
		D3D::GetDC()->DrawInstanced
		(
			vertexCountPerInstance,
			instanceCount,
			startVertexLocation,
			startInstanceLocation
		);
	}
	EndDraw();
}

void Shader::Pass::DrawIndexedInstanced( UINT indexCountPerInstance, UINT instanceCount, UINT startIndexLocation, INT baseVertexLocation, UINT startInstanceLocation )
{
	BeginDraw();
	{
		D3D::GetDC()->DrawIndexedInstanced
		( 
			indexCountPerInstance,
			instanceCount,
			startIndexLocation,
			baseVertexLocation,
			startIndexLocation
		);
	}
	EndDraw();
}

void Shader::Pass::BeginDraw()
{
	IPass->ComputeStateBlockMask( &StateBlockMask );

	D3D::GetDC()->IASetInputLayout( InputLayout );
	IPass->Apply( 0, D3D::GetDC() );
}

void Shader::Pass::EndDraw()
{
	if ( StateBlockMask.RSRasterizerState == 1 )
		D3D::GetDC()->RSSetState( StateBlock->RSRasterizerState );

	if ( StateBlockMask.OMDepthStencilState == 1 )
		D3D::GetDC()->OMSetDepthStencilState( StateBlock->OMDepthStencilState, StateBlock->OMStencilRef );

	if ( StateBlockMask.OMBlendState == 1 )
		D3D::GetDC()->OMSetBlendState( StateBlock->OMBlendState, StateBlock->OMBlendFactor, StateBlock->OMSampleMask );

	D3D::GetDC()->HSSetShader( NULL, NULL, 0 );
	D3D::GetDC()->DSSetShader( NULL, NULL, 0 );
	D3D::GetDC()->GSSetShader( NULL, NULL, 0 );
}

void Shader::Pass::Dispatch( UINT x, UINT y, UINT z )
{
	IPass->Apply( 0, D3D::GetDC() );
	D3D::GetDC()->Dispatch( x, y, z );

	ID3D11ShaderResourceView* null[ 1 ] = { 0 };
	D3D::GetDC()->CSSetShaderResources( 0, 1, null );

	ID3D11UnorderedAccessView* nullUav[ 1 ] = { 0 };
	D3D::GetDC()->CSSetUnorderedAccessViews( 0, 1, nullUav, NULL );

	D3D::GetDC()->CSSetShader( NULL, NULL, 0 );
}

// ======================================================================
//							Technique Struct
// ======================================================================
void Shader::Technique::Draw( UINT pass, UINT vertexCount, UINT startVertexLocation )
{
	Passes[ pass ].Draw
	( 
		vertexCount,
		startVertexLocation
	);
}

void Shader::Technique::DrawIndexed( UINT pass, UINT indexCount, UINT startIndexLocation, INT baseVertexLocation )
{
	Passes[ pass ].DrawIndexed
	( 
		indexCount, 
		startIndexLocation, 
		baseVertexLocation
	);
}

void Shader::Technique::DrawInstanced( UINT pass, UINT vertexCountPerInstance, UINT instanceCount, UINT startVertexLocation, UINT startInstanceLocation )
{
	Passes[ pass ].DrawInstanced
	(
		vertexCountPerInstance,
		instanceCount,
		startVertexLocation,
		startInstanceLocation
	);
}

void Shader::Technique::DrawIndexedInstanced( UINT pass, UINT indexCountPerInstance, UINT instanceCount, UINT startIndexLocation, INT baseVertexLocation, UINT startInstanceLocation )
{
	Passes[ pass ].DrawIndexedInstanced
	(
		indexCountPerInstance,
		instanceCount,
		startIndexLocation,
		baseVertexLocation,
		startInstanceLocation
	);
}

void Shader::Technique::Dispatch( UINT pass, UINT x, UINT y, UINT z )
{
	Passes[ pass ].Dispatch( x, y, z );
}
