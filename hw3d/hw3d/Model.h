#pragma once

#include "Transform.h"
#include "Maths.h"

#include <string>
#include <DirectXMath.h>
#include <wrl.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <stdio.h>

class Model
{
public:
	Model()  = default;
	~Model();

	void Init();
	void Update(Matrix& worldMatrix, Transform& objtrans);
	void Render(const Matrix& worldMatrix);

	Transform& GetOffset();

	const std::string& ModelType();
	void ModelType(const std::string& _shapeType);
	const std::string& Texture();
	void Texture(const std::string& _shapeType);
	const std::string& Shader();
	void Shader(const std::string& _shapeType);

private:

	std::string mModelType = "iso";
	std::string mTexure = "Simon";
	std::string mShader = "basic";

	DirectX::XMMATRIX mWorldMatrix;
	Transform transform;
};