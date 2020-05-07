#pragma once

#include "Constants.h"
#include "DataConstants.h"
#include "Shader.h"
#include "Texture.h"
#include "Vertices.h"
#include "Buffer.h"

#include <vector>
#include <map>
#include <string>
#include <memory>

enum DataTypes {
	MODELS = 0,
	TEXTURES = 1,
	SHADERS = 2,
};

struct ResourceData
{
	ResourceData();

	bool LoadMeshData(const std::string& meshName);

	bool LoadImageData(std::string image);

	std::map<std::string, ImageData> m_ImageData;
	std::map<std::string, Meshes> m_MeshData;
	std::map<ShaderType, std::string> m_ShaderIDMap;
	std::map<std::string, ShaderType> m_StrToShaderIDMap;
	std::map<TextureType, std::string> m_TextureIDMap;
	std::map<std::string, TextureType> m_StrToTextureIDMap;
	std::map<ModelType, std::string> m_ModelIDMap;
	std::map<std::string, ModelType> m_StrToModelIDMap;

};

struct Resources
{
	Resources() = default;
	~Resources();

	ResourceData m_Data;
	void LoadResources();

	std::map<ShaderType, std::unique_ptr<Shaders>> up_ShaderMap;
	std::map<TextureType, std::unique_ptr<Texture>> up_TextureMap;
	std::map<ModelType, std::unique_ptr<Buffer>> up_VerticesMap;
	std::map<ModelType, std::unique_ptr<Buffer>> up_IndicesMap;
};
