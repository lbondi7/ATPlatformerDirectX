#pragma once

#include <DirectXMath.h>

class Camera
{
public: 
	Camera();
	~Camera();

	void Update();
	void Render();


	DirectX::XMVECTOR GetPos();
	float GetPosX();
	float GetPosY();
	float GetPosZ();

	DirectX::XMVECTOR GetRot();
	float GetRotX();
	float GetRotY();
	float GetRotZ();

	void SetPos(DirectX::XMVECTOR pos);
	void SetPos(float x, float y, float z);
	void SetPosX(float x);
	void SetPosY(float y);
	void SetPosZ(float z);
	void SetRot(DirectX::XMVECTOR rot);
	void SetRot(float x, float y, float z);
	void SetRotX(float x);
	void SetRotY(float y);
	void SetRotZ(float z);

	DirectX::XMMATRIX GetViewMatrix();
	void SetViewMatrix(DirectX::XMMATRIX matrix);

private:

	DirectX::XMMATRIX mViewMatrix;
	DirectX::XMVECTOR position;
	DirectX::XMVECTOR rotation;
	DirectX::XMMATRIX rotationMatrix;
	DirectX::XMVECTOR up;
	DirectX::XMVECTOR lookAt;
};

