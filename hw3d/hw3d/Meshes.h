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
	std::vector<Vec4> vectors;
	std::vector<unsigned short> indices;
};

struct Meshes
{
	uint32_t vertexCount;
	uint32_t indexCount;
	std::vector<Float3> vectors;
	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;
};