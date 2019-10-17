#include "Model.h"
#include "Locator.h"
#include "D3D.h"
#include "Timer.h"
#include "Graphics.h"

#include <D3Dcompiler.h>

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

Model::Model()
{
	position = { 0.0f, 0.0f, 0.0f, 1.0f };
	rotation = { 0.0f, 0.0f, 0.0f, 1.0f };
	shapeType = "cube";


}

Model::~Model()
{
}

bool Model::Init()
{

	
	D3D11_BUFFER_DESC cbd = {};
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(MatrixBufferType);
	cbd.StructureByteStride = 0u;
	//D3D11_SUBRESOURCE_DATA csd = {};
	//csd.pSysMem = &cb;
	Locator::GetGraphics()->GetD3D()->GetDevice()->CreateBuffer(&cbd, 0, &m_matrixBuffer);

	 wrl::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	Locator::GetD3D()->GetDevice()->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);

	//// create vertex shader
	//wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	Locator::GetD3D()->GetDevice()->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);

	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "SV_Position",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "Color",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	Locator::GetD3D()->GetDevice()->CreateInputLayout(
		ied, (UINT)std::size(ied),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayout
	);

	// bind vertex layout
	Locator::GetD3D()->GetDeviceContext()->IASetInputLayout(pInputLayout.Get());


	m_worldMatrix = dx::XMMatrixIdentity();
	return true;
}

void Model::Update()
{

}

HRESULT Model::Render(DirectX::XMMATRIX viewMatrix)
{
	UpdateConstantBuffer();

	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;

	// Transpose the matrices to prepare them for the shader.
	m_worldMatrix = dx::XMMatrixTranspose(
		dx::XMMatrixRotationX(dx::XMVectorGetX(rotation)) *
		dx::XMMatrixRotationY(dx::XMVectorGetY(rotation)) *
		dx::XMMatrixRotationZ(dx::XMVectorGetZ(rotation)) *
		dx::XMMatrixTranslation(
			dx::XMVectorGetX(position),
			dx::XMVectorGetY(position),
			dx::XMVectorGetZ(position)));

	dx::XMMATRIX projMatrix = Locator::GetD3D()->GetProjMatrix();
	projMatrix = dx::XMMatrixTranspose(projMatrix);

	viewMatrix = dx::XMMatrixTranspose(viewMatrix);

	// Lock the constant buffer so it can be written to.
	if (FAILED(hr = Locator::GetD3D()->GetDeviceContext()->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource)))
	{
		return hr;
	}
	// Get a pointer to the data in the constant buffer.
	dataPtr = (MatrixBufferType*)mappedResource.pData;

	// Copy the matrices into the constant buffer.
	dataPtr->world = m_worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projMatrix;

	// Unlock the constant buffer.
	Locator::GetD3D()->GetDeviceContext()->Unmap(m_matrixBuffer, 0);

	Locator::GetD3D()->GetDeviceContext()->VSSetConstantBuffers(0u, 1u, &m_matrixBuffer);

	Locator::GetD3D()->GetDeviceContext()->PSSetShader(pPixelShader.Get(), nullptr, 0u);

	Locator::GetD3D()->GetDeviceContext()->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	Locator::GetD3D()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Locator::GetD3D()->GetDeviceContext()->DrawIndexed((UINT)Locator::GetBuffers()->GetIndeciesSize(shapeType), 0u, 0u);
	//Locator::GetD3D()->GetDeviceContext()->Draw((UINT)Locator::GetBuffers()->GetIndeciesSize(shapeType), 0u);


	return hr;
	//Locator::GetGraphics()->DrawGeometry(shapeType);
}

