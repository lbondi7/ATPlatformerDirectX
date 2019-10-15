#include "Graphics.h"
#include "dxerr.h"
#include "Timer.h"
#include "Locator.h"

#include <sstream>
#include <d3dcompiler.h>
#include <DirectXMath.h>

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

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
	GRAPHICS_THROW_INFO( D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pDeviceContext
	) );
	// gain access to texture subresource in swap chain (back buffer)
	wrl::ComPtr<ID3D11Resource> pBackBuffer;
	GRAPHICS_THROW_INFO( pSwap->GetBuffer( 0,__uuidof(ID3D11Resource),&pBackBuffer ) );
	GRAPHICS_THROW_INFO( pDevice->CreateRenderTargetView( pBackBuffer.Get(),nullptr,&pTargetView ) );

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	wrl::ComPtr<ID3D11DepthStencilState> pDDState;
	GRAPHICS_THROW_INFO(pDevice->CreateDepthStencilState(&dsDesc, &pDDState));

	pDeviceContext->OMSetDepthStencilState(pDDState.Get(), 1u);

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

	GRAPHICS_THROW_INFO(pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil));


	D3D11_DEPTH_STENCIL_VIEW_DESC descDepStenView = {};
	descDepStenView.Format = DXGI_FORMAT_D32_FLOAT;
	descDepStenView.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDepStenView.Texture2D.MipSlice = 0u;
	GRAPHICS_THROW_INFO(pDevice->CreateDepthStencilView(pDepthStencil.Get(), &descDepStenView, &pDepStenView));

	// bind render target
	pDeviceContext->OMSetRenderTargets(1u, pTargetView.GetAddressOf(), pDepStenView.Get());
}

