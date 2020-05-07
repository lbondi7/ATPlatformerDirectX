#pragma once

#include "DataConstants.h"

#include <d3d11.h>
#include <string>
#include <map>
#include <vector>
#include <wrl.h>

struct Texture
{
	HRESULT CreateTexture(const ImageData& image);
	
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_Texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TextureView;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_SampleState;

};