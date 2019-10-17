#include "Model.h"
#include "Locator.h"
#include "D3D.h"
#include "Timer.h"
#include "Graphics.h"


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
	if (FAILED(hr = Locator::GetGraphics()->GetD3D()->GetDevice()->CreateBuffer(&cbd, 0, &m_matrixBuffer)))
	{
		return hr;
	}

	wrl::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(L"PixelShaderTex.cso", &pBlob);
	Locator::GetD3D()->GetDevice()->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
	//// create vertex shader
//wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	D3DReadFileToBlob(L"VertexShaderTex.cso", &pBlob);
	Locator::GetD3D()->GetDevice()->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "SV_Position",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	;
	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreateInputLayout(
		ied, (UINT)std::size(ied),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayout
	)))
	{
		return hr;
	}

	// bind vertex layout

	D3D11_SAMPLER_DESC samplerDesc = {};
	// Create a texture sampler state description.
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	// Create the texture sampler state.
	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreateSamplerState(&samplerDesc, &m_sampleState)))
	{
		return hr;
	}
	int height, width;
	D3D11_TEXTURE2D_DESC textureDesc;
	unsigned int rowPitch;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

	std::string file = "..//Data//Simon.tga";
	if (!LoadTarga(file.data(), height, width))
	{
		return false;
	}

	// Setup the description of the texture.
	textureDesc.Height = height;
	textureDesc.Width = width;
	textureDesc.MipLevels = 0;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	HRESULT hResult;
	// Create the empty texture.
	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreateTexture2D(&textureDesc, NULL, &m_texture)))
	{
		return hr;// Set the row pitch of the targa image data.
	}
	rowPitch = (width * 4) * sizeof(unsigned char);

	// Copy the targa image data into the texture.
	Locator::GetD3D()->GetDeviceContext()->UpdateSubresource(m_texture, 0, NULL, m_targaData, rowPitch, 0);

	// Setup the shader resource view description.
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	// Create the shader resource view for the texture.
	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreateShaderResourceView(m_texture, &srvDesc, &m_textureView)))
	{
		return hr;
	}
	// Generate mipmaps for this texture.
	Locator::GetD3D()->GetDeviceContext()->GenerateMips(m_textureView);

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

	Locator::GetD3D()->GetDeviceContext()->PSSetShaderResources(0u, 1u, &m_textureView);

	Locator::GetD3D()->GetDeviceContext()->IASetInputLayout(pInputLayout.Get());

	Locator::GetD3D()->GetDeviceContext()->PSSetShader(pPixelShader.Get(), nullptr, 0u);

	Locator::GetD3D()->GetDeviceContext()->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	Locator::GetD3D()->GetDeviceContext()->PSSetSamplers(0, 1, &m_sampleState);

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

bool Model::LoadTarga(char* filename, int& height, int& width)
{
	int error, bpp, imageSize, index, i, j, k;
	FILE* filePtr;
	unsigned int count;
	TargaHeader targaFileHeader;
	unsigned char* targaImage;


	// Open the targa file for reading in binary.
	error = fopen_s(&filePtr, filename, "rb");
	if (error != 0)
	{
		return false;
	}

	// Read in the file header.
	count = (unsigned int)fread(&targaFileHeader, sizeof(TargaHeader), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	// Get the important information from the header.
	height = (int)targaFileHeader.height;
	width = (int)targaFileHeader.width;
	bpp = (int)targaFileHeader.bpp;

	// Check that it is 32 bit and not 24 bit.
	if (bpp != 32)
	{
		return false;
	}

	// Calculate the size of the 32 bit image data.
	imageSize = width * height * 4;

	// Allocate memory for the targa image data.
	targaImage = new unsigned char[imageSize];
	if (!targaImage)
	{
		return false;
	}

	// Read in the targa image data.
	count = (unsigned int)fread(targaImage, 1, imageSize, filePtr);
	if (count != imageSize)
	{
		return false;
	}

	// Close the file.
	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	// Allocate memory for the targa destination data.
	m_targaData = new unsigned char[imageSize];
	if (!m_targaData)
	{
		return false;
	}

	// Initialize the index into the targa destination data array.
	index = 0;

	// Initialize the index into the targa image data.
	k = (width * height * 4) - (width * 4);

	// Now copy the targa image data into the targa destination array in the correct order since the targa format is stored upside down.
	for (j = 0; j < height; j++)
	{
		for (i = 0; i < width; i++)
		{
			m_targaData[index + 0] = targaImage[k + 2];  // Red.
			m_targaData[index + 1] = targaImage[k + 1];  // Green.
			m_targaData[index + 2] = targaImage[k + 0];  // Blue
			m_targaData[index + 3] = targaImage[k + 3];  // Alpha

			// Increment the indexes into the targa data.
			k += 4;
			index += 4;
		}

		// Set the targa image data index back to the preceding row at the beginning of the column since its reading it in upside down.
		k -= (width * 8);
	}

	// Release the targa image data now that it was copied into the destination array.
	delete[] targaImage;
	targaImage = 0;

	return true;
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
