#include "Buffer.h"
#include "DXInitialisers.h"
#include "Locator.h"
#include "D3D.h"

HRESULT Buffer::CreateBuffer(D3D11_BIND_FLAG flag, D3D11_USAGE usage, UINT accessFlags, const void* _data, UINT _size, UINT _stride)
{
	HRESULT hr;
	D3D11_BUFFER_DESC descInfo;
	descInfo.BindFlags = flag;
	descInfo.Usage = usage;
	descInfo.CPUAccessFlags = accessFlags;
	descInfo.MiscFlags = 0u;
	descInfo.ByteWidth = _size;
	descInfo.StructureByteStride = _stride;
	m_Data = _data;
	m_Size = _size;
	switch (flag)
	{
	case D3D11_BIND_VERTEX_BUFFER:
	case D3D11_BIND_INDEX_BUFFER:
	{
		D3D11_SUBRESOURCE_DATA subSourceData = {};
		subSourceData.pSysMem = m_Data;

		m_Stride = _stride;
		m_Offset = 0u;

		hr = Locator::GetD3D()->GetDevice()->CreateBuffer(&descInfo, &subSourceData, m_Buffer.GetAddressOf());
		return hr;
		break;
	}
	case D3D11_BIND_CONSTANT_BUFFER:
	{
		hr = Locator::GetD3D()->GetDevice()->CreateBuffer(&descInfo, 0, m_Buffer.GetAddressOf());
		return hr;
		break;
	}
	}
}

HRESULT Buffer::MapToGPU(const void* _data, size_t _size)
{

	if (FAILED(m_HR = Locator::GetD3D()->GetDeviceContext()->Map(m_Buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &m_MappedData)))
		return m_HR;

	memcpy(m_MappedData.pData, _data, _size);

	Locator::GetD3D()->GetDeviceContext()->Unmap(m_Buffer.Get(), 0);
}
