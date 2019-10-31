#pragma once
#include "Model.h"
#include "Transform.h"
#include "Maths.h"

class GameObject
{
public:
	GameObject() = default;
	~GameObject();

	void Init();
	void AddModel();
	Model* GetModel();

	void Update(const Matrix& worldMatrix);
	void Render();

	Transform& GetTransform();

	bool BoundingBoxCollision(const Vector4& objBBMinVertex, const Vector4& objBBMaxVertex);

	Vector4 GetMinVert();
	Vector4 GetMaxVert();

private:

	Model* pModel = nullptr;
	Transform mTransform;

	Vector4 mBBMin;
	Vector4 mBBMax;

	Matrix mObjMatrix;
	void CalculateBoundingBox(const Matrix& worldMatrix);
};

