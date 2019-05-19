#include "Constants.hlsl"

cbuffer PS_Sky : register(b2)
{
    float4 _center;
    float4 _apex;
	float _height;
	float3 _skyPadding;
}

struct VertexInput
{
    float4 position : POSITION0;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float4 wPosition : TEXCOORD0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);

    output.wPosition = input.position;

    return output;
}

Texture2D _diffuseMap : register(t0);
Texture2D _normalMap : register(t1);
Texture2D _specularMap : register(t2);

float4 PS(PixelInput input) : SV_TARGET
{
    float height = saturate(input.wPosition.y);

    return lerp(_center, _apex, height * _height);
}