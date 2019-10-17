#pragma once
#include "Scene.h"

#include <memory>

class SceneManager
{
public:

	bool Init();
	void Update();
	void Render();

private:

	std::unique_ptr<Scene> activeScene;

	enum class CurrentScene : int {
		MENU = 0,
		GAME = 1,
	};

	CurrentScene currentScene = CurrentScene::MENU;

};

