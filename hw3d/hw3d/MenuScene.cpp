#include "MenuScene.h"

#include "Locator.h"
#include "Keyboard.h"
#include "Misc.h"

MenuScene::~MenuScene()
{
}

bool MenuScene::Init()
{
	Locator::GetMisc()->SetClearColour({ 1, 0, 0, 1 });
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
