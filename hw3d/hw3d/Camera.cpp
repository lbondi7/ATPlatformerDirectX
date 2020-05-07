#include "Camera.h"
#include "Locator.h"
#include "D3D.h"

#include "imgui/imgui.h"


Camera::Camera()
{
	//m_Transform.position = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_LookAtPos = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_Up = { 0.0f, 1.0f, 0.0f, 1.0f };
	m_Offset = { 0.0f, 0.0f, -10.0f, 1.0f };
}

Camera::~Camera()
{
}

void Camera::Init()
{
	mViewMatrix = &Locator::GetD3D()->GetViewMatrix();
}

void Camera::Update()
{
	//up = { 0.0f, 1.0f, 0.0f, 1.0f };

	//// Setup where the camera is looking by default.
	//lookAtPos = { 0.0f, 0.0f, 1.0f, 1.0f };

	//// Create the rotation matrix from the yaw, pitch, and roll values.
	////rotationMatrix = dx::XMMatrixRotationRollPitchYawFromVector(transform.GetRotRad());

	//rotationMatrix = XMMatrixRotationRollPitchYaw(
	//	transform.GetRotY() * 0.0174532925f,
	//	transform.GetRotX() * 0.0174532925f,
	//	transform.GetRotZ() * 0.0174532925f);

	////distance = dx::XMVectorSubtract(lookAtPos, transform.GetPos());

	//// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	//lookAtPos = XMVector4Transform(lookAtPos, rotationMatrix);
	//up = XMVector4Transform(up, rotationMatrix);

	//// Translate the rotated camera position to the location of the viewer.
	//lookAtPos = XMVectorAdd(transform.GetPos(), lookAtPos);

	////pos = VectorTransform(transform.GetPos(),
	////	XMMatrixRotationRollPitchYaw(phi, -theta, 0));

	//*mViewMatrix = XMMatrixLookAtLH(transform.GetPos(), lookAtPos,
	//	up);

	//transform.SetPos(VectorAdd(lookAtPos,
	//	VectorTransform(VectorMul(offset,
	//		{ sinf(0.0f / 57.2958f) , sinf(0.0f / 57.2958f) , cosf(0.0f / 57.2958f) }),
	//	XMMatrixRotationRollPitchYawFromVector(transform.GetRotRad()))));
	//
	////const auto pos = VectorTransform(transform.GetPos(),
	////	XMMatrixRotationRollPitchYaw(phi, -theta, 0.0f));


	//const auto pos = VectorTransform(m_Transform.GetPos(), m_RotationMatrix);
	//const auto pos2 = VectorTransform(m_LookAtPos, m_RotationMatrix);
	//const auto pos3 = VectorTransform(m_Up, m_RotationMatrix);
	//auto hey = VectorAdd(pos2, pos);

	//m_RotationMatrix = XMMatrixRotationRollPitchYawFromVector(m_Transform.GetRotRad());


	m_Transform.SetPos(DirectX::XMVectorAdd(m_LookAtPos,  m_Offset));
	//const auto pos = VectorTransform(m_Transform.GetPos(), XMMatrixRotationRollPitchYawFromVector(m_Transform.GetRotRad()));

	*mViewMatrix = DirectX::XMMatrixLookAtLH(m_Transform.GetPos(), m_LookAtPos, m_Up);
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
	// lookAt = { 0.0f, 0.0f, 1.0f, 1.0f };

	//// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	// pitch = GetRotX() * 0.0174532925f;
	// yaw = GetRotY() * 0.0174532925f;
	// roll = GetRotZ() * 0.0174532925f;

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

	if (ImGui::Begin("Camera Offset"))
	{
		ImGui::SliderFloat("Cam X Off", &m_Offset.m128_f32[0], -5.0f, 5.0f);
		ImGui::SliderFloat("Cam Y Off", &m_Offset.m128_f32[1], 0.0f, 10.0f);
		ImGui::SliderFloat("Cam Z Off", &m_Offset.m128_f32[2], -20.0f, 0.0f);
	}
	ImGui::End();
}

void Camera::SetLookAt(const Vec4& _lookAt)
{
	m_LookAtPos = _lookAt;
}

void Camera::SetRotMatrix(const Matrix& rotMat)
{
	m_RotationMatrix = rotMat;
}

Transform& Camera::GetTransform()
{
	return m_Transform;
}

void Camera::SetOffset(const Vec4& _offset)
{

}

void Camera::SetPhiTheta(float _phi, float _theta)
{
	phi = _phi;
	theta = -_theta;
}
