#pragma once
#include "Window.h"
#include "Timer.h"

class Game
{
public:
	Game();

	bool Init();
	int Run();
	void Update();
	void Exit();

private:
	Window* wnd = nullptr;
	Timer timer;
};

