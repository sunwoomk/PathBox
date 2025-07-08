cbuffer WorldBuffer : register(b0)
{
    matrix world;
}
cbuffer ViewBuffer : register(b1)
{
    matrix view;
}
cbuffer ProjectionBuffer : register(b2)
{
    matrix projection;
}

struct Input
{
    float4 pos : POSITION;
    float2 uv : UV;
};

struct Output
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

Output VS(Input input)
{
    Output output;
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.uv = input.uv;
    
    return output;
}

cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

Texture2D baseMap : register(t0);
SamplerState samplerState : register(s0);

cbuffer LightBuffer : register(b1)
{
    float2 imageSize;
    float2 lightPos1; // 플레이어
    float2 lightPos2; // 횃불
    float torchIntensity; // 횃불 밝기(0~1, 선형보간용)
}

cbuffer RangeBuffer : register(b2)
{
    float range1; // 플레이어 빛 범위
    float range2; // 횃불 빛 범위
}

float4 PS(Output output) : SV_TARGET
{
    float4 baseColor = baseMap.Sample(samplerState, output.uv);
    float2 coord = output.uv * imageSize;

    // 플레이어 조명
    float dist1 = length(lightPos1 - coord);
    float temp1 = 1.0f - saturate(dist1 / range1);

    // 횃불 조명 (torchIntensity로 점점 밝아지게)
    float dist2 = length(lightPos2 - coord);
    float temp2 = (1.0f - saturate(dist2 / range2)) * torchIntensity;

    // 둘 중 더 밝은 쪽을 사용
    float temp = max(temp1, temp2);

    // 완전히 어두운 곳은 검정, temp=0~1
    return float4((baseColor.rgb * temp), baseColor.a);
}