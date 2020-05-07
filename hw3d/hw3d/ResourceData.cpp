#include "ResourceData.h"
#include "nlohmann/json.hpp"

#include <fstream>
#include <algorithm>
#include <set>

ResourceData::ResourceData()
{
}

bool ResourceData::LoadMeshData(const std::string& meshName)
{

	m_MeshData.emplace(meshName, Meshes());

	std::vector<Float3> positions;
	std::vector<Float2> texCoords;
	std::vector<Float3> normals;
	std::vector<Int3> faces;
	int vertPerFace = 3;
	bool skip = false;
	std::fstream file;
	file.open("Data/models/" + meshName + ".obj");
	bool hasUV = false;
	bool hasNorm = false;
	if (file.is_open())
	{
		char lineChar;
		while (!file.eof())
		{
			file.get(lineChar);
			skip = false;
			if (lineChar == 'v')
			{
				file.get(lineChar);
				switch (lineChar)
				{
				case ' ':
				{
					Float3 position;
					file >> position.x >> position.y >> position.z;
					positions.push_back(position);
					break;
				}
				case 't':
				{
					hasUV = true;
					Float2 uv;
					file.get(lineChar);

					if (lineChar != ' ') break;

					file >> uv.x >> uv.y;
					texCoords.push_back({1 - uv.x, 1 - uv.y });
					break;
				}
				case 'n':
				{
					hasNorm = true;
					Float3 normal;
					file.get(lineChar);

					if (lineChar != ' ') break;

					file >> normal.x >> normal.y >> normal.z;
					normals.push_back(normal);
					break;
				}
				}
			}
			else if (lineChar == 'f')
			{
				file.get(lineChar);
				if (lineChar == ' ')
				{
					for (size_t i = 0; i < vertPerFace; i++)
					{
						Int3 face;
						file >> face.x;

						file.get(lineChar);

						if (hasUV) file >> face.y;
						else face.y = -1;

						file.get(lineChar);

						if (hasNorm) file >> face.z;
						else face.z = -1;

						faces.push_back(face);
					}
				}
			}
		}
		file.close();
	}
	m_MeshData[meshName].vectors = positions;
	std::vector<Vertex> uniqueVertices = {};
	std::vector<uint32_t> uniqueIndices = {};

	int i = 0;
	for (auto& f : faces)
	{
		Vertex vertex;
		vertex.position = positions[f.x - 1];
		vertex.texCoord = texCoords[f.y - 1];
		vertex.normal = normals[f.z - 1];

		int place = 0;
		int count = 0;
		for (int i = 0; i < uniqueVertices.size(); ++i)
		{
			if (uniqueVertices[i] == vertex)
			{
				++count;
				place = i;
				break;
			}
		}
		if (count == 0)
		{
			uniqueVertices.emplace_back(vertex);
			uniqueIndices.emplace_back(static_cast<uint32_t>(m_MeshData[meshName].vertices.size()));
			m_MeshData[meshName].vertices.push_back(vertex);
			place = uniqueVertices.size() - 1;
		}

		m_MeshData[meshName].indices.emplace_back(uniqueIndices[place]);
	}
	m_MeshData[meshName].indexCount = m_MeshData[meshName].indices.size();
	m_MeshData[meshName].vertexCount = m_MeshData[meshName].vertices.size();

	return true;
}

