#pragma once
#include "WinSetup.h"
#include "D3D.h"
#include "Vertices.h"
#include "RenderData.h"

#include <vector>
#include <memory>

class Graphics
{
public:
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;
	void Render(const RenderData* renderData);
	void EndFrame();
	void BeginFrame() noexcept;

private:

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepStenView;
	std::unique_ptr<D3D> d3d;
	ID3D11RasterizerState* m_rasterState;
	DirectX::XMMATRIX mProjMatrixCopy;
	DirectX::XMMATRIX mViewMatrixCopy;
};