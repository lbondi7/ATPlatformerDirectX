#include "Utilities.h"

const std::vector<Vec4>& Utilities::ConvertToVec4StdVec(const std::vector<Float3>& other)
{
	std::vector<Vec4> v;
	v.resize(other.size());

	for (size_t i = 0; i < v.size(); i++)
	{
		v[i].m128_f32[0] = other[i].x;
		v[i].m128_f32[1] = other[i].y;
		v[i].m128_f32[2] = other[i].z;
		v[i].m128_f32[3] = 1;
	}
	return v;
}

const Vec4& Utilities::ConvertToVec4Point(const Float3& other)
{
	Vec4 v;
	v.m128_f32[0] = other.x;
	v.m128_f32[1] = other.y;
	v.m128_f32[2] = other.z;
	v.m128_f32[3] = 1;
	return v;
}

const Vec4& Utilities::ConvertToVec4Dir(const Float3& other)
{
	Vec4 v;
	v.m128_f32[0] = other.x;
	v.m128_f32[1] = other.y;
	v.m128_f32[2] = other.z;
	v.m128_f32[3] = 0;
	return v;
}

const Float3& Utilities::ConvertToFloat3(const Vec4& other)
{
	Float3 f;
	f.x = other.m128_f32[0];
	f.y = other.m128_f32[1];
	f.z = other.m128_f32[2];
	return f;
}

const Float3& Utilities::AddFloat(const Float3& f1, const Float3& f2)
{
	Float3 f;
	f.x = f1.x + f2.x;
	f.y = f1.y + f2.y;
	f.z = f1.z + f2.z;
	return f;
}

