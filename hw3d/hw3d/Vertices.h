#pragma once
#include "Maths.h"

#include <d3d11.h>
#include <wrl.h>
#include <vector> 
#include <map>
#include <string>

class Vertices
{
public:
	struct VertexType
	{
		struct
		{
			Vector4 position;
		}pos;

		struct
		{
			float u;
			float v;
		}txt;

		struct
		{
			Vector4 normal;
		}norm;

		//struct
		//{
		//	DirectX::XMVECTOR color;
		//}color;
	};

	Vertices();
	~Vertices() = default;

	HRESULT CreateBuffer(const std::string& shapeName);

	ID3D11Buffer*& GetVertexBuffer(const std::string& modelName);
	ID3D11Buffer*& GetIndexBuffer(const std::string& modelName);
	const UINT& GetStride(const std::string& modelName);
	const UINT& GetOffset(const std::string& modelName);
	unsigned int GetIndicesSize(const std::string& modelName);
	const std::vector<Vector4>& GetVertices(const std::string& modelName);

	//VertexType* GetVertices();

private:

	HRESULT CreateVertexBuffer(const std::string& shapeName);
	HRESULT CreateIndexBuffer(const std::string& shapeName);
	int GetBufferNum(const std::string& shapeName);

	std::vector<ID3D11Buffer*> pVertexBuffers;
	std::vector<ID3D11Buffer*> pIndexBuffers;
	std::vector<unsigned int> indicesSize;
	std::vector<UINT> stride;
	std::vector<UINT> offset;
	std::vector<int> vertexCount;
	std::vector<std::vector<Vector4>> vertices;

	int bufferCount = 0;

	std::map<std::string, int> model;

	//std::vector<std::vector<VertexType>>vert;
	//VertexType* vertices = nullptr;
};