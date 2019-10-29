#include "SceneManager.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "Locator.h"
#include "Graphics.h"

bool SceneManager::Init()
{


	activeScene = std::make_unique<MenuScene>();
	activeScene->Init();

	return true;
}

void SceneManager::Update()
{
	switch (activeScene->Update())
	{
	case Scene::CurrentScene::MENU:
		activeScene.reset();
		activeScene = std::make_unique<MenuScene>();
		activeScene->Init();
		currentScene = SceneManager::CurrentScene::MENU;
		break;
	case Scene::CurrentScene::GAME:
		activeScene.reset();
		activeScene = std::make_unique<GameScene>();
		activeScene->Init();
		currentScene = SceneManager::CurrentScene::GAME;
		break;
	}

}

void SceneManager::Render()
{
	if (currentScene == SceneManager::CurrentScene::MENU)
		Locator::GetGraphics()->ClearBuffer(1.0f, 0.0f, 0.0f, 1.0f);
	else if (currentScene == SceneManager::CurrentScene::GAME)
		Locator::GetGraphics()->ClearBuffer(0.0f, 0.0f, 1.0f, 1.0f);

	activeScene->Render();

	Locator::GetGraphics()->EndFrame();
}
