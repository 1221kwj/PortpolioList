#pragma once
// ======================================================================
//								Struct Vertex
// ======================================================================
struct Vertex
{
	Vertex() : Position( 0.0f, 0.0f, 0.0f ) {}

	Vector3 Position;
};
// ======================================================================
//							Struct VertexColor
// ======================================================================
struct VertexColor
{
	VertexColor()
		: Position	( 0.0f, 0.0f, 0.0f )
		, Color		( 0.0f, 0.0f, 0.0f, 1.0f ) {}

	Vector3	Position;
	Vector4	Color;
} typedef VC;

// ======================================================================
//						Struct VertexColorNormal
// ======================================================================
struct VertexColorNormal
{
	VertexColorNormal()
		: Position	( 0.0f, 0.0f, 0.0f )
		, Color		( 0.0f, 0.0f, 0.0f, 1.0f )
		, Normal	( 0.0f, 0.0f, 0.0f ) {}

	Vector3 Position;
	Vector4 Color;
	Vector3 Normal;
} typedef VCN;

// ======================================================================
//						Struct VertexTexture
// ======================================================================
struct VertexTexture
{
	VertexTexture()
		: Position	( 0.0f, 0.0f, 0.0f )
		, Uv		( 0.0f, 0.0f ) {}

	Vector3	Position;
	Vector2	Uv;
} typedef VT;

// ======================================================================
//						Struct VertexTextureNormal
// ======================================================================
struct VertexTextureNormal
{
	VertexTextureNormal()
		: Position	( 0.0f, 0.0f, 0.0f )
		, Uv		( 0.0f, 0.0f )
		, Normal	( 0.0f, 0.0f, 0.0f ) {}

	Vector3 Position;
	Vector2 Uv;
	Vector3 Normal;
} typedef VTN;

// ======================================================================
//						Struct VertexColorTextureNormal
// ======================================================================
struct VertexColorTextureNormal
{
	VertexColorTextureNormal()
		: Position	( 0.0f, 0.0f, 0.0f )
		, Color		( 0.0f, 0.0f, 0.0f, 1.0f )
		, Uv		( 0.0f, 0.0f )
		, Normal	( 0.0f, 0.0f, 0.0f ) {}

	Vector3 Position;
	Vector4 Color;
	Vector2 Uv;
	Vector3 Normal;
} typedef VCTN;

// ======================================================================
//						Struct VertexTextureNormalBlend
// ======================================================================
struct VertexTextureNormalBlend
{
	VertexTextureNormalBlend()
		: Position		( 0.0f, 0.0f, 0.0f )
		, Uv			( 0.0f, 0.0f )
		, Normal		( 0.0f, 0.0f, 0.0f )
		, BlendIndices	( 0.0f, 0.0f, 0.0f, 0.0f )
		, BlendWeights	( 0.0f, 0.0f, 0.0f, 0.0f ) {}

	Vector3 Position;
	Vector2 Uv;
	Vector3 Normal;
	Vector4 BlendIndices;
	Vector4 BlendWeights;
};

// ======================================================================
//					Struct VertexTextureNormalTangent
// ======================================================================
struct VertexTextureNormalTangent
{
	VertexTextureNormalTangent()
		: Position	( 0.0f, 0.0f, 0.0f )
		, Uv		( 0.0f, 0.0f )
		, Normal	( 0.0f, 0.0f, 0.0f )
		, Tangent	( 0.0f, 0.0f, 0.0f ) {}

	VertexTextureNormalTangent
	( 
		float px, float py, float pz,
		float u , float v ,
		float nx, float ny, float nz,
		float tx, float ty, float tz
	)
		: Position	( px, py, pz )
		, Uv		( u, v )
		, Normal	( nx, ny, nz )
		, Tangent	( tx, ty, tz ) {}

	Vector3	Position;
	Vector2	Uv;
	Vector3	Normal;
	Vector3 Tangent;
} typedef VTNT;

// ======================================================================
//					Struct VertexTextureNormalTangentBlend
// ======================================================================
struct VertexTextureNormalTangentBlend
{
	VertexTextureNormalTangentBlend()
		: Position		( 0.0f, 0.0f, 0.0f )
		, Uv			( 0.0f, 0.0f )
		, Normal		( 0.0f, 0.0f, 0.0f )
		, Tangent		( 0.0f, 0.0f, 0.0f )
		, BlendIndices	( 0.0f, 0.0f, 0.0f, 0.0f )
		, BlendWeights	( 0.0f, 0.0f, 0.0f, 0.0f ) {}

	Vector3	Position;
	Vector2	Uv;
	Vector3	Normal;
	Vector3 Tangent;
	Vector4 BlendIndices;
	Vector4 BlendWeights;
} typedef VTNTB;

// ======================================================================
//						Struct VertexTextureColor2
// ======================================================================
struct VertexTextureColor2
{
	VertexTextureColor2()
		: Position	( 0.0f, 0.0f, 0.0f )
		, Uv		( 0.0f, 0.0f )
		, Color		( 0.0f, 0.0f, 0.0f, 1.0f )
		, Color2	( 0.0f, 0.0f, 0.0f, 1.0f ) {}

	Vector3 Position;
	Vector2 Uv;
	Vector4 Color;
	Vector4 Color2;
} typedef VTC2;