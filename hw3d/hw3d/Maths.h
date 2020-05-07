#pragma once

#include <DirectXMath.h>

/*
A wrapper for the direct x vector. It has 4 values x, y, z and w.
The last one doesn't need to be used.
*/
using Vec4 = DirectX::XMVECTOR;
using Matrix = DirectX::XMMATRIX;
using Float4 = DirectX::XMFLOAT4;
using Float3 = DirectX::XMFLOAT3;
using Float2 = DirectX::XMFLOAT2;
using Int3 = DirectX::XMINT3;

namespace LewisMath
{
	/* Returns the multiplication of the two vectors */
	Vec4 VectorMul(const Vec4& vec1, const Vec4& vec2);

	/* Returns the addition of the two vectors */
	Vec4 VecAdd(const Vec4& vec1, const Vec4& vec2);

	/* Returns the subtraction of the two vectors */
	Vec4 VectorSub(const Vec4& vec1, const Vec4& vec2);

	Vec4 VectDiv(const Vec4& vec1, const Vec4& vec2);

	/* Returns the multiplication of the a vector and a float */
	Vec4 VecScale(const Vec4& vec1, float val);

	/* Returns the transform vector of the vector and the matrix */
	Vec4 VectorTransform(const Vec4& vec1, const Matrix& mat);

	/* Returns a matrix of X */
	const Matrix& MatrixFromX(float x);

	/* Returns a matrix of Y */
	Matrix MatrixFromY(float y);

	/* Returns a matrix of Z */
	const Matrix& MatrixFromZ(float z);

	/* Returns a matrix from a vector */
	const Matrix& MatrixFromVector(const Vec4& vec);

	/* Returns a default forward vector */
	Vec4 Forward();

	/* Returns a default up vector */
	Vec4 Up();

	/* Returns a default right vector */
	Vec4 Right();

	/* Returns a vector that is calculated by using the vector passed in and moving it forward by
	the amount passed in and the direction based of the Y rotation passed in*/
	Vec4 MoveForward(const Vec4& pos, float amount, float rotationY);

	/* Returns a vector that is calculated by using the vector passed in and moving it backward by
	the amount passed in and the direction based of the Y rotation passed in*/
	Vec4 MoveBackward(const Vec4& pos, float amount, float rotationY);

	/* Returns the X value of the vector passed in */
	float VectorX(const Vec4& vec);

	/* Returns the Y value of the vector passed in */
	float VectorY(const Vec4& vec);

	/* Returns the Z value of the vector passed in */
	float VectorZ(const Vec4& vec);

	/* Sets the X value of the vector passed in to the float value passed in */
	Vec4 VectorSetX(const Vec4& vec, float x);

	/* Sets the Y value of the vector passed in to the float value passed in */
	Vec4 VectorSetY(const Vec4& vec, float y);

	/* Sets the Z value of the vector passed in to the float value passed in */
	Vec4 VectorSetZ(const Vec4& vec, float z);

//	Vector GetVecterDir(const Vector& vec);

};

using namespace LewisMath;

