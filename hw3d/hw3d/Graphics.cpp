#include "Graphics.h"
#include "dxerr.h"
#include "Timer.h"
#include "Locator.h"

#include <sstream>
#include <D3Dcompiler.h>
#include <DirectXMath.h>

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

#define BF Locator::GetBuffers()

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

// graphics exception checking/throwing macros (some with dxgi infos)
#define GRAPHICS_EXCEPT_NOINFO(hr) Graphics::HrException( __LINE__,__FILE__,(hr) )
#define GRAPHICS_THROW_NOINFO(hrcall) if( FAILED( hr = (hrcall) ) ) throw Graphics::HrException( __LINE__,__FILE__,hr )

#ifndef NDEBUG
#define GRAPHICS_EXCEPT(hr) Graphics::HrException( __LINE__,__FILE__,(hr),infoManager.GetMessages() )
#define GRAPHICS_THROW_INFO(hrcall) infoManager.Set(); if( FAILED( hr = (hrcall) ) ) throw GRAPHICS_EXCEPT(hr)
#define GRAPHICS_DEVICE_REMOVED_EXCEPT(hr) Graphics::DeviceRemovedException( __LINE__,__FILE__,(hr),infoManager.GetMessages() )
#define GRAPHICS_THROW_INFO_ONLY(call) infoManager.Set(); (call); {auto v = infoManager.GetMessages(); if(!v.empty()) {throw Graphics::InfoException( __LINE__,__FILE__,v);}}
#else
#define GRAPHICS_EXCEPT(hr) Graphics::HrException( __LINE__,__FILE__,(hr) )
#define GRAPHICS_THROW_INFO(hrcall) GRAPHICS_THROW_NOINFO(hrcall)
#define GRAPHICS_DEVICE_REMOVED_EXCEPT(hr) Graphics::DeviceRemovedException( __LINE__,__FILE__,(hr) )
#define GRAPHICS_THROW_INFO_ONLY(call) (call)
#endif

Graphics::Graphics( HWND hWnd )
{
	// for checking results of d3d functions
	HRESULT hr;

	d3d = std::make_unique<D3D>();
	GRAPHICS_THROW_INFO( d3d->Init(hWnd));
	Locator::InitD3D(d3d.get());

	// gain access to texture subresource in swap chain (back buffer)
	wrl::ComPtr<ID3D11Resource> pBackBuffer;
	GRAPHICS_THROW_INFO( d3d->GetSwapChain()->GetBuffer( 0,__uuidof(ID3D11Resource),&pBackBuffer ) );
	GRAPHICS_THROW_INFO( d3d->GetDevice()->CreateRenderTargetView( pBackBuffer.Get(),nullptr,&pTargetView ) );

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	wrl::ComPtr<ID3D11DepthStencilState> pDDState;
	GRAPHICS_THROW_INFO(d3d->GetDevice()->CreateDepthStencilState(&dsDesc, &pDDState));

	d3d->GetDeviceContext()->OMSetDepthStencilState(pDDState.Get(), 1u);

	wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = 500u;
	descDepth.Height = 500u;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	GRAPHICS_THROW_INFO(d3d->GetDevice()->CreateTexture2D(&descDepth, nullptr, &pDepthStencil));


	D3D11_DEPTH_STENCIL_VIEW_DESC descDepStenView = {};
	descDepStenView.Format = DXGI_FORMAT_D32_FLOAT;
	descDepStenView.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDepStenView.Texture2D.MipSlice = 0u;
	GRAPHICS_THROW_INFO(d3d->GetDevice()->CreateDepthStencilView(pDepthStencil.Get(), &descDepStenView, &pDepStenView));

	// bind render target
	d3d->GetDeviceContext()->OMSetRenderTargets(1u, pTargetView.GetAddressOf(), pDepStenView.Get());


	// configure viewport
	D3D11_VIEWPORT viewport;
	viewport.Width = 500;
	viewport.Height = 500;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	d3d->GetDeviceContext()->RSSetViewports(1u, &viewport);

	Locator::GetBuffers()->CreateBuffer("cube");
	Locator::GetBuffers()->CreateBuffer("triangle");
	Locator::GetBuffers()->CreateBuffer("square");

	//rasterDesc.AntialiasedLineEnable = false;
	//rasterDesc.CullMode = D3D11_CULL_BACK;
	//rasterDesc.DepthBias = 0;
	//rasterDesc.DepthBiasClamp = 0.0f;
	//rasterDesc.DepthClipEnable = true;
	//rasterDesc.FillMode = D3D11_FILL_SOLID;
	//rasterDesc.FrontCounterClockwise = false;
	//rasterDesc.MultisampleEnable = false;
	//rasterDesc.ScissorEnable = false;
	//rasterDesc.SlopeScaledDepthBias = 0.0f;

	//// Create the rasterizer state from the description we just filled out.
	//result = m_device->CreateRasterizerState(&rasterDesc, &m_rasterState);
	//if (FAILED(result))
	//{
	//	return false;
	//}

	//// Now set the rasterizer state.
	//m_deviceContext->RSSetState(m_rasterState);
}

