#include "Game.h"
#include "Locator.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "LewisException.h"

#include <iomanip>
#include <thread>

Game::Game()
{
}

bool Game::Init()
{
	window = new Window(500, 500, "hello");

	Locator::InitKey(new Keyboard());
	Locator::InitMouse(new Mouse());
	Locator::InitExitBool();
	Locator::GetKey()->Initialise();
	Locator::GetMouse()->Initialise();

	return true;
}

void Game::Run()
{
	while (*Locator::GetExitBool() != true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		//if (const auto ecode = Window::ProcessMessages())
		//{
		//	return *ecode;
		//}
		Window::ProcessMessages();
		Update();
	}
}

void Game::Update()
{
	const float r = sin(timer.Peek());
	const float g = sin(timer.Peek() * 2.0f);
	const float b = sin(timer.Peek() / 2.0f);
	const float a = 1.0f;
	window->GetGraphics()->ClearBuffer(r, g, b, a);
	window->GetGraphics()->DrawTestTriangle();
	window->GetGraphics()->EndFrame();
	//const float t = timer.Peek();
	//window->SetWindowTitle("Seconds: " + std::to_string((int)t) + " - Delta Time: " + std::to_string(timer.DeltaTime()));
}

void Game::Exit()
{
	delete window;
	window = nullptr;
}
