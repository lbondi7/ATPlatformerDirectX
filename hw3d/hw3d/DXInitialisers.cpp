#include "DXInitialisers.h"

D3D11_BUFFER_DESC DXInitialisers::VertexBufferDescInfo()
{
	D3D11_BUFFER_DESC descInfo;
	descInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	descInfo.Usage = D3D11_USAGE_DEFAULT;
	descInfo.CPUAccessFlags = 0u;
	descInfo.MiscFlags = 0u;
	return descInfo;
}

D3D11_BUFFER_DESC DXInitialisers::IndexBufferDescrInfo()
{
	D3D11_BUFFER_DESC descInfo;
	descInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	descInfo.Usage = D3D11_USAGE_DEFAULT;
	descInfo.CPUAccessFlags = 0u;
	descInfo.MiscFlags = 0u;
	return descInfo;
}

D3D11_BUFFER_DESC DXInitialisers::ConstantBufferDescrInfo()
{
	D3D11_BUFFER_DESC descInfo;
	descInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	descInfo.Usage = D3D11_USAGE_DYNAMIC;
	descInfo.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	descInfo.MiscFlags = 0u;
	return descInfo;
}
