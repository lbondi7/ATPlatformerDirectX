#include "LevelLoader.h"
#include "nlohmann/json.hpp"

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
	std::ifstream shape_file("Data//levels//Level1.json");
	shape_file >> shapeJson;
	numberOfObjects = shapeJson["Object Count"];

	objects.resize(numberOfObjects);
	for (size_t i = 0; i < numberOfObjects; i++)
	{
		auto object = shapeJson["Objects"][std::to_string(i)];
		objects[i] = new GameObject();
		objects[i]->Init(object["Model"]);
		objects[i]->AddModel();
		objects[i]->GetModel()->ModelType(object["Model"]);
		objects[i]->GetModel()->Texture(object["Texture"]);
		objects[i]->GetTransform().SetScale(object["Scale"][0], object["Scale"][1], object["Scale"][2]);
		objects[i]->GetTransform().SetPos(object["Position"][0], object["Position"][1], object["Position"][2]);
		objects[i]->SetTag(tags[object["Tag"]]);
	}
}
