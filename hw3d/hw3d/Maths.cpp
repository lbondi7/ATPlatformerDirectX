#include "Maths.h"

using namespace DirectX;

Vector LewisMath::VectorMul(const Vector& vec1, const Vector& vec2)
{
	return XMVectorMultiply(vec1, vec2);
}

Vector LewisMath::VectorAdd(const Vector& vec1, const Vector& vec2)
{
	return XMVectorAdd(vec1, vec2);
}

Vector LewisMath::VectorSub(const Vector& vec1, const Vector& vec2)
{
	return XMVectorSubtract(vec1, vec2);
}

Vector LewisMath::VectorMultiplyByFloat(const Vector& vec1, float val)
{
	return XMVectorScale(vec1, val);
}

Vector LewisMath::VectorTransform(const Vector& vec1, const Matrix& mat)
{
	return XMVector4Transform(vec1, mat);
}

const Matrix& LewisMath::MatrixFromX(float x)
{
	return XMMatrixRotationX(x);
}

Matrix LewisMath::MatrixFromY(float y)
{
	return XMMatrixRotationY(y);
}

const Matrix& LewisMath::MatrixFromZ(float z)
{
	return XMMatrixRotationZ(z);
}

const Matrix& LewisMath::MatrixFromVector(const Vector& vec)
{
	return XMMatrixRotationRollPitchYawFromVector(vec);
}

Vector LewisMath::Forward()
{
	return { 0.0f, 0.0f, 1.0f, 1.0f };
}

Vector LewisMath::Up()
{
	return { 0.0f, 1.0f, 0.0f, 1.0f };
}

Vector LewisMath::Right()
{
	return { 1.0f, 0.0f, 0.0f, 1.0f };
}

Vector LewisMath::MoveForward(const Vector& pos, float amount, float rotationY)
{
	return XMVectorAdd(pos, XMVector3Transform({ 0, 0, amount, 1 }, XMMatrixRotationY(rotationY)));
}

Vector LewisMath::MoveBackward(const Vector& pos, float amount, float rotationY)
{
	return XMVectorSubtract(pos, XMVector3Transform({ 0, 0, amount, 1 }, XMMatrixRotationY(rotationY)));
}

float LewisMath::VectorX(const Vector& vec)
{
	//return XMVectorGetX(vec);
	return vec.m128_f32[0];
}

float LewisMath::VectorY(const Vector& vec)
{
	//return XMVectorGetY(vec);
	return vec.m128_f32[1];
}

float LewisMath::VectorZ(const Vector& vec)
{
	//return XMVectorGetZ(vec);
	return vec.m128_f32[2];
}

Vector LewisMath::VectorSetX(const Vector& vec, float x)
{
	return { x, vec.m128_f32[1], vec.m128_f32[2] };
}

Vector LewisMath::VectorSetY(const Vector& vec, float y)
{
	return { vec.m128_f32[0], y, vec.m128_f32[2] };
}

Vector LewisMath::VectorSetZ(const Vector& vec, float z)
{
	return { vec.m128_f32[0], vec.m128_f32[1], z };
}
