#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"

class LevelEditorScene : public Scene
{
public:

	~LevelEditorScene();

	bool Init() override;
	Scene::CurrentScene Update() override;
	void Render() override;

	void SaveLevel();

private:
	enum class ChangeScene : int
	{
		NONE = 0,
		MENU = 1
	};

	ChangeScene changeScene = ChangeScene::NONE;

	std::vector<GameObject*> p_GameObjects;
	GameObject* p_ActiveGO;


	std::unique_ptr<Camera> up_Cam;

	char p_LevelName[20];

};

