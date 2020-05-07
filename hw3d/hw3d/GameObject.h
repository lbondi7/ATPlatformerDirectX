#pragma once
#include "Model.h"
#include "Player.h"
#include "Bounds.h"
#include "RenderData.h"
#include "Constants.h"
#include "Physics.h"
#include "InstanceData.h"

#include <vector>

class GameObject
{
public:

	GameObject() = default;
	~GameObject();

	void Init();
	void Init(ModelType model, TextureType texture, ShaderType shader);
	void InitRenderData();

	void InitInstance(int instanceCount, std::vector<Vec4>& positions);

	void AddModel();
	Model* GetModel();

	void AddPlayer();
	Player* GetPlayer();

	void AddPhysics();
	Physics* GetPhysics();

	void Update();
	void Render();

	Transform& GetTransform();

	GameObjectTag GetTag();

	void SetTag(GameObjectTag _tag);

	Bounds& GetBB();

	Matrix& GetMatrix();

	RenderData& GetRenderData() { return m_RenderData; }

	PhysicsData& GetPhysicsData() { return m_PhysicsData; }

	std::vector<int>& BoundIDs() { return m_BoundsID; }

private:

	Model* p_Model = nullptr;
	Player* p_Player = nullptr;
	Physics* p_Physics = nullptr;
	Transform m_Transform;

	ModelType m_Model;
	TextureType m_Texture;
	ShaderType m_Shader;

	PhysicsData m_PhysicsData;

	GameObjectTag tag = GameObjectTag::STATIC;

	Matrix m_ObjMatrix = DirectX::XMMatrixIdentity();
	std::vector<Float3> m_Verts;

	MatrixBufferData matrices;
	RenderData m_RenderData;
	Bounds m_BB;

	std::vector<int> m_BoundsID;
	//int m_BoundsID = 0;

};

