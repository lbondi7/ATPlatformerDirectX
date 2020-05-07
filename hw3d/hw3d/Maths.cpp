#include "Maths.h"

using namespace DirectX;

Vec4 LewisMath::VectorMul(const Vec4& vec1, const Vec4& vec2)
{
	return XMVectorMultiply(vec1, vec2);
}

Vec4 LewisMath::VecAdd(const Vec4& vec1, const Vec4& vec2)
{
	return XMVectorAdd(vec1, vec2);
}

Vec4 LewisMath::VectorSub(const Vec4& vec1, const Vec4& vec2)
{
	return XMVectorSubtract(vec1, vec2);
}

Vec4 LewisMath::VectDiv(const Vec4& vec1, const Vec4& vec2)
{
	return XMVectorDivide(vec1, vec2);
}

Vec4 LewisMath::VecScale(const Vec4& vec1, float val)
{
	return XMVectorScale(vec1, val);
}

Vec4 LewisMath::VectorTransform(const Vec4& vec1, const Matrix& mat)
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

const Matrix& LewisMath::MatrixFromVector(const Vec4& vec)
{
	return XMMatrixRotationRollPitchYawFromVector(vec);
}

Vec4 LewisMath::Forward()
{
	return { 0.0f, 0.0f, 1.0f, 1.0f };
}

Vec4 LewisMath::Up()
{
	return { 0.0f, 1.0f, 0.0f, 1.0f };
}

Vec4 LewisMath::Right()
{
	return { 1.0f, 0.0f, 0.0f, 1.0f };
}

Vec4 LewisMath::MoveForward(const Vec4& pos, float amount, float rotationY)
{
	return XMVectorAdd(pos, XMVector3Transform({ 0, 0, amount, 1 }, XMMatrixRotationY(rotationY)));
}

Vec4 LewisMath::MoveBackward(const Vec4& pos, float amount, float rotationY)
{
	return XMVectorSubtract(pos, XMVector3Transform({ 0, 0, amount, 1 }, XMMatrixRotationY(rotationY)));
}

float LewisMath::VectorX(const Vec4& vec)
{
	//return XMVectorGetX(vec);
	return vec.m128_f32[0];
}

float LewisMath::VectorY(const Vec4& vec)
{
	//return XMVectorGetY(vec);
	return vec.m128_f32[1];
}

float LewisMath::VectorZ(const Vec4& vec)
{
	//return XMVectorGetZ(vec);
	return vec.m128_f32[2];
}

Vec4 LewisMath::VectorSetX(const Vec4& vec, float x)
{
	return { x, vec.m128_f32[1], vec.m128_f32[2] };
}

Vec4 LewisMath::VectorSetY(const Vec4& vec, float y)
{
	return { vec.m128_f32[0], y, vec.m128_f32[2] };
}

Vec4 LewisMath::VectorSetZ(const Vec4& vec, float z)
{
	return { vec.m128_f32[0], vec.m128_f32[1], z };
}
