#include "Game.h"
#include "Locator.h"
#include "Keyboard.h"
#include "Mouse.h"
#include <iomanip>
#include <thread>

Game::Game()
{
}

bool Game::Init()
{
	wnd = new Window(500, 500, "hello");

	Locator::InitKey(new Keyboard());
	Locator::InitMouse(new Mouse());
	bool exit = false;
	Locator::InitExitBool();
	Locator::GetKey()->Initialise();
	Locator::GetMouse()->Initialise();

	return true;
}

int Game::Run()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//if (const auto ecode = Window::ProcessMessages())
		//{
		//	return *ecode;
		//}
		Window::ProcessMessages();
		Update();
	}
	
	return 0;
}

void Game::Update()
{
	const float t = timer.Peek();
	wnd->SetWindowTitle("Seconds: " + std::to_string((int)t) + " - Delta Time: " + std::to_string(timer.DeltaTime()));
}

void Game::Exit()
{
	delete wnd;
	wnd = nullptr;
}
