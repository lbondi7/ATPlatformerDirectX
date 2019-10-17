#pragma once

#include <string>
#include <DirectXMath.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <d3d11.h>

class Model
{
public:
	Model();
	~Model();

	bool Init();
	void Update();
	HRESULT Render(DirectX::XMMATRIX viewMatrix);

	void UpdateConstantBuffer();

	DirectX::XMVECTOR GetPos();
	float GetPosX();
	float GetPosY();
	float GetPosZ();

	DirectX::XMVECTOR GetRot();
	float GetRotX();
	float GetRotY();
	float GetRotZ();

	void SetPos(float x, float y, float z);
	void SetPosX(float x);
	void SetPosY(float y);
	void SetPosZ(float z);
	void SetRot(float x, float y, float z);
	void SetRotX(float x);
	void SetRotY(float y);
	void SetRotZ(float z);

	const std::string& GetGeometry();
	void SetGeometry(const std::string& _shapeType);

private:

	std::string shapeType;
	
	float x;
	float y;
	float z;
	DirectX::XMVECTOR position;
	DirectX::XMVECTOR rotation;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	DirectX::XMMATRIX m_worldMatrix;
	ID3D11Buffer* m_matrixBuffer;
	struct MatrixBufferType
	{
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX view;
		DirectX::XMMATRIX projection;
	};
};

