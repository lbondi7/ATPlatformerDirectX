#pragma once
#include "Meshes.h"
#include "Constants.h"

#include <d3d11.h>
#include <wrl.h>
#include <vector> 
#include <map>
#include <string>
#include <future>

class Vertices
{
public:


	Vertices();
	~Vertices() = default;

	bool LoadVertices(const std::string& shapeName);

	HRESULT CreateBuffer(const std::string& shapeName);

	int GetBufferNum(const std::string& shapeName);

	ID3D11Buffer*& GetVertexBuffer(const std::string& modelName);
	ID3D11Buffer*& GetIndexBuffer(const std::string& modelName);
	const UINT& GetStride(const std::string& modelName);
	const UINT& GetOffset(const std::string& modelName);
	unsigned int GetIndicesSize(const std::string& modelName);
	const std::vector<VertexType>& GetVertices(const std::string& modelName);

	const std::vector<unsigned short>& GetIndices(const std::string& modelName);

	//VertexType* GetVertices();

private:

	static HRESULT CreateBuffers(std::vector<Mesh>* meshes, int num, std::string meshName);
	static HRESULT CreateVertexBuffer(std::vector<Mesh>* meshes, int num, const std::string& meshName);
	static HRESULT CreateIndexBuffer(std::vector<Mesh>* meshes, int num);
	HRESULT CreateVertexBuffer(const std::string& modelTag);
	HRESULT CreateIndexBuffer(const std::string& shapeName);
	static void loadOBJ(const std::string& modelTag, std::vector<VertexType>& vert, std::vector<Mesh>* meshes, int num);


	std::vector<Mesh> m_Meshes;

	std::vector<ID3D11Buffer*> pVertexBuffers;
	std::vector<ID3D11Buffer*> pIndexBuffers;
	std::vector<uint32_t> m_Strides;
	std::vector<uint32_t> m_Offsets;
	std::vector<int> m_VertexCounts;
	std::vector<std::vector<Vec4>> m_Vertices;
	std::vector<std::future<HRESULT>> m_Futures;

	int bufferCount = 0;

	std::map<std::string, int> model;

	//std::vector<std::vector<VertexType>>vert;
	//VertexType* vertices = nullptr;
};