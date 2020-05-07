Texture2D shaderTexture;
SamplerState SampleType;

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD;
	float3 normal : NORMAL;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float4 textureColor;
	float4 color;


	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = shaderTexture.Sample(SampleType, input.tex);

	// Multiply the texture pixel and the final diffuse color to get the final pixel color result.
	color = textureColor;

	return color;
}