#pragma once
#include "Constants.h"

#include <DirectXMath.h>

struct Transform
{
public:
	DirectX::XMVECTOR position = DirectX::XMVectorZero();
	DirectX::XMVECTOR rotation = DirectX::XMVectorZero();
	DirectX::XMVECTOR scale = {1.0f, 1.0f, 1.0f, 1.0f};

	void Update()
	{
		if (rotation.m128_f32[0] >= 360.0f || rotation.m128_f32[0] <= -360.0f)
		{
			rotation.m128_f32[0] = 0.0f;
		}
		if (rotation.m128_f32[1] >= 360.0f || rotation.m128_f32[1] <= -360.0f)
		{
			rotation.m128_f32[1] = 0.0f;
		}
		if (rotation.m128_f32[2] >= 360.0f || rotation.m128_f32[2] <= -360.0f)
		{
			rotation.m128_f32[2] = 0.0f;
		}
	}

	const DirectX::XMVECTOR& GetPos() { return position; }

	float GetPosX() { return position.m128_f32[0]; }

	float GetPosY() { return position.m128_f32[1]; }

	float GetPosZ() { return position.m128_f32[2]; }

	const DirectX::XMVECTOR& GetRot() { return rotation; }

	const DirectX::XMVECTOR& GetRotRad()
	{
		return DirectX::XMVECTOR{
			rotation.m128_f32[0] / RADIAN,
			rotation.m128_f32[1] / RADIAN,
			rotation.m128_f32[2] / RADIAN,
		    1.0f };
	}

	float GetRotX() { return rotation.m128_f32[0]; }

	float GetRotY() { return rotation.m128_f32[1]; }

	float GetRotZ() { return rotation.m128_f32[2]; }

	float GetRotXRad() { return rotation.m128_f32[0] / RADIAN; }

	float GetRotYRad() { return rotation.m128_f32[1] / RADIAN; }

	float GetRotZRad() { return rotation.m128_f32[2] / RADIAN; }

	const DirectX::XMVECTOR& GetScale() { return scale; }

	float GetScaleX() { return scale.m128_f32[0]; }

	float GetScaleY() { return scale.m128_f32[1]; }

	float GetScaleZ() { return scale.m128_f32[2]; }

	void SetPos(const DirectX::XMVECTOR& pos) { position = pos; }

	void SetPos(float x, float y, float z)
	{
		position.m128_f32[0] = x;
		position.m128_f32[1] = y;
		position.m128_f32[2] = z;
		//position = { x, y, z, DirectX::XMVectorGetW(position) };
	}

	void SetPosX(float x){ position.m128_f32[0] = x; }

	void SetPosY(float y) { position.m128_f32[1] = y; }

	void SetPosZ(float z) { position.m128_f32[2] = z; }

	void SetRot(const DirectX::XMVECTOR& _rotation) { rotation = _rotation; }

	void SetRot(float x, float y, float z)
	{
		rotation.m128_f32[0] = x;
		rotation.m128_f32[1] = y;
		rotation.m128_f32[2] = z;
		//rotation = { x, y, z, DirectX::XMVectorGetW(rotation) };
	}

	void SetRotX(float x) { rotation.m128_f32[0] = x; }

	void SetRotY(float y) { rotation.m128_f32[1] = y; }

	void SetRotZ(float z) { rotation.m128_f32[2] = z; }

	void SetScale(const DirectX::XMVECTOR& _scale) { scale = _scale; }

	void SetScale(float x, float y, float z)
	{
		scale.m128_f32[0] = x;
		scale.m128_f32[1] = y;
		scale.m128_f32[2] = z;
		//scale = { x, y, z, DirectX::XMVectorGetW(scale) };
	}

	void SetScaleX(float x) { scale.m128_f32[0] = x; }

	void SetScaleY(float y) { scale.m128_f32[1] = y; }

	void SetScaleZ(float z) { scale.m128_f32[2] = z; }
};