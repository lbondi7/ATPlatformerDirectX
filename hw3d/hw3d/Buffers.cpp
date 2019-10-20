#include "Buffers.h"
#include "Locator.h"
#include "D3D.h"

#include <DirectXMath.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>

#include "nlohmann/json.hpp"

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

Buffers::Buffers()
{
	//shapes["cube"] = 0;
}

HRESULT Buffers::CreateBuffer(const std::string& shapeName)
{
	HRESULT hr;
	shapes[shapeName] = bufferCount;
	pVertexBuffers.resize(shapes.size());
	pIndexBuffers.resize(shapes.size());
	stride.resize(shapes.size());
	offset.resize(shapes.size());
	indicesSize.resize(shapes.size());
	vertexCount.resize(shapes.size());
	//create Vertex Buffer
	if (FAILED(hr = CreateVertexBuffer(shapeName)))
	{
		return hr;
	}
	// create Index Buffer
	if (FAILED(hr = CreateIndexBuffer(shapeName)))
	{
		return hr;
	}

	bufferCount++;
	//// bind index buffer
	//d3d->GetDeviceContext()->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
	return hr;
}

HRESULT Buffers::CreateVertexBuffer(const std::string& shapeName)
{
	vertexCount[shapes[shapeName]] = 0;

	//nlohmann::json shapeJson;
	//std::ifstream shape_file("..//Data//" + shapeName + ".json");
	//shape_file >> shapeJson;

	//vertexCount[shapes[shapeName]] = shapeJson["Vertex Count"];
	//VertexType* vertices = new VertexType[vertexCount[shapes[shapeName]]];
	//for (int i = 0; i < vertexCount[shapes[shapeName]]; ++i) {
	//auto vertex = shapeJson["Vertecies"]["Position"][std::to_string(i)];
	////auto colour = shapeJson["Vertecies"]["Colour"][std::to_string(i)];
	//auto tex = shapeJson["Vertecies"]["Texture"][std::to_string(i)];
	//auto norm = shapeJson["Vertecies"]["Normal"][std::to_string(i)];
	//vertices[i] = { vertex[0],vertex[1],vertex[2],0.0f,tex[0],tex[1],norm[0],norm[1],norm[2],0.0f };
	//}

	struct Faces
	{
		int vIndex;
		int tIndex;
		int nIndex;
	};

	std::vector<DirectX::XMVECTOR> vert;
	std::vector<DirectX::XMVECTOR> texs;
	std::vector<DirectX::XMVECTOR> norm;
	std::vector<std::vector<Faces>> faces;
	std::vector<Faces> face;
	int vertPerFace = 3;
	face.reserve(vertPerFace);
	bool skip = false;
	std::fstream file;
	file.open("..//Data//" + shapeName + ".obj");
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
					vert.push_back({ x, y, z });
					break;
				}
				case 't':
				{
					file.get(lineChar);
					if (lineChar != ' ')
						break;

					file >> x >> y;
					texs.push_back({ x, y });
					break;
				}
				case 'n':
				{
					file.get(lineChar);
					if (lineChar != ' ')
						break;

					file >> x >> y >> z;
					norm.push_back({ x, y, z });
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
						file >> y;
						file.get(lineChar);
						file >> z;
						face.push_back({ (int)x, (int)y, (int)z });
					}
					faces.push_back(face);
					face.clear();
					face.reserve(3);
				}
			}
		}
		file.close();
	}

	vertexCount[shapes[shapeName]] = faces.size() * vertPerFace;
	VertexType* vertices = new VertexType[vertexCount[shapes[shapeName]]];
	size_t l = 0;
	float vIn;
	float vtIn;
	float vnIn;
	for (size_t i = 0; i < faces.size(); i++)
	{
		for (size_t j = 0; j < faces[i].size(); j++)
		{
			vIn = faces[i][j].vIndex - 1;
			vtIn = faces[i][j].tIndex - 1;
			vnIn = faces[i][j].nIndex - 1;
			vertices[l] = {DirectX::XMVectorGetX(vert[vIn]), DirectX::XMVectorGetY(vert[vIn]), DirectX::XMVectorGetZ(vert[vIn]),
			DirectX::XMVectorGetX(texs[vtIn]), DirectX::XMVectorGetY(texs[vtIn]), 
			DirectX::XMVectorGetX(norm[vnIn]), DirectX::XMVectorGetY(norm[vnIn]), DirectX::XMVectorGetZ(norm[vnIn])};
			++l;
		}
	}

	D3D11_BUFFER_DESC vbd = {};
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.CPUAccessFlags = 0u;
	vbd.MiscFlags = 0u;
	vbd.ByteWidth = sizeof(VertexType) * vertexCount[shapes[shapeName]];
	vbd.StructureByteStride = sizeof(VertexType);
	D3D11_SUBRESOURCE_DATA vsd = {};
	vsd.pSysMem = vertices;

	stride[shapes[shapeName]] = sizeof(VertexType);
	offset[shapes[shapeName]] = 0u;

	return Locator::GetD3D()->GetDevice()->CreateBuffer(&vbd, &vsd, &pVertexBuffers[shapes[shapeName]]);
}

HRESULT Buffers::CreateIndexBuffer(const std::string& shapeName)
{
	unsigned short* indices = new unsigned short[vertexCount[shapes[shapeName]]];

	for (int i = 0; i < vertexCount[shapes[shapeName]]; i++)
	{
		indices[i] = i;
	}

	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = sizeof(unsigned short) * vertexCount[shapes[shapeName]];
	ibd.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;
	indicesSize[shapes[shapeName]] = vertexCount[shapes[shapeName]];

	return Locator::GetD3D()->GetDevice()->CreateBuffer(&ibd, &isd, &pIndexBuffers[shapes[shapeName]]);
}

int Buffers::GetBufferNum(const std::string& shapeName)
{
	int bufNum = shapes[shapeName];
	return bufNum;
}

ID3D11Buffer*& Buffers::GetVertexBuffer(const std::string& shapeName)
{
	return pVertexBuffers[GetBufferNum(shapeName)];
}

ID3D11Buffer*& Buffers::GetIndexBuffer(const std::string& shapeName)
{
	return pIndexBuffers[GetBufferNum(shapeName)];
}

const UINT& Buffers::GetStride(const std::string& shapeName)
{
	return stride[GetBufferNum(shapeName)];
}

const UINT& Buffers::GetOffset(const std::string& shapeName)
{
	return offset[GetBufferNum(shapeName)];
}

unsigned int Buffers::GetIndeciesSize(const std::string& shapeName)
{
	return indicesSize[GetBufferNum(shapeName)];
}
