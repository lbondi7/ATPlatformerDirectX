#pragma once

#include "Maths.h"
#include "Transform.h"
#include "Ray.h"

#include <vector>

struct Bounds
{
	Float3 m_Min = { FLT_MAX, FLT_MAX, FLT_MAX };
	Float3 m_Max = { FLT_MIN, FLT_MIN, FLT_MIN };

	void CalculateBoundingBox(const Vec4& pos, const std::vector<Float3> & verts, Matrix& worldMatrix);
	bool IsInside(const Float3& objBBMinVertex, const Float3& objBBMaxVertex);
	bool IsInside(const Bounds& other);
	bool RayBoxIntersect(Ray& r);
};

