#pragma once

#include <DirectXMath.h>

/*
A wrapper for the direct x vector. It has 4 values x, y, z and w.
The last one doesn't need to be used.
*/
using Vector = DirectX::XMVECTOR;
using Matrix = DirectX::XMMATRIX;
using Float4 = DirectX::XMFLOAT4;

namespace LewisMath
{
	/* Returns the multiplication of the two vectors */
	Vector VectorMul(const Vector& vec1, const Vector& vec2);

	/* Returns the addition of the two vectors */
	Vector VectorAdd(const Vector& vec1, const Vector& vec2);

	/* Returns the subtraction of the two vectors */
	Vector VectorSub(const Vector& vec1, const Vector& vec2);

	/* Returns the multiplication of the a vector and a float */
	Vector VectorMultiplyByFloat(const Vector& vec1, float val);

	/* Returns the transform vector of the vector and the matrix */
	Vector VectorTransform(const Vector& vec1, const Matrix& mat);

	/* Returns a matrix of X */
	const Matrix& MatrixFromX(float x);

	/* Returns a matrix of Y */
	Matrix MatrixFromY(float y);

	/* Returns a matrix of Z */
	const Matrix& MatrixFromZ(float z);

	/* Returns a matrix from a vector */
	const Matrix& MatrixFromVector(const Vector& vec);

	/* Returns a default forward vector */
	Vector Forward();

	/* Returns a default up vector */
	Vector Up();

	/* Returns a default right vector */
	Vector Right();

	/* Returns a vector that is calculated by using the vector passed in and moving it forward by
	the amount passed in and the direction based of the Y rotation passed in*/
	Vector MoveForward(const Vector& pos, float amount, float rotationY);

	/* Returns a vector that is calculated by using the vector passed in and moving it backward by
	the amount passed in and the direction based of the Y rotation passed in*/
	Vector MoveBackward(const Vector& pos, float amount, float rotationY);

	/* Returns the X value of the vector passed in */
	float VectorX(const Vector& vec);

	/* Returns the Y value of the vector passed in */
	float VectorY(const Vector& vec);

	/* Returns the Z value of the vector passed in */
	float VectorZ(const Vector& vec);

	/* Sets the X value of the vector passed in to the float value passed in */
	Vector VectorSetX(const Vector& vec, float x);

	/* Sets the Y value of the vector passed in to the float value passed in */
	Vector VectorSetY(const Vector& vec, float y);

	/* Sets the Z value of the vector passed in to the float value passed in */
	Vector VectorSetZ(const Vector& vec, float z);

//	Vector GetVecterDir(const Vector& vec);

};

using namespace LewisMath;

