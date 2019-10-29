#include "Game.h"
#include "Locator.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Timer.h"
#include "Vertices.h"
#include "D3D.h"
#include "Texture.h"
#include "Shader.h"
#include "Light.h"
#include "Matrices.h"

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
	Locator::InitVertices(new Vertices());
	Locator::InitTexture(new Texture());
	Locator::InitShader(new Shader());
	Locator::InitLight(new Light());
	Locator::InitMatrices(new Matrices());

	Locator::InitExitBool();
	Locator::GetKey()->Initialise();
	Locator::GetMouse()->Initialise();

	window = new Window(500, 500, "hello");
	sceneManager = std::make_unique<SceneManager>();
	sceneManager->Init();

	return true;
}

void Game::Run()
{
	while (*Locator::GetExitBool() != true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		Locator::GetTimer()->SetDeltaTime();
		Locator::GetMouse()->Update();
		Locator::GetKey()->Update();
		Window::ProcessMessages();
		Update();
	}
}

void Game::Update()
{
	sceneManager->Update();
	sceneManager->Render();
	
}

void Game::Exit()
{
	delete window;
	window = nullptr;
}
