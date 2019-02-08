#include "000_Header.fx"

struct VertexOutput
{
    float4 Position     : SV_POSITION0;
    float4 oPosition    : POSITION1;
};

VertexOutput VS(VertexTextureNormalTangent input)
{
    VertexOutput output;

    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    output.oPosition = input.Position;

    return output;
}

///////////////////////////////////////////////////////////////////////////////

SamplerState Sampler
{
    Filter      = MIN_MAG_MIP_LINEAR;
    AddressU    = Wrap;
    AddressV    = Wrap;
    AddressW    = Wrap;
};

TextureCube CubeMap;

float4 PS(VertexOutput input) : SV_TARGET
{
    float3 normal = normalize(input.oPosition.xyz);

    return CubeMap.Sample(Sampler, normal);
}

DepthStencilState Depth
{
    //DepthEnable = false;
    DepthFunc   = LESS_EQUAL;
};

RasterizerState Cull
{
    //FillMode = WireFrame;
    FrontCounterClockwise = true;
};

technique11 T0
{
    pass P0
    {
        SetVertexShader (CompileShader(vs_5_0, VS()));
        SetPixelShader  (CompileShader(ps_5_0, PS()));

        SetDepthStencilState(Depth, 0);
        SetRasterizerState  (Cull);
    }
}