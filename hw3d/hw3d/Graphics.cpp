#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

#include "Graphics.h"
#include "Locator.h"

#include <d3d11.h>
#include <d3dcompiler.h>


Graphics::Graphics(const HWND &hWnd)
{

	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	HRESULT hr;
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pDeviceContext
	)))
	{
		MessageBox(nullptr, (LPCSTR)hr, "Exception", MB_OK | MB_ICONEXCLAMATION);
	}

	// creating a render target from the back buffer using com
	Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer);
	pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTargetView);
	pBackBuffer->Release();
}

void Graphics::EndFrame()
{
	pSwapChain->Present(1u, 0u);
}

void Graphics::ClearBuffer(float r, float g, float b, float a)
{
	const float colour[] = { r, g, b, a };
	pDeviceContext->ClearRenderTargetView(pTargetView.Get(), colour);
}

void Graphics::DrawTestTriangle()
{
	struct Vertex
	{
		float x;
		float y;
	};

	const Vertex verticies[] = 
	{
		{ 0.0f, 1.0f },
		{-1.0f, -1.0f },
		{ 1.0f, -1.0f }
	};
	HRESULT hr;

	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0u;
	bd.MiscFlags = 0u;
	bd.ByteWidth = sizeof(verticies);
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = verticies;
	if (FAILED(hr = pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer)))
	{
		MessageBox(nullptr, (LPCSTR)hr, "Create Buffer", MB_OK | MB_ICONEXCLAMATION);
	}

	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	pDeviceContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
	
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	//D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	if (FAILED(hr = D3DReadFileToBlob(L"PixelShader.cso", &pBlob)))
	{
		MessageBox(nullptr, (LPCSTR)hr, "Load Pixel Shader", MB_OK | MB_ICONEXCLAMATION);
	}
	//pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
	if (FAILED(hr = pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader)))
	{
		MessageBox(nullptr, (LPCSTR)hr, "Create Pixel Shader", MB_OK | MB_ICONEXCLAMATION);
	}
	pDeviceContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);

	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	//D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	if (FAILED(hr = D3DReadFileToBlob(L"VertexShader.cso", &pBlob)))
	{
		MessageBox(nullptr, (LPCSTR)hr, "Load Vertex Shader", MB_OK | MB_ICONEXCLAMATION);
	}
	//pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
	if (FAILED(hr = pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader)))
	{
		MessageBox(nullptr, (LPCSTR)hr, "Create Vertex Shader", MB_OK | MB_ICONEXCLAMATION);
	}
	pDeviceContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);

	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	//pDevice->CreateInputLayout(
	//	ied, (UINT)std::size(ied),
	//	pBlob->GetBufferPointer(),
	//	pBlob->GetBufferSize(),
	//	&pInputLayout
	//);
	if (FAILED(hr = pDevice->CreateInputLayout(
		ied, (UINT)std::size(ied),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayout
	)))
	{
		MessageBox(nullptr, (LPCSTR)hr, "Create Input Layout", MB_OK | MB_ICONEXCLAMATION);
	}

	pDeviceContext->IASetInputLayout(pInputLayout.Get());

	pDeviceContext->OMSetRenderTargets(1u, pTargetView.GetAddressOf(), nullptr);

	CD3D11_VIEWPORT viewport;
	viewport.Width = 500;
	viewport.Height = 500;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	pDeviceContext->RSSetViewports(1u, &viewport);

	pDeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pDeviceContext->Draw((UINT)std::size(verticies), 0u);
}
