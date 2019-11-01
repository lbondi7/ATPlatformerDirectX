#include "GameObject.h"
#include "Locator.h"
#include "Vertices.h"

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
	mTransform.SetScale({1, 1, 1});
	mVerts = Locator::GetVertices()->GetVertices("cube");
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

	if (pPlayer)
	{
		//model->Update(transform);
		pPlayer->Update(mTransform);
	}

	if (pModel)
	{
		//model->Update(transform);
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

//void GameObject::CalculateBoundingBox(const Matrix& worldMatrix)
//{
//
//	XMFLOAT3 minVert = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
//	XMFLOAT3 maxVert = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
//	//auto length = verts.size();
//	Vector vec;
//	for (size_t i = 0; i < mVerts.size(); i++)
//	{
//		vec = mVerts[i];
//
//		vec = VectorTransform(vec, worldMatrix);
//
//		//Get the smallest vertex 
//		minVert.x = min(minVert.x, XMVectorGetX(vec));
//		minVert.y = min(minVert.y, XMVectorGetY(vec));
//		minVert.z = min(minVert.z, XMVectorGetZ(vec));
//
//		//Get the largest vertex 
//		maxVert.x = max(maxVert.x, XMVectorGetX(vec));
//		maxVert.y = max(maxVert.y, XMVectorGetY(vec));
//		maxVert.z = max(maxVert.z, XMVectorGetZ(vec));
//	}
//
//	mBBMin = { minVert.x, minVert.y, minVert.z };
//	mBBMax = { maxVert.x, maxVert.y, maxVert.z };
//
//	mBBMin = VectorAdd(mTransform.GetPos(), mBBMin);
//	mBBMax = VectorAdd(mTransform.GetPos(), mBBMax);
//}
//
//bool GameObject::IsInside(const Vector& objBBMinVertex,
//	const Vector& objBBMaxVertex)
//{
//	//Is obj1's max X greater than obj2's min X? If not, obj1 is to the LEFT of obj2
//	if (XMVectorGetX(mBBMax) > XMVectorGetX(objBBMinVertex))
//
//		//Is obj1's min X less than obj2's max X? If not, obj1 is to the RIGHT of obj2
//		if (XMVectorGetX(mBBMin) < XMVectorGetX(objBBMaxVertex))
//
//			//Is obj1's max Y greater than obj2's min Y? If not, obj1 is UNDER obj2
//			if (XMVectorGetY(mBBMax) > XMVectorGetY(objBBMinVertex))
//
//				//Is obj1's min Y less than obj2's max Y? If not, obj1 is ABOVE obj2
//				if (XMVectorGetY(mBBMin) < XMVectorGetY(objBBMaxVertex))
//
//					//Is obj1's max Z greater than obj2's min Z? If not, obj1 is IN FRONT OF obj2
//					if (XMVectorGetZ(mBBMax) > XMVectorGetZ(objBBMinVertex))
//
//						//Is obj1's min Z less than obj2's max Z? If not, obj1 is BEHIND obj2
//						if (XMVectorGetZ(mBBMin) < XMVectorGetZ(objBBMaxVertex))
//
//							//If we've made it this far, then the two bounding boxes are colliding
//							return true;
//
//	//If the two bounding boxes are not colliding, then return false
//	return false;
//}
//
//Vector GameObject::GetMinVert()
//{
//	return mBBMin;
//}
//
//Vector GameObject::GetMaxVert()
//{
//	return mBBMax;
//}

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
