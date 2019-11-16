#pragma once
#include "WinSetup.h"
#include "LewisException.h"
#include "DxgiInfoManager.h"
#include "D3D.h"
#include "Vertices.h"

#include <d3d11.h>
#include <wrl.h>

#include <vector>
#include <memory>

class Graphics
{
public:
	class Exception : public LewisException
	{
		using LewisException::LewisException;
	};
	class HrException : public Exception
	{
	public:
		HrException(int line, const char* file, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT hr;
		std::string info;
	};
	class InfoException : public Exception
	{
	public:
		InfoException(int line, const char* file, std::vector<std::string> infoMsgs) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
	};
	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	private:
		std::string reason;
	};
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;
	void Render(DirectX::XMMATRIX wMtrx,
		const std::string& model,
		const std::string& texture,
		const std::string& shader);
	void EndFrame();
	void BeginFrame() noexcept;
	void CheckHResults(HRESULT hr);
	D3D* GetD3D();

private:
#ifndef NDEBUG
	DxgiInfoManager infoManager;
#endif
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepStenView;
	std::unique_ptr<D3D> d3d;
	ID3D11RasterizerState* m_rasterState;
	DirectX::XMMATRIX mProjMatrixCopy;
	DirectX::XMMATRIX mViewMatrixCopy;
};