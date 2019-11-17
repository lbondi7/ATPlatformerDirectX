#pragma once
#include "Maths.h"

#include <d3d11.h>
#include <vector> 

struct Mesh
{
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	UINT stride;
	UINT offset;
	int vertexCount;
	std::vector<Vector> vertices;
};