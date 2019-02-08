#pragma once

class Shader
{
public:
	friend struct Pass;

public:
	Shader( wstring file, bool bSubContext = false );
	~Shader();

	wstring			GetFile()	{ return file; }
	ID3DX11Effect*	GetEffect()	{ return effect; }

	void Draw
	( 
		UINT technique,
		UINT pass,
		UINT vertexCount,
		UINT startVertexLocation = 0
	);
	void DrawIndexed
	( 
		UINT technique,
		UINT pass,
		UINT indexCount,
		UINT startIndexLocation		= 0,
		INT  baseVertexLocation		= 0
	);
	void DrawInstanced
	( 
		UINT technique,
		UINT pass,
		UINT vertexCountPerInstance,
		UINT instanceCount,
		UINT startVertexLocation	= 0,
		UINT startInstanceLocation	= 0
	);
	void DrawIndexedInstanced
	(
		UINT technique,
		UINT pass,
		UINT indexCountPerInstance,
		UINT instanceCount,
		UINT startIndexLocation		= 0,
		INT  baseVertexLocation		= 0,
		UINT startInstanceLocation	= 0
	);

	void Dispatch( UINT technique, UINT pass, UINT x, UINT y, UINT z );

	ID3DX11EffectVariable*						GetVariable( string name );
	ID3DX11EffectScalarVariable*				GetAsScalar( string name );
	ID3DX11EffectVectorVariable*				GetAsVector( string name );
	ID3DX11EffectMatrixVariable*				GetAsMatrix( string name );
	ID3DX11EffectStringVariable*				GetAsString( string name );
	ID3DX11EffectShaderResourceVariable*		GetAsShaderResource( string name );
	ID3DX11EffectRenderTargetViewVariable*		GetAsRTV( string name );
	ID3DX11EffectDepthStencilViewVariable*		GetAsDSV( string name );
	ID3DX11EffectUnorderedAccessViewVariable*	GetAsUAV( string name );
	ID3DX11EffectConstantBuffer*				GetAsConstantBuffer( string name );
	ID3DX11EffectShaderVariable*				GetAsShader( string name );
	ID3DX11EffectBlendVariable*					GetAsBlend( string name );
	ID3DX11EffectDepthStencilVariable*			GetAsDepthStencil( string name );
	ID3DX11EffectRasterizerVariable*			GetAsRasterizer( string name );
	ID3DX11EffectSamplerVariable*				GetAsSampler( string name );

private:
	void CreateEffect();
	ID3D11InputLayout* CreateInputLayout
	(
		ID3DBlob*								fxBolob,
		D3DX11_EFFECT_SHADER_DESC*				effectVsDesc,
		vector<D3D11_SIGNATURE_PARAMETER_DESC>& params
	);

private:
	wstring				file;

	ID3DX11Effect*		effect;
	D3DX11_EFFECT_DESC	effectDesc;

private:
	// ======================================================================
	//						Effect Buffer Struct
	// ======================================================================
	struct EffectBuffer
	{
		UINT							Index;
		ID3DX11EffectConstantBuffer*	Buffer;
		D3DX11_EFFECT_VARIABLE_DESC		Desc;

		ID3DX11EffectVariable* GetVariable( string name )
		{
			return Buffer->GetAnnotationByName( name.c_str() );
		}
	};
	map<string, EffectBuffer>	cBufferMap;

	// ======================================================================
	//						EffectVariable Struct
	// ======================================================================
	struct EffectVariable
	{
		UINT					Index;
		ID3DX11EffectVariable*	Variable;
	};
	map<string, EffectVariable> variableMap;

	// ======================================================================
	//							StateBlock Struct
	// ======================================================================
	struct StateBlock
	{
		ID3D11RasterizerState*		RSRasterizerState;
		ID3D11BlendState*			OMBlendState;
		FLOAT						OMBlendFactor[ 4 ];
		UINT						OMSampleMask;
		ID3D11DepthStencilState*	OMDepthStencilState;
		UINT						OMStencilRef;
	};
	StateBlock* initialStateBlock;

	// ======================================================================
	//							  Pass Struct
	// ======================================================================
	struct Pass
	{
		wstring									Name;
		ID3DX11EffectPass*						IPass;
		D3DX11_PASS_DESC						Desc;

		ID3D11InputLayout*						InputLayout;
		D3DX11_PASS_SHADER_DESC					PassVsDesc;
		D3DX11_EFFECT_SHADER_DESC				EffectVsDesc;
		vector<D3D11_SIGNATURE_PARAMETER_DESC>	SignatureDescs;

		D3DX11_STATE_BLOCK_MASK					StateBlockMask;
		StateBlock*								StateBlock;

		void Draw
		(
			UINT vertexCount,
			UINT startVertexLocation = 0
		);
		void DrawIndexed
		(
			UINT indexCount,
			UINT startIndexLocation = 0,
			INT  baseVertexLocation = 0
		);
		void DrawInstanced
		(
			UINT vertexCountPerInstance,
			UINT instanceCount,
			UINT startVertexLocation	= 0,
			UINT startInstanceLocation	= 0
		);
		void DrawIndexedInstanced
		(
			UINT indexCountPerInstance,
			UINT instanceCount,
			UINT startIndexLocation		= 0,
			INT  baseVertexLocation		= 0,
			UINT startInstanceLocation	= 0
		);

		void BeginDraw();
		void EndDraw();

		void Dispatch( UINT x, UINT y, UINT z );
	};

	// ======================================================================
	//							Technique Struct
	// ======================================================================
	struct Technique
	{
		wstring					Name;
		D3DX11_TECHNIQUE_DESC	Desc;
		ID3DX11EffectTechnique* ITechnique;

		vector<Pass> Passes;

		void Draw
		(
			UINT pass,
			UINT vertexCount,
			UINT startVertexLocation = 0
		);
		void DrawIndexed
		(
			UINT pass,
			UINT indexCount,
			UINT startIndexLocation = 0,
			INT  baseVertexLocation = 0
		);
		void DrawInstanced
		(
			UINT pass,
			UINT vertexCountPerInstance,
			UINT instanceCount,
			UINT startVertexLocation	= 0,
			UINT startInstanceLocation	= 0
		);
		void DrawIndexedInstanced
		(
			UINT pass,
			UINT indexCountPerInstance,
			UINT instanceCount,
			UINT startIndexLocation		= 0,
			INT  baseVertexLocation		= 0,
			UINT startInstanceLocation	= 0
		);

		void Dispatch( UINT pass, UINT x, UINT y, UINT z );
	};
	vector<Technique> techniques;
};

class Shaders
{
public:
	friend class Shader;
	
	struct ShaderDesc
	{
		ID3DBlob*		Blob;
		ID3DX11Effect*	Effect;
	};

	typedef pair<wstring, ShaderDesc> Pair;

public:
	static void Delete();
	static void GetEffect( wstring fileName, _Out_ ID3DBlob** blob, ID3DX11Effect** effect );

private:
	static unordered_map<wstring, ShaderDesc> shaders;
};