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

	ID3D11Device* GetDevice();
	IDXGISwapChain* GetSwapChain();
	ID3D11DeviceContext* GetDeviceContext();
	DirectX::XMMATRIX& GetViewMatrix();
	DirectX::XMMATRIX GetProjMatrix();
	void SetViewMatrix(DirectX::XMMATRIX maxtrix);
	void SetProjMatrix(DirectX::XMMATRIX maxtrix);

private:
	ID3D11Device* pDevice = nullptr;
	ID3D11DeviceContext* pDeviceContext = nullptr;
	IDXGISwapChain* pSwapChain = nullptr;
	DirectX::XMMATRIX mProjectionMatrix;
	DirectX::XMMATRIX mViewMatrix;
};

