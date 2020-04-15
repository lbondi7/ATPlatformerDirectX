#pragma once
#include "Model.h"
#include "Player.h"
#include "Bounds.h"
#include "RenderData.h"
#include "Constants.h"

#include <vector>

class GameObject
{
public:

	GameObject() = default;
	~GameObject();

	void Init();
	void Init(std::string mod);
	void AddModel();
	Model* GetModel();

	void AddPlayer();
	Player* GetPlayer();

	void Update(const Matrix& worldMatrix);
	void Render();

	Transform& GetTransform();

	GameObjectTag GetTag();

	void SetTag(GameObjectTag _tag);

	Bounds& GetBB();

	Matrix GetMatrix();

private:

	Model* pModel = nullptr;
	Player* pPlayer = nullptr;
	Transform mTransform;

	GameObjectTag tag = GameObjectTag::STATIC;

	Matrix mObjMatrix;
	std::vector<Vector> mVerts;

	MatrixBufferType matrices;

	RenderData renderData;
	Bounds mBB;
};

