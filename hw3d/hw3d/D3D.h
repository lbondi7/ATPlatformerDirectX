#pragma once
#include "WinSetup.h"

#include <d3d11.h>
#include <wrl.h>
#include <DirectXMath.h>

class D3D
{
public:

	D3D() = default;
	~D3D() = default;

	HRESULT Init(HWND hWnd);

	//Microsoft::WRL::ComPtr<ID3D11Device> GetDevice();
	//Microsoft::WRL::ComPtr<IDXGISwapChain> GetSwapChain();
	//Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext();
	ID3D11Device* GetDevice();
	IDXGISwapChain* GetSwapChain();
	ID3D11DeviceContext* GetDeviceContext();
	DirectX::XMMATRIX GetWorldMatrix();
	DirectX::XMMATRIX GetProjMatrix();
	void SetWorldMatrix(DirectX::XMMATRIX maxtrix);
	void SetProjMatrix(DirectX::XMMATRIX maxtrix);

	//Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	//Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	//Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext;
private:
	ID3D11Device* p_device = nullptr;
	ID3D11DeviceContext* p_deviceContext = nullptr;
	IDXGISwapChain* p_swapChain = nullptr;
	DirectX::XMMATRIX m_projectionMatrix;
	DirectX::XMMATRIX m_worldMatrix;
};

