#pragma once
#include "WinSetup.h"

#include <d3d11.h>
#include <wrl.h>

class D3D
{
public:

	D3D() = default;
	~D3D() = default;

	void Init(HWND hWnd);

	//Microsoft::WRL::ComPtr<ID3D11Device> GetDevice();
	//Microsoft::WRL::ComPtr<IDXGISwapChain> GetSwapChain();
	//Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDeviceContext();
	ID3D11Device* GetDevice();
	IDXGISwapChain* GetSwapChain();
	ID3D11DeviceContext* GetDeviceContext();

	//Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	//Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	//Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext;
	IDXGISwapChain* pSwapChain = nullptr;
private:
	ID3D11Device* pDevice = nullptr;
	ID3D11DeviceContext* pDeviceContext = nullptr;
};

