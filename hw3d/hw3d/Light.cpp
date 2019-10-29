#include "Light.h"
#include "Locator.h"
#include "D3D.h"

Light::~Light()
{
}

HRESULT Light::CreateBuffer()
{
	D3D11_BUFFER_DESC lightBufferDesc = {};
	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBufferType);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	return Locator::GetD3D()->GetDevice()->CreateBuffer(&lightBufferDesc, NULL, &pLightBuffer);
	
}

HRESULT Light::MapResource()
{

	if (FAILED(hr = Locator::GetD3D()->GetDeviceContext()->Map(pLightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mMappedResource)))
	{
		return hr;
	}

	// Get a pointer to the data in the constant buffer.
	pLightData = (LightBufferType*)mMappedResource.pData;

	// Copy the lighting variables into the constant buffer.
	pLightData->diffuseColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	pLightData->lightDirection = { 1.0f, 0.0, 1.0, 1.0f };
	pLightData->padding = 0.0f;

	// Unlock the constant buffer.
	Locator::GetD3D()->GetDeviceContext()->Unmap(pLightBuffer, 0);

	return hr;
}

ID3D11Buffer*& Light::GetBuffer()
{
	return pLightBuffer;
}
