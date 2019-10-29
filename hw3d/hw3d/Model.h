#pragma once

#include "Transform.h"

#include <string>
#include <DirectXMath.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <stdio.h>

class Model
{
public:
	Model()  = default;
	~Model();

	void Init();
	void Update();
	void Render(DirectX::XMMATRIX viewMatrix);

	Transform& GetTransform();

	const std::string& ModelType();
	void ModelType(const std::string& _shapeType);
	const std::string& Texture();
	void Texture(const std::string& _shapeType);
	const std::string& Shader();
	void Shader(const std::string& _shapeType);

private:

	std::string mModelType = "iso";
	std::string mTexure = "Simon";
	std::string mShader = "basic";

	ID3D11SamplerState* m_sampleState;
	DirectX::XMMATRIX mWorldMatrix;
	ID3D11Buffer* m_matrixBuffer;
	struct MatrixBufferType
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};
	struct LightBufferType
	{
		DirectX::XMVECTOR diffuseColor;
		DirectX::XMVECTOR lightDirection;
		float padding;  // Added extra padding so structure is a multiple of 16 for CreateBuffer function requirements.
	};

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;
	//ID3D11Buffer* m_lightBuffer;
	//LightBufferType* dataPtr2;


	Transform transform;
};