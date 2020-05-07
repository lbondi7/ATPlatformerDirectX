#include "Bounds.h"
#include "Utilities.h"

#include <algorithm>

using namespace DirectX;

void Bounds::CalculateBoundingBox(const Vec4& pos, const std::vector<Float3>& verts, Matrix& worldMatrix)
{
	XMFLOAT3 minVert = XMFLOAT3(FLT_MAX, FLT_MAX, FLT_MAX);
	XMFLOAT3 maxVert = XMFLOAT3(FLT_MIN, FLT_MIN, FLT_MIN);
	m_Min = { FLT_MAX, FLT_MAX, FLT_MAX };
	m_Max = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
	Vec4 vec;
	for (size_t i = 0; i < verts.size(); i++)
	{
		vec = Utilities::ConvertToVec4Point(verts[i]);

		vec = XMVector3Transform(vec, worldMatrix);
		
		//Get the smallest vertex 
		m_Min.x = std::min(m_Min.x, XMVectorGetX(vec));
		m_Min.y = std::min(m_Min.y, XMVectorGetY(vec));
		m_Min.z = std::min(m_Min.z, XMVectorGetZ(vec));

		//Get the largest vertex 
		m_Max.x = std::max(m_Max.x, XMVectorGetX(vec));
		m_Max.y = std::max(m_Max.y, XMVectorGetY(vec));
		m_Max.z = std::max(m_Max.z, XMVectorGetZ(vec));
	}

	//mBBMin = { minVert.x, minVert.y, minVert.z };
	//mBBMax = { maxVert.x, maxVert.y, maxVert.z };
}

bool Bounds::IsInside(const Float3& objBBMinVertex,
	const Float3& objBBMaxVertex)
{
	//Is obj1's max X greater than obj2's min X? If not, obj1 is to the LEFT of obj2
	if ((m_Max.x > objBBMinVertex.x && m_Min.x < objBBMaxVertex.x) &&
		(m_Max.y > objBBMinVertex.y && m_Min.y < objBBMaxVertex.y) && 
		(m_Max.z > objBBMinVertex.z && m_Min.z < objBBMaxVertex.z))
		return true;

	//If the two bounding boxes are not colliding, then return false
	return false;
}

bool Bounds::IsInside(const Bounds& other)
{
	//Is obj1's max X greater than obj2's min X? If not, obj1 is to the LEFT of obj2
	if ((m_Max.x >= other.m_Min.x && m_Min.x <= other.m_Max.x))
		if ((m_Max.y >= other.m_Min.y && m_Min.y <= other.m_Max.y))
			if ((m_Max.z >= other.m_Min.z && m_Min.z <= other.m_Max.z))
			return true;

	//If the two bounding boxes are not colliding, then return false
	return false;
}


bool Bounds::RayBoxIntersect(Ray& r)
{
	float txmin = (m_Min.x - r.Origin().x) * r.InvDirection().x;
	float txmax = (m_Max.x - r.Origin().x) * r.InvDirection().x;

	float tymin = (m_Min.y - r.Origin().y) * r.InvDirection().y;
	float tymax = (m_Max.y - r.Origin().y) * r.InvDirection().y;

	float tzmin = (m_Min.z - r.Origin().z) * r.InvDirection().z;
	float tzmax = (m_Max.z - r.Origin().z) * r.InvDirection().z;

	float tmin = std::max(std::max(std::min(txmin, txmax), std::min(tymin, tymax)), std::min(tzmin, tzmax));
	float tmax = std::min(std::min(std::max(txmin, txmax), std::max(tymin, tymax)), std::max(tzmin, tzmax));

	if (tmax < 0)
	{
		r.T(tmax);
		return false;
	}

	if (tmin > tmax)
	{
		r.T(tmax);
		return false;
	}

	if (tmin < 0) {
		r.T(tmax);
	}
	else {
		r.T(tmin);
	}
	return true;
}