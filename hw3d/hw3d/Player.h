#pragma once

#include "Transform.h"
#include "Constants.h"
#include "Maths.h"

class Player
{
public:

	Player() = default;
	~Player();

	void Init();
	void Update(Transform& goTranform);

	PlayerMotionState GetState();

	void SetState(PlayerMotionState _state);

private:

	PlayerMotionState state = PlayerMotionState::FALLING;
	Vector velocity;
	float mass = 25;
	float acceleration = 0.0f;
	float drag = 200.0f;
	float speed = 7500.0f;
	float rotSpeed = 100000.0f;
};

