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
	mModelMatrix = dx::XMMatrixIdentity();
	mTransform.SetPos(dx::XMVectorZero());
	mTransform.SetRot(dx::XMVectorZero());
	mTransform.SetScale({1.0f, 1.0f, 1.0f, 1.0f});
}

void Model::Update(Matrix& objMatrix, Transform& goTransform)
{
	mTransform.Update();

	mModelMatrix = dx::XMMatrixTranspose(
	dx::XMMatrixRotationRollPitchYawFromVector(mTransform.GetRotRad())*
		dx::XMMatrixScalingFromVector(mTransform.GetScale())*
		dx::XMMatrixTranslationFromVector(mTransform.GetPos()));
	mModelMatrix *= objMatrix;
	//dx::XMMatrixRotationRollPitchYawFromVector(goTransform.GetRotRad()) *
//dx::XMMatrixRotationRollPitchYaw(goTransform.GetRotXRad(),
//	goTransform.GetRotYRad(),
//	goTransform.GetRotZRad()) *
//dx::XMMatrixScalingFromVector(goTransform.GetScale()) *
//dx::XMMatrixTranslationFromVector(goTransform.GetPos()));
}

void Model::Render(const Matrix& worldMatrix)
{
	Locator::GetGraphics()->Render(mModelMatrix, mModelType, mTexure, mShader);
}

Transform& Model::GetOffset()
{
	return mTransform;
}

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