#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <wrl.h>
#include <vector> 
#include <map>
#include <string>

class Buffers
{
public:
	Buffers();
	~Buffers() = default;

	HRESULT CreateBuffer(const std::string& shapeName);

	HRESULT LoadModel(const std::string& filename);

	ID3D11Buffer*& GetVertexBuffer(const std::string& shapeName);
	ID3D11Buffer*& GetIndexBuffer(const std::string& shapeName);
	const UINT& GetStride(const std::string& shapeName);
	const UINT& GetOffset(const std::string& shapeName);
	unsigned int GetIndeciesSize(const std::string& shapeName);

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

	int bufferCount = 0;

	std::map<std::string, int> shapes;

	struct VertexType
	{
		struct
		{
			DirectX::XMVECTOR position;
		}pos;

		struct
		{
			float u;
			float v;
		}txt;

		struct
		{
			DirectX::XMVECTOR normal;
		}norm;

		//struct
		//{
		//	DirectX::XMVECTOR color;
		//}color;
	};
};