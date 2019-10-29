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

	for (int i = 0; i < mObjNum; i++)
	{
		Model mod;
		mod.ModelType("cube");
		mod.Texture(texName[2]);
		mod.GetTransform().SetPos(0, 0, 2);
		mod.GetTransform().SetScale(1, 1, 1);
		mGObjects.push_back(mod);
		mGObjects[i].Init();
	}

	mCam = std::make_unique<Camera>();
	mCam->SetPos(0, 0, -5);
	mCam->SetRot(0, 0, 0);

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

	float speed = 10.0f;
	float rotSpeed = 100.0f;

	if (Locator::GetKey()->IsKeyPressed(VK_NUMPAD5) || Locator::GetKey()->IsKeyRepeated(VK_NUMPAD5))
	{
		mCam->SetPosZ(mCam->GetPosZ() - speed * Locator::GetTimer()->DeltaTime());
	}
	else if (Locator::GetKey()->IsKeyPressed(VK_NUMPAD8) || Locator::GetKey()->IsKeyRepeated(VK_NUMPAD8))
	{
		mCam->SetPosZ(mCam->GetPosZ() + speed * Locator::GetTimer()->DeltaTime());
	}
	if (Locator::GetKey()->IsKeyPressed(VK_NUMPAD4) || Locator::GetKey()->IsKeyRepeated(VK_NUMPAD4))
	{
		mCam->SetPosX(mCam->GetPosX() - speed * Locator::GetTimer()->DeltaTime());
	}
	else if (Locator::GetKey()->IsKeyPressed(VK_NUMPAD6) || Locator::GetKey()->IsKeyRepeated(VK_NUMPAD6))
	{
		mCam->SetPosX(mCam->GetPosX() + speed * Locator::GetTimer()->DeltaTime());
	}
	if (Locator::GetKey()->IsKeyPressed(VK_NUMPAD7) || Locator::GetKey()->IsKeyRepeated(VK_NUMPAD7))
	{
		mCam->SetRotX(mCam->GetRotX() - rotSpeed * Locator::GetTimer()->DeltaTime());
	}
	else if (Locator::GetKey()->IsKeyPressed(VK_NUMPAD9) || Locator::GetKey()->IsKeyRepeated(VK_NUMPAD9))
	{
		mCam->SetRotX(mCam->GetRotX() + rotSpeed * Locator::GetTimer()->DeltaTime());
	}

	for (int i = 0; i < mObjNum; i++)
	{
		mGObjects[i].GetTransform().SetRotY(30* Locator::GetTimer()->Peek());
		mGObjects[i].Update();
	}

	mCam->Update();
	return Scene::CurrentScene::NONE;
}

void GameScene::Render()
{
	//mCam->Render();
	for (int i = 0; i < mObjNum; i++)
	{
		Locator::GetGraphics()->CheckHResults(mGObjects[i].Render(mCam->GetViewMatrix()));
	}
}