void Graphics::EndFrame()
{
	HRESULT hr;
#ifndef NDEBUG
	infoManager.Set();
#endif
	if( FAILED( hr = pSwap->Present( 1u,0u ) ) )
	{
		if( hr == DXGI_ERROR_DEVICE_REMOVED )
		{
			throw GRAPHICS_DEVICE_REMOVED_EXCEPT( pDevice->GetDeviceRemovedReason() );
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
	pDeviceContext->ClearRenderTargetView( pTargetView.Get(),color );
	pDeviceContext->ClearDepthStencilView(pDepStenView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::DrawTestTriangle(float _angle, float x, float z)
{
	HRESULT hr;

	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		} pos;
	};

	struct ConstantBuffer
	{
		dx::XMMATRIX transform;
	};

	static float angle = _angle;
	angle += 1000.0f * Locator::GetTimer()->DeltaTime();
	ConstantBuffer cb
	{
		dx::XMMatrixTranspose(
			dx::XMMatrixRotationX(angle * 2)*
			dx::XMMatrixRotationY(angle * 3) *
			dx::XMMatrixRotationZ(angle * 5)*
			dx::XMMatrixTranslation(x, 0.0f, z) *
			dx::XMMatrixPerspectiveFovLH(1.0f, 1.0f, 0.5f, 1000.0f)
		)
	};

	wrl::ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC cbd = {};
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0u;
	cbd.ByteWidth = sizeof(cb);
	cbd.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;
	GRAPHICS_THROW_INFO(pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer));

	pDeviceContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());

	struct ConstantBuffer2
	{
		struct
		{
			float r;
			float g;
			float b;
			float a;
		}face_colours[6];
	};

	const ConstantBuffer2 cb2
	{
		{
			{1.0f, 0.0f, 0.0f},
			{0.0f, 1.0f, 0.0f},
			{0.0f, 0.0f, 1.0f},
			{1.0f, 1.0f, 0.0f},
			{1.0f, 0.0f, 1.0f},
			{0.0f, 1.0f, 1.0f},
		}
	};
	wrl::ComPtr<ID3D11Buffer> pConstantBuffer2;
	D3D11_BUFFER_DESC cbd2 = {};
	cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd2.Usage = D3D11_USAGE_DEFAULT;
	cbd2.CPUAccessFlags = 0u;
	cbd2.MiscFlags = 0u;
	cbd2.ByteWidth = sizeof(cb2);
	cbd2.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd2 = {};
	csd2.pSysMem = &cb2;
	GRAPHICS_THROW_INFO(pDevice->CreateBuffer(&cbd2, &csd2, &pConstantBuffer2));

	pDeviceContext->PSSetConstantBuffers(0u, 1u, pConstantBuffer2.GetAddressOf());

	// create vertex buffer (1 2d triangle at center of screen)
	Vertex vertices[] =
	{
		{ -0.5f,-0.5f,-0.5f},
		{ -0.5f,0.5f,-0.5f,},
		{ 0.5f,0.5f,-0.5f,},
		{ 0.5f,-0.5f,-0.5f,},
		{ 0.5f,-0.5f,0.5f,},
		{ 0.5f,0.5f,0.5f,},
		{ -0.5f,0.5f,0.5f,},
		{ -0.5f,-0.5f,0.5f,},
	};
	wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC vbd = {};
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.Usage = D3D11_USAGE_DEFAULT;
	vbd.CPUAccessFlags = 0u;
	vbd.MiscFlags = 0u;
	vbd.ByteWidth = sizeof( vertices );
	vbd.StructureByteStride = sizeof( Vertex );
	D3D11_SUBRESOURCE_DATA vsd = {};
	vsd.pSysMem = vertices;
	GRAPHICS_THROW_INFO( pDevice->CreateBuffer( &vbd,&vsd,&pVertexBuffer ) );
	
	// Bind vertex buffer to pipeline
	const UINT stride = sizeof( Vertex );
	const UINT offset = 0u;
	pDeviceContext->IASetVertexBuffers( 0u,1u,pVertexBuffer.GetAddressOf(),&stride,&offset );


	// create index buffer
	const unsigned short indices[] =
	{
		0,1,2,	0,2,3,
		3,2,5,	3,5,4,
		4,5,6,	4,6,7,
		7,6,1,	7,1,0,
		1,6,5,	1,5,2,
		7,0,3,	7,3,4,
	};
	wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;
	ibd.ByteWidth = sizeof( indices );
	ibd.StructureByteStride = sizeof( unsigned short );
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;
	GRAPHICS_THROW_INFO( pDevice->CreateBuffer( &ibd,&isd,&pIndexBuffer ) );

	// bind index buffer
	pDeviceContext->IASetIndexBuffer( pIndexBuffer.Get(),DXGI_FORMAT_R16_UINT,0u );

	// create pixel shader
	wrl::ComPtr<ID3D11PixelShader> pPixelShader;
	wrl::ComPtr<ID3DBlob> pBlob;
	GRAPHICS_THROW_INFO( D3DReadFileToBlob( L"PixelShader.cso",&pBlob ) );
	GRAPHICS_THROW_INFO( pDevice->CreatePixelShader( pBlob->GetBufferPointer(),pBlob->GetBufferSize(),nullptr,&pPixelShader ) );

	// bind pixel shader
	pDeviceContext->PSSetShader( pPixelShader.Get(),nullptr,0u );

	// create vertex shader
	wrl::ComPtr<ID3D11VertexShader> pVertexShader;
	GRAPHICS_THROW_INFO( D3DReadFileToBlob( L"VertexShader.cso",&pBlob ) );
	GRAPHICS_THROW_INFO( pDevice->CreateVertexShader( pBlob->GetBufferPointer(),pBlob->GetBufferSize(),nullptr,&pVertexShader ) );

	// bind vertex shader
	pDeviceContext->VSSetShader( pVertexShader.Get(),nullptr,0u );
		

	// input (vertex) layout (2d position only)
	wrl::ComPtr<ID3D11InputLayout> pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
	};
	GRAPHICS_THROW_INFO( pDevice->CreateInputLayout(
		ied,(UINT)std::size( ied ),
		pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(),
		&pInputLayout
	) );

	// bind vertex layout
	pDeviceContext->IASetInputLayout( pInputLayout.Get() );


	// Set primitive topology to triangle list (groups of 3 vertices)
	pDeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );


	// configure viewport
	D3D11_VIEWPORT viewport;
	viewport.Width = 500;
	viewport.Height = 500;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	pDeviceContext->RSSetViewports( 1u,&viewport );


	GRAPHICS_THROW_INFO_ONLY( pDeviceContext->DrawIndexed( (UINT)std::size( indices ),0u,0u ) );
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