void Model::UpdateConstantBuffer()
{
	//struct ConstantBuffer
	//{
	//	dx::XMMATRIX transform;
	//};

	////angle += 100.0f * Locator::GetTimer()->DeltaTime();
	//ConstantBuffer cb
	//{
	//	dx::XMMatrixTranspose(
	//		dx::XMMatrixRotationX(dx::XMVectorGetX(rotation)) *
	//		dx::XMMatrixRotationY(dx::XMVectorGetY(rotation)) *
	//		dx::XMMatrixRotationZ(dx::XMVectorGetZ(rotation)) *
	//		dx::XMMatrixTranslation(
	//			dx::XMVectorGetX(position),
	//			dx::XMVectorGetY(position),
	//			dx::XMVectorGetZ(position)) *
	//		dx::XMMatrixPerspectiveFovLH(1.0f, 1.0f, 1.0f, 1000.0f)
	//	)
	//};

	//wrl::ComPtr<ID3D11Buffer> pConstantBuffer;
	//D3D11_BUFFER_DESC cbd = {};
	//cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//cbd.Usage = D3D11_USAGE_DYNAMIC;
	//cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//cbd.MiscFlags = 0u;
	//cbd.ByteWidth = sizeof(cb);
	//cbd.StructureByteStride = 0u;
	//D3D11_SUBRESOURCE_DATA csd = {};
	//csd.pSysMem = &cb;
	//Locator::GetGraphics()->GetD3D()->GetDevice()->CreateBuffer(&cbd, &csd, &pConstantBuffer);

	//Locator::GetGraphics()->GetD3D()->GetDeviceContext()->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());

	Locator::GetGraphics()->GetD3D()->GetDeviceContext()->IASetVertexBuffers(0u, 1u, &Locator::GetBuffers()->GetVertexBuffer(shapeType), &Locator::GetBuffers()->GetStride(shapeType), &Locator::GetBuffers()->GetOffset(shapeType));

	// bind index buffer
	Locator::GetGraphics()->GetD3D()->GetDeviceContext()->IASetIndexBuffer(Locator::GetBuffers()->GetIndexBuffer(shapeType), DXGI_FORMAT_R16_UINT, 0u);

}

DirectX::XMVECTOR Model::GetPos()
{
	return position;
}

float Model::GetPosX()
{
	return dx::XMVectorGetX(position);
}

float Model::GetPosY()
{
	return dx::XMVectorGetY(position);
}

float Model::GetPosZ()
{
	return dx::XMVectorGetZ(position);
}

DirectX::XMVECTOR Model::GetRot()
{
	return rotation;
}

float Model::GetRotX()
{
	return dx::XMVectorGetX(rotation);
}

float Model::GetRotY()
{
	return dx::XMVectorGetY(rotation);
}

float Model::GetRotZ()
{
	return dx::XMVectorGetZ(rotation);
}

void Model::SetPos(float x, float y, float z)
{
	position = { x, y, z, dx::XMVectorGetW(position) };
}

void Model::SetPosX(float x)
{
	position = { x, dx::XMVectorGetY(position), dx::XMVectorGetZ(position), dx::XMVectorGetW(position) };
}

void Model::SetPosY(float y)
{
	position = { dx::XMVectorGetX(position), y, dx::XMVectorGetZ(position), dx::XMVectorGetW(position) };
}

void Model::SetPosZ(float z)
{
	position = { dx::XMVectorGetX(position), dx::XMVectorGetY(position), z, dx::XMVectorGetW(position) };
}

void Model::SetRot(float x, float y, float z)
{
	rotation = { x, y, z, dx::XMVectorGetW(rotation) };
}

void Model::SetRotX(float x)
{
	rotation = { x, dx::XMVectorGetY(rotation), dx::XMVectorGetZ(rotation), dx::XMVectorGetW(rotation) };
}

void Model::SetRotY(float y)
{
	rotation = { dx::XMVectorGetX(rotation), y, dx::XMVectorGetZ(rotation), dx::XMVectorGetW(rotation) };
}

void Model::SetRotZ(float z)
{
	rotation = { dx::XMVectorGetX(rotation), dx::XMVectorGetY(rotation), z, dx::XMVectorGetW(rotation) };
}

const std::string& Model::GetGeometry()
{
	return shapeType;
}

void Model::SetGeometry(const std::string& _shapeType)
{
	shapeType = _shapeType;
}
