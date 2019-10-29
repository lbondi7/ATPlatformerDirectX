#include "Model.h"
#include "Locator.h"
#include "Graphics.h"

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;

Model::~Model()
{
}

void Model::Init()
{
	mWorldMatrix = dx::XMMatrixIdentity();
}

void Model::Update()
{
	mWorldMatrix = dx::XMMatrixTranspose(
		dx::XMMatrixRotationX(dx::XMConvertToRadians(dx::XMVectorGetX(transform.GetRot()))) *
		dx::XMMatrixRotationY(dx::XMConvertToRadians(dx::XMVectorGetY(transform.GetRot()))) *
		dx::XMMatrixRotationZ(dx::XMConvertToRadians(dx::XMVectorGetZ(transform.GetRot()))) *
		//dx::XMMatrixRotationRollPitchYawFromVector(transform.GetRot())*
		dx::XMMatrixScaling(dx::XMVectorGetX(transform.GetScale()),
			dx::XMVectorGetY(transform.GetScale()),
			dx::XMVectorGetZ(transform.GetScale())) *
		dx::XMMatrixTranslation(
			dx::XMVectorGetX(transform.GetPos()),
			dx::XMVectorGetY(transform.GetPos()),
			dx::XMVectorGetZ(transform.GetPos())));

	//m_worldMatrix = dx::XMMatrixTranspose(
	//	dx::XMMatrixRotationX(dx::XMConvertToRadians(dx::XMVectorGetX(transform.rotation))) *
	//	dx::XMMatrixRotationY(dx::XMConvertToRadians(dx::XMVectorGetY(transform.rotation))) *
	//	dx::XMMatrixRotationZ(dx::XMConvertToRadians(dx::XMVectorGetZ(transform.rotation))) *
	//	dx::XMMatrixScaling(dx::XMVectorGetX(transform.scale),
	//		dx::XMVectorGetY(transform.scale),
	//		dx::XMVectorGetZ(transform.scale)) *
	//	dx::XMMatrixTranslation(
	//		dx::XMVectorGetX(transform.position),
	//		dx::XMVectorGetY(transform.position),
	//		dx::XMVectorGetZ(transform.position)));
	//
	//m_worldMatrix = dx::XMMatrixTranspose(
	//	dx::XMMatrixRotationX(dx::XMConvertToRadians(dx::XMVectorGetX(rotation))) *
	//	dx::XMMatrixRotationY(dx::XMConvertToRadians(dx::XMVectorGetY(rotation))) *
	//	dx::XMMatrixRotationZ(dx::XMConvertToRadians(dx::XMVectorGetZ(rotation))) *
	//	dx::XMMatrixScaling(dx::XMVectorGetX(scale),
	//		dx::XMVectorGetY(scale),
	//		dx::XMVectorGetZ(scale)) *
	//	dx::XMMatrixTranslation(
	//		dx::XMVectorGetX(position),
	//		dx::XMVectorGetY(position),
	//		dx::XMVectorGetZ(position)));
}

void Model::Render(DirectX::XMMATRIX viewMatrix)
{
	viewMatrix = dx::XMMatrixTranspose(viewMatrix);

	Locator::GetGraphics()->Render(mWorldMatrix, viewMatrix, mModelType, mTexure, mShader);
}

Transform& Model::GetTransform()
{
	return transform;
}

//
//DirectX::XMVECTOR Model::GetPos()
//{
//	return position;
//}
//
//float Model::GetPosX()
//{
//	return dx::XMVectorGetX(position);
//}
//
//float Model::GetPosY()
//{
//	return dx::XMVectorGetY(position);
//}
//
//float Model::GetPosZ()
//{
//	return dx::XMVectorGetZ(position);
//}
//
//DirectX::XMVECTOR Model::GetRot()
//{
//	return rotation;
//}
//
//float Model::GetRotX()
//{
//	return dx::XMVectorGetX(rotation);
//}
//
//float Model::GetRotY()
//{
//	return dx::XMVectorGetY(rotation);
//}
//
//float Model::GetRotZ()
//{
//	return dx::XMVectorGetZ(rotation);
//}
//
//DirectX::XMVECTOR Model::GetScale()
//{
//	return DirectX::XMVECTOR();
//}
//
//float Model::GetScaleX()
//{
//	return dx::XMVectorGetX(scale);
//}
//
//float Model::GetScaleY()
//{
//	return dx::XMVectorGetY(scale);
//}
//
//float Model::GetScaleZ()
//{
//	return dx::XMVectorGetZ(scale);
//}
//
//void Model::SetPos(float x, float y, float z)
//{
//	position = { x, y, z, dx::XMVectorGetW(position) };
//}
//
//void Model::SetPosX(float x)
//{
//	position = { x, dx::XMVectorGetY(position), dx::XMVectorGetZ(position), dx::XMVectorGetW(position) };
//}
//
//void Model::SetPosY(float y)
//{
//	position = { dx::XMVectorGetX(position), y, dx::XMVectorGetZ(position), dx::XMVectorGetW(position) };
//}
//
//void Model::SetPosZ(float z)
//{
//	position = { dx::XMVectorGetX(position), dx::XMVectorGetY(position), z, dx::XMVectorGetW(position) };
//}
//
//void Model::SetRot(float x, float y, float z)
//{
//	rotation = { x, y, z, dx::XMVectorGetW(rotation) };
//}
//
//void Model::SetRotX(float x)
//{
//	rotation = { x, dx::XMVectorGetY(rotation), dx::XMVectorGetZ(rotation), dx::XMVectorGetW(rotation) };
//}
//
//void Model::SetRotY(float y)
//{
//	rotation = { dx::XMVectorGetX(rotation), y, dx::XMVectorGetZ(rotation), dx::XMVectorGetW(rotation) };
//}
//
//void Model::SetRotZ(float z)
//{
//	rotation = { dx::XMVectorGetX(rotation), dx::XMVectorGetY(rotation), z, dx::XMVectorGetW(rotation) };
//}
//
//void Model::SetScale(float x, float y, float z)
//{
//	scale = { x, y, z, dx::XMVectorGetW(scale) };
//}
//
//void Model::SetScaleX(float x)
//{
//	scale = { x, dx::XMVectorGetY(scale), dx::XMVectorGetZ(scale), dx::XMVectorGetW(scale) };
//}
//
//void Model::SetScaleY(float y)
//{
//	scale = { dx::XMVectorGetX(scale), y, dx::XMVectorGetZ(scale), dx::XMVectorGetW(scale) };
//}
//
//void Model::SetScaleZ(float z)
//{
//	scale = { dx::XMVectorGetX(scale), dx::XMVectorGetY(scale), z, dx::XMVectorGetW(scale) };
//}

const std::string& Model::ModelType()
{
	return mModelType;
}

void Model::ModelType(const std::string& _shapeType)
{
	mModelType = _shapeType;
}

const std::string& Model::Texture()
{
	return mTexure;
}

void Model::Texture(const std::string& _texType)
{
	mTexure = _texType;
}

const std::string& Model::Shader()
{
	return mShader;
}

void Model::Shader(const std::string& shaderType)
{
	mShader = shaderType;
}