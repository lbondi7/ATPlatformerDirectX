#pragma once
#include "Window.h"
#include "Timer.h"
#include "SceneManager.h"

class Game
{
public:
	Game();

	bool Init();
	void Run();
	void Exit();

private:
	void Update();
	Window* window = nullptr;
	Timer timer;
	std::unique_ptr<SceneManager> sceneManager;
};

