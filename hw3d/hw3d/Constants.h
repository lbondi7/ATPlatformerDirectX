#pragma once

const float GRAVITY = 9.80665f;
const float RADIAN = 57.29577951;

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