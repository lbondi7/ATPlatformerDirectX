#pragma once

const float gravityForce = 9.80665f;

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