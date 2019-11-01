#pragma once
#include "Transform.h"
#include "Maths.h"

class Camera
{
public: 
	Camera();
	~Camera();

	void Init();
	void Update();
	void Render();

	void SetLookAt(const Vector& _lookAt);
	void SetRotMatrix(const Matrix& rotMat);

	Transform& GetTransform();

	void SetOffset(const Vector& _offset);

	void SetPhiTheta(float _phi, float _theta);

private:

	DirectX::XMMATRIX* mViewMatrix = nullptr;
	DirectX::XMMATRIX rotationMatrix;
	DirectX::XMVECTOR up, lookAtPos, offset;
	float phi = 0, theta = 0;
	Transform transform;
};

