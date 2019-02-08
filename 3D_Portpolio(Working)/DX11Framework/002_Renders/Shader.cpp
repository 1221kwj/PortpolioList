#include "stdafx.h"
#include "Shader.h"

Shader::Shader( wstring file, bool bSubContext )
	: file	( file )
	, effect( NULL )
{
	initialStateBlock = new StateBlock();
	{
		D3D::GetDC()->RSGetState			
		( 
			&initialStateBlock->RSRasterizerState
		);
		D3D::GetDC()->OMGetBlendState		
		( 
			&initialStateBlock	->OMBlendState,
			initialStateBlock	->OMBlendFactor,
			&initialStateBlock	->OMSampleMask
		);
		D3D::GetDC()->OMGetDepthStencilState
		( 
			&initialStateBlock->OMDepthStencilState,
			&initialStateBlock->OMStencilRef
		);
	}

	CreateEffect();

	if ( bSubContext == false )
		Context::Get()->AddShader( this );
}

Shader::~Shader()
{
	for ( Technique& temp : techniques )
	{
		for ( Pass& pass : temp.Passes )
		{
			SAFE_RELEASE( pass.InputLayout );
		}
	}

	SAFE_DELETE( initialStateBlock );

	SAFE_RELEASE( effect );
}

void Shader::CreateEffect()
{
	ID3DBlob* fxBlob;

	Shaders::GetEffect( file, &fxBlob, &effect );

	effect->GetDesc( &effectDesc );

	for ( UINT t = 0; t < effectDesc.Techniques; t++ )
	{
		Technique technique;
		technique.ITechnique = effect->GetTechniqueByIndex( t );
		technique.ITechnique->GetDesc( &technique.Desc );
		technique.Name = String::ToWString( technique.Desc.Name );

		for ( UINT p = 0; p < technique.Desc.Passes; p++ )
		{
			Pass pass;
			pass.IPass = technique.ITechnique->GetPassByIndex( p );
			pass.IPass->GetDesc( &pass.Desc );
			pass.Name = String::ToWString( pass.Desc.Name );
			pass.IPass->GetVertexShaderDesc( &pass.PassVsDesc );
			pass.PassVsDesc.pShaderVariable->GetShaderDesc( pass.PassVsDesc.ShaderIndex, &pass.EffectVsDesc );

			for ( UINT s = 0; s < pass.EffectVsDesc.NumInputSignatureEntries; s++ )
			{
				D3D11_SIGNATURE_PARAMETER_DESC desc;
				HRESULT hr = pass.PassVsDesc.pShaderVariable->GetInputSignatureElementDesc( pass.PassVsDesc.ShaderIndex, s, &desc );
				assert( SUCCEEDED( hr ) );

				pass.SignatureDescs.push_back( desc );
			}

			pass.InputLayout	= CreateInputLayout( fxBlob, &pass.EffectVsDesc, pass.SignatureDescs );
			pass.StateBlock		= initialStateBlock;

			technique.Passes.push_back( pass );
		}

		techniques.push_back( technique );
	}

	for ( UINT i = 0; i < effectDesc.ConstantBuffers; i++ )
	{
		EffectBuffer cBuffer;

		ID3DX11EffectConstantBuffer* iBuffer;
		iBuffer = effect->GetConstantBufferByIndex( i );

		D3DX11_EFFECT_VARIABLE_DESC vDesc;
		iBuffer->GetDesc( &vDesc );

		cBuffer.Index	= i;
		cBuffer.Buffer	= iBuffer;
		cBuffer.Desc	= vDesc;

		cBufferMap.insert( pair<string, EffectBuffer>( vDesc.Name, cBuffer ) );
	}

	for ( UINT i = 0; i < effectDesc.GlobalVariables; i++ )
	{
		EffectVariable variable;

		ID3DX11EffectVariable* iVariable;
		iVariable = effect->GetVariableByIndex( i );

		D3DX11_EFFECT_VARIABLE_DESC vDesc;
		iVariable->GetDesc( &vDesc );

		variable.Index		= i;
		variable.Variable	= iVariable;

		variableMap.insert( pair<string, EffectVariable>( vDesc.Name, variable ) );
	}
}

