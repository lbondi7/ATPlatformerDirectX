#pragma once
#include "Scene.h"
#include "Model.h"
#include "Camera.h"

#include <memory>


class GameScene :
	public Scene
{
public:
	~GameScene() override;

	bool Init() override;
	Scene::CurrentScene Update() override;
	void Render() override;

private:
	enum class ChangeScene : int
	{
		NONE = 0,
		MENU = 1
	};

	ChangeScene changeScene = ChangeScene::NONE;

	std::unique_ptr<Model> model;
	std::unique_ptr<Model> model2;
	std::unique_ptr<Camera> cam;
	//std::vector<Model> models;
};