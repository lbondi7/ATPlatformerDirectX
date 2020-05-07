#include "Graphics.h"
#include "dxerr.h"
#include "Timer.h"
#include "Locator.h"
#include "Texture.h"
#include "Shader.h"
#include "Misc.h"
#include "ResourceData.h"

#include "imgui//imgui.h"
#include "imgui//imgui_impl_win32.h"
#include "imgui//imgui_impl_dx11.h"
#include "imgui/ImGuizmo.h"

#include <sstream>

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;


Graphics::Graphics( HWND hWnd )
{
	// for checking results of d3d functions
	HRESULT hr;

	d3d = std::make_unique<D3D>();
	d3d->Init(hWnd);
	Locator::InitD3D(d3d.get());

	// gain access to texture subresource in swap chain (back buffer)
	wrl::ComPtr<ID3D11Resource> pBackBuffer;
	d3d->GetSwapChain()->GetBuffer( 0,__uuidof(ID3D11Resource),&pBackBuffer);
	d3d->GetDevice()->CreateRenderTargetView( pBackBuffer.Get(),nullptr,&pTargetView);

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	wrl::ComPtr<ID3D11DepthStencilState> pDDState;
	d3d->GetDevice()->CreateDepthStencilState(&dsDesc, &pDDState);

	d3d->GetDeviceContext()->OMSetDepthStencilState(pDDState.Get(), 1u);

	wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = WINDOW_WIDTH;
	descDepth.Height = WINDOW_HEIGHT;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	d3d->GetDevice()->CreateTexture2D(&descDepth, nullptr, &pDepthStencil);


	D3D11_DEPTH_STENCIL_VIEW_DESC descDepStenView = {};
	descDepStenView.Format = DXGI_FORMAT_D32_FLOAT;
	descDepStenView.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDepStenView.Texture2D.MipSlice = 0u;
	d3d->GetDevice()->CreateDepthStencilView(pDepthStencil.Get(), &descDepStenView, &pDepStenView);

	D3D11_RASTERIZER_DESC rasterDesc = {};
	rasterDesc.AntialiasedLineEnable = true;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	// Create the rasterizer state from the description we just filled out.
	d3d->GetDevice()->CreateRasterizerState(&rasterDesc, &m_rasterState);

	// Now set the rasterizer state.
	d3d->GetDeviceContext()->RSSetState(m_rasterState);

	// bind render target
	d3d->GetDeviceContext()->OMSetRenderTargets(1u, pTargetView.GetAddressOf(), pDepStenView.Get());


	// configure viewport
	D3D11_VIEWPORT viewport;
	viewport.Width = WINDOW_WIDTH;
	viewport.Height = WINDOW_HEIGHT;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	d3d->GetDeviceContext()->RSSetViewports(1u, &viewport);

	Locator::GetResources()->LoadResources();
	Locator::GetMisc()->SetClearColour({ 1, 0, 0, 1 });
}

void Graphics::Render(const RenderData* renderData)
{
	/*******	REQUIRED	********************/

	Locator::GetD3D()->GetDeviceContext()->VSSetConstantBuffers(0u, 1u, renderData->up_MatrixBuffer->m_Buffer.GetAddressOf());

	if (renderData->m_DrawInstanced)
	{
		ID3D11Buffer* vBuffers[]{renderData->p_VertexBuffer->m_Buffer.Get(), renderData->up_InstanceBuffer->m_Buffer.Get()};
		unsigned int strides[]{ renderData->p_VertexBuffer->m_Stride, renderData->up_InstanceBuffer->m_Stride };
		unsigned int offsets[]{ renderData->p_VertexBuffer->m_Offset, renderData->up_InstanceBuffer->m_Offset };

		UINT size = static_cast<UINT>(std::size(vBuffers));
		Locator::GetD3D()->GetDeviceContext()->IASetVertexBuffers(0u, size, vBuffers,
			strides, offsets);
	}
	else
	{
		Locator::GetD3D()->GetDeviceContext()->IASetVertexBuffers(0u, 1u, renderData->p_VertexBuffer->m_Buffer.GetAddressOf(),
			&renderData->p_VertexBuffer->m_Stride, &renderData->p_VertexBuffer->m_Offset);
	}

	Locator::GetD3D()->GetDeviceContext()->IASetIndexBuffer(renderData->p_IndexBuffer->m_Buffer.Get(), DXGI_FORMAT_R16_UINT, 0u);

	if (renderData->up_LightBuffer)
	{
		Locator::GetD3D()->GetDeviceContext()->PSSetShader(renderData->p_Shader->m_PixelShader.Get(), nullptr, 0u);
		Locator::GetD3D()->GetDeviceContext()->VSSetShader(renderData->p_Shader->m_VertexShader.Get(), nullptr, 0u);
	}
	else
	{
		Locator::GetD3D()->GetDeviceContext()->PSSetShader(Locator::GetResources()->up_ShaderMap[ShaderType::DEFAULT]->m_PixelShader.Get(), nullptr, 0u);
		Locator::GetD3D()->GetDeviceContext()->VSSetShader(Locator::GetResources()->up_ShaderMap[ShaderType::DEFAULT]->m_VertexShader.Get(), nullptr, 0u);
	}

	Locator::GetD3D()->GetDeviceContext()->IASetInputLayout(renderData->p_Shader->m_InputLayout.Get());

	Locator::GetD3D()->GetDeviceContext()->IASetPrimitiveTopology(renderData->m_Topolgy);

	/*******************************************/

	/*******	OPTIONAL	********************/

	if(renderData->up_LightBuffer)
		Locator::GetD3D()->GetDeviceContext()->PSSetConstantBuffers(0, 1, renderData->up_LightBuffer->m_Buffer.GetAddressOf());

	if (renderData->p_Texture)
	{
		Locator::GetD3D()->GetDeviceContext()->PSSetShaderResources(0u, 1u, renderData->p_Texture->m_TextureView.GetAddressOf());
		Locator::GetD3D()->GetDeviceContext()->PSSetSamplers(0, 1, renderData->p_Texture->m_SampleState.GetAddressOf());
	}

	/*******************************************/

	if (renderData->m_DrawInstanced)
	{
		if (renderData->m_DrawIndexed)
			Locator::GetD3D()->GetDeviceContext()->DrawIndexedInstanced(renderData->m_IndexCount, renderData->up_InstanceData->instanceCount, 0u, 0u, 0u);
	}
	else
	{
		if (renderData->m_DrawIndexed)
			Locator::GetD3D()->GetDeviceContext()->DrawIndexed(renderData->m_IndexCount, 0u, 0u);
	}

}

void Graphics::BeginFrame() noexcept
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();

	const float colour[] = { Locator::GetMisc()->GetClearColour().x,
		Locator::GetMisc()->GetClearColour().y,
		Locator::GetMisc()->GetClearColour().z,
		Locator::GetMisc()->GetClearColour().w };
	d3d->GetDeviceContext()->ClearRenderTargetView( pTargetView.Get(),colour );
	d3d->GetDeviceContext()->ClearDepthStencilView( pDepStenView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::EndFrame()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


	//HRESULT hr;
	d3d->GetSwapChain()->Present(1u, 0u);
}
