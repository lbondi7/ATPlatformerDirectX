#include "Game.h"
#include "Locator.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Timer.h"
#include "Buffers.h"
#include "D3D.h"

#include <iomanip>
#include <thread>

Game::Game()
{
}

bool Game::Init()
{

	Locator::InitKey(new Keyboard());
	Locator::InitMouse(new Mouse());
	Locator::InitTimer(new Timer());
	Locator::InitBuffers(new Buffers());

	Locator::InitExitBool();
	Locator::GetKey()->Initialise();
	Locator::GetMouse()->Initialise();

	window = new Window(500, 500, "hello");

	return true;
}

void Game::Run()
{
	while (*Locator::GetExitBool() != true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		Locator::GetTimer()->SetDeltaTime();
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
	window->GetGraphics()->ClearBuffer(1.0f, 1.0f, 1.0f, 0.0f);
	window->GetGraphics()->DrawTestTriangle(70.5f, -0.5f, 10, "triangle");
	window->GetGraphics()->DrawTestTriangle(5.0f, 0.5f, 10, "cube");
	window->GetGraphics()->EndFrame();
	//const float t = timer.Peek();
	//window->SetWindowTitle("Seconds: " + std::to_string((int)t) + " - Delta Time: " + std::to_string(timer.DeltaTime()));
}

void Game::Exit()
{
	delete window;
	window = nullptr;
}
