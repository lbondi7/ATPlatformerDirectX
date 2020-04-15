#pragma once

#include "Constants.h"

#include <vector>
#include <map>
#include <string>

enum DataTypes {
	MODELS = 0,
	TEXTURES = 1,
	SHADERS = 2,
};

struct ResourceData
{
	ResourceData();

	bool LoadImageData(std::string image);

	std::map<std::string, ImageData> images;
};

