#pragma once

#include "Constants.h"

#include <d3d11.h>

class Matrices
{
public: 
	Matrices() = default;
	~Matrices();

	HRESULT CreateBuffer();

	HRESULT MapResource(DirectX::XMMATRIX wMtrx, DirectX::XMMATRIX vMtrx, DirectX::XMMATRIX pMtrxD);

	ID3D11Buffer*& GetBuffer();


private:

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ID3D11Buffer* m_matrixBuffer;
	MatrixBufferType* dataPtr;
	HRESULT hr;
};

