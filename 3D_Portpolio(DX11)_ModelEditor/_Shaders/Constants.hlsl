cbuffer VS_ViewProjection : register(b0)
{
	matrix _view;
    matrix _projection;
    float3 _viewPosition;
    float _viewProjectionPadding;
}

cbuffer VS_World : register(b1)
{
	matrix _world;
}

cbuffer PS_Sun : register(b0)
{
    float3 _direction;
    float _sunPadding;
}


//디퓨즈 라이팅 계산
float CalculateDiffuseLighting(float3 normal)
{
    float3 light = _direction * -1;
    float intensity = saturate(dot(normal, light));

    return intensity;
}

float CalculateSpecularLighting(float3 direction, float3 normal, float3 eye, float power)
{
    float3 reflection = reflect(direction, normal);
    return pow(saturate(dot(reflection, eye)), power);
}

float3 NormalMapSampling(float3 normalMap, float3 normal, float3 tangent, float3 biNormal)
{
    float3 tempNormal = 2.0f * normalMap - 1.0f;
    float3 N = normal;
    float3 T = tangent;
    float3 B = cross(N, T);
    //float3 B = biNormal;

    float3x3 TBN = float3x3(T, B, N);

    return mul(tempNormal, TBN);
}