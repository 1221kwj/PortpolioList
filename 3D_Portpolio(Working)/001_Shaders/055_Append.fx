struct Data
{
    int Id;
    int Value;
    int Sum;
};

ConsumeStructuredBuffer<int> Input : register(u0);
AppendStructuredBuffer<Data> Output : register(u1);

[numthreads(64, 1, 1)]
void CS(int3 id : SV_GroupThreadId)
{
    int data = Input.Consume();

    uint a, b;
    Input.GetDimensions(a, b);
    
    Data result;
    result.Id = id;
    result.Value = data;
    result.Sum = data;

    Output.Append(result);
}

//-----------------------------------------------------------------------------
// Technique
//-----------------------------------------------------------------------------
technique11 T0
{
    pass P0
    {
        SetVertexShader(NULL);
        SetPixelShader(NULL);
        SetComputeShader(CompileShader(cs_5_0, CS()));
    }
}