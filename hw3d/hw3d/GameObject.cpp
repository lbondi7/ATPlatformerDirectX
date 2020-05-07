#include "GameObject.h"
#include "Locator.h"
#include "Vertices.h"
#include "D3D.h"
#include "Graphics.h"
#include "ResourceData.h"

#include "imgui/imgui.h"

GameObject::~GameObject()
{
	if (p_Model)
	{
		delete p_Model;
		p_Model = nullptr;
	}

	if (p_Player)
	{
		delete p_Player;
		p_Player = nullptr;
	}
}

void GameObject::Init()
{

}

void GameObject::Init(ModelType model, TextureType texture, ShaderType shader)
{
	m_Transform.SetPos({ 0.0f, 0.0f, 0.0f , 1.0f});
	m_Transform.SetRot({ 0.0f, 0.0f, 0.0f , 1.0f});
	m_Transform.SetScale({ 1.0f, 1.0f, 1.0f , 1.0f});

	m_Model = model;
	m_Texture = texture;
	m_Shader = shader;
	InitRenderData();

	m_Verts = Locator::GetResources()->m_Data.m_MeshData[Locator::GetResources()->m_Data.m_ModelIDMap[m_Model]].vectors;

	m_BB.CalculateBoundingBox(m_Transform.GetPos(), m_Verts, m_ObjMatrix);
}

void GameObject::InitRenderData()
{
	m_RenderData.up_MatrixBuffer = std::make_unique<Buffer>();
	m_RenderData.up_MatrixBuffer->CreateBuffer(D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE,
		&matrices, sizeof(MatrixBufferData));
	m_RenderData.up_LightBuffer = std::make_unique<Buffer>();
	m_RenderData.up_LightBuffer->CreateBuffer(D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE,
		nullptr, sizeof(LightBufferData));
	m_RenderData.m_IndexCount = Locator::GetResources()->m_Data.m_MeshData[Locator::GetResources()->m_Data.m_ModelIDMap[m_Model]].indexCount;
	m_RenderData.m_VertexCount = Locator::GetResources()->m_Data.m_MeshData[Locator::GetResources()->m_Data.m_ModelIDMap[m_Model]].vertexCount;
	m_RenderData.p_VertexBuffer = Locator::GetResources()->up_VerticesMap[m_Model].get();
	m_RenderData.p_IndexBuffer = Locator::GetResources()->up_IndicesMap[m_Model].get();
	m_RenderData.p_Texture = Locator::GetResources()->up_TextureMap[m_Texture].get();
	m_RenderData.p_Shader = Locator::GetResources()->up_ShaderMap[m_Shader].get();

	//renderData.m_LightBuffer.CreateBuffer(D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE, nullptr, sizeof(LightBufferData));
}

void GameObject::InitInstance(int instanceCount, std::vector<Vec4>& positions)
{
	m_RenderData.m_DrawInstanced = true;
	m_RenderData.up_InstanceData = std::make_unique<InstanceData>();
	m_RenderData.up_InstanceData->instanceCount = instanceCount;
	m_RenderData.up_InstanceData->positions = positions;
	m_RenderData.up_InstanceBuffer = std::make_unique<Buffer>();
	m_RenderData.up_InstanceBuffer->CreateBuffer(D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DEFAULT, 0u,
		m_RenderData.up_InstanceData->positions.data(), m_RenderData.up_InstanceData->instanceCount * sizeof(Vec4), sizeof(Vec4));

	m_Shader = ShaderType::INSTANCE;
	m_RenderData.p_Shader = Locator::GetResources()->up_ShaderMap[m_Shader].get();
	m_PhysicsData.physicsTag = PhysicsTag::STATIC;
}


void GameObject::AddModel()
{
	if (!p_Model)
	{
		p_Model = new Model();
		p_Model->Init();
	}
}

Model* GameObject::GetModel()
{
	return p_Model;
}

void GameObject::AddPlayer()
{
	if (!p_Player)
	{
		p_Player = new Player();
		p_Player->Init();
	}
}

Player* GameObject::GetPlayer()
{
	return p_Player;
}

void GameObject::AddPhysics()
{
	if (!p_Physics)
	{
		p_Physics = new Physics();
		p_Physics->Init();
		Float3 dir = { 0.0f, -1.0f, 0.0f };
		Float3 origin = Utilities::ConvertToFloat3(m_Transform.GetPos());
		origin.y -= m_Transform.GetScaleY();
		p_Physics->GetRay().Origin(origin);
		p_Physics->GetRay().Direction(dir);
	}
}

Physics* GameObject::GetPhysics()
{
	return p_Physics;
}

void GameObject::Update()
{
	m_Transform.Update();
	m_ObjMatrix = DirectX::XMMatrixScalingFromVector(m_Transform.GetScale()) * 
		DirectX::XMMatrixRotationRollPitchYawFromVector(m_Transform.GetRotRad())  *
		DirectX::XMMatrixTranslationFromVector(m_Transform.GetPos());

	if (p_Player)
		p_Player->Update(m_PhysicsData, m_Transform);

	if (p_Model)
		p_Model->Update(m_ObjMatrix, m_Transform);

	if (p_Physics)
		p_Physics->Update(m_PhysicsData, m_Transform);

	m_BB.CalculateBoundingBox(m_Transform.GetPos(), m_Verts, m_ObjMatrix);

	matrices.world = DirectX::XMMatrixTranspose(m_ObjMatrix);
	matrices.view = DirectX::XMMatrixTranspose(Locator::GetD3D()->GetViewMatrix());
	matrices.projection = DirectX::XMMatrixTranspose(Locator::GetD3D()->GetProjMatrix());

	m_RenderData.up_MatrixBuffer->MapToGPU(&matrices, sizeof(MatrixBufferData));
}

void GameObject::Render()
{

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

	if (p_Model)
	{
		Locator::GetGraphics()->Render(&m_RenderData);
		//pModel->Render(mObjMatrix);
	}
}

Transform& GameObject::GetTransform()
{
	return m_Transform;
}

GameObjectTag GameObject::GetTag()
{
	return tag;
}

void GameObject::SetTag(GameObjectTag _tag)
{
	tag = _tag;
}

Bounds& GameObject::GetBB()
{
	return m_BB;
}

Matrix& GameObject::GetMatrix()
{
	return m_ObjMatrix;
}
