#include "000_Header.hlsl"

struct PixelInput
{
    float4 Position : SV_POSITION;
    float2 Uv       : UV0;
    float3 Normal   : NORMAL0;
    float3 Tangent  : TANGENT0;
    float3 ViewDir  : VIEW0;
};

PixelInput VS(VertexTextureNormalTangentBlend input)
{
    PixelInput output;

    matrix world = 0;

    [branch]
    if ( UseBlend == true )
        world = SkinWorld(input.BlendIndices, input.BlendWeights);
    else
        world = BoneWorld();

    output.Position = mul(input.Position, world);
    output.ViewDir  = WorldViewDirection(output.Position);

    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    output.Normal   = WorldNormal(input.Normal, world);
    output.Tangent  = WorldTangent(input.Tangent, world);

    output.Uv       = input.Uv;

    return output;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float4 color = 0;

    float4 diffuse = DiffuseMap.Sample(DiffuseSampler, input.Uv);
    float4 normalMap = NormalMap.Sample(NormalSampler, input.Uv);
    float4 specularMap = SpecularMap.Sample(SpecularSampler, input.Uv);

    DiffuseLighting (color, diffuse, input.Normal);
    NormalMapping   (color, normalMap, input.Normal, input.Tangent);
    SpecularLighting(color, specularMap, input.Normal, input.ViewDir);
    return color;
}
