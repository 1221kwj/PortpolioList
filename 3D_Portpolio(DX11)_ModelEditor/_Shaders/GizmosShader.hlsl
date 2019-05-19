#include "Constants.hlsl"

cbuffer PS_COLLISIONCOLOR : register(b1)
{
    bool    _collision;
    float3  _collisionPadding;
};

struct VertexInput
{
    float4 position : POSITION0;
    float4 color : COLOR0;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;

    output.position = mul(input.position, _world);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);

    output.color = input.color;

    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    if ( _collision == true )
    {
        return float4(1, 0, 0, 1);
    }

    return input.color;
}