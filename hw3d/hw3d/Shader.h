#pragma once

#include "Constants.h"

#include <d3d11.h>
#include <string>
#include <map>
#include <vector>
#include <wrl.h>

struct Shaders
{
	HRESULT Create(const std::string& shader);

	HRESULT Create(const std::string& shader, bool instancing);

	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout;
};

