#include "Vertices.h"
#include "Locator.h"
#include "D3D.h"

#include <DirectXMath.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "nlohmann/json.hpp"

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

static std::mutex meshMutex;

#define ASYNC false;

Vertices::Vertices()
{
	//shapes["cube"] = 0;
}

HRESULT Vertices::CreateBuffer(const std::string& shapeName)
{
	HRESULT hr = S_OK;
	model[shapeName] = bufferCount;
	bufferCount++;

#if ASYNC 
	meshMutex.lock();
	m_Meshes.resize(model.size());
	meshMutex.unlock();

	//CreateBuffers(&m_Meshes, mod, name);
	const auto& mod = model[shapeName];
	m_Futures.push_back(std::async(std::launch::async , CreateBuffers, &m_Meshes, mod, shapeName));

#else
	m_Meshes.resize(model.size());
	if (FAILED(hr = CreateVertexBuffer(shapeName)))
	{
		return hr;
	}

	// create Index Buffer
	if (FAILED(hr = CreateIndexBuffer(shapeName)))
	{
		return hr;
	}
#endif
	//pVertexBuffers.resize(model.size());
	//pIndexBuffers.resize(model.size());
	//m_Strides.resize(model.size());
	//m_Offsets.resize(model.size());
	//m_VertexCounts.resize(model.size());
	//m_Vertices.resize(model.size());
	////create Vertex Buffer
	//if (FAILED(hr = CreateVertexBuffer(shapeName)))
	//{
	//	return hr;
	//}
	//
	//// create Index Buffer
	//if (FAILED(hr = CreateIndexBuffer(shapeName)))
	//{
	//	return hr;
	//}
	return hr;
}

HRESULT Vertices::CreateBuffers(std::vector<Mesh>* meshes, int num, std::string meshName)
{
	HRESULT hr;

	// create Vertex Buffer
	if (FAILED(hr = CreateVertexBuffer(meshes, num, meshName)))
	{
		return hr;
	}

	// create Index Buffer
	if (FAILED(hr = CreateIndexBuffer(meshes, num)))
	{
		return hr;
	}

	return hr;
}

HRESULT Vertices::CreateVertexBuffer(std::vector<Mesh>* meshes, int num, const std::string& modelTag)
{	
		std::vector<VertexType> vert;

		loadOBJ(modelTag, vert, meshes, num);

		D3D11_BUFFER_DESC vbd = {};
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.Usage = D3D11_USAGE_DEFAULT;
		vbd.CPUAccessFlags = 0u;
		vbd.MiscFlags = 0u;
		vbd.ByteWidth = sizeof(VertexType) * vert.size();
		//vbd.ByteWidth = sizeof(VertexType) * m_VertexCounts[num];
		vbd.StructureByteStride = sizeof(VertexType);
		D3D11_SUBRESOURCE_DATA vsd = {};
		vsd.pSysMem = vert.data();
	
		std::lock_guard<std::mutex> lock(meshMutex);
		(*meshes)[num].stride = sizeof(VertexType);
		(*meshes)[num].offset = 0u;
		//(*meshes)[num].vertexCount = vert.size();
	
		return Locator::GetD3D()->GetDevice()->CreateBuffer(&vbd, &vsd, &(*meshes)[num].vertexBuffer);
}

