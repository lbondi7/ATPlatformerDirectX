struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD;
	float3 normal : NORMAL;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float4 color = float4(1.0f, 0.0f, 1.0f, 1.0f);

	return color;
}