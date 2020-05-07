#pragma once
#include "Utilities.h"

const unsigned int WINDOW_WIDTH = 1200;
const unsigned int WINDOW_HEIGHT = 800;

const float GRAVITY = 9.80665f;
const float RADIAN = 57.29577951f;

enum class GameObjectTag : int
{
	STATIC = 0,
	MOVEABLE = 1,
	PLAYER = 2,
	GROUND = 3,
	KILLBOX = 4,
	PROP = 5
};

enum class ObjectMotionState : int
{
	GROUNDED = 0,
	FALLING = 1,
};

struct MatrixBufferData
{
	alignas(16) DirectX::XMMATRIX world;
	alignas(16) DirectX::XMMATRIX view;
	alignas(16) DirectX::XMMATRIX projection;
};

struct VertexType
{
	struct
	{
		Vec4 position;
	}pos;

	struct
	{
		float u;
		float v;
	}txt;

	struct
	{
		Vec4 normal;
	}norm;
};

struct Vertex
{
	alignas(16) Float3 position;
	alignas(16) Float2 texCoord;
	alignas(16) Float3 normal;

	bool operator==(const Vertex other) const {
		bool posCheck = (position.x == other.position.x && position.y == other.position.y && position.z == other.position.z);
		bool texCheck = (texCoord.x == other.texCoord.x && texCoord.y == other.texCoord.y);
		bool normCheck = (normal.x == other.normal.x && normal.y == other.normal.y && normal.z == other.normal.z);
		return posCheck && texCheck && normCheck;
	}
};
