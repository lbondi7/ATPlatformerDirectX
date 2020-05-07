#include "LevelLoader.h"
#include "nlohmann/json.hpp"
#include "Locator.h"
#include "ResourceData.h"

#include <map>
#include <fstream>

void LevelLoader::LoadObjects(std::vector<GameObject*>& objects)
{

	std::map<std::string, GameObjectTag> tags;
	tags["player"] = GameObjectTag::PLAYER;
	tags["ground"] = GameObjectTag::GROUND;
	tags["static"] = GameObjectTag::STATIC;
	tags["killbox"] = GameObjectTag::KILLBOX;
	tags["moveable"] = GameObjectTag::MOVEABLE;


	int numberOfObjects;
	nlohmann::json shapeJson;
	std::ifstream shape_file("Data/levels/Level1.json");
	shape_file >> shapeJson;
	numberOfObjects = shapeJson["Object Count"];

	objects.resize(numberOfObjects);
	for (size_t i = 0; i < numberOfObjects; ++i)
	{
		auto object = shapeJson["Objects"][std::to_string(i)];
		objects[i] = new GameObject();
		objects[i]->Init(Locator::GetResources()->m_Data.m_StrToModelIDMap[object["Model"]],
			Locator::GetResources()->m_Data.m_StrToTextureIDMap[object["Texture"]],
			Locator::GetResources()->m_Data.m_StrToShaderIDMap[object["Shader"]]);
		objects[i]->AddModel();
		if (object["Instanced"])
		{
			auto instanceCount = object["InstCount"];
			std::vector<Vec4> positions;
			float x, y, z;
			for (size_t j = 0; j < instanceCount; ++j)
			{
				x = object["InstPositions"][std::to_string(j)][0];
				y = object["InstPositions"][std::to_string(j)][1];
				z = object["InstPositions"][std::to_string(j)][2];
				DirectX::XMVECTOR vec = {x, y, z, 1.0f};
				positions.emplace_back(vec);
			}

			objects[i]->InitInstance(instanceCount, positions);
		}
		objects[i]->GetTransform().SetScale(object["Scale"][0], object["Scale"][1], object["Scale"][2]);
		objects[i]->GetTransform().SetRot(object["Rotation"][0], object["Rotation"][1], object["Rotation"][2]);
		objects[i]->GetTransform().SetPos(object["Position"][0], object["Position"][1], object["Position"][2]);
	}
}
