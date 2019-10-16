#include "Buffers.h"
#include "Locator.h"
#include "D3D.h"

#include <DirectXMath.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

Buffers::Buffers()
{
	//shapes["cube"] = 0;
}

void Buffers::CreateBuffer(const std::string& shapeName)
{
	shapes[shapeName] = bufferCount;
	pVertexBuffers.resize(shapes.size());
	pIndexBuffers.resize(shapes.size());
	stride.resize(shapes.size());
	offset.resize(shapes.size());
	indicesSize.resize(shapes.size());
	//create Vertex Buffer
	CreateVertexBuffer(shapeName);
	// create Index Buffer
	CreateIndexBuffer(shapeName);

	bufferCount++;
	//// bind index buffer
	//d3d->GetDeviceContext()->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);
}

void Buffers::CreateIndexBuffer(const std::string& shapeName)
{
	//pIndexBuffers.emplace_back();

	nlohmann::json shapeJson;
	std::ifstream shape_file("..//Data//" + shapeName + ".json");
	shape_file >> shapeJson;

	int vertexCount = shapeJson["Vertex Count"];
	unsigned short* indices = new unsigned short[vertexCount];

	for (int i = 0; i < vertexCount; i++)
	{
		indices[i] = i;
	}

	//const unsigned short indices[] =
	//{
	//	0,1,2,	    3,4,5,
	//	6,7,8,	    9,10,11,
	//	12,13,14,	15,16,17,
	//	18,19,20,	21,22,23,
	//	24,25,26,	27,28,29,
	//	30,31,32,	33,34,35,
	//};
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = sizeof(unsigned short) * vertexCount;
	ibd.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;
	indicesSize[shapes[shapeName]] = vertexCount;

	Locator::GetD3D()->GetDevice()->CreateBuffer(&ibd, &isd, &pIndexBuffers[shapes[shapeName]]);
}

int Buffers::GetBufferNum(const std::string& shapeName)
{
	int bufNum = shapes[shapeName];
	return bufNum;
}

void Buffers::CreateVertexBuffer(const std::string& shapeName)
{
	
	nlohmann::json shapeJson;
	std::ifstream shape_file("..//Data//" + shapeName + ".json");
	shape_file >> shapeJson;

	int vertexCount = shapeJson["Vertex Count"];
	VertexType* vertices = new VertexType[vertexCount];

	for (int i = 0; i < vertexCount; ++i) {
		auto vertex = shapeJson["Vertecies"][std::to_string(i)];
		vertices[i] = { vertex[0],vertex[1],vertex[2],vertex[3],vertex[4],vertex[5],vertex[6],vertex[7] };
	}

	//VertexType vertices[] =
	//{
	//	{ -0.5f,-0.5f,-0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{ -0.5f, 0.5f,-0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{  0.5f, 0.5f,-0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{ -0.5f,-0.5f,-0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{  0.5f, 0.5f,-0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{  0.5f,-0.5f,-0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{  0.5f,-0.5f,-0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{  0.5f, 0.5f,-0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{  0.5f, 0.5f, 0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{  0.5f,-0.5f,-0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{  0.5f, 0.5f, 0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{  0.5f,-0.5f, 0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{  0.5f,-0.5f, 0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{  0.5f, 0.5f, 0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{ -0.5f, 0.5f, 0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{  0.5f,-0.5f, 0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{ -0.5f, 0.5f, 0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{ -0.5f,-0.5f, 0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{ -0.5f,-0.5f, 0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{ -0.5f, 0.5f, 0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{ -0.5f, 0.5f,-0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{ -0.5f,-0.5f, 0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{ -0.5f, 0.5f,-0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{ -0.5f,-0.5f,-0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{ -0.5f, 0.5f,-0.5f,1.0f,	1.0f,0.0f,0.0f,1.0f },
	//	{ -0.5f, 0.5f, 0.5f,1.0f,	1.0f,0.0f,0.0f,1.0f },
	//	{  0.5f, 0.5f, 0.5f,1.0f,	1.0f,0.0f,0.0f,1.0f },
	//	{ -0.5f, 0.5f,-0.5f,1.0f,	1.0f,0.0f,0.0f,1.0f },
	//	{  0.5f, 0.5f, 0.5f,1.0f,	1.0f,0.0f,0.0f,1.0f },
	//	{  0.5f, 0.5f,-0.5f,1.0f,	1.0f,0.0f,0.0f,1.0f },
	//	{ -0.5f,-0.5f, 0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{ -0.5f,-0.5f,-0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{  0.5f,-0.5f,-0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{ -0.5f,-0.5f, 0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{  0.5f,-0.5f,-0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//	{  0.5f,-0.5f, 0.5f,1.0f,	1.0f,1.0f,0.0f,1.0f },
	//};

	D3D11_BUFFER_DESC vbd = {};
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.CPUAccessFlags = 0u;
	vbd.MiscFlags = 0u;
	vbd.ByteWidth = sizeof(VertexType)*vertexCount;
	vbd.StructureByteStride = sizeof(VertexType);
	D3D11_SUBRESOURCE_DATA vsd = {};
	vsd.pSysMem = vertices;

	stride[shapes[shapeName]] = sizeof(VertexType);
	offset[shapes[shapeName]] = 0u;

	Locator::GetD3D()->GetDevice()->CreateBuffer(&vbd, &vsd, &pVertexBuffers[shapes[shapeName]]);
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
