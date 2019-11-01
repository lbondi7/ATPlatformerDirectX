#pragma once

#include "Maths.h"
#include "Transform.h"

#include <vector>

struct Bounds
{
public:

	Vector mBBMin;
	Vector mBBMax;

	void CalculateBoundingBox(const Vector& pos, const std::vector<Vector> & verts, const Matrix& worldMatrix);
	bool IsInside(const Vector& objBBMinVertex, const Vector& objBBMaxVertex);
};

