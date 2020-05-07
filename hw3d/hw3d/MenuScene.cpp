#include "MenuScene.h"

#include "Locator.h"
#include "Keyboard.h"
#include "Misc.h"
#include "imgui/imgui.h"

MenuScene::~MenuScene()
{
}

bool MenuScene::Init()
{
	Locator::GetMisc()->SetClearColour({ 0.8, 0.5, 0, 1 });
	return true;
}

Scene::CurrentScene MenuScene::Update()
{
	if (changeScene == MenuScene::ChangeScene::GAME)
		return Scene::CurrentScene::GAME;
	else if (changeScene == MenuScene::ChangeScene::LEVEL_EDITOR)
		return Scene::CurrentScene::LEVEL_EDITOR;

	if (Locator::GetKey()->IsKeyPressed('K'))
		changeScene = MenuScene::ChangeScene::GAME;
	//else if (Locator::GetKey()->IsKeyPressed('J'))
	//	changeScene = MenuScene::ChangeScene::LEVEL_EDITOR;
	if (Locator::GetKey()->IsKeyPressed('L'))
		*Locator::GetExitBool() = true;


	return Scene::CurrentScene::NONE;
}

void MenuScene::Render()
{
	ImGui::Begin("Controls");

	ImGui::Text("Press K to load game scene");
	ImGui::Text("Press L to exit game scene and quit game");

	ImGui::End();
}
