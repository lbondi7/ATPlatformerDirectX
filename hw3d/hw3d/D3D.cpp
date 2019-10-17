#include "D3D.h"

namespace dx = DirectX;

HRESULT D3D::Init(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
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

	UINT swapCreateFlags = 0u;
#ifndef NDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// for checking results of d3d functions
	HRESULT hr;

	// create device and front/back buffers, and swap chain and rendering context
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&p_swapChain,
		&p_device,
		nullptr,
		&p_deviceContext
	);

	float fieldOfView = (float)dx::XM_PI / 4.0f;
	float screenAspect = (float)500 / (float)500;

	//// Create the projection matrix for 3D rendering.
	//D3DXMatrixPerspectiveFovLH(&m_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);


	m_projectionMatrix = dx::XMMatrixPerspectiveFovLH(1.0f, screenAspect, 0.1f, 1000.0f);
	m_worldMatrix = dx::XMMatrixIdentity();


	return hr;
}

ID3D11Device* D3D::GetDevice()
{
	return p_device;
}

IDXGISwapChain* D3D::GetSwapChain()
{
	return p_swapChain;
}

ID3D11DeviceContext* D3D::GetDeviceContext()
{
	return p_deviceContext;
}

DirectX::XMMATRIX D3D::GetWorldMatrix()
{
	return m_worldMatrix;
}

DirectX::XMMATRIX D3D::GetProjMatrix()
{
	return m_projectionMatrix;
}

void D3D::SetWorldMatrix(DirectX::XMMATRIX maxtrix)
{
	m_worldMatrix = maxtrix;
}

void D3D::SetProjMatrix(DirectX::XMMATRIX maxtrix)
{
	m_projectionMatrix = maxtrix;
}

//Microsoft::WRL::ComPtr<ID3D11Device> D3D::GetDevice()
//{
//	return pDevice;
//}
//
//Microsoft::WRL::ComPtr<IDXGISwapChain> D3D::GetSwapChain()
//{
//	return pSwapChain;
//}
//
//Microsoft::WRL::ComPtr<ID3D11DeviceContext> D3D::GetDeviceContext()
//{
//	return pDeviceContext;
//}
