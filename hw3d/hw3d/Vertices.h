#pragma once
#include "Maths.h"
#include "Meshes.h"

#include <d3d11.h>
#include <wrl.h>
#include <vector> 
#include <map>
#include <string>
#include <future>

class Vertices
{
public:
	struct VertexType
	{
		struct
		{
			Vector position;
		}pos;

		struct
		{
			float u;
			float v;
		}txt;

		struct
		{
			Vector normal;
		}norm;

		//struct
		//{
		//	DirectX::XMVECTOR color;
		//}color;
	};

	Vertices();
	~Vertices() = default;

	HRESULT CreateBuffer(const std::string& shapeName);

	int GetBufferNum(const std::string& shapeName);

	ID3D11Buffer*& GetVertexBuffer(const std::string& modelName);
	ID3D11Buffer*& GetIndexBuffer(const std::string& modelName);
	const UINT& GetStride(const std::string& modelName);
	const UINT& GetOffset(const std::string& modelName);
	unsigned int GetIndicesSize(const std::string& modelName);
	const std::vector<Vector>& GetVertices(const std::string& modelName);

	//VertexType* GetVertices();

private:

	static HRESULT CreateBuffers(std::vector<Mesh>* meshes, int num, std::string meshName);
	static HRESULT CreateVertexBuffer(std::vector<Mesh>* meshes, int num, const std::string& meshName);
	static HRESULT CreateIndexBuffer(std::vector<Mesh>* meshes, int num);
	HRESULT CreateVertexBuffer(const std::string& modelTag);
	HRESULT CreateIndexBuffer(const std::string& shapeName);
	static void loadOBJ(const std::string& modelTag, std::vector<Vertices::VertexType>& vert, std::vector<Mesh>* meshes, int num);


	std::vector<Mesh> m_Meshes;

	std::vector<ID3D11Buffer*> pVertexBuffers;
	std::vector<ID3D11Buffer*> pIndexBuffers;
	std::vector<uint32_t> m_Strides;
	std::vector<uint32_t> m_Offsets;
	std::vector<int> m_VertexCounts;
	std::vector<std::vector<Vector>> m_Vertices;
	std::vector<std::future<HRESULT>> m_Futures;

	int bufferCount = 0;

	std::map<std::string, int> model;

	//std::vector<std::vector<VertexType>>vert;
	//VertexType* vertices = nullptr;
};