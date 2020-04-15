#pragma once

#include "Buffer.h"
#include "Texture.h"

struct RenderData
{
	Buffer VertexBuffer;
	Buffer IndexBuffer;
	Buffer ConstantBuffer;

	UINT indexCount = 0;
	UINT vertexCount = 0;

	D3D_PRIMITIVE_TOPOLOGY topolgy;

	Texture texture;
};