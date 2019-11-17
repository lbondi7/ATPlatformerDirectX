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

	for (int i = 0; i < 11; i++)
	{
		GameObject* go = new GameObject();
		go->Init();
		go->AddModel();

		pGObjects.emplace_back(go);
		mObjNum++;
		go = nullptr;
	}

	LevelLoader::LoadObjects(pGObjects);

	pPlayer = std::make_unique<GameObject>();
	pPlayer->Init();
	pPlayer->AddModel();
	pPlayer->GetModel()->ModelType("helli2");
	pPlayer->GetModel()->Texture("Simon");
	pPlayer->GetTransform().SetScale(1, 1, 1);
	pPlayer->GetTransform().SetPos(0, 3, 0);
	pPlayer->AddPlayer();
	pPlayer->SetTag(GameObjectTag::PLAYER);
	pGObjects.emplace_back(pPlayer.get());

	mCam = std::make_unique<Camera>();
	mCam->Init();
	mCam->GetTransform().SetPos(-10, 15, -10);
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

			if ((pPlayer->GetTransform().GetPosY() > VectorY(pGObjects[i]->GetBB().mBBMax)) &&
				VectorY(pPlayer->GetPlayer()->GetVelocity()) < 0)
			{
				pPlayer->GetTransform().SetPosY(pPlayer->GetTransform().GetPosY() + 0.001f);
				pPlayer->GetTransform().SetPosY(
					pPlayer->GetTransform().GetPosY() -
					VectorY(pPlayer->GetPlayer()->GetVelocity()) *
					Locator::GetTimer()->DeltaTime());

				pPlayer->GetPlayer()->SetState(PlayerMotionState::GROUNDED);
			}
			else 
			{
				pPlayer->GetTransform().SetPosX(
					pPlayer->GetTransform().GetPosX() - VectorX(pPlayer->GetPlayer()->GetVelocity())
					* Locator::GetTimer()->DeltaTime());

				pPlayer->GetTransform().SetPosZ(
					pPlayer->GetTransform().GetPosZ() - VectorZ(pPlayer->GetPlayer()->GetVelocity())
					* Locator::GetTimer()->DeltaTime());

				auto vec = DirectX::XMVector3Normalize(pPlayer->GetPlayer()->GetVelocity());
				pPlayer->GetTransform().SetPosX(pPlayer->GetTransform().GetPosX() - (VectorX(vec) * 0.1f));
				pPlayer->GetTransform().SetPosZ(pPlayer->GetTransform().GetPosZ() - (VectorZ(vec) * 0.1f));
			}
				////pPlayer->GetTransform().SetPosX(pPlayer->GetTransform().GetPosX() - 0.01f);
				//pPlayer->GetTransform().SetPosX(
				//	pPlayer->GetTransform().GetPosX() - VectorX(pPlayer->GetPlayer()->GetVelocity())
				//	* Locator::GetTimer()->DeltaTime());
				////pPlayer->GetTransform().SetPosZ(pPlayer->GetTransform().GetPosZ() - 0.01f);
				//pPlayer->GetTransform().SetPosZ(
				//	pPlayer->GetTransform().GetPosZ() - VectorZ(pPlayer->GetPlayer()->GetVelocity())
				//	* Locator::GetTimer()->DeltaTime());

				//auto vec = DirectX::XMVector3Normalize(pPlayer->GetPlayer()->GetVelocity());
				//pPlayer->GetTransform().SetPosX(pPlayer->GetTransform().GetPosX() - (VectorX(vec) * 0.1f));
				//pPlayer->GetTransform().SetPosZ(pPlayer->GetTransform().GetPosZ() - (VectorZ(vec) * 0.1f));


			//auto playerDim = VectorSub(pPlayer->GetBB().mBBMax, pPlayer->GetBB().mBBMin);
			//auto objDim = VectorSub(pGObjects[i]->GetBB().mBBMax, pGObjects[i]->GetBB().mBBMin);

			//auto difference = DirectX::XMVectorSubtract(
			//	pPlayer->GetTransform().GetPos(), 
			//	pGObjects[i]->GetTransform().GetPos());

			////playerDim = VectorMultiplyByFloat(playerDim, 0.5f);
			////objDim = VectorMultiplyByFloat(objDim, 0.5f);
			////difference = DirectX::XMVector3Normalize(difference);
			////difference = DirectX::XMVectorMultiply(difference, VectorAdd(playerDim, objDim));
			////pPlayer->GetTransform().SetPos(VectorAdd(pGObjects[i]->GetTransform().GetPos(), difference));
			////pPlayer->GetTransform().SetPos(VectorAdd(pGObjects[i]->GetTransform().GetPos(), 
			////	{ DirectX::XMVectorGetX(difference), 
			////	((DirectX::XMVectorGetY(playerDim) - 0.1f) + (DirectX::XMVectorGetY(objDim) - 0.1f)) * 0.5f,
			////	DirectX::XMVectorGetZ(difference) }));

			//pPlayer->GetPlayer()->SetState(PlayerMotionState::GROUNDED);
			break;
		}
	}

	//if (!isColliding)
	//{
	//	pPlayer->GetPlayer()->SetState(PlayerMotionState::FALLING);
	//}

	for (std::vector<GameObject*>::iterator it = pGObjects.begin(); it != pGObjects.end(); ++it) {
		(*it)->Update(mWorldMatrix);
	}

	mCam->SetLookAt(pPlayer->GetTransform().GetPos());
	//mCam->SetRotMatrix(pPlayer->GetMatrix());
	mCam->Update();
	return Scene::CurrentScene::NONE;
}

void GameScene::Render()
{

	for (std::vector<GameObject*>::iterator it = pGObjects.begin(); it != pGObjects.end(); ++it) {
		(*it)->Render();
	}
}
