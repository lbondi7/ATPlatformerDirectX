#pragma once
#include "Scene.h"

class MenuScene :
	public Scene
{
public:
	~MenuScene() override;

	bool Init() override;
	Scene::CurrentScene Update() override;
	void Render() override;

private:

	enum class ChangeScene : int
	{
		NONE = 0,
		GAME = 1
	};

	ChangeScene changeScene = ChangeScene::NONE;

};

