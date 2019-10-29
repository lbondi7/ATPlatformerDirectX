#include "Camera.h"

namespace dx = DirectX;

Camera::Camera()
{
	position = { 0, 0, 0, 0 };
	rotation = { 0, 0, 0, 0 };
}

Camera::~Camera()
{
}

void Camera::Update()
{
	up = { 0.0f, 1.0f, 0.0f, 1.0f };

	// Setup the position of the camera in the world.
	position = GetPos();

	// Setup where the camera is looking by default.
	lookAt = { 0.0f, 0.0f, 1.0f, 1.0f };

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = dx::XMMatrixRotationRollPitchYaw(
		GetRotY() * 0.0174532925f,
		GetRotX() * 0.0174532925f,
		GetRotZ() * 0.0174532925f);


	lookAt = dx::XMVector4Transform(lookAt, rotationMatrix);
	up = dx::XMVector4Transform(up, rotationMatrix);
	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	//D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	//D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	// Translate the rotated camera position to the location of the viewer.
	lookAt = dx::XMVectorAdd(GetPos(), lookAt);


	mViewMatrix = dx::XMMatrixLookAtLH(GetPos(), lookAt, up);
}

void Camera::Render()
{
	//dx::XMVECTOR up, position, lookAt;
	//float yaw, pitch, roll;
	//dx::XMMATRIX rotationMatrix;


	//// Setup the vector that points upwards.
	//up = {0.0f, 1.0f, 0.0f, 1.0f};

	//// Setup the position of the camera in the world.
	//position = GetPos();

	//// Setup where the camera is looking by default.
	//lookAt = { 0.0f, 0.0f, 1.0f, 1.0f };

	//// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	//pitch = GetRotX() * 0.0174532925f;
	//yaw = GetRotY() * 0.0174532925f;
	//roll = GetRotZ() * 0.0174532925f;

	//// Create the rotation matrix from the yaw, pitch, and roll values.
	//rotationMatrix = dx::XMMatrixRotationRollPitchYaw(yaw, pitch, roll);


	//lookAt = dx::XMVector4Transform(lookAt, rotationMatrix);
	//up = dx::XMVector4Transform(up, rotationMatrix);
	//// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	////D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	////D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	//// Translate the rotated camera position to the location of the viewer.
	//lookAt = dx::XMVectorAdd(position, lookAt);


	//mViewMatrix = dx::XMMatrixLookAtLH(position, lookAt, up);
	// Finally create the view matrix from the three updated vectors.
	//D3DXMatrixLookAtLH(&m_viewMatrix, &position, &lookAt, &up);
}

DirectX::XMVECTOR Camera::GetPos()
{
	return position;
}

float Camera::GetPosX()
{
	return dx::XMVectorGetX(position);
}

float Camera::GetPosY()
{
	return dx::XMVectorGetY(position);
}

float Camera::GetPosZ()
{
	return dx::XMVectorGetZ(position);
}

DirectX::XMVECTOR Camera::GetRot()
{
	return rotation;
}

float Camera::GetRotX()
{
	return dx::XMVectorGetX(rotation);
}

float Camera::GetRotY()
{
	return dx::XMVectorGetY(rotation);
}

float Camera::GetRotZ()
{
	return dx::XMVectorGetZ(rotation);
}

void Camera::SetPos(DirectX::XMVECTOR pos)
{
	position = pos;
}

void Camera::SetPos(float x, float y, float z)
{
	position = { x, y, z, dx::XMVectorGetW(position) };
}

void Camera::SetPosX(float x)
{
	position = { x, dx::XMVectorGetY(position), dx::XMVectorGetZ(position), dx::XMVectorGetW(position) };
}

void Camera::SetPosY(float y)
{
	position = { dx::XMVectorGetX(position), y, dx::XMVectorGetZ(position), dx::XMVectorGetW(position) };
}

void Camera::SetPosZ(float z)
{
	position = { dx::XMVectorGetX(position), dx::XMVectorGetY(position), z, dx::XMVectorGetW(position) };
}

void Camera::SetRot(DirectX::XMVECTOR rot)
{
	rotation = rot;
}

void Camera::SetRot(float x, float y, float z)
{
	rotation = { x, y, z, dx::XMVectorGetW(rotation) };
}

void Camera::SetRotX(float x)
{
	rotation = { x, dx::XMVectorGetY(rotation), dx::XMVectorGetZ(rotation), dx::XMVectorGetW(rotation) };
}

void Camera::SetRotY(float y)
{
	rotation = { dx::XMVectorGetX(rotation), y, dx::XMVectorGetZ(rotation), dx::XMVectorGetW(rotation) };
}

void Camera::SetRotZ(float z)
{
	rotation = { dx::XMVectorGetX(rotation), dx::XMVectorGetY(rotation), z, dx::XMVectorGetW(rotation) };
}

DirectX::XMMATRIX Camera::GetViewMatrix()
{
	return mViewMatrix;
}

void Camera::SetViewMatrix(DirectX::XMMATRIX matrix)
{
	mViewMatrix = matrix;
}
