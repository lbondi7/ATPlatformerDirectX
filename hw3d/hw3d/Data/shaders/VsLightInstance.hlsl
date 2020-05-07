cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

//struct VertexInputType
//{
//	float4 position : SV_POSITION;
//	float2 tex : TEXCOORD;
//	float3 normal : NORMAL;
//	float4 inpos : INSTANCEPOS;
//};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD;
	float3 normal : NORMAL;
	float4 inpos : INSTANCEPOS;
};


////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType main(PixelInputType input)
{
	PixelInputType output;


	// Change the position vector to be 4 units for proper matrix calculations.
	input.position.w = 1.0f;

	input.position.x += input.inpos.x;
	input.position.y += input.inpos.y;
	input.position.z += input.inpos.z;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projectionMatrix);

	// Store the texture coordinates for the pixel shader.
	output.tex = input.tex;
	//The normal vector for this vertex is calculated in world space and then normalized before being sent as input into the pixel shader.

		// Calculate the normal vector against the world matrix only.
	output.normal = mul(input.normal, (float3x3)worldMatrix);

	// Normalize the normal vector.
	output.normal = normalize(output.normal);

	return output;
}