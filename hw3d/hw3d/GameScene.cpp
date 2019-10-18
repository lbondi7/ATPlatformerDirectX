#include "GameScene.h"

#include "Locator.h"
#include "Timer.h"
#include "Keyboard.h"
#include "Graphics.h"
#include "WinSetup.h"

#include <iostream>
#include <random>
#include <map>


GameScene::~GameScene()
{

}

bool GameScene::Init()
{
	std::map<int, std::string> texName;
	texName[0] = "MrBean";
	texName[1] = "Scary";
	texName[2] = "Simon";
	model = std::make_unique<Model>();
	model2 = std::make_unique<Model>();
	model3 = std::make_unique<Model>();
	model4 = std::make_unique<Model>();
	model->SetTexture(texName[2]);
	model2->SetTexture(texName[0]);
	model3->SetTexture(texName[1]);
	model4->SetTexture(texName[2]);
	Locator::GetGraphics()->DrawGeometry(model->Init());
	Locator::GetGraphics()->DrawGeometry(model2->Init());
	Locator::GetGraphics()->DrawGeometry(model3->Init());
	Locator::GetGraphics()->DrawGeometry(model4->Init());

	std::random_device rd;
	std::uniform_real_distribution<float> dist(0, 100);
	std::uniform_int_distribution<int> dist1(0, 1);
	std::uniform_real_distribution<float> dist2(20, 60);
	std::uniform_real_distribution<float> dist3(1, 10);
	std::uniform_real_distribution<float> dist4(1, 25);
	std::uniform_int_distribution<int> dist5(0, 2);

	for (int i = 0; i < cubeAmount; i++)
	{
		Model mod;
		mod.SetGeometry("cube");
		mod.SetTexture(texName[2]);
		float pos = dist(rd);
		float x_pos = pos;
		float y_pos = pos;
		float dist_x = dist4(rd);
		float dist_y = dist4(rd);
		if (dist1(rd) == 0)
		{
			x_pos *= -1;
		}
		if (dist1(rd) == 0)
		{
			y_pos *= -1;
		}
		if (dist1(rd) == 0)
		{
			dist_x *= -1;
		}
		if (dist1(rd) == 0)
		{
			dist_y *= -1;
		}
		mod.SetPos(x_pos + dist_x , y_pos + dist_y, dist2(rd));
		mod.SetScale(dist3(rd), dist3(rd), dist3(rd));
		cubes.push_back(mod);
		cubes[i].Init();
	}

	model->SetPos(0.0f, 0.0f, 0.5);
	model->SetScale(2, 2, 1);
	model->SetGeometry("square");
	model2->SetGeometry("cube");
	model3->SetGeometry("square");
	model4->SetGeometry("triangle");
	model2->SetPos(-3.0f, 0.0f, -5);
	model3->SetPos(0.0f, 0.0f, -5);
	model4->SetPos(3.0f, 0.0f, -5);
	model3->SetRot(0, 180.0f, 0);
	model4->SetRot(0, 180.0f, 0);

	cam = std::make_unique<Camera>();
	cam->SetPos(0, 0, 0);
	cam->SetRot(-180, 0, 0);

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

	float speed = 10000.0f;
	float rotSpeed = 100000.0f;

	if (Locator::GetKey()->IsKeyPressed(VK_NUMPAD5) || Locator::GetKey()->IsKeyRepeated(VK_NUMPAD5))
	{
		//DirectX::XMVECTOR forward = {0, 0, 1, 0};
		//forward = DirectX::XMVector4Transform(forward, cam->GetViewMatrix());
		//cam->SetPos(DirectX::XMVectorAdd(cam->GetPos(),));
		cam->SetPosZ(cam->GetPosZ() - speed * Locator::GetTimer()->DeltaTime() * 3);
	}
	else if (Locator::GetKey()->IsKeyPressed(VK_NUMPAD8) || Locator::GetKey()->IsKeyRepeated(VK_NUMPAD8))
	{
		cam->SetPosZ(cam->GetPosZ() + speed * Locator::GetTimer()->DeltaTime() * 3);
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

	model2->SetRotY(30 * Locator::GetTimer()->Peek());
	model->Update();
	model2->Update();
	std::cout << model2->GetPosX() << std::endl;

	for (int i = 0; i < cubeAmount; i++)
	{
		cubes[i].SetRotY(30* Locator::GetTimer()->Peek());
		cubes[i].Update();
	}

	return Scene::CurrentScene::NONE;
}

void GameScene::Render()
{
	cam->Render();
	Locator::GetGraphics()->DrawGeometry(model->Render(cam->GetViewMatrix()));
	Locator::GetGraphics()->DrawGeometry(model2->Render(cam->GetViewMatrix()));
	Locator::GetGraphics()->DrawGeometry(model3->Render(cam->GetViewMatrix()));
	Locator::GetGraphics()->DrawGeometry(model4->Render(cam->GetViewMatrix()));
	for (int i = 0; i < cubeAmount; i++)
	{
		Locator::GetGraphics()->DrawGeometry(cubes[i].Render(cam->GetViewMatrix()));
	}
}
