#include "Shader.h"
#include "Locator.h"
#include "D3D.h"

#include <wrl.h>
#include <d3dcompiler.h>



HRESULT Shader::CreateShader(const std::string& shader)
{
	HRESULT hr;

	shaderMap[shader] = shaderCount;
	pPixelShaders.resize(shaderMap.size());
	pVertexShaders.resize(shaderMap.size());
	pInputLayouts.resize(shaderMap.size());


	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(L"PixelShaderLight.cso", &pBlob);
	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShaders[shaderMap[shader]])))
	{
		return hr;
	}

	//// create vertex shader
	D3DReadFileToBlob(L"VertexShaderLight.cso", &pBlob);
	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShaders[shaderMap[shader]])))
	{
		return hr;
	}

	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "SV_Position",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "TEXCOORD",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "NORMAL",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};

	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreateInputLayout(
		ied, (UINT)std::size(ied),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayouts[shaderMap[shader]]
	)))
	{
		return hr;
	}

	return hr;
}

ID3D11PixelShader*& Shader::GetPixelShader(const std::string& shader)
{
	return pPixelShaders[shaderMap[shader]];
}

ID3D11VertexShader*& Shader::GetVertexShader(const std::string& shader)
{
	return pVertexShaders[shaderMap[shader]];
}

ID3D11InputLayout*& Shader::GetInputLayout(const std::string& shader)
{
	return pInputLayouts[shaderMap[shader]];
}
