Texture2D textures;
SamplerState colorSampler : register(s0);

cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projMatrix;
	float4 valores;
};

struct VS_Input
{
	float4 pos : POSITION;
	float2 tex0 : TEXCOORD0;
};

struct PS_Input
{
	float4 pos : SV_POSITION;
	float2 tex0 : TEXCOORD0;
	
	//niebla
    float fogFactor : FOG;
	//niebla
};

PS_Input VS_Main(VS_Input vertex)
{
	
		//niebla
    float4 vertexPos;
	//niebla
	PS_Input vsOut = (PS_Input)0;
	vsOut.pos = mul(vertex.pos, worldMatrix);
	vsOut.pos = mul(vsOut.pos, viewMatrix);
	vsOut.pos = mul(vsOut.pos, projMatrix);
		//niebla
    vertexPos = vsOut.pos;
	//niebla
	vsOut.tex0 = vertex.tex0;
		//niebla
    float fogStart = -10.0f;
    float fogEnd = 50.0f;
	
    float fogFactor = saturate((fogEnd - vertexPos.z) / (fogEnd - fogStart));
    vsOut.fogFactor = fogFactor;
	//niebla
	return vsOut;
}

float4 PS_Main(PS_Input pix) : SV_TARGET
{
	float4 finalColor = textures.Sample(colorSampler, pix.tex0);
	
		//niebla
    float4 fogColor = float4(0.5f, 0.5f, 0.5f, 1.0f);
	
    finalColor = pix.fogFactor * finalColor + (1.0 - pix.fogFactor) * fogColor;
	//niebla

	return finalColor;
}