#include "Matrices.h"
#include "Locator.h" 
#include "D3D.h"

namespace dx = DirectX;
Matrices::~Matrices()
{
}

HRESULT Matrices::CreateBuffer()
{
	D3D11_BUFFER_DESC cbd = {};
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(MatrixBufferType);
	cbd.StructureByteStride = 0u;
	return Locator::GetD3D()->GetDevice()->CreateBuffer(&cbd, 0, &m_matrixBuffer);
}

HRESULT Matrices::MapResource(dx::XMMATRIX wMtrx, dx::XMMATRIX vMtrx, dx::XMMATRIX pMtrx)
{
	// Lock the constant buffer so it can be written to.
	if (FAILED(hr = Locator::GetD3D()->GetDeviceContext()->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)))
	{
		return hr;
	}

	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = wMtrx;
	dataPtr->view = vMtrx;
	dataPtr->projection = pMtrx;

	// Unlock the constant buffer.
	Locator::GetD3D()->GetDeviceContext()->Unmap(m_matrixBuffer, 0);

	return hr;
}

ID3D11Buffer*& Matrices::GetBuffer()
{
	return m_matrixBuffer;
}
