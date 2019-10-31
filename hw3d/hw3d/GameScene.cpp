#include "GameScene.h"

#include "Locator.h"
#include "Timer.h"
#include "Keyboard.h"
#include "Graphics.h"
#include "WinSetup.h"
#include "Constants.h"
#include "Maths.h"
#include "Misc.h"

#include <iostream>
#include <random>
#include <map>

using namespace DirectX;
namespace dx = DirectX;

GameScene::~GameScene()
{

}

bool GameScene::Init()
{
	Locator::GetMisc()->SetClearColour({ 0, 1, 0, 1 });

	std::map<int, std::string> texName;
	texName[0] = "MrBean";
	texName[1] = "UV";
	texName[2] = "Simon";

	//for (int i = 0; i < mObjNum; i++)
	//{
	//	Model mod;
	//	mod.ModelType("cube");
	//	mod.Texture(texName[2]);
	//	mod.GetOffset().SetPos(0, 0, 2);
	//	mod.GetOffset().SetScale(1, 1, 1);
	//	mGObjects.push_back(mod);
	//	mGObjects[i].Init();
	//}
	//mGObjects[1].GetOffset().SetPosX(1);
	for (int i = 0; i < mObjNum; i++)
	{
		GameObject go;
		mGObjects.emplace_back(go);
	}

	for (int i = 0; i < mObjNum; i++)
	{
		mGObjects[i].Init();
		mGObjects[i].AddModel();
		mGObjects[i].GetModel()->ModelType("iso");
		mGObjects[i].GetModel()->Texture(i < 2 ? texName[1] : texName[0]);
		mGObjects[i].GetTransform().SetScale(1, 1, 1);
	}
	for (int i = 2; i < mObjNum; i++)
	{
		mGObjects[i].GetTransform().SetScale(0.2f, 0.2f, 0.2f);
	}

	//mGObjects[1].GetTransform().SetPosZ(3);
	mCam = std::make_unique<Camera>();
	mCam->Init();
	mCam->GetTransform().SetPos(0, 3, -5);
	mCam->GetTransform().SetRot(0, 0, 0);

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

	float speed = 500.0f * Locator::GetTimer()->DeltaTime();
	float rotSpeed = 10000.0f;
	if (Locator::GetKey()->IsKeyPressed('W') || Locator::GetKey()->IsKeyRepeated('W'))
	{
		mGObjects[0].GetTransform().SetPos(MoveForward(
			mGObjects[0].GetTransform().GetPos(),
			speed,
			mGObjects[0].GetTransform().GetRotYRad()));
	}
	else if (Locator::GetKey()->IsKeyPressed('S') || Locator::GetKey()->IsKeyRepeated('S'))
	{
		mGObjects[0].GetTransform().SetPos(MoveBackward(
			mGObjects[0].GetTransform().GetPos(),
			speed,
			mGObjects[0].GetTransform().GetRotYRad()));
	}

	if (Locator::GetKey()->IsKeyPressed('Q') || Locator::GetKey()->IsKeyRepeated('Q'))
	{
		mGObjects[0].GetTransform().SetRotY(mGObjects[0].GetTransform().GetRotY() - rotSpeed * Locator::GetTimer()->DeltaTime());
	}
	else if (Locator::GetKey()->IsKeyPressed('E') || Locator::GetKey()->IsKeyRepeated('E'))
	{
		mGObjects[0].GetTransform().SetRotY(mGObjects[0].GetTransform().GetRotY() + rotSpeed * Locator::GetTimer()->DeltaTime());
	}
	
	mGObjects[2].GetTransform().SetPos(mGObjects[0].GetMinVert());
	mGObjects[3].GetTransform().SetPos(mGObjects[0].GetMaxVert());
	mGObjects[4].GetTransform().SetPos(mGObjects[1].GetMinVert());
	mGObjects[5].GetTransform().SetPos(mGObjects[1].GetMaxVert());

	for (int i = 0; i < mObjNum; i++)
	{
		//mGObjects[i].GetTransform().SetRotY(10* Locator::GetTimer()->Peek());
		//mGObjects[i].GetModel()->GetOffset().SetRotY(30 * Locator::GetTimer()->Peek());
		mGObjects[i].Update(mWorldMatrix);
	}


	if (mGObjects[1].BoundingBoxCollision(mGObjects[0].GetMinVert(), mGObjects[0].GetMaxVert()))
	{
		Locator::GetMisc()->SetClearColour({ 1, 1, 1, 1 });
	}
	else
	{
		Locator::GetMisc()->SetClearColour({ 1, 1, 0, 1 });
	}

	mCam->SetLookAt(mGObjects[0].GetTransform().GetPos());
	//mCam->SetRotMatrix(MatrixFromVector({ mGObjects[0].GetTransform().GetRotXRad(),
	//	mGObjects[0].GetTransform().GetRotYRad(),
	//     0, 1}));
	//mCam->SetPhiTheta(0, 0);
	mCam->Update();
	return Scene::CurrentScene::NONE;
}

void GameScene::Render()
{
	//mCam->Render();
	for (int i = 0; i < mObjNum; i++)
	{
		mGObjects[i].Render();
	}
}
