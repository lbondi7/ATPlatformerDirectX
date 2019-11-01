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
	return XMVector3Transform(vec1, mat);
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
	return { 0, 0, 1, 1 };
}

Vector LewisMath::Up()
{
	return { 0, 1, 0, 1 };
}

Vector LewisMath::Right()
{
	return { 1, 0, 0, 1 };
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
	return XMVectorGetX(vec);
}

float LewisMath::VectorY(const Vector& vec)
{
	return XMVectorGetY(vec);
}

float LewisMath::VectorZ(const Vector& vec)
{
	return XMVectorGetZ(vec);
}

Vector LewisMath::VectorSetX(const Vector& vec, float x)
{
	return { x, XMVectorGetY(vec), XMVectorGetZ(vec) };
}

Vector LewisMath::VectorSetY(const Vector& vec, float y)
{
	return { XMVectorGetX(vec), y, XMVectorGetZ(vec) };
}

Vector LewisMath::VectorSetZ(const Vector& vec, float z)
{
	return { XMVectorGetX(vec), XMVectorGetY(vec), z };
}