bool ResourceData::LoadImageData(std::string image)
{
	//ImageData img;
	//images.emplace(image + "_padding", ImageData());
	FILE* filePtr;

	ImageData imageData;
	// Open the targa file for reading in binary.
	if (fopen_s(&filePtr, ("Data//textures//" + image + ".tga").c_str(), "rb") != 0)
		return false;

	// Read in the file header.
	auto error = static_cast<int>(fread(&imageData.buffer, sizeof(ImageDataBuffer), 1, filePtr));
	if (error != 1)
		return false;

	m_ImageData.emplace(image, imageData);

	// Check that it is 32 bit and not 24 bit.
	if (static_cast<int>(m_ImageData[image].buffer.bpp) != 32)
		return false;

	// Get the important information from the header.
	auto height = static_cast<int>(imageData.buffer.height);
	auto width = static_cast<int>(imageData.buffer.width);

	// Calculate the size of the 32 bit image data.
	int imageSize = width * height * 4;

	// Allocate memory for the targa image data.
	unsigned char* targaImage = new unsigned char[imageSize];
	if (!targaImage)
		return false;

	// Read in the targa image data.
	auto kool = (int)fread(targaImage, 1, imageSize, filePtr);
	if (kool != imageSize)
		return false;

	// Close the file.
	if (fclose(filePtr) != 0)
		return false;

    // Allocate memory for the targa destination data.
	m_ImageData[image].data = new unsigned char[imageSize];
	if (!m_ImageData[image].data)
		return false;

	// Initialize the index into the targa destination data array.
	int index = 0;

	// Initialize the index into the targa image data.
	int k = (width * height * 4) - (width * 4);

	// Now copy the targa image data into the targa destination array in the correct order since the targa format is stored upside down.
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			m_ImageData[image].data[index + 0] = targaImage[k + 2]; // Red.
			m_ImageData[image].data[index + 1] = targaImage[k + 1]; // Green.
			m_ImageData[image].data[index + 2] = targaImage[k + 0]; // Blue
			m_ImageData[image].data[index + 3] = targaImage[k + 3]; // Alpha

			// Increment the indexes into the targa data.
			k += 4;
			index += 4;
		}

		// Set the targa image data index back to the preceding row at the beginning of the column since its reading it in upside down.
		k -= (width * 8);
	}

	// Release the targa image data now that it was copied into the destination array.
	delete[] targaImage;
	targaImage = nullptr;

	return true;
}



Resources::~Resources()
{
	up_ShaderMap.clear();
	up_TextureMap.clear();
}

void Resources::LoadResources()
{

	nlohmann::json resourcesJson;
	std::ifstream resources_data("Data/resources.json");
	resources_data >> resourcesJson;
	int modelCount = resourcesJson["Model Count"];
	int textureCount = resourcesJson["Texture Count"];
	int shaderCount = resourcesJson["Shader Count"];

	int maxCount = max(modelCount, max(textureCount, shaderCount));

	for (int i = 0; i < maxCount; ++i)
	{
		if (i < modelCount)
		{
			m_Data.LoadMeshData(resourcesJson["Models"][i]);
			m_Data.m_ModelIDMap.emplace(static_cast<ModelType>(i), resourcesJson["Models"][i]);
			m_Data.m_StrToModelIDMap.emplace(resourcesJson["Models"][i], static_cast<ModelType>(i));
			up_VerticesMap.emplace(static_cast<ModelType>(i), std::make_unique<Buffer>());
			up_VerticesMap[static_cast<ModelType>(i)]->CreateBuffer(D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DEFAULT, 0u,
				m_Data.m_MeshData[m_Data.m_ModelIDMap[static_cast<ModelType>(i)]].vertices.data(), 
				m_Data.m_MeshData[m_Data.m_ModelIDMap[static_cast<ModelType>(i)]].vertexCount *
				sizeof(Vertex), sizeof(Vertex));
			up_IndicesMap.emplace(static_cast<ModelType>(i), std::make_unique<Buffer>());
			up_IndicesMap[static_cast<ModelType>(i)]->CreateBuffer(D3D11_BIND_INDEX_BUFFER, D3D11_USAGE_DEFAULT, 0u,
				m_Data.m_MeshData[m_Data.m_ModelIDMap[static_cast<ModelType>(i)]].indices.data(),
				m_Data.m_MeshData[m_Data.m_ModelIDMap[static_cast<ModelType>(i)]].indexCount *
				sizeof(unsigned short), sizeof(unsigned short));
		}

		if (i < textureCount)
		{
			m_Data.LoadImageData(resourcesJson["Textures"][i]);
			m_Data.m_TextureIDMap.emplace(static_cast<TextureType>(i), resourcesJson["Textures"][i]);
			m_Data.m_StrToTextureIDMap.emplace(resourcesJson["Textures"][i], static_cast<TextureType>(i));
			up_TextureMap.emplace(static_cast<TextureType>(i), std::make_unique<Texture>());
			up_TextureMap[static_cast<TextureType>(i)]->CreateTexture(m_Data.m_ImageData[m_Data.m_TextureIDMap[static_cast<TextureType>(i)]]);
		}

		if (i < shaderCount)
		{
			m_Data.m_ShaderIDMap.emplace(static_cast<ShaderType>(i), resourcesJson["Shaders"][i]);
			m_Data.m_StrToShaderIDMap.emplace(resourcesJson["Shaders"][i], static_cast<ShaderType>(i));
			up_ShaderMap.emplace(static_cast<ShaderType>(i), std::make_unique<Shaders>());
			up_ShaderMap[static_cast<ShaderType>(i)]->Create(m_Data.m_ShaderIDMap[static_cast<ShaderType>(i)], i == 3);
		}
	}
}
