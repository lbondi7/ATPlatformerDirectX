cbuffer CBuf
{
	matrix transform;
};

struct PixelInputType
{
	float4 color : COLOR;
	float4 position : SV_POSITION;
};

PixelInputType main(PixelInputType input)
{
	PixelInputType output;

	// Change the position vector to be 4 units for proper matrix calculations.
	//input.position.w = 1.0f;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	//output.position = mul(input.position, worldMatrix);
	//output.position = mul(output.position, viewMatrix);
	//output.position = mul(output.position, projectionMatrix);
	output.position = mul(input.position, transform);

	// Store the input color for the pixel shader to use.
	output.color = input.color;

	return output;
	//return mul(float4(pos, 1.0f), transform);
}