ID3D11InputLayout * Shader::CreateInputLayout( ID3DBlob * fxBolob, D3DX11_EFFECT_SHADER_DESC * effectVsDesc, vector<D3D11_SIGNATURE_PARAMETER_DESC>& params )
{
	vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
	
	for ( D3D11_SIGNATURE_PARAMETER_DESC& paramDesc : params )
	{
		D3D11_INPUT_ELEMENT_DESC elementDesc;
		elementDesc.SemanticName			= paramDesc.SemanticName;
		elementDesc.SemanticIndex			= paramDesc.SemanticIndex;
		elementDesc.InputSlot				= 0;
		elementDesc.AlignedByteOffset		= D3D11_APPEND_ALIGNED_ELEMENT;
		elementDesc.InputSlotClass			= D3D11_INPUT_PER_VERTEX_DATA;
		elementDesc.InstanceDataStepRate	= 0;

		if ( paramDesc.Mask == 1 )
		{
			if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 )
				elementDesc.Format = DXGI_FORMAT_R32_UINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 )
				elementDesc.Format = DXGI_FORMAT_R32_SINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 )
				elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
		}
		else if ( paramDesc.Mask <= 3 )
		{
			if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 )
				elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 )
				elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 )
				elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
		}
		else if ( paramDesc.Mask <= 7 )
		{
			if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 )
				elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 )
				elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 )
				elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
		}
		else if ( paramDesc.Mask <= 15 )
		{
			if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32 )
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32 )
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
			else if ( paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32 )
				elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		}

		string name = paramDesc.SemanticName;
		if ( name == "POSITION" )
			elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

		if ( name == "INSTANCE" )
		{
			elementDesc.InputSlot				= 1;
			elementDesc.AlignedByteOffset		= D3D11_APPEND_ALIGNED_ELEMENT;
			elementDesc.InputSlotClass			= D3D11_INPUT_PER_INSTANCE_DATA;
			elementDesc.InstanceDataStepRate	= 1;
		}

		inputLayoutDesc.push_back( elementDesc );
	}


	const void* pCode	= effectVsDesc->pBytecode;
	UINT pCodeSize		= effectVsDesc->BytecodeLength;

	if ( inputLayoutDesc.size() > 0 )
	{
		ID3D11InputLayout* inputLayout = NULL;
		HRESULT hr = D3D::GetDevice()->CreateInputLayout
		(
			&inputLayoutDesc[ 0 ],
			( UINT )inputLayoutDesc.size(),
			pCode,
			pCodeSize,
			&inputLayout
		);
		assert( SUCCEEDED( hr ) );

		return inputLayout;
	}

	return NULL;
}

void Shader::Draw
( 
	UINT technique,
	UINT pass,
	UINT vertexCount,
	UINT startVertexLocation
)
{
	techniques[ technique ].Passes[ pass ].Draw
	( 
		vertexCount,
		startVertexLocation
	);
}

void Shader::DrawIndexed
( 
	UINT technique,
	UINT pass,
	UINT indexCount,
	UINT startIndexLocation,
	INT  baseVertexLocation
)
{
	techniques[ technique ].Passes[ pass ].DrawIndexed
	( 
		indexCount,
		startIndexLocation,
		baseVertexLocation
	);
}

void Shader::DrawInstanced
( 
	UINT technique,
	UINT pass,
	UINT vertexCountPerInstance,
	UINT instanceCount,
	UINT startVertexLocation,
	UINT startInstanceLocation
)
{
	techniques[ technique ].Passes[ pass ].DrawInstanced
	( 
		vertexCountPerInstance,
		instanceCount,
		startVertexLocation,
		startInstanceLocation
	);
}

void Shader::DrawIndexedInstanced
( 
	UINT technique,
	UINT pass,
	UINT indexCountPerInstance,
	UINT instanceCount,
	UINT startIndexLocation,
	INT  baseVertexLocation,
	UINT startInstanceLocation
)
{
	techniques[ technique ].Passes[ pass ].DrawIndexedInstanced
	(
		indexCountPerInstance,
		instanceCount,
		startIndexLocation,
		baseVertexLocation,
		startInstanceLocation
	);
}

void Shader::Dispatch( UINT technique, UINT pass, UINT x, UINT y, UINT z )
{
	techniques[ technique ].Passes[ pass ].Dispatch( x, y, z );
}

