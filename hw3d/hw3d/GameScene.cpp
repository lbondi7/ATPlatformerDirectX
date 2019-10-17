#include "GameScene.h"

#include "Locator.h"
#include "Timer.h"
#include "Keyboard.h"
#include "Graphics.h"
#include "WinSetup.h"

#include <iostream>
#include <random>


GameScene::~GameScene()
{

}

bool GameScene::Init()
{
	model = std::make_unique<Model>();
	model2 = std::make_unique<Model>();
	Locator::GetGraphics()->DrawGeometry(model->Init());
	Locator::GetGraphics()->DrawGeometry(model2->Init());

	for (int i = 0; i < 30; i++)
	{

	}

	model->SetPos(0.0f, 0.0f, 2);
	model2->SetPos(0.0f, 0.0f, 5);
	model->SetGeometry("square");
	model2->SetGeometry("cube");

	cam = std::make_unique<Camera>();
	cam->SetPos(0, 0, 0);
	cam->SetRot(0, 0, 0);

	return true;
}

Scene::CurrentScene GameScene::Update()
{
	if (changeScene == GameScene::ChangeScene::MENU)
	{
		return Scene::CurrentScene::MENU;
	}

	if (Locator::GetKey()->IsKeyPressed('L'))
	{
		changeScene = GameScene::ChangeScene::MENU;
	}

	float speed = 5000.0f;
	float rotSpeed = 100000.0f;

	if (Locator::GetKey()->IsKeyPressed(VK_NUMPAD5) || Locator::GetKey()->IsKeyRepeated(VK_NUMPAD5))
	{
		//DirectX::XMVECTOR forward = {0, 0, 1, 0};
		//forward = DirectX::XMVector4Transform(forward, cam->GetViewMatrix());
		//cam->SetPos(DirectX::XMVectorAdd(cam->GetPos(),));
		cam->SetPosZ(cam->GetPosZ() - speed * Locator::GetTimer()->DeltaTime());
	}
	else if (Locator::GetKey()->IsKeyPressed(VK_NUMPAD8) || Locator::GetKey()->IsKeyRepeated(VK_NUMPAD8))
	{
		cam->SetPosZ(cam->GetPosZ() + speed * Locator::GetTimer()->DeltaTime());
	}
	if (Locator::GetKey()->IsKeyPressed(VK_NUMPAD4) || Locator::GetKey()->IsKeyRepeated(VK_NUMPAD4))
	{
		cam->SetPosX(cam->GetPosX() - speed * Locator::GetTimer()->DeltaTime());
	}
	else if (Locator::GetKey()->IsKeyPressed(VK_NUMPAD6) || Locator::GetKey()->IsKeyRepeated(VK_NUMPAD6))
	{
		cam->SetPosX(cam->GetPosX() + speed * Locator::GetTimer()->DeltaTime());
	}
	if (Locator::GetKey()->IsKeyPressed(VK_NUMPAD7) || Locator::GetKey()->IsKeyRepeated(VK_NUMPAD7))
	{
		cam->SetRotX(cam->GetRotX() - rotSpeed * Locator::GetTimer()->DeltaTime());
	}
	else if (Locator::GetKey()->IsKeyPressed(VK_NUMPAD9) || Locator::GetKey()->IsKeyRepeated(VK_NUMPAD9))
	{
		cam->SetRotX(cam->GetRotX() + rotSpeed * Locator::GetTimer()->DeltaTime());
	}


	//cam->SetRot(model2->GetRot());

	model2->SetRotY(Locator::GetTimer()->Peek());
	model->Update();
	model2->Update();
	std::cout << model2->GetPosX() << std::endl;

	return Scene::CurrentScene::NONE;
}

void GameScene::Render()
{
	cam->Render();
	Locator::GetGraphics()->DrawGeometry(model->Render(cam->GetViewMatrix()));
	Locator::GetGraphics()->DrawGeometry(model2->Render(cam->GetViewMatrix()));
}
