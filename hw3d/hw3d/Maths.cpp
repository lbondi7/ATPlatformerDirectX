#include "Maths.h"

using namespace DirectX;

Vector4 LewisMath::VectorMul(const Vector4& vec1, const Vector4& vec2)
{
	return XMVectorMultiply(vec1, vec2);
}

Vector4 LewisMath::VectorAdd(const Vector4& vec1, const Vector4& vec2)
{
	return XMVectorAdd(vec1, vec2);
}

Vector4 LewisMath::VectorSub(const Vector4& vec1, const Vector4& vec2)
{
	return XMVectorSubtract(vec1, vec2);
}

Vector4 LewisMath::VectorMultiplyByFloat(const Vector4& vec1, float val)
{
	return XMVectorMultiply(vec1, { val, val, val });
}

Vector4 LewisMath::VectorTransform(const Vector4& vec1, const Matrix& mat)
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

const Matrix& LewisMath::MatrixFromVector(const Vector4& vec)
{
	return XMMatrixRotationRollPitchYawFromVector(vec);
}

Vector4 LewisMath::Forward()
{
	return { 0, 0, 1, 1 };
}

Vector4 LewisMath::Up()
{
	return { 0, 1, 0, 1 };
}

Vector4 LewisMath::Right()
{
	return { 1, 0, 0, 1 };
}

Vector4 LewisMath::MoveForward(const Vector4& pos, float amount, float rotationY)
{
	return VectorAdd(pos, VectorTransform({ 0, 0, amount, 1 }, MatrixFromY(rotationY)));
}

Vector4 LewisMath::MoveBackward(const Vector4& pos, float amount, float rotationY)
{
	return VectorSub(pos, VectorTransform({ 0, 0, amount, 1 }, MatrixFromY(rotationY)));
}

float LewisMath::VectorX(const Vector4& vec)
{
	return XMVectorGetX(vec);
}

float LewisMath::VectorY(const Vector4& vec)
{
	return XMVectorGetY(vec);
}

float LewisMath::VectorZ(const Vector4& vec)
{
	return XMVectorGetZ(vec);
}