ID3DX11EffectVariable * Shader::GetVariable( string name )
{
	return variableMap[ name ].Variable;
}

ID3DX11EffectScalarVariable * Shader::GetAsScalar( string name )
{
	return variableMap[ name ].Variable->AsScalar();
}

ID3DX11EffectVectorVariable * Shader::GetAsVector( string name )
{
	return variableMap[ name ].Variable->AsVector();
}

ID3DX11EffectMatrixVariable * Shader::GetAsMatrix( string name )
{
	return variableMap[ name ].Variable->AsMatrix();
}

ID3DX11EffectStringVariable * Shader::GetAsString( string name )
{
	return variableMap[ name ].Variable->AsString();
}

ID3DX11EffectShaderResourceVariable * Shader::GetAsShaderResource( string name )
{
	return variableMap[ name ].Variable->AsShaderResource();
}

ID3DX11EffectRenderTargetViewVariable * Shader::GetAsRTV( string name )
{
	return variableMap[ name ].Variable->AsRenderTargetView();
}

ID3DX11EffectDepthStencilViewVariable * Shader::GetAsDSV( string name )
{
	return variableMap[ name ].Variable->AsDepthStencilView();
}

ID3DX11EffectUnorderedAccessViewVariable * Shader::GetAsUAV( string name )
{
	return variableMap[ name ].Variable->AsUnorderedAccessView();
}

ID3DX11EffectConstantBuffer * Shader::GetAsConstantBuffer( string name )
{
	return cBufferMap[ name ].Buffer;
}

ID3DX11EffectShaderVariable * Shader::GetAsShader( string name )
{
	return variableMap[ name ].Variable->AsShader();
}

ID3DX11EffectBlendVariable * Shader::GetAsBlend( string name )
{
	return variableMap[ name ].Variable->AsBlend();
}

ID3DX11EffectDepthStencilVariable * Shader::GetAsDepthStencil( string name )
{
	return variableMap[ name ].Variable->AsDepthStencil();
}

ID3DX11EffectRasterizerVariable * Shader::GetAsRasterizer( string name )
{
	return variableMap[ name ].Variable->AsRasterizer();
}

ID3DX11EffectSamplerVariable * Shader::GetAsSampler( string name )
{
	return variableMap[ name ].Variable->AsSampler();
}

// ======================================================================
//							  Shaders
// ======================================================================
unordered_map<wstring, Shaders::ShaderDesc> Shaders::shaders;

void Shaders::Delete()
{
	for ( Pair p : shaders )
	{
		SAFE_RELEASE( p.second.Blob );
		SAFE_RELEASE( p.second.Effect );
	}
}

void Shaders::GetEffect( wstring fileName, _Out_ ID3DBlob ** blob, ID3DX11Effect ** effect )
{
	bool bFind = false;

	if ( shaders.count( fileName ) < 1 )
	{
		Pair p;

		ID3DBlob* error;
		INT flag = D3D10_SHADER_ENABLE_BACKWARDS_COMPATIBILITY | D3D10_SHADER_PACK_MATRIX_ROW_MAJOR;

		HRESULT hr;
		hr = D3DCompileFromFile
		(
			fileName.c_str(),
			NULL,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			NULL,
			"fx_5_0",
			flag,
			NULL,
			&p.second.Blob,
			&error
		);
		if ( FAILED( hr ) )
		{
			if ( error != NULL )
			{
				string str = ( const char* )error->GetBufferPointer();
				MessageBoxA( NULL, str.c_str(), "Shader Error", MB_OK );
			}
			assert( false );
		}

		hr = D3DX11CreateEffectFromMemory
		(
			p.second.Blob->GetBufferPointer(),
			p.second.Blob->GetBufferSize(),
			0,
			D3D::GetDevice(),
			&p.second.Effect
		);
		assert( SUCCEEDED( hr ) );

		p.first = fileName;

		shaders.insert( p );

		*blob = p.second.Blob;
		p.second.Effect->CloneEffect( D3DX11_EFFECT_CLONE_FORCE_NONSINGLE, effect );
	}
	else
	{
		ShaderDesc desc = shaders.at( fileName );

		*blob = desc.Blob;
		desc.Effect->CloneEffect( D3DX11_EFFECT_CLONE_FORCE_NONSINGLE, effect );
	}
}