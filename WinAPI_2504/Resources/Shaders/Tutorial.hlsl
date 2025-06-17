//Shader : GPU�� �ٷ�� ���α׷��� ���
//�ø�ƽ(Sementic) : ��ȯ�ڷ����̳� �Ű������� ���뵵�� ǥ���ϴ� ����
//SV : System Value

//Constant Buffer(�������) : CPU���� �����ϴ� ��
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
    float4 color : COLOR;
};

struct Output
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

Output VS( Input input )
{
    Output output;
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.color = input.color;
    
	return output;
}

cbuffer ColorBuffer : register(b0)
{
    float4 color;
}

float4 PS( Output output ) : SV_TARGET
{
    return output.color * color;
}