#include "GameScene.h"

#include "Locator.h"
#include "Timer.h"
#include "Keyboard.h"
#include "WinSetup.h"
#include "Constants.h"
#include "Maths.h"
#include "Misc.h"
#include "LevelLoader.h"
#include "imgui/imgui.h"

#include <iostream>
#include <map>

GameScene::~GameScene()
{

}

bool GameScene::Init()
{
	Locator::GetMisc()->SetClearColour({ 0, 1, 0, 1 });

	//for (int i = 0; i < 11; i++)
	//{
	//	GameObject* go = new GameObject();
	//	go->Init();
	//	go->AddModel();

	//	pGObjects.emplace_back(go);
	//	mObjNum++;
	//	go = nullptr;
	//}

	//pGObjects.resize(11);

	LevelLoader::LoadObjects(p_GObjects);

	pPlayer = std::make_unique<GameObject>();
	pPlayer->Init(ModelType::HELI, TextureType::SIMON, ShaderType::TEXTURE);
	pPlayer->AddModel();
	pPlayer->GetModel()->ModelType("cube");
	pPlayer->GetModel()->Texture("Simon");
	pPlayer->GetTransform().SetScale(1, 1, 1);
	pPlayer->GetTransform().SetPos(10, 10, 10);
	pPlayer->AddPlayer();
	pPlayer->AddPhysics();
	pPlayer->GetPhysicsData().physicsTag = PhysicsTag::MOVEABLE;
	pPlayer->GetPhysicsData().m_Mass = 100.0f;
	pPlayer->SetTag(GameObjectTag::PLAYER);
	p_GObjects.emplace_back(pPlayer.get());

	mCam = std::make_unique<Camera>();
	mCam->Init();
	mCam->SetLookAt(pPlayer->GetTransform().GetPos());

	light.diffuseColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	light.lightDirection = { 1.0f, -1.0f, 1.0f, 1.0f };
	//light.padding = 0.0f;

	for (std::vector<GameObject*>::iterator it = p_GObjects.begin(); it != p_GObjects.end(); ++it) {
		(*it)->Update();
	}

	grid = std::make_unique<BoundingGrid>();
	Float3 dims(50, 25, 35);
	grid->Init(dims);
	grid->GetObjectIDs(p_GObjects);

	return true;
}

Scene::CurrentScene GameScene::Update()
{
	if (changeScene == GameScene::ChangeScene::MENU)
		return Scene::CurrentScene::MENU;

	if (Locator::GetKey()->IsKeyPressed('L'))
		changeScene = GameScene::ChangeScene::MENU;

	for (std::vector<GameObject*>::iterator it = p_GObjects.begin(); it != p_GObjects.end(); ++it) 
	{
		(*it)->Update();
	}

	grid->GetObjectIDs(p_GObjects);

	for (size_t i = 0; i < p_GObjects.size(); ++i)
	{
		if (p_GObjects[i]->GetPhysicsData().physicsTag == PhysicsTag::STATIC)
			continue;

		bool colliding = false;

		grid->GetObjectsInGrid(p_GObjects[i], m_CollideableObjects);

		for (size_t j = 0; j < m_CollideableObjects.size(); ++j)
		{
			auto ray = p_GObjects[i]->GetPhysics()->GetRay();
			if (m_CollideableObjects[j]->GetBB().RayBoxIntersect(ray) && ray.T() < 1.0f)
			{
				p_GObjects[i]->GetTransform().SetPosY(m_CollideableObjects[j]->GetBB().m_Max.y +
					(VectorY(VectorSub(p_GObjects[i]->GetTransform().GetPos(), Utilities::ConvertToVec4Point(p_GObjects[i]->GetBB().m_Min)))));
				p_GObjects[i]->GetPhysicsData().motionState = ObjectMotionState::GROUNDED;
				colliding = true;
			}
		}

		if (!colliding)
		{
			p_GObjects[i]->GetPhysicsData().motionState = ObjectMotionState::FALLING;
		}

		for (auto& cO : m_CollideableObjects)
		{
			cO = nullptr;
		}
		m_CollideableObjects.clear();
		//for (size_t j = 0; j < p_GObjects.size(); ++j)
		//{
		//	if (i == j) continue;

		//	auto ray = p_GObjects[i]->GetPhysics()->GetRay();
		//	if (p_GObjects[j]->GetBB().RayBoxIntersect(ray) && ray.T() < 1.0f)
		//	{
		//		p_GObjects[i]->GetTransform().SetPosY(p_GObjects[j]->GetBB().m_Max.y + 
		//			(VectorY(VectorSub(p_GObjects[i]->GetTransform().GetPos(), Utilities::ConvertToVec4Point(p_GObjects[i]->GetBB().m_Min)))));
		//		p_GObjects[i]->GetPhysicsData().motionState = ObjectMotionState::GROUNDED;
		//		colliding = true;
		//	}

		//	//if (p_GObjects[i]->GetBB().IsInside(p_GObjects[j]->GetBB()))
		//	//{
		//	//	p_GObjects[i]->GetTransform().SetPosY(p_GObjects[j]->GetBB().m_Max.y + 
		//	//		(VectorY(VectorSub(p_GObjects[i]->GetTransform().GetPos(), Utilities::ConvertToVec4Point(p_GObjects[i]->GetBB().m_Min)))));
		//	//	p_GObjects[i]->GetPhysicsData().motionState = ObjectMotionState::GROUNDED;
		//	//	colliding = true;
		//	//}
		//}

		//if (!colliding)
		//{
		//	p_GObjects[i]->GetPhysicsData().motionState = ObjectMotionState::FALLING;
		//}
	}




	//isColliding = false;
	//for (size_t i = 0; i < pGObjects.size(); ++i)
	//{
	//	if (pPlayer->GetBB().IsInside(pGObjects[i]->GetBB().m_BBMin, pGObjects[i]->GetBB().m_BBMax))
	//	{
	//		isColliding = true;
	//		if (pGObjects[i]->GetTag() == GameObjectTag::KILLBOX)
	//		{
	//			//pPlayer->GetPlayer()->SetState(ObjectMotionState::GROUNDED);
	//			pPlayer->GetTransform().SetPos(0, 3, 0);
	//			pPlayer->GetTransform().SetRot(0, 0, 0);
	//			break;
	//		}
	//		if ((pPlayer->GetTransform().GetPosY() > pGObjects[i]->GetBB().m_BBMax.y) &&
	//			VectorY(pPlayer->GetPlayer()->GetVelocity()) < 0)
	//		{
	//			pPlayer->GetTransform().SetPosY(pPlayer->GetTransform().GetPosY() + 0.001f);
	//			pPlayer->GetTransform().SetPosY(
	//				pPlayer->GetTransform().GetPosY() -
	//				VectorY(pPlayer->GetPlayer()->GetVelocity()) *
	//				Locator::GetTimer()->DeltaTime());
	//			pPlayer->GetPlayer()->SetState(ObjectMotionState::GROUNDED);
	//		}
	//		else 
	//		{
	//			pPlayer->GetTransform().SetPosX(
	//				pPlayer->GetTransform().GetPosX() - VectorX(pPlayer->GetPlayer()->GetVelocity())
	//				* Locator::GetTimer()->DeltaTime());
	//			pPlayer->GetTransform().SetPosZ(
	//				pPlayer->GetTransform().GetPosZ() - VectorZ(pPlayer->GetPlayer()->GetVelocity())
	//				* Locator::GetTimer()->DeltaTime());
	//			auto vec = DirectX::XMVector3Normalize(pPlayer->GetPlayer()->GetVelocity());
	//			pPlayer->GetTransform().SetPosX(pPlayer->GetTransform().GetPosX() - (VectorX(vec) * 0.1f));
	//			pPlayer->GetTransform().SetPosZ(pPlayer->GetTransform().GetPosZ() - (VectorZ(vec) * 0.1f));
	//		}
	//			////pPlayer->GetTransform().SetPosX(pPlayer->GetTransform().GetPosX() - 0.01f);
	//			//pPlayer->GetTransform().SetPosX(
	//			//	pPlayer->GetTransform().GetPosX() - VectorX(pPlayer->GetPlayer()->GetVelocity())
	//			//	* Locator::GetTimer()->DeltaTime());
	//			////pPlayer->GetTransform().SetPosZ(pPlayer->GetTransform().GetPosZ() - 0.01f);
	//			//pPlayer->GetTransform().SetPosZ(
	//			//	pPlayer->GetTransform().GetPosZ() - VectorZ(pPlayer->GetPlayer()->GetVelocity())
	//			//	* Locator::GetTimer()->DeltaTime());
	//			//auto vec = DirectX::XMVector3Normalize(pPlayer->GetPlayer()->GetVelocity());
	//			//pPlayer->GetTransform().SetPosX(pPlayer->GetTransform().GetPosX() - (VectorX(vec) * 0.1f));
	//			//pPlayer->GetTransform().SetPosZ(pPlayer->GetTransform().GetPosZ() - (VectorZ(vec) * 0.1f));
	//		//auto playerDim = VectorSub(pPlayer->GetBB().mBBMax, pPlayer->GetBB().mBBMin);
	//		//auto objDim = VectorSub(pGObjects[i]->GetBB().mBBMax, pGObjects[i]->GetBB().mBBMin);
	//		//auto difference = DirectX::XMVectorSubtract(
	//		//	pPlayer->GetTransform().GetPos(), 
	//		//	pGObjects[i]->GetTransform().GetPos());

	//		////playerDim = VectorMultiplyByFloat(playerDim, 0.5f);
	//		////objDim = VectorMultiplyByFloat(objDim, 0.5f);
	//		////difference = DirectX::XMVector3Normalize(difference);
	//		////difference = DirectX::XMVectorMultiply(difference, VectorAdd(playerDim, objDim));
	//		////pPlayer->GetTransform().SetPos(VectorAdd(pGObjects[i]->GetTransform().GetPos(), difference));
	//		////pPlayer->GetTransform().SetPos(VectorAdd(pGObjects[i]->GetTransform().GetPos(), 
	//		////	{ DirectX::XMVectorGetX(difference), 
	//		////	((DirectX::XMVectorGetY(playerDim) - 0.1f) + (DirectX::XMVectorGetY(objDim) - 0.1f)) * 0.5f,
	//		////	DirectX::XMVectorGetZ(difference) }));

	//		//pPlayer->GetPlayer()->SetState(PlayerMotionState::GROUNDED);
	//		break;
	//	}
	//}

	//if (!isColliding)
	//{
	//	pPlayer->GetPlayer()->SetState(ObjectMotionState::FALLING);
	//}

	pPlayer->GetRenderData().up_LightBuffer->MapToGPU(&light, sizeof(LightBufferData)); 

	mCam->SetLookAt(pPlayer->GetTransform().GetPos());
	mCam->SetRotMatrix(pPlayer->GetMatrix());
	mCam->Update();
	return Scene::CurrentScene::NONE;
}

void GameScene::Render()
{
	for (std::vector<GameObject*>::iterator it = p_GObjects.begin(); it != p_GObjects.end(); ++it) {
		(*it)->Render();
	}
	mCam->Render();


	ImGui::Begin("Controls");

	ImGui::Text("Use A and D and space for a broken jump (didn't get round to fixing it, the jump and the game)");
	ImGui::Text("Press L to exit game scene");

	ImGui::End();

}
