#pragma once

#include "Constants.h"

const float FIXED_DT = 1.0f / 60.0f;

enum class PhysicsTag : int
{
	STATIC = 0,
	MOVEABLE = 1,
};

struct PhysicsData
{
	float m_Mass = 1.0f;
	Float2 m_Force = { 0.0f, 0.0f };
	Float3 m_Acceleration = { 0.0f, 0.0f, 0.0f };
	Float3 m_Velocity = { 0.0f, 0.0f, 0.0f };
	Float3 m_PrevVelocity = { 0.0f, 0.0f, 0.0f };
	Float3 m_ForceDir = { 0.0f, 0.0f, 0.0f };

	PhysicsTag physicsTag = PhysicsTag::STATIC;
	ObjectMotionState motionState = ObjectMotionState::FALLING;

};