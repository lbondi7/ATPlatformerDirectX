#pragma once
#include "Scene.h"
#include "Model.h"
#include "Camera.h"

#include <memory>
#include <vector>
#include <thread>


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

	int cubeAmount = 1000;

	std::unique_ptr<Model> model;
	std::unique_ptr<Model> model2;
	std::unique_ptr<Model> model3;
	std::unique_ptr<Model> model4;
	std::unique_ptr<Camera> cam;
	std::vector<Model> cubes;
	std::vector<Model> sqs;
	std::vector<Model> tris;
};