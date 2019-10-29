#include "Model.h"
#include "Locator.h"
#include "Texture.h"
#include "D3D.h"
#include "Timer.h"
#include "Shader.h"
#include "Graphics.h"


namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

Model::Model()
{
	position = { 0.0f, 0.0f, 0.0f, 1.0f };
	rotation = { 0.0f, 0.0f, 0.0f, 1.0f };
}

Model::~Model()
{
}

HRESULT Model::Init()
{

	HRESULT hr;
	D3D11_BUFFER_DESC cbd = {};
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(MatrixBufferType);
	cbd.StructureByteStride = 0u;
	//D3D11_SUBRESOURCE_DATA csd = {};
	//csd.pSysMem = &cb;
	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreateBuffer(&cbd, 0, &m_matrixBuffer)))
	{
		return hr;
	}

	D3D11_BUFFER_DESC lightBufferDesc = {};
	lightBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBufferType);
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;
	lightBufferDesc.StructureByteStride = 0;

	// Create the constant buffer pointer so we can access the vertex shader constant buffer from within this class.
	Locator::GetD3D()->GetDevice()->CreateBuffer(&lightBufferDesc, NULL, &m_lightBuffer);

	m_worldMatrix = dx::XMMatrixIdentity();
	return hr;
}

void Model::Update()
{
	m_worldMatrix = dx::XMMatrixTranspose(
		dx::XMMatrixRotationX(dx::XMConvertToRadians(dx::XMVectorGetX(rotation))) *
		dx::XMMatrixRotationY(dx::XMConvertToRadians(dx::XMVectorGetY(rotation))) *
		dx::XMMatrixRotationZ(dx::XMConvertToRadians(dx::XMVectorGetZ(rotation))) *
		dx::XMMatrixScaling(dx::XMVectorGetX(scale),
			dx::XMVectorGetY(scale),
			dx::XMVectorGetZ(scale)) *
		dx::XMMatrixTranslation(
			dx::XMVectorGetX(position),
			dx::XMVectorGetY(position),
			dx::XMVectorGetZ(position)));
}

HRESULT Model::Render(DirectX::XMMATRIX viewMatrix)
{
	HRESULT hr;

	dx::XMMATRIX projMatrix = Locator::GetD3D()->GetProjMatrix();
	projMatrix = dx::XMMatrixTranspose(projMatrix);

	viewMatrix = dx::XMMatrixTranspose(viewMatrix);

	//Locator::GetGraphics()->GetD3D()->GetDeviceContext()->IASetVertexBuffers(0u, 1u, &Locator::GetBuffers()->GetVertexBuffer(mModelType), &Locator::GetBuffers()->GetStride(mModelType), &Locator::GetBuffers()->GetOffset(mModelType));

	//// bind index buffer
	//Locator::GetGraphics()->GetD3D()->GetDeviceContext()->IASetIndexBuffer(Locator::GetBuffers()->GetIndexBuffer(mModelType), DXGI_FORMAT_R16_UINT, 0u);

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

	Locator::GetD3D()->GetDeviceContext()->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// Get a pointer to the data in the constant buffer.
	dataPtr2 = (LightBufferType*)mappedResource.pData;

	// Copy the lighting variables into the constant buffer.
	dataPtr2->diffuseColor = {1.0f, 1.0f, 1.0f, 1.0f};
	dataPtr2->lightDirection = {1.0f, 0.0, 1.0, 1.0f};
	dataPtr2->padding = 0.0f;

	// Unlock the constant buffer.
	Locator::GetD3D()->GetDeviceContext()->Unmap(m_lightBuffer, 0);

	// Set the position of the light constant buffer in the pixel shader.
	bufferNumber = 0;

	// Finally set the light constant buffer in the pixel shader with the updated values.
	Locator::GetD3D()->GetDeviceContext()->PSSetConstantBuffers(bufferNumber, 1, &m_lightBuffer);

	Locator::GetGraphics()->GetD3D()->GetDeviceContext()->IASetVertexBuffers(0u, 1u, &Locator::GetBuffers()->GetVertexBuffer(mModelType), &Locator::GetBuffers()->GetStride(mModelType), &Locator::GetBuffers()->GetOffset(mModelType));

	Locator::GetGraphics()->GetD3D()->GetDeviceContext()->IASetIndexBuffer(Locator::GetBuffers()->GetIndexBuffer(mModelType), DXGI_FORMAT_R16_UINT, 0u);

	Locator::GetD3D()->GetDeviceContext()->PSSetShaderResources(0u, 1u, &Locator::GetTexture()->GetTextureView(mTexure));

	Locator::GetD3D()->GetDeviceContext()->IASetInputLayout(Locator::GetShader()->GetInputLayout(mShader));

	Locator::GetD3D()->GetDeviceContext()->PSSetShader(Locator::GetShader()->GetPixelShader(mShader), nullptr, 0u);

	Locator::GetD3D()->GetDeviceContext()->VSSetShader(Locator::GetShader()->GetVertexShader(mShader), nullptr, 0u);

	Locator::GetD3D()->GetDeviceContext()->PSSetSamplers(0, 1, &Locator::GetTexture()->GetSampleState(mTexure));

	Locator::GetD3D()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Locator::GetD3D()->GetDeviceContext()->DrawIndexed((UINT)Locator::GetBuffers()->GetIndeciesSize(mModelType), 0u, 0u);
	//Locator::GetD3D()->GetDeviceContext()->Draw((UINT)Locator::GetBuffers()->GetIndeciesSize(shapeType), 0u);


	return hr;
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

DirectX::XMVECTOR Model::GetScale()
{
	return DirectX::XMVECTOR();
}

float Model::GetScaleX()
{
	return dx::XMVectorGetX(scale);
}

float Model::GetScaleY()
{
	return dx::XMVectorGetY(scale);
}

float Model::GetScaleZ()
{
	return dx::XMVectorGetZ(scale);
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

void Model::SetScale(float x, float y, float z)
{
	scale = { x, y, z, dx::XMVectorGetW(scale) };
}

void Model::SetScaleX(float x)
{
	scale = { x, dx::XMVectorGetY(scale), dx::XMVectorGetZ(scale), dx::XMVectorGetW(scale) };
}

void Model::SetScaleY(float y)
{
	scale = { dx::XMVectorGetX(scale), y, dx::XMVectorGetZ(scale), dx::XMVectorGetW(scale) };
}

void Model::SetScaleZ(float z)
{
	scale = { dx::XMVectorGetX(scale), dx::XMVectorGetY(scale), z, dx::XMVectorGetW(scale) };
}

void Model::ModelType(const std::string& _shapeType)
{
	mModelType = _shapeType;
}

const std::string& Model::Texture()
{
	return mTexure;
}

void Model::Texture(const std::string& _texType)
{
	mTexure = _texType;
}

const std::string& Model::Shader()
{
	return mShader;
}

void Model::Shader(const std::string& shaderType)
{
	mShader = shaderType;
}