#include "SceneManager.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "Locator.h"

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
		activeScene->Update();
		currentScene = SceneManager::CurrentScene::MENU;
		break;
	case Scene::CurrentScene::GAME:
		activeScene.reset();
		activeScene = std::make_unique<GameScene>();
		activeScene->Init();
		activeScene->Update();
		currentScene = SceneManager::CurrentScene::GAME;
		break;
	}

}

void SceneManager::Render()
{
	activeScene->Render();
}
