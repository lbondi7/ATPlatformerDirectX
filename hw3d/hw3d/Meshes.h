#pragma once
#include "Maths.h"
#include "Constants.h"

#include <d3d11.h>
#include <vector> 

struct Mesh
{
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	uint32_t stride;
	uint32_t offset;
	uint32_t vertexCount;
	uint32_t indexCount;
	std::vector<VertexType> vertices;
	std::vector<Vector> vectors;
	std::vector<unsigned short> indices;
};