
cbuffer GLOBAL_MATRIX1 : register(b0)
{
    float4 vOffset;
};

cbuffer GLOBAL_MATRIX2 : register(b1)
{
    float4 vOffset1;
};

cbuffer GLOBAL_MATRIX3 : register(b2)
{
    float4 vOffset2;
};

cbuffer GLOBAL_MATRIX4 : register(b3)
{
    float4 vOffset3;
};

cbuffer GLOBAL_DATA : register(b5)
{
    float fDT;
    float fAccTime;
    float fWidth;
    float fHeight;
};

Texture2D g_tex_0 : register(t0);
Texture2D g_tex_1 : register(t1);

SamplerState g_sam_0 : register(s0);    // anisotrophic
SamplerState g_sam_1 : register(s1);    // point

struct VS_INPUT
{
    float3 vPos : POSITION; // sementic (������) ���� Layout �� ����       
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 vOutPos : SV_Position;
    float4 vOutColor : COLOR;
    float2 vUV : TEXCOORD;
};

// ==================
// Test Vertex Shader
// ==================
VS_OUTPUT VS_Test(VS_INPUT _input)
{
    VS_OUTPUT output = (VS_OUTPUT)0;

    output.vOutPos = float4(_input.vPos, 1.f);
    output.vOutPos.x += vOffset.x;

    output.vOutColor = _input.vColor;
    
    output.vUV = _input.vUV;

    return output;
}

// Rasterizer 
// �������̴����� ��ȯ�� ������ǥ�� ���ؼ�
// Target ���ۿ��� ȣ�� �Ǿ�� �ϴ� Pixel �� ã�Ƴ���.

// Cull Mode �ɼǿ� ����, ���� �� Toplogy �� �����Ѵ�.
// CULL_BACK(ccw)

// Pixel Shader
// Rasterizer ���� ������ �ȼ��鸶�� ȣ�� �Ǵ� �Լ�
// �������� ��ȯ�� ������ Ÿ�ٿ� ����Ѵ�.
float4 PS_Test(VS_OUTPUT _input) : SV_Target
{
    float fRatio = _input.vOutPos.x / 1280.f;

    float4 vOutColor = g_tex_0.Sample(g_sam_0, _input.vUV);

    return vOutColor;
}