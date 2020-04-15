#include "GameObject.h"
#include "Locator.h"
#include "Vertices.h"
#include "D3D.h"
#include "Graphics.h"
#include "ResourceData.h"

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
	//mVerts = Locator::GetVertices()->GetVertices("cube");
	std::vector<unsigned short> indices = Locator::GetVertices()->GetIndices("cube");
	renderData.VertexBuffer.CreateBuffer(D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DEFAULT, 0u, 
		mVerts.data(), sizeof(mVerts[0]) * mVerts.size(), sizeof(mVerts[0]));
	renderData.IndexBuffer.CreateBuffer(D3D11_BIND_INDEX_BUFFER, D3D11_USAGE_DEFAULT, 0u, 
		indices.data(), sizeof(indices[0]) * indices.size(), sizeof(indices[0]));
	renderData.ConstantBuffer.CreateBuffer(D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE, 
		&matrices, sizeof(MatrixBufferType), 0u);
	renderData.indexCount = indices.size();

	mBB.CalculateBoundingBox(mTransform.GetPos(), mVerts, mObjMatrix);
}

void GameObject::Init(std::string mod)
{
	mTransform.SetPos(XMVectorZero());
	mTransform.SetRot(XMVectorZero());
	mTransform.SetScale({ 1.0f, 1.0f, 1.0f });
	//mVerts = Locator::GetVertices()->GetVertices("cube");
	std::vector<VertexType> vertices = Locator::GetVertices()->GetVertices(mod);
	std::vector<unsigned short> indices = Locator::GetVertices()->GetIndices(mod);
	renderData.VertexBuffer.CreateBuffer(D3D11_BIND_VERTEX_BUFFER, D3D11_USAGE_DEFAULT, 0u,
		vertices.data(), sizeof(VertexType) * vertices.size(), sizeof(VertexType));
	renderData.IndexBuffer.CreateBuffer(D3D11_BIND_INDEX_BUFFER, D3D11_USAGE_DEFAULT, 0u,
		indices.data(), sizeof(indices[0]) * indices.size(), sizeof(unsigned short));
	renderData.ConstantBuffer.CreateBuffer(D3D11_BIND_CONSTANT_BUFFER, D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE,
		&matrices, sizeof(MatrixBufferType), 0u);
	renderData.indexCount = indices.size();
	renderData.vertexCount = vertices.size();
	renderData.texture.CreateTexture(Locator::GetResourceData()->images["Simon"]);
	//mBB.CalculateBoundingBox(mTransform.GetPos(), mVerts, mObjMatrix);
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

	//if (pPlayer)
	//{
	//	pPlayer->Update(mTransform);
	//}

	if (pModel)
	{
		pModel->Update(mObjMatrix, mTransform);
	}

	matrices.world = mObjMatrix;
	matrices.view = DirectX::XMMatrixTranspose(Locator::GetD3D()->GetViewMatrix());
	matrices.projection = DirectX::XMMatrixTranspose(Locator::GetD3D()->GetProjMatrix());
	//dx::XMMatrixTranspose(d3d->GetProjMatrix());
	//d3d->GetViewMatrix();
	//dx::XMMatrixTranspose(mViewMatrixCopy);

	if (FAILED(renderData.ConstantBuffer.MapToGPU(&matrices, sizeof(MatrixBufferType))))
	{
		int x = 0;
	}
	//mBB.CalculateBoundingBox(mTransform.GetPos(), mVerts, mObjMatrix);
}

void GameObject::Render()
{
	if (pModel)
	{
		Locator::GetGraphics()->Render(&renderData, pModel->Texture(), pModel->Shader());
		//pModel->Render(mObjMatrix);
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
