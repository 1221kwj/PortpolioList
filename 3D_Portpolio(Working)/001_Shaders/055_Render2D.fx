#include "000_Header.fx"

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
struct VertexOutput
{
    float4 Position : SV_POSITION;
    float2 Uv       : UV0;
};

VertexOutput VS(VertexTexture input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    //NDC °ø°£ - FVF_RHWXYZ
    //output.Position = input.Position;

    output.Uv = input.Uv;

    return output;
}

//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
SamplerState Sampler
{
    Filter = MIN_MAG_MIP_LINEAR;
};
Texture2D Map : register(t10);

float4 PS(VertexOutput input) : SV_TARGET
{
    float4 color = Map.Sample(Sampler, input.Uv);

    return color;
}

//-----------------------------------------------------------------------------
// States
//-----------------------------------------------------------------------------
DepthStencilState Depth
{
    DepthEnable = false;
};

//-----------------------------------------------------------------------------
// Techniques
//-----------------------------------------------------------------------------
technique11 T0
{
    pass P0
    {
        SetVertexShader (CompileShader(vs_5_0, VS()));
        SetPixelShader  (CompileShader(ps_5_0, PS()));

        SetDepthStencilState(Depth, 0);
    }
}