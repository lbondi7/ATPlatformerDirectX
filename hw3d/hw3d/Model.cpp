#include "Model.h"
#include "Locator.h"
#include "Graphics.h"

#include <DirectXCollision.h>

namespace dx = DirectX;

Model::~Model()
{
}

void Model::Init()
{
	mWorldMatrix = dx::XMMatrixIdentity();
	transform.SetPos(dx::XMVectorZero());
	transform.SetRot(dx::XMVectorZero());
	transform.SetScale({1, 1, 1, 1});
}

void Model::Update(Matrix& objMatrix, Transform& goTransform)
{
	transform.Update();

	objMatrix = dx::XMMatrixTranspose(
		//dx::XMMatrixRotationRollPitchYawFromVector(goTransform.GetRotRad()) *
		dx::XMMatrixRotationRollPitchYaw(goTransform.GetRotXRad(),
			goTransform.GetRotYRad(),
			goTransform.GetRotZRad()) *
		dx::XMMatrixScalingFromVector(goTransform.GetScale()) *
		dx::XMMatrixTranslationFromVector(goTransform.GetPos()));
		//dx::XMMatrixRotationRollPitchYawFromVector(transform.GetRotRad()) *
		//dx::XMMatrixScalingFromVector(transform.GetScale()) *
		//dx::XMMatrixTranslationFromVector(transform.GetPos())
}

void Model::Render(const Matrix& worldMatrix)
{
	Locator::GetGraphics()->Render(worldMatrix, mModelType, mTexure, mShader);
}

Transform& Model::GetOffset()
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