#pragma once

#include "Maths.h"

#include <string>
#include <vector>

namespace Utilities
{
	const std::vector<Vec4>& ConvertToVec4StdVec(const std::vector<Float3>& other);

	const Vec4& ConvertToVec4Point(const Float3& other);

	const Vec4& ConvertToVec4Dir(const Float3& other);

	const Float3& ConvertToFloat3(const Vec4& other);

	const Float3& AddFloat(const Float3& f1, const Float3& f2);

}