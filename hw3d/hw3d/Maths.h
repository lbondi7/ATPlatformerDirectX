#pragma once

#include <DirectXMath.h>
/*
A wrapper for the direct x vector. It has 4 values x, y, z and w.
The last one doesn't need to be used.
*/
using Vector4 = DirectX::XMVECTOR;
using Matrix = DirectX::XMMATRIX;
using Float4 = DirectX::XMFLOAT4;

namespace LewisMath
{
	/* Returns the multiplication of the two vectors */
	Vector4 VectorMul(const Vector4& vec1, const Vector4& vec2);

	/* Returns the addition of the two vectors */
	Vector4 VectorAdd(const Vector4& vec1, const Vector4& vec2);

	/* Returns the subtraction of the two vectors */
	Vector4 VectorSub(const Vector4& vec1, const Vector4& vec2);

	/* Returns the multiplication of the a vector and a float */
	Vector4 VectorMultiplyByFloat(const Vector4& vec1, float val);

	/* Returns the transform vector of the vector and the matrix */
	Vector4 VectorTransform(const Vector4& vec1, const Matrix& mat);

	/* Returns a matrix of X */
	const Matrix& MatrixFromX(float x);

	/* Returns a matrix of Y */
	Matrix MatrixFromY(float y);

	/* Returns a matrix of Z */
	const Matrix& MatrixFromZ(float z);

	/* Returns a matrix from a vector */
	const Matrix& MatrixFromVector(const Vector4& vec);

	/* Returns a default forward vector */
	Vector4 Forward();

	/* Returns a default up vector */
	Vector4 Up();

	/* Returns a default right vector */
	Vector4 Right();

	/* Returns a vector that is calculated by using the vector passed in and moving it forward by
	the amount passed in and the direction based of the Y rotation passed in*/
	Vector4 MoveForward(const Vector4& pos, float amount, float rotationY);

	/* Returns a vector that is calculated by using the vector passed in and moving it backward by
	the amount passed in and the direction based of the Y rotation passed in*/
	Vector4 MoveBackward(const Vector4& pos, float amount, float rotationY);

	/* Returns the X value of the vector passed in */
	float VectorX(const Vector4& vec);

	/* Returns the Y value of the vector passed in */
	float VectorY(const Vector4& vec);

	/* Returns the Z value of the vector passed in */
	float VectorZ(const Vector4& vec);

};

using namespace LewisMath;