//void Vertices::loadOBJ(const std::string& modelTag, std::vector<Vertices::VertexType>& vert, std::vector<Mesh>* meshes, int num)
//{
//	struct Faces
//	{
//		int vIndex;
//		int tIndex;
//		int nIndex;
//	};
//
//	std::vector<Vector> verticess;
//	size_t maxi = verticess.max_size();
//	size_t maxu = verticess.capacity();
//	std::vector<DirectX::XMFLOAT2> textureCoords;
//	std::vector<Vector> normals;
//	std::vector<std::vector<Faces>> facesVector;
//	std::vector<Faces> faces;
//	int vertPerFace = 3;
//	faces.reserve(vertPerFace);
//	bool skip = false;
//	std::fstream file;
//	file.open("..//Data//models//" + modelTag + ".obj");
//	bool hasUV = false;
//	bool hasNorm = false;
//	char* line;
//	std::string l;
//	if (file.is_open())
//	{
//		//std::stringstream ss;
//		char lineChar;
//		//ss << file.rdbuf();
//		float x, y, z;
//		while (!file.eof())
//		{
//			file.get(lineChar);
//			if (lineChar == 'v')
//			{
//				file.get(lineChar);
//				if (lineChar == ' ')
//				{
//					Vector newVec;
//					file >> newVec.m128_i32[0] >> newVec.m128_i32[1] >> newVec.m128_i32[2];
//					verticess.push_back(newVec);
//				}
//				else if (lineChar == 't')
//				{
//					hasUV = true;
//					Vector newVec;
//					file >> newVec.m128_i32[0] >> newVec.m128_i32[1];
//					verticess.push_back(newVec);
//				}
//				else if (lineChar == 'n')
//				{
//					hasNorm = true;
//					Vector newVec;
//					file >> newVec.m128_i32[0] >> newVec.m128_i32[1] >> newVec.m128_i32[2];
//					verticess.emplace_back(newVec);
//				}				
//			}
//			else if (lineChar == 'f')
//			{
//				Faces face;
//				file >> face.vIndex;
//				if (hasUV)
//				{
//					file.get(lineChar);
//					file >> face.tIndex;
//				}
//				if (hasNorm)
//				{
//					file.get(lineChar);
//					file >> face.nIndex;
//				}
//				faces.emplace_back(face);
//			}
//		}
//		file.close();
//	}
//
//#if ASYNC
//	meshMutex.lock();
//	(*meshes)[num].indexCount = facesVector.size() * vertPerFace;
//	(*meshes)[num].vertexCount = verticess.size();
//	meshMutex.unlock();
//#else
//	(*meshes)[num].indexCount = facesVector.size() * vertPerFace;
//#endif
//
//	size_t l = 0;
//	float vIn;
//	float vtIn;
//	float vnIn;
//	DirectX::XMFLOAT2 t;
//	Vector n;
//
//	for (size_t i = 0; i < facesVector.size(); i++)
//	{
//		for (size_t j = 0; j < facesVector[i].size(); j++)
//		{
//			vIn = facesVector[i][j].vIndex - 1;
//			vtIn = facesVector[i][j].tIndex - 1;
//			vnIn = facesVector[i][j].nIndex - 1;
//
//			vtIn >= 0 ? t = textureCoords[vtIn] : t = { 0.0f, 0.0f };
//			vnIn >= 0 ? n = normals[vnIn] : n = { 0.0f, 0.0f, 0.0f };
//
//			vert.push_back({ DirectX::XMVectorGetX(verticess[vIn]), DirectX::XMVectorGetY(verticess[vIn]), DirectX::XMVectorGetZ(verticess[vIn]), 0.0f,
//				t.x, t.y,
//				DirectX::XMVectorGetX(n), DirectX::XMVectorGetY(n), DirectX::XMVectorGetZ(n), 0.0f });
//
//
//			//vert.push_back({DirectX::XMVectorGetX(vertices[model[modelTag]][vIn]), DirectX::XMVectorGetY(vertices[model[modelTag]][vIn]), DirectX::XMVectorGetZ(vertices[model[modelTag]][vIn]), 0.0f,
//			//texs[vtIn].x, texs[vtIn].y,
//			// DirectX::XMVectorGetX(norm[vnIn]), DirectX::XMVectorGetY(norm[vnIn]), DirectX::XMVectorGetZ(norm[vnIn]), 0.0f });
//
//			++l;
//		}
//	}
//
//#if ASYNC
//	std::lock_guard<std::mutex> lock(meshMutex);
//#endif
//	(*meshes)[num].vertices = verticess;
//}

