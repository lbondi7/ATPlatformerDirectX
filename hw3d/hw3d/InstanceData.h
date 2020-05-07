#pragma once

#include "Bounds.h"

struct InstanceData {

	int instanceCount = 0;

	std::vector<Bounds> instanceBounds;
	std::vector<Vec4> positions;
	std::vector<Vec4> rotations;
	std::vector<Vec4> scales;
};