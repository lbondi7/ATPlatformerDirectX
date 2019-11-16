#include "GameObject.h"
#include "Locator.h"
#include "Vertices.h"
#include "imgui/imgui.h"

using namespace DirectX;

GameObject::~GameObject()
{
	if (pModel)
	{
		delete pModel;
		pModel = nullptr;
	}

	if (pPlayer)
	{
		delete pPlayer;
		pPlayer = nullptr;
	}
}

void GameObject::Init()
{
	mTransform.SetPos(XMVectorZero());
	mTransform.SetRot(XMVectorZero());
	mTransform.SetScale({1.0f, 1.0f, 1.0f});
	mVerts = Locator::GetVertices()->GetVertices("cube");
	mBB.CalculateBoundingBox(mTransform.GetPos(), mVerts, mObjMatrix);
}

void GameObject::AddModel()
{
	if (!pModel)
	{
		pModel = new Model();
		pModel->Init();
	}
}

Model* GameObject::GetModel()
{
	return pModel;
}

void GameObject::AddPlayer()
{
	if (!pPlayer)
	{
		pPlayer = new Player();
		pPlayer->Init();
	}
}

Player* GameObject::GetPlayer()
{
	return pPlayer;
}

void GameObject::Update(const Matrix& worldMatrix)
{
	mTransform.Update();
	mObjMatrix = XMMatrixTranspose(
		XMMatrixRotationRollPitchYawFromVector(mTransform.GetRotRad()) *
		XMMatrixScalingFromVector(mTransform.GetScale()) *
		XMMatrixTranslationFromVector(mTransform.GetPos()));

	if (pPlayer)
	{
		pPlayer->Update(mTransform);
	}

	if (pModel)
	{
		pModel->Update(mObjMatrix, mTransform);
	}
	mBB.CalculateBoundingBox(mTransform.GetPos(), mVerts, mObjMatrix);
}

void GameObject::Render()
{
	if (pModel)
	{
		pModel->Render(mObjMatrix);
	}
}

Transform& GameObject::GetTransform()
{
	return mTransform;
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
	return mBB;
}

Matrix GameObject::GetMatrix()
{
	return mObjMatrix;
}
