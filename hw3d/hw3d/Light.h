#pragma once

#include <DirectXMath.h>
#include <d3d11.h>

#include <optional>

class Light
{
public:

	Light() = default;
	~Light();

	HRESULT CreateBuffer();

	HRESULT MapResource();

	ID3D11Buffer*& GetBuffer();

private:

	struct LightBufferType
	{
		DirectX::XMVECTOR diffuseColor;
		DirectX::XMVECTOR lightDirection;
		float padding;  // Added extra padding so structure is a multiple of 16 for CreateBuffer function requirements.
	};

	D3D11_MAPPED_SUBRESOURCE mMappedResource;
	ID3D11Buffer* pLightBuffer;
	LightBufferType* pLightData;
	HRESULT hr;
};

