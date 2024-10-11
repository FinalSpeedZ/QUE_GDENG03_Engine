struct PS_INPUT
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
    float4 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
    row_major float4x4 m_world;
    row_major float4x4 m_view;
    row_major float4x4 m_proj;
    float m_time;
};

float4 psmain(PS_INPUT input) : SV_TARGET
{
    float time = (sin(m_time) + 1.0f) / 2.0f;

    float remappedTime = lerp(0.2f, 0.8f, time);

    return lerp(input.color, input.color1, remappedTime);
}