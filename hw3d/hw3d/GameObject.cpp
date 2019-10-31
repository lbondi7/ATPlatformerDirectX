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
}

void GameObject::Init()
{
	mTransform.SetPos(DirectX::XMVectorZero());
	mTransform.SetRot(DirectX::XMVectorZero());
	mTransform.SetScale({1, 1, 1, 1});
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

void GameObject::Update(const Matrix& worldMatrix)
{
	mTransform.Update();

	if (pModel)
	{
		//model->Update(transform);
		pModel->Update(mObjMatrix, mTransform);
	}
	CalculateBoundingBox(mObjMatrix);
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

void GameObject::CalculateBoundingBox(const Matrix& worldMatrix)
{

	XMFLOAT3 minVert = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
	XMFLOAT3 maxVert = XMFLOAT3(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	std::vector<Vector4> verts = Locator::GetVertices()->GetVertices("cube");
	size_t length = verts.size();
	Vector4 vec;
	for (size_t i = 0; i < length; i++)
	{
		vec = verts[i];

		vec = VectorTransform(vec, worldMatrix);

		//Get the smallest vertex 
		minVert.x = min(minVert.x, XMVectorGetX(vec));
		minVert.y = min(minVert.y, XMVectorGetY(vec));
		minVert.z = min(minVert.z, XMVectorGetZ(vec));

		//Get the largest vertex 
		maxVert.x = max(maxVert.x, XMVectorGetX(vec));
		maxVert.y = max(maxVert.y, XMVectorGetY(vec));
		maxVert.z = max(maxVert.z, XMVectorGetZ(vec));
	}

	mBBMin = { minVert.x, minVert.y, minVert.z };
	mBBMax = { maxVert.x, maxVert.y, maxVert.z };

	//mBBMin = VectorTransform(mBBMin, worldMatrix);
	//mBBMax = VectorTransform(mBBMax, worldMatrix);

	mBBMin = VectorAdd(mTransform.GetPos(), mBBMin);
	mBBMax = VectorAdd(mTransform.GetPos(), mBBMax);
}

bool GameObject::BoundingBoxCollision(const Vector4& objBBMinVertex,
	const Vector4& objBBMaxVertex)
{
	//Is obj1's max X greater than obj2's min X? If not, obj1 is to the LEFT of obj2
	if (XMVectorGetX(mBBMax) > XMVectorGetX(objBBMinVertex))

		//Is obj1's min X less than obj2's max X? If not, obj1 is to the RIGHT of obj2
		if (XMVectorGetX(mBBMin) < XMVectorGetX(objBBMaxVertex))

			//Is obj1's max Y greater than obj2's min Y? If not, obj1 is UNDER obj2
			if (XMVectorGetY(mBBMax) > XMVectorGetY(objBBMinVertex))

				//Is obj1's min Y less than obj2's max Y? If not, obj1 is ABOVE obj2
				if (XMVectorGetY(mBBMin) < XMVectorGetY(objBBMaxVertex))

					//Is obj1's max Z greater than obj2's min Z? If not, obj1 is IN FRONT OF obj2
					if (XMVectorGetZ(mBBMax) > XMVectorGetZ(objBBMinVertex))

						//Is obj1's min Z less than obj2's max Z? If not, obj1 is BEHIND obj2
						if (XMVectorGetZ(mBBMin) < XMVectorGetZ(objBBMaxVertex))

							//If we've made it this far, then the two bounding boxes are colliding
							return true;

	//If the two bounding boxes are not colliding, then return false
	return false;
}

Vector4 GameObject::GetMinVert()
{
	return mBBMin;
}

Vector4 GameObject::GetMaxVert()
{
	return mBBMax;
}
