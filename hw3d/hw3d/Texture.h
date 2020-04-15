#pragma once

#include "Constants.h"

#include <d3d11.h>
#include <string>
#include <map>
#include <vector>
#include <wrl.h>

class Texture
{
public:
	Texture() = default;
	~Texture() = default;


	HRESULT CreateTextures(const std::string& texture);

	HRESULT CreateTexture(const ImageData& image);

	bool LoadTarga(char* filename, int& height, int& width);

	ID3D11ShaderResourceView*& GetTextureView(const std::string& texture);
	
	ID3D11SamplerState*& GetSampleState(const std::string& texture);
	

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_Texture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_TextureView;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_SampleState;

private:

	struct TargaHeader
	{
		unsigned char data[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};
	unsigned char* m_targaData;
	std::vector<ID3D11Texture2D*> mTextures;
	std::vector<ID3D11ShaderResourceView*> mTextureViews;
	std::vector<ID3D11SamplerState*> mSampleStates;

	std::map<std::string, int> textureMap;
	int textureCount = 0;

};

//class Textu
//{
//public:
//	Textu() = default;
//	~Textu() = default;
//
//
//	HRESULT CreateTextures(const std::string& texture);
//
//	bool LoadTarga(char* filename, int& height, int& width);
//
//	ID3D11ShaderResourceView*& GetTextureView(const std::string& texture);
//
//	ID3D11SamplerState*& GetSampleState(const std::string& texture);
//
//private:
//
//	struct TargaHeader
//	{
//		unsigned char data1[12];
//		unsigned short width;
//		unsigned short height;
//		unsigned char bpp;
//		unsigned char data2;
//	};
//	unsigned char* m_targaData;
//	std::vector<ID3D11Texture2D> mTextures;
//	std::vector<ID3D11ShaderResourceView*> mTextureViews;
//	std::vector<ID3D11SamplerState*> mSampleStates;
//
//	std::map<std::string, int> textureMap;
//	int textureCount = 0;
//
//};