void Vertices::loadOBJ(const std::string& modelTag, std::vector<VertexType>& vert, std::vector<Mesh>* meshes, int num)
{
	struct Faces
	{
		int vIndex;
		int tIndex;
		int nIndex;
	};

	std::vector<Vector> verticess;
	size_t maxi = verticess.max_size();
	size_t maxu = verticess.capacity();
	std::vector<DirectX::XMFLOAT2> textureCoords;
	std::vector<Vector> normals;
	std::vector<std::vector<Faces>> faces;
	std::vector<Faces> face;
	int vertPerFace = 3;
	face.reserve(vertPerFace);
	bool skip = false;
	std::fstream file;
	file.open("Data//models//" + modelTag + ".obj");
	bool isUV = false;
	bool isNorm = false;
	if (file.is_open())
	{
		//std::stringstream ss;
		char lineChar;
		//ss << file.rdbuf();
		float x, y, z;
		while (!file.eof())
		{
			file.get(lineChar);

			skip = false;
			if (lineChar == 'v')
			{
				file.get(lineChar);
				switch (lineChar)
				{
				case ' ':
				{
					file >> x >> y >> z;
					verticess.push_back({ x, y, z });
					break;
				}
				case 't':
				{
					isUV = true;
					file.get(lineChar);
					if (lineChar != ' ')
						break;

					file >> x >> y;
					textureCoords.push_back({ 1 - x, 1 - y });
					break;
				}
				case 'n':
				{
					isNorm = true;
					file.get(lineChar);
					if (lineChar != ' ')
						break;

					file >> x >> y >> z;
					normals.push_back({ x, y, z });
					break;
				}
				}
			}
			else if (lineChar == 'f')
			{
				file.get(lineChar);
				if (lineChar == ' ')
				{
					for (size_t i = 0; i < vertPerFace; i++)
					{
						file >> x;
						file.get(lineChar);
						if (isUV)
							file >> y;
						else
							y = -1;
						file.get(lineChar);
						if (isNorm)
							file >> z;
						else
							z = -1;
						face.push_back({ (int)x, (int)y, (int)z });
					}
					faces.push_back(face);
					face.clear();
					face.reserve(vertPerFace);
				}
			}
		}
		file.close();
	}

#if ASYNC
	meshMutex.lock();
	(*meshes)[num].indexCount = faces.size() * vertPerFace;
	(*meshes)[num].vertexCount = verticess.size();
	meshMutex.unlock();
#else
	(*meshes)[num].indexCount = faces.size() * vertPerFace;
#endif

	size_t l = 0;
	float vIn;
	float vtIn;
	float vnIn;
	DirectX::XMFLOAT2 t;
	Vector n;

	for (size_t i = 0; i < faces.size(); i++)
	{
		for (size_t j = 0; j < faces[i].size(); j++)
		{
			vIn = faces[i][j].vIndex - 1;
			vtIn = faces[i][j].tIndex - 1;
			vnIn = faces[i][j].nIndex - 1;

			vtIn >= 0 ? t = textureCoords[vtIn] : t = { 0.0f, 0.0f };
			vnIn >= 0 ? n = normals[vnIn] : n = { 0.0f, 0.0f, 0.0f };

			vert.push_back({ DirectX::XMVectorGetX(verticess[vIn]), DirectX::XMVectorGetY(verticess[vIn]), DirectX::XMVectorGetZ(verticess[vIn]), 0.0f,
				t.x, t.y,
				DirectX::XMVectorGetX(n), DirectX::XMVectorGetY(n), DirectX::XMVectorGetZ(n), 0.0f });


			//vert.push_back({DirectX::XMVectorGetX(vertices[model[modelTag]][vIn]), DirectX::XMVectorGetY(vertices[model[modelTag]][vIn]), DirectX::XMVectorGetZ(vertices[model[modelTag]][vIn]), 0.0f,
			//texs[vtIn].x, texs[vtIn].y,
			// DirectX::XMVectorGetX(norm[vnIn]), DirectX::XMVectorGetY(norm[vnIn]), DirectX::XMVectorGetZ(norm[vnIn]), 0.0f });

			++l;
		}
	}

#if ASYNC
	std::lock_guard<std::mutex> lock(meshMutex);
#endif
	(*meshes)[num].vectors = verticess;
}

HRESULT Vertices::CreateIndexBuffer(std::vector<Mesh>* meshes, int num)
{
	meshMutex.lock();
	auto size = (*meshes)[num].indexCount;
	meshMutex.unlock();

	unsigned short* indices = new unsigned short[size];

	for (int i = 0; i < size; i++)
	{
		indices[i] = i;
	}

	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = sizeof(unsigned short) * size;
	ibd.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;

	std::lock_guard<std::mutex> lock(meshMutex);
	return Locator::GetD3D()->GetDevice()->CreateBuffer(&ibd, &isd, &(*meshes)[num].indexBuffer);
}

HRESULT Vertices::CreateVertexBuffer(const std::string& modelTag)
{
	std::vector<VertexType> vert;
	const auto& num = model[modelTag];
	loadOBJ(modelTag, m_Meshes[num].vertices, &m_Meshes, num);
	//m_Meshes[num].vertices = vert

	D3D11_BUFFER_DESC vbd = {};
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.CPUAccessFlags = 0u;
	vbd.MiscFlags = 0u;
	vbd.ByteWidth = sizeof(VertexType) * m_Meshes[num].vertices.size();
	vbd.StructureByteStride = sizeof(VertexType);
	D3D11_SUBRESOURCE_DATA vsd = {};
	vsd.pSysMem = m_Meshes[num].vertices.data();

	m_Meshes[num].stride = sizeof(VertexType);
	m_Meshes[num].offset = 0u;
	m_Meshes[num].vertexCount = m_Meshes[num].vertices.size();

	return Locator::GetD3D()->GetDevice()->CreateBuffer(&vbd, &vsd, &m_Meshes[num].vertexBuffer);
}

HRESULT Vertices::CreateIndexBuffer(const std::string& shapeName)
{
	unsigned short* indices = new unsigned short[m_Meshes[model[shapeName]].vertexCount];

	m_Meshes[model[shapeName]].indices.resize(m_Meshes[model[shapeName]].vertexCount);

	for (int i = 0; i < m_Meshes[model[shapeName]].vertexCount; i++)
	{
		m_Meshes[model[shapeName]].indices[i] = i;
		indices[i] = i;
	}

	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = sizeof(unsigned short) * m_Meshes[model[shapeName]].vertexCount;
	ibd.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;


	return Locator::GetD3D()->GetDevice()->CreateBuffer(&ibd, &isd, &m_Meshes[model[shapeName]].indexBuffer);
}

int Vertices::GetBufferNum(const std::string& shapeName)
{
	int bufNum = model[shapeName];
	return bufNum;
}


ID3D11Buffer*& Vertices::GetVertexBuffer(const std::string& shapeName)
{
	return m_Meshes[model[shapeName]].vertexBuffer;
}

ID3D11Buffer*& Vertices::GetIndexBuffer(const std::string& shapeName)
{
	return m_Meshes[model[shapeName]].indexBuffer;
}

const UINT& Vertices::GetStride(const std::string& shapeName)
{
	return m_Meshes[model[shapeName]].stride;
}

const UINT& Vertices::GetOffset(const std::string& shapeName)
{
	return m_Meshes[model[shapeName]].offset;
}

unsigned int Vertices::GetIndicesSize(const std::string& shapeName)
{
	return m_Meshes[model[shapeName]].indexCount;
}

const std::vector<VertexType>& Vertices::GetVertices(const std::string& modelName)
{
	return m_Meshes[model[modelName]].vertices;
}

const std::vector<unsigned short>& Vertices::GetIndices(const std::string& modelName)
{
	return m_Meshes[model[modelName]].indices;
}

//ID3D11Buffer*& Vertices::GetVertexBuffer(const std::string& shapeName)
//{
//	return pVertexBuffers[model[shapeName]];
//}
//
//ID3D11Buffer*& Vertices::GetIndexBuffer(const std::string& shapeName)
//{
//	return pIndexBuffers[model[shapeName]];
//}
//
//const UINT& Vertices::GetStride(const std::string& shapeName)
//{
//	return m_Strides[GetBufferNum(shapeName)];
//}
//
//const UINT& Vertices::GetOffset(const std::string& shapeName)
//{
//	return m_Offsets[model[shapeName]];
//}
//
//unsigned int Vertices::GetIndicesSize(const std::string& shapeName)
//{
//	return m_VertexCounts[model[shapeName]];
//}
//
//const std::vector<Vector>& Vertices::GetVertices(const std::string& modelName)
//{
//	return m_Vertices[model[modelName]];
//}