void Graphics::EndFrame()
{
	HRESULT hr;
#ifndef NDEBUG
	infoManager.Set();
#endif
	if( FAILED( hr = d3d->GetSwapChain()->Present( 1u,0u ) ) )
	{
		if( hr == DXGI_ERROR_DEVICE_REMOVED )
		{
			throw GRAPHICS_DEVICE_REMOVED_EXCEPT(d3d->GetDevice()->GetDeviceRemovedReason() );
		}
		else
		{
			throw GRAPHICS_EXCEPT( hr );
		}
	}
}

void Graphics::ClearBuffer( float r,float g,float b , float a) noexcept
{
	const float color[] = { r, g, b, a };
	d3d->GetDeviceContext()->ClearRenderTargetView( pTargetView.Get(),color );
	d3d->GetDeviceContext()->ClearDepthStencilView( pDepStenView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::DrawGeometry(HRESULT hr)
{

	GRAPHICS_THROW_INFO(hr);

	//HRESULT hr;


	//struct ConstantBuffer
	//{
	//	dx::XMMATRIX transform;
	//};

	//static float angle = _angle;
	//angle += 100.0f * Locator::GetTimer()->DeltaTime();
	//ConstantBuffer cb
	//{
	//	dx::XMMatrixTranspose(
	//		dx::XMMatrixRotationX(angle)*
	//		dx::XMMatrixRotationY(angle) *
	//		dx::XMMatrixRotationZ(angle)*
	//		dx::XMMatrixTranslation(x, 0.0f, 2) *
	//		dx::XMMatrixPerspectiveFovLH(1.0f, 1.0f, 0.5f, 1000.0f)
	//	)
	//};

	//wrl::ComPtr<ID3D11Buffer> pConstantBuffer;
	//D3D11_BUFFER_DESC cbd = {};
	//cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//cbd.Usage = D3D11_USAGE_DYNAMIC;
	//cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//cbd.MiscFlags = 0u;
	//cbd.ByteWidth = sizeof(cb);
	//cbd.StructureByteStride = 0u;
	//D3D11_SUBRESOURCE_DATA csd = {};
	//csd.pSysMem = &cb;
	//GRAPHICS_THROW_INFO(d3d->GetDevice()->CreateBuffer(&cbd, &csd, &pConstantBuffer));

	//d3d->GetDeviceContext()->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());

	//model->Render();

	 //create pixel shader

	//Locator::GetGraphics()->GetD3D()->GetDeviceContext()->IASetVertexBuffers(
	//	0u, 
	//	1u, 
	//	&Locator::GetBuffers()->GetVertexBuffer(shapeName), 
	//	&Locator::GetBuffers()->GetStride(shapeName), 
	//	&Locator::GetBuffers()->GetOffset(shapeName));

	//// bind index buffer
	//Locator::GetGraphics()->GetD3D()->GetDeviceContext()->IASetIndexBuffer(
	//	Locator::GetBuffers()->GetIndexBuffer(shapeName), 
	//	DXGI_FORMAT_R16_UINT, 
	//	0u);

	//wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	//wrl::ComPtr<ID3DBlob> pBlob;
	//GRAPHICS_THROW_INFO( D3DReadFileToBlob( L"PixelShader.cso",&pBlob ) );
	//GRAPHICS_THROW_INFO( d3d->GetDevice()->CreatePixelShader( pBlob->GetBufferPointer(),pBlob->GetBufferSize(),nullptr,&pPixelShader ) );

	//// bind pixel shader
	//d3d->GetDeviceContext()->PSSetShader( pPixelShader.Get(),nullptr,0u );

	// create vertex shader
	//wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	//GRAPHICS_THROW_INFO( D3DReadFileToBlob( L"VertexShader.cso",&pBlob ) );
	//GRAPHICS_THROW_INFO( d3d->GetDevice()->CreateVertexShader( pBlob->GetBufferPointer(),pBlob->GetBufferSize(),nullptr,&pVertexShader ) );

	//// bind vertex shader
	//d3d->GetDeviceContext()->VSSetShader( pVertexShader.Get(),nullptr,0u );
		

	//// input (vertex) layout (2d position only)
	//wrl::ComPtr<ID3D11InputLayout> pInputLayout;
	//const D3D11_INPUT_ELEMENT_DESC ied[] =
	//{
	//	{ "SV_Position",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
	//	{ "Color",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0 },
	//};
	//GRAPHICS_THROW_INFO( d3d->GetDevice()->CreateInputLayout(
	//	ied,(UINT)std::size( ied ),
	//	pBlob->GetBufferPointer(),
	//	pBlob->GetBufferSize(),
	//	&pInputLayout
	//) );

	//// bind vertex layout
	//d3d->GetDeviceContext()->IASetInputLayout( pInputLayout.Get() );


	// Set primitive topology to triangle list (groups of 3 vertices)
	//d3d->GetDeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	//GRAPHICS_THROW_INFO_ONLY( d3d->GetDeviceContext()->DrawIndexed( (UINT)Locator::GetBuffers()->GetIndeciesSize(shapeName),0u,0u ) );
	//d3d->GetDeviceContext()->Draw((UINT)Locator::GetBuffers()->GetIndeciesSize(shapeName), 0u);
}

D3D* Graphics::GetD3D()
{
	return d3d.get();
}


// Graphics exception stuff
Graphics::HrException::HrException( int line,const char * file,HRESULT hr,std::vector<std::string> infoMsgs ) noexcept
	:
	Exception( line,file ),
	hr( hr )
{
	// join all info messages with newlines into single string
	for( const auto& m : infoMsgs )
	{
		info += m;
		info.push_back( '\n' );
	}
	// remove final newline if exists
	if( !info.empty() )
	{
		info.pop_back();
	}
}

const char* Graphics::HrException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Error String] " << GetErrorString() << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl;
	if( !info.empty() )
	{
		oss << "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
	}
	oss << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Graphics::HrException::GetType() const noexcept
{
	return "Lewis Graphics Exception";
}

HRESULT Graphics::HrException::GetErrorCode() const noexcept
{
	return hr;
}

std::string Graphics::HrException::GetErrorString() const noexcept
{
	return DXGetErrorString( hr );
}

std::string Graphics::HrException::GetErrorDescription() const noexcept
{
	char buf[512];
	DXGetErrorDescription( hr,buf,sizeof( buf ) );
	return buf;
}

std::string Graphics::HrException::GetErrorInfo() const noexcept
{
	return info;
}


const char* Graphics::DeviceRemovedException::GetType() const noexcept
{
	return "Lewis Graphics Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
}
Graphics::InfoException::InfoException( int line,const char * file,std::vector<std::string> infoMsgs ) noexcept
	:
	Exception( line,file )
{
	// join all info messages with newlines into single string
	for( const auto& m : infoMsgs )
	{
		info += m;
		info.push_back( '\n' );
	}
	// remove final newline if exists
	if( !info.empty() )
	{
		info.pop_back();
	}
}


const char* Graphics::InfoException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "\n[Error Info]\n" << GetErrorInfo() << std::endl << std::endl;
	oss << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Graphics::InfoException::GetType() const noexcept
{
	return "Lewis Graphics Info Exception";
}

std::string Graphics::InfoException::GetErrorInfo() const noexcept
{
	return info;
}
