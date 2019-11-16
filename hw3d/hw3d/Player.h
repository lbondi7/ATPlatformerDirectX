#pragma once

#include "Transform.h"
#include "Constants.h"
#include "Maths.h"

#include <map>
#include <string>

class Player
{
public:

	Player() = default;
	~Player();

	void Init();
	void Update(Transform& goTranform);

	PlayerMotionState GetState();

	void SetState(PlayerMotionState _state);

	const Vector& GetVelocity();

private:

	PlayerMotionState state = PlayerMotionState::FALLING;
	Vector mVelocity;
	float mass = 25;
	float acceleration = 0.0f;
	float drag = 200.0f;
	float mSpeed = 7500.0f;
	float mRotSpeed = 100000.0f;
	std::map<PlayerMotionState, std::string> stateMap;
};

