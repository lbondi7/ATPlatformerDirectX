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

	void CreateBuffer(const std::string& shapeName);

	ID3D11Buffer*& GetVertexBuffer(const std::string& shapeName);
	ID3D11Buffer*& GetIndexBuffer(const std::string& shapeName);
	const UINT& GetStride(const std::string& shapeName);
	const UINT& GetOffset(const std::string& shapeName);
	unsigned int GetIndeciesSize(const std::string& shapeName);

private:

	void CreateVertexBuffer(const std::string& shapeName);
	void CreateIndexBuffer(const std::string& shapeName);
	int GetBufferNum(const std::string& shapeName);

	std::vector<ID3D11Buffer*> pVertexBuffers;
	std::vector<ID3D11Buffer*> pIndexBuffers;
	std::vector<unsigned int> indicesSize;
	std::vector<UINT> stride;
	std::vector<UINT> offset;

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
			DirectX::XMVECTOR color;
		}color;
	};

};

