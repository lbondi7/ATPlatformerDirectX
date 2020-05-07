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

	void SetLookAt(const Vec4& _lookAt);
	void SetRotMatrix(const Matrix& rotMat);

	Transform& GetTransform();

	void SetOffset(const Vec4& _offset);

	void SetPhiTheta(float _phi, float _theta);

private:

	DirectX::XMMATRIX* mViewMatrix = nullptr;
	DirectX::XMMATRIX m_RotationMatrix;
	Vec4 m_Up, m_LookAtPos, m_Offset;
	float phi = 0, theta = 0;
	Transform m_Transform;
};

