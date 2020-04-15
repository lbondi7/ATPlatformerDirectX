#pragma once

#include <d3d11.h>
#include <memory>
#include <wrl.h>

struct Buffer
{
	void CreateVertexIndex(D3D11_BIND_FLAG flag, D3D11_USAGE usage, const void* data, UINT byteWidth, UINT _stride);
	HRESULT CreateBuffer(D3D11_BIND_FLAG flag, D3D11_USAGE usage, UINT accessFlags, const void* _data, UINT _size, UINT _stride);
	void CreateConstant(D3D11_BIND_FLAG flag, D3D11_USAGE usage, const void* _data, UINT accessFlags, UINT byteWidth, UINT _stride);
	void CopyData(const void* _data);
	HRESULT MapToGPU(const void* _data, size_t _size);

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_Buffer;
	uint32_t m_Stride;
	uint32_t m_Offset;
	const void* m_Data = nullptr;
	D3D11_MAPPED_SUBRESOURCE m_MappedData;
	size_t m_Size;
	HRESULT m_HR;
};

