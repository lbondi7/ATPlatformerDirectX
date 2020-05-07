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
	m_Transform.SetPos(dx::XMVectorZero());
	m_Transform.SetRot(dx::XMVectorZero());
	m_Transform.SetScale({1.0f, 1.0f, 1.0f, 1.0f});
}

void Model::Update(Matrix& objMatrix, Transform& goTransform)
{
	m_Transform.Update();

	mModelMatrix = dx::XMMatrixTranspose(
	dx::XMMatrixRotationRollPitchYawFromVector(m_Transform.GetRotRad())*
		dx::XMMatrixScalingFromVector(m_Transform.GetScale())*
		dx::XMMatrixTranslationFromVector(m_Transform.GetPos()));
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
	//Locator::GetGraphics()->Render(mModelMatrix, mModelType, mTexure, mShader);
}

Transform& Model::GetOffset()
{
	return m_Transform;
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