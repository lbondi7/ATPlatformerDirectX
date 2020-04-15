#pragma once

#include "Maths.h"

const float GRAVITY = 9.80665f;
const float RADIAN = 57.29577951f;

enum class GameObjectTag : int
{
	STATIC = 0,
	MOVEABLE = 1,
	PLAYER = 2,
	GROUND = 3,
	KILLBOX = 4,
};

enum class PlayerMotionState : int
{
	GROUNDED = 0,
	FALLING = 1,
};

struct MatrixBufferType
{
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX projection;
};

struct VertexType
{
	struct
	{
		Vector position;
	}pos;

	struct
	{
		float u;
		float v;
	}txt;

	struct
	{
		Vector normal;
	}norm;

	//struct
	//{
	//	DirectX::XMVECTOR color;
	//}color;
};

struct ImageData
{
	struct ImageBufferData
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;

	}buffer;

	unsigned char* data = nullptr;
};