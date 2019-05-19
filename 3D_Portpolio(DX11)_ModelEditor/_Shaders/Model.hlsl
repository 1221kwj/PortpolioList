#include "Constants.hlsl"

cbuffer VS_Bone : register(b2)
{
    matrix _boneScale;
    matrix _boneArray[100];
}

cbuffer VS_Mesh : register(b3)
{
	bool _skinning;
	float3 _bonePadding;
}

cbuffer PS_Material : register(b1)
{
    float4 _ambient;
    float4 _diffuse;
    float4 _normal;
    float4 _specular;
    float4 _emissive;
}

struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 tangent : TANGENT0;
    float3 biNormal : BINORMAL0;
    float4 boneIndices : BLENDINDICES;
    float4 boneWeights : BLENDWEIGHT;
};

struct PixelInput
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL0;
    float3 tangent : TANGENT0;
    float3 biNormal : BINORMAL0;
    float3 viewDirection : OUTPUT0;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    float3 worldPosition;
     
    if (_skinning)
    {
        float4x4 skinTransform = 0;
        skinTransform += mul(input.boneWeights.x, _boneArray[(uint) input.boneIndices.x]);
        skinTransform += mul(input.boneWeights.y, _boneArray[(uint) input.boneIndices.y]);
        skinTransform += mul(input.boneWeights.z, _boneArray[(uint) input.boneIndices.z]);
        skinTransform += mul(input.boneWeights.w, _boneArray[(uint) input.boneIndices.w]);

        output.position = mul(input.position, skinTransform);
        output.normal = normalize(mul(input.normal, (float3x3) skinTransform));
        output.tangent = normalize(mul(input.tangent, (float3x3) skinTransform));
        output.biNormal = normalize(mul(input.biNormal, (float3x3) skinTransform));
        
        output.position = mul(output.position, _boneScale);
        worldPosition = output.position;
    }
    else
    {
        output.position = mul(input.position, _world);
        output.normal = normalize(mul(input.normal, (float3x3) _world));
        output.tangent = normalize(mul(input.tangent, (float3x3) _world));
        output.biNormal = normalize(mul(input.biNormal, (float3x3) _world));
        worldPosition = output.position;
    }
	
    output.viewDirection = normalize(_viewPosition.xyz - worldPosition.xyz);
    output.position = mul(output.position, _view);
    output.position = mul(output.position, _projection);

    output.uv = input.uv;

    return output;
}

Texture2D    _diffuseMap  : register(t0);
Texture2D    _normalMap   : register(t1);
Texture2D    _specularMap : register(t2);
SamplerState _sampler     : register(s0);

float4 PS(PixelInput input) : SV_TARGET
{
    float4 diffuseColor = _diffuseMap.Sample(_sampler, input.uv) * _diffuse;
    float3 normalMapSample = _normalMap.Sample(_sampler, input.uv).rgb;
    float3 bumped = NormalMapSampling(normalMapSample, input.normal, input.tangent, input.biNormal);
    
    float intensity = CalculateDiffuseLighting(bumped);

    float4 color = diffuseColor * intensity;

    float4 specularPower = _specularMap.Sample(_sampler, input.uv);

    float4 specular = CalculateSpecularLighting(_direction, bumped, input.viewDirection, 1);
    specular *= specularPower;

    return color = saturate(color + specular);
}