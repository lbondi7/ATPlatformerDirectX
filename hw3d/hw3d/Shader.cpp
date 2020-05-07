#include "Shader.h"
#include "Locator.h"
#include "D3D.h"
#include "Utilities.h"

#include <d3dcompiler.h>

std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

HRESULT Shaders::Create(const std::string& shader)
{
	HRESULT hr;
	
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(s2ws("Data/shaders/Ps" + shader + ".cso").c_str(), &pBlob);
	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, m_PixelShader.GetAddressOf())))
		return hr;

	//// create vertex shader
	D3DReadFileToBlob(s2ws("Data/shaders/Vs" + shader + ".cso").c_str(), &pBlob);
	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, m_VertexShader.GetAddressOf())))
		return hr;

	//const D3D11_INPUT_ELEMENT_DESC ied[] =
	//{
	//	{ "SV_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//};

	std::vector<D3D11_INPUT_ELEMENT_DESC> ied;

	ied = {
			{ "SV_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	//if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreateInputLayout(ied, (UINT)std::size(ied), 
	//	pBlob->GetBufferPointer(), pBlob->GetBufferSize(), m_InputLayout.GetAddressOf())))
	//{
	//	return hr;
	//}

	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreateInputLayout(ied.data(), (UINT)ied.size(),
		pBlob->GetBufferPointer(), pBlob->GetBufferSize(), m_InputLayout.GetAddressOf())))
	{
		return hr;
	}

	return hr;
}

HRESULT Shaders::Create(const std::string& shader, bool instancing)
{
	HRESULT hr;

	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	D3DReadFileToBlob(s2ws("Data/shaders/Ps" + shader + ".cso").c_str(), &pBlob);
	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, m_PixelShader.GetAddressOf())))
		return hr;

	//// create vertex shader
	D3DReadFileToBlob(s2ws("Data/shaders/Vs" + shader + ".cso").c_str(), &pBlob);
	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, m_VertexShader.GetAddressOf())))
		return hr;

	//const D3D11_INPUT_ELEMENT_DESC ied[] =
	//{
	//	{ "SV_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	//};


	std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDescriptorSet;

	if (instancing)
	{
		inputElementDescriptorSet = {
			{ "SV_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "INSTANCEPOS", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		};
	}
	else
	{
		inputElementDescriptorSet = {
			{ "SV_POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
	}

	UINT size = static_cast<UINT>(inputElementDescriptorSet.size());
	if (FAILED(hr = Locator::GetD3D()->GetDevice()->CreateInputLayout(inputElementDescriptorSet.data(), size,
		pBlob->GetBufferPointer(), pBlob->GetBufferSize(), m_InputLayout.GetAddressOf())))
	{
		return hr;
	}

	return hr;
}