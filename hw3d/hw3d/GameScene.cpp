#include "GameScene.h"

#include "Locator.h"
#include "Timer.h"
#include "Keyboard.h"
#include "WinSetup.h"
#include "Constants.h"
#include "Maths.h"
#include "Misc.h"
#include "LevelLoader.h"

#include <iostream>
#include <map>

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

	Vector poss[11]{ {0, 0, 0},
		{0, 0, 15},
		{15, 0, 15},
		{30, 0, 15},
		{45, 0, 15},
		{45, 0, 0},
		{45, 0, -15},
		{30, 0, -15},
		{15, 0, -15},
		{0, 0, -15},
	    {22, -5, 0}
	};

	Vector scales[11]{ {5, 1, 5},
		{5, 1, 5},
		{5, 1, 5},
		{5, 1, 5},
		{5, 1, 5},
		{5, 1, 5},
		{5, 1, 5},
		{5, 1, 5},
		{5, 1, 5},
		{5, 1, 5},
		{50, 2, 50} 
	};

	for (int i = 0; i < 11; i++)
	{
		GameObject* go = new GameObject();
		go->Init();
		go->AddModel();
		//go->GetModel()->ModelType("cube");
		//go->GetModel()->Texture(texName[1]);
		//go->GetTransform().SetScale(scales[i]);
		//go->GetTransform().SetPos(poss[i]);
		//go->SetTag(GameObjectTag::GROUND);
		//if (i == 10)
		//{
		//	go->SetTag(GameObjectTag::KILLBOX);
		//}

		pGObjects.emplace_back(go);
		mObjNum++;
		go = nullptr;
	}

	LevelLoader::LoadObjects(pGObjects);

	pPlayer = std::make_unique<GameObject>();
	pPlayer->Init();
	pPlayer->AddModel();
	pPlayer->GetModel()->ModelType("iso");
	pPlayer->GetModel()->Texture(texName[2]);
	pPlayer->GetTransform().SetScale(1, 1, 1);
	pPlayer->GetTransform().SetPos(0, 3, 0);
	pPlayer->AddPlayer();
	pPlayer->SetTag(GameObjectTag::PLAYER);
	pGObjects.emplace_back(pPlayer.get());

	mCam = std::make_unique<Camera>();
	mCam->Init();
	mCam->GetTransform().SetPos(0, 4, -5);
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

	for (std::vector<GameObject*>::iterator it = pGObjects.begin(); it != pGObjects.end(); ++it) {
		(*it)->Update(mWorldMatrix);
	}

	//if (mGObjects[1].GetBB().IsInside(mGObjects[0].GetBB().mBBMin, mGObjects[0].GetBB().mBBMax))
	//{
	//	Locator::GetMisc()->SetClearColour({ 1, 1, 1, 1 });
	//}
	//else
	//{
	//	Locator::GetMisc()->SetClearColour({ 1, 1, 0, 1 });
	//}

	isColliding = false;
	for (size_t i = 0; i < mObjNum; ++i)
	{
		if (pPlayer->GetBB().IsInside(pGObjects[i]->GetBB().mBBMin, pGObjects[i]->GetBB().mBBMax))
		{
			isColliding = true;

			if (pGObjects[i]->GetTag() == GameObjectTag::KILLBOX)
			{
				pPlayer->GetPlayer()->SetState(PlayerMotionState::GROUNDED);
				pPlayer->GetTransform().SetPos(0, 3, 0);
				pPlayer->GetTransform().SetRot(0, 0, 0);
				break;
			}

			auto playerDim = VectorSub(pPlayer->GetBB().mBBMax, pPlayer->GetBB().mBBMin);
			auto objDim = VectorSub(pGObjects[i]->GetBB().mBBMax, pGObjects[i]->GetBB().mBBMin);

			auto difference = DirectX::XMVectorSubtract(
				pPlayer->GetTransform().GetPos(), 
				pGObjects[i]->GetTransform().GetPos());

			//playerDim = VectorMultiplyByFloat(playerDim, 0.5f);
			//objDim = VectorMultiplyByFloat(objDim, 0.5f);
			//difference = DirectX::XMVector3Normalize(difference);
			//difference = DirectX::XMVectorMultiply(difference, VectorAdd(playerDim, objDim));
			////difference = VectorMultiplyByFloat(difference, 0.5f);
			//pPlayer->GetTransform().SetPos(VectorAdd(pGObjects[i]->GetTransform().GetPos(), difference));
			pPlayer->GetTransform().SetPos(VectorAdd(pGObjects[i]->GetTransform().GetPos(), 
				{ DirectX::XMVectorGetX(difference), 
				((DirectX::XMVectorGetY(playerDim) - 0.1f) + (DirectX::XMVectorGetY(objDim) - 0.1f)) * 0.5f,
				DirectX::XMVectorGetZ(difference) }));


			pPlayer->GetPlayer()->SetState(PlayerMotionState::GROUNDED);
			break;
		}
	}

	if (!isColliding)
	{
		pPlayer->GetPlayer()->SetState(PlayerMotionState::FALLING);
	}

	mCam->SetLookAt(pPlayer->GetTransform().GetPos());
	mCam->Update();
	return Scene::CurrentScene::NONE;
}

void GameScene::Render()
{
	for (std::vector<GameObject*>::iterator it = pGObjects.begin(); it != pGObjects.end(); ++it) {
		(*it)->Render();
	}
}
