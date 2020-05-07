#pragma once

#include "Transform.h"
#include "Constants.h"
#include "PhysicsData.h"
#include "Maths.h"

#include <map>
#include <string>

class Player
{
public:

	Player() = default;
	~Player();

	void Init();
	void Update(PhysicsData& physData, Transform& goTranform);

	const Vec4& GetVelocity();

private:

	Vec4 mVelocity;
	float mass = 25;
	float acceleration = 0.0f;
	float drag = 200.0f;
	float mSpeed = 7500.0f;
	float mRotSpeed = 100000.0f;
	std::map<ObjectMotionState, std::string> stateMap;
};

