#pragma once
#include <DirectXMath.h>

struct Transform
{
public:
	DirectX::XMVECTOR position = DirectX::XMVectorZero();
	DirectX::XMVECTOR rotation = DirectX::XMVectorZero();
	DirectX::XMVECTOR scale = {1, 1, 1, 1};

	void Update()
	{
		if (DirectX::XMVectorGetX(rotation) >= 360.0f)
		{
			DirectX::XMVectorSetX(rotation, 0.0f);
		}
		if (DirectX::XMVectorGetY(rotation) >= 360.0f)
		{
			DirectX::XMVectorSetY(rotation, 0.0f);
		}
		if (DirectX::XMVectorGetZ(rotation) >= 360.0f)
		{
			DirectX::XMVectorSetZ(rotation, 0.0f);
		}
	}

	const DirectX::XMVECTOR& GetPos()
	{
		return position;
	}

	float GetPosX()
	{
		return DirectX::XMVectorGetX(position);
	}

	float GetPosY()
	{
		return DirectX::XMVectorGetY(position);
	}

	float GetPosZ()
	{
		return DirectX::XMVectorGetZ(position);
	}

	const DirectX::XMVECTOR& GetRot()
	{
		return rotation;
	}

	const DirectX::XMVECTOR& GetRotRad()
	{
		return DirectX::XMVECTOR{
			DirectX::XMConvertToRadians(DirectX::XMVectorGetX(rotation)),
			DirectX::XMConvertToRadians(DirectX::XMVectorGetY(rotation)),
			DirectX::XMConvertToRadians(DirectX::XMVectorGetZ(rotation)),
		    1.0f };
	}

	float GetRotX()
	{
		return DirectX::XMVectorGetX(rotation);
	}

	float GetRotY()
	{
		return DirectX::XMVectorGetY(rotation);
	}

	float GetRotZ()
	{
		return DirectX::XMVectorGetZ(rotation);
	}

	float GetRotXRad()
	{
		return DirectX::XMConvertToRadians(DirectX::XMVectorGetX(rotation));
	}

	float GetRotYRad()
	{
		return DirectX::XMConvertToRadians(DirectX::XMVectorGetY(rotation));
	}

	float GetRotZRad()
	{
		return DirectX::XMConvertToRadians(DirectX::XMVectorGetZ(rotation));
	}

	const DirectX::XMVECTOR& GetScale()
	{
		return scale;
	}

	float GetScaleX()
	{
		return DirectX::XMVectorGetX(scale);
	}

	float GetScaleY()
	{
		return DirectX::XMVectorGetY(scale);
	}

	float GetScaleZ()
	{
		return DirectX::XMVectorGetZ(scale);
	}

	void SetPos(const DirectX::XMVECTOR& pos)
	{
		position = pos;
	}

	void SetPos(float x, float y, float z)
	{
		position = { x, y, z, DirectX::XMVectorGetW(position) };
	}

	void SetPosX(float x)
	{
		position = { x, DirectX::XMVectorGetY(position), DirectX::XMVectorGetZ(position), DirectX::XMVectorGetW(position) };
	}

	void SetPosY(float y)
	{
		position = { DirectX::XMVectorGetX(position), y, DirectX::XMVectorGetZ(position), DirectX::XMVectorGetW(position) };
	}

	void SetPosZ(float z)
	{
		position = { DirectX::XMVectorGetX(position), DirectX::XMVectorGetY(position), z, DirectX::XMVectorGetW(position) };
	}

	void SetRot(const DirectX::XMVECTOR& _rotation)
	{
		rotation = _rotation;
	}

	void SetRot(float x, float y, float z)
	{
		rotation = { x, y, z, DirectX::XMVectorGetW(rotation) };
	}

	void SetRotX(float x)
	{
		rotation = { x, DirectX::XMVectorGetY(rotation), DirectX::XMVectorGetZ(rotation), DirectX::XMVectorGetW(rotation) };
	}

	void SetRotY(float y)
	{
		rotation = { DirectX::XMVectorGetX(rotation), y, DirectX::XMVectorGetZ(rotation), DirectX::XMVectorGetW(rotation) };
	}

	void SetRotZ(float z)
	{
		rotation = { DirectX::XMVectorGetX(rotation), DirectX::XMVectorGetY(rotation), z, DirectX::XMVectorGetW(rotation) };
	}

	void SetScale(const DirectX::XMVECTOR& _scale)
	{
		scale = _scale;
	}

	void SetScale(float x, float y, float z)
	{
		scale = { x, y, z, DirectX::XMVectorGetW(scale) };
	}

	void SetScaleX(float x)
	{
		scale = { x, DirectX::XMVectorGetY(scale), DirectX::XMVectorGetZ(scale), DirectX::XMVectorGetW(scale) };
	}

	void SetScaleY(float y)
	{
		scale = { DirectX::XMVectorGetX(scale), y, DirectX::XMVectorGetZ(scale), DirectX::XMVectorGetW(scale) };
	}

	void SetScaleZ(float z)
	{
		scale = { DirectX::XMVectorGetX(scale), DirectX::XMVectorGetY(scale), z, DirectX::XMVectorGetW(scale) };
	}
};