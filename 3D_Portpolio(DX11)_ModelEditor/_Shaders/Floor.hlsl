#include "Constants.hlsl"

cbuffer PS_Color : register(b2)
{
	float4 _color;
}

struct VertexInput
{
    float4 position : POSITION0;
};

struct PixelInput
{
    float4 position : SV_POSITION;
	float3 wPosition : POSITION0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);
	
	return output;
}

Texture2D _diffuseMap : register(t0);
Texture2D _normalMap : register(t1);
Texture2D _specularMap : register(t2);

float4 PS(PixelInput input) : SV_TARGET
{
	return _color; 
}