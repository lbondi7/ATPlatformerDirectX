#pragma once
#include "WinSetup.h"

#include <d3d11.h>
#include <vector>
#include <wrl.h>

class Graphics
{
public:

	Graphics(const HWND& hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;
	void EndFrame();
	void ClearBuffer(float r, float g, float b, float a);
	void DrawTestTriangle();

private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pDeviceContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTargetView;
};

