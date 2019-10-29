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

	int mObjNum = 2;

	std::unique_ptr<Camera> mCam;
	std::vector<Model> mGObjects;
};