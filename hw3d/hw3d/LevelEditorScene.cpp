#include "LevelEditorScene.h"
#include "Locator.h"
#include "Keyboard.h"
#include "ResourceData.h"
#include "Misc.h"

#include "imgui/imgui.h"
#include "imgui/ImGuizmo.h"

LevelEditorScene::~LevelEditorScene()
{
}

bool LevelEditorScene::Init()
{
	Locator::GetMisc()->SetClearColour({ 0, 0.9f, 0.9f, 1 });

	up_Cam = std::make_unique<Camera>();


	GameObject* go = new GameObject();
	go->Init(ModelType::CUBE, TextureType::SIMON, ShaderType::DEFAULT);
	go->AddModel();
	go->GetTransform().SetScale(1, 1, 1);
	go->GetTransform().SetRot(0, 0, 0);
	go->GetTransform().SetPos(1, 0, 0);
	p_GameObjects.emplace_back(go);

	p_ActiveGO = p_GameObjects[0];

	return true;
}

Scene::CurrentScene LevelEditorScene::Update()
{
	if (changeScene == LevelEditorScene::ChangeScene::MENU)
		return Scene::CurrentScene::MENU;

	if (Locator::GetKey()->IsKeyPressed('L'))
		changeScene = LevelEditorScene::ChangeScene::MENU;


	for (auto& go : p_GameObjects)
	{
		go->Update();
	}

	if (p_ActiveGO)
	{
		//auto goPos = p_ActiveGO->GetTransform().position;
		//goPos.m128_f32[2] = up_Cam->GetTransform().GetPosZ();
		//up_Cam->GetTransform().SetPos(p_ActiveGO->GetTransform().position);
		up_Cam->SetLookAt(p_ActiveGO->GetTransform().position);
		up_Cam->Update();
	}

	return Scene::CurrentScene::NONE;
}

void LevelEditorScene::Render()
{

	for (auto& go : p_GameObjects)
	{
		go->Render();
	}
	up_Cam->Render();

	float matrixTranslation[3], matrixRotation[3], matrixScale[3];
	ImGuizmo::DecomposeMatrixToComponents(p_ActiveGO->GetMatrix().r[3].m128_f32, matrixTranslation, matrixRotation, matrixScale);
	ImGui::InputFloat3("Tr", matrixTranslation, 3);
	ImGui::InputFloat3("Rt", matrixRotation, 3);
	ImGui::InputFloat3("Sc", matrixScale, 3);
	ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, p_ActiveGO->GetMatrix().r[3].m128_f32);

	ImGui::Begin("Active GameObject");

	//ImGui::Text("Acceleration: %f: %f: %f", m_PhysicsData.m_Acceleration.x, m_PhysicsData.m_Acceleration.y, m_PhysicsData.m_Acceleration.z);
	//ImGui::Text("Velocity: %f: %f: %f", m_PhysicsData.m_Velocity.x, m_PhysicsData.m_Velocity.y, m_PhysicsData.m_Velocity.z);
	//ImGui::Text("Force: %f: %f", m_PhysicsData.m_Force.x, m_PhysicsData.m_Force.y);

	ImGui::End();


	ImGui::Begin("Active GameObject");

	ImGui::InputText("string", p_LevelName, IM_ARRAYSIZE(p_LevelName));
	//if (ImGui::Button("Save"))
	//	SaveLevel();



	//ImGui::Text("Acceleration: %f: %f: %f", m_PhysicsData.m_Acceleration.x, m_PhysicsData.m_Acceleration.y, m_PhysicsData.m_Acceleration.z);
	//ImGui::Text("Velocity: %f: %f: %f", m_PhysicsData.m_Velocity.x, m_PhysicsData.m_Velocity.y, m_PhysicsData.m_Velocity.z);
	//ImGui::Text("Force: %f: %f", m_PhysicsData.m_Force.x, m_PhysicsData.m_Force.y);

	ImGui::End();

	//ImGui::ShowDemoWindow(&showDemo);

	//ImGui::Begin("Object Data");

	////ImGui::Text("Pos: %f: %f: %f", m_Transform.position.m128_f32[0], m_Transform.position.m128_f32[1], m_Transform.position.m128_f32[2]);
	//ImGui::Text("Max: %f: %f: %f", m_BB.m_Max.x, m_BB.m_Max.y, m_BB.m_Max.z);
	//ImGui::Text("Min: %f: %f: %f", m_BB.m_Min.x, m_BB.m_Min.y, m_BB.m_Min.z);

	//ImGui::End();

	//if (p_Physics)
	//{
	//	ImGui::Begin("Physics Data");

	//	ImGui::Text("Acceleration: %f: %f: %f", m_PhysicsData.m_Acceleration.x, m_PhysicsData.m_Acceleration.y, m_PhysicsData.m_Acceleration.z);
	//	ImGui::Text("Velocity: %f: %f: %f", m_PhysicsData.m_Velocity.x, m_PhysicsData.m_Velocity.y, m_PhysicsData.m_Velocity.z);
	//	ImGui::Text("Force: %f: %f", m_PhysicsData.m_Force.x, m_PhysicsData.m_Force.y);

	//	ImGui::End();
	//}


}


void LevelEditorScene::SaveLevel()
{

}
