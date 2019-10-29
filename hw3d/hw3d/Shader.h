#pragma once
#include <d3d11.h>
#include <string>
#include <map>
#include <vector>

class Shader
{
public:
	Shader() = default;
	~Shader() = default;

	HRESULT CreateShader(const std::string& shader);

	ID3D11PixelShader*& GetPixelShader(const std::string& shader);
	ID3D11VertexShader*& GetVertexShader(const std::string& shader);
	ID3D11InputLayout*& GetInputLayout(const std::string& shader);

private:

	std::vector<ID3D11PixelShader*> pPixelShaders;
	std::vector<ID3D11VertexShader*> pVertexShaders;
	std::vector<ID3D11InputLayout*> pInputLayouts;

	std::map<std::string, int> shaderMap;
	int shaderCount = 0;
};

