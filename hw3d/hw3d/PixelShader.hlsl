cbuffer cBuf
{
	float4 face_colours[6];
};

float4 main(uint tid : SV_PrimitiveID) : SV_TARGET
{
	return face_colours[tid / 2];
	//return float4(colour.r, colour.g, colour.b, colour.a);
}