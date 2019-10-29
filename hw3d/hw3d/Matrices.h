#pragma once

#include <DirectXMath.h>
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

	struct MatrixBufferType
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ID3D11Buffer* m_matrixBuffer;
	MatrixBufferType* dataPtr;
	HRESULT hr;
};

