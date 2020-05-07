#include "Texture.h"
#include "Locator.h"
#include "D3D.h"
#include <iostream>
#include <fstream>
#include <memory>

HRESULT Texture::CreateTexture(const ImageData& image)
{
	HRESULT hr;

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
	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreateSamplerState(&samplerDesc, m_SampleState.GetAddressOf())))
	{
		return hr;
	}
	int height, width;
	D3D11_TEXTURE2D_DESC textureDesc;
	unsigned int rowPitch;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;

	// Setup the description of the texture.
	textureDesc.Height = static_cast<int>(image.buffer.height);
	textureDesc.Width = static_cast<int>(image.buffer.width);
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	// Create the empty texture.
	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreateTexture2D(&textureDesc, NULL, m_Texture.GetAddressOf())))
	{
		return hr;// Set the row pitch of the targa image data.
	}
	rowPitch = (static_cast<int>(image.buffer.width) * 4) * sizeof(unsigned char);

	// Copy the targa image data into the texture.
	Locator::GetD3D()->GetDeviceContext()->UpdateSubresource(m_Texture.Get(), 0, NULL, image.data, rowPitch, 0);

	// Setup the shader resource view description.
	srvDesc.Format = textureDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = -1;

	// Create the shader resource view for the texture.
	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreateShaderResourceView(m_Texture.Get(), &srvDesc, m_TextureView.GetAddressOf())))
	{
		return hr;
	}
	// Generate mipmaps for this texture.
	Locator::GetD3D()->GetDeviceContext()->GenerateMips(m_TextureView.Get());

	return hr;
}
