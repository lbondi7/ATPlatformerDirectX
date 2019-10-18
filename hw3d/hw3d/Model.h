#pragma once

#include <string>
#include <DirectXMath.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <stdio.h>

class Model
{
public:
	Model();
	~Model();

	HRESULT Init();
	void Update();
	HRESULT Render(DirectX::XMMATRIX viewMatrix);

	void UpdateConstantBuffer();

	bool LoadTarga(char* filename, int& height, int& width);

	DirectX::XMVECTOR GetPos();
	float GetPosX();
	float GetPosY();
	float GetPosZ();

	DirectX::XMVECTOR GetRot();
	float GetRotX();
	float GetRotY();
	float GetRotZ();

	DirectX::XMVECTOR GetScale();
	float GetScaleX();
	float GetScaleY();
	float GetScaleZ();

	void SetPos(float x, float y, float z);
	void SetPosX(float x);
	void SetPosY(float y);
	void SetPosZ(float z);
	void SetRot(float x, float y, float z);
	void SetRotX(float x);
	void SetRotY(float y);
	void SetRotZ(float z);

	void SetScale(float x, float y, float z);
	void SetScaleX(float x);
	void SetScaleY(float y);
	void SetScaleZ(float z);

	const std::string& GetGeometry();
	void SetGeometry(const std::string& _shapeType);
	const std::string& GetTexture();
	void SetTexture(const std::string& _shapeType);

private:

	std::string shapeType;
	std::string texName = "";

	float x;
	float y;
	float z;
	DirectX::XMVECTOR position;
	DirectX::XMVECTOR rotation;
	DirectX::XMVECTOR scale = {1, 1, 1, 0};
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	ID3D11SamplerState* m_sampleState;
	DirectX::XMMATRIX m_worldMatrix;
	ID3D11Buffer* m_matrixBuffer;
	struct MatrixBufferType
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};

	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};
	unsigned char* m_targaData;
	ID3D11Texture2D* m_texture;
	ID3D11ShaderResourceView* m_textureView;

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;
};