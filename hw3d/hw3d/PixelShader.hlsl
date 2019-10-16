cbuffer cBuf
{
	float4 face_colours[6];
};

struct PixelInputType
{
	float4 color : COLOR;
	float4 position : SV_POSITION;
};

float4 main(PixelInputType input) : SV_TARGET
{
	return input.color;
	//return float4(colour.r, colour.g, colour.b, colour.a);
}
