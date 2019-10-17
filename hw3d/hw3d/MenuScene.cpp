#include "MenuScene.h"

#include "Locator.h"
#include "Graphics.h"
#include "Keyboard.h"

MenuScene::~MenuScene()
{
}

bool MenuScene::Init()
{
	return true;
}

Scene::CurrentScene MenuScene::Update()
{
	if (changeScene == MenuScene::ChangeScene::GAME)
	{
		return Scene::CurrentScene::GAME;
	}

	if (Locator::GetKey()->IsKeyPressed('K'))
	{
		changeScene = MenuScene::ChangeScene::GAME;
	}



	return Scene::CurrentScene::NONE;
}

void MenuScene::Render()
{

}
