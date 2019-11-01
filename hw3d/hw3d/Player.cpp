#include "Player.h"
#include "Locator.h"
#include "Timer.h"
#include "WinSetup.h"
#include "Keyboard.h"

#include <iostream>

using namespace DirectX;

Player::~Player()
{
}

void Player::Init()
{
	velocity = XMVectorZero();
}

void Player::Update(Transform& goTransform)
{
	if (Locator::GetKey()->IsKeyPressed('W') || Locator::GetKey()->IsKeyRepeated('W'))
	{
		goTransform.SetPos(MoveForward(
			goTransform.GetPos(),
			speed * Locator::GetTimer()->DeltaTime(),
			goTransform.GetRotYRad()));
	}
	else if (Locator::GetKey()->IsKeyPressed('S') || Locator::GetKey()->IsKeyRepeated('S'))
	{
		goTransform.SetPos(MoveBackward(
			goTransform.GetPos(),
			speed * Locator::GetTimer()->DeltaTime(),
			goTransform.GetRotYRad()));
	}
	if (Locator::GetKey()->IsKeyPressed('Q') || Locator::GetKey()->IsKeyRepeated('Q'))
	{
		goTransform.SetRotY(goTransform.GetRotY() - rotSpeed * Locator::GetTimer()->DeltaTime());
	}
	else if (Locator::GetKey()->IsKeyPressed('E') || Locator::GetKey()->IsKeyRepeated('E'))
	{
		goTransform.SetRotY(goTransform.GetRotY() + rotSpeed * Locator::GetTimer()->DeltaTime());
	}

	switch (state)
	{
	case PlayerMotionState::GROUNDED:
	{
		acceleration = 0;
		velocity = VectorSetY(velocity, 0);
		if (Locator::GetKey()->IsKeyPressed(VK_SPACE) && state == PlayerMotionState::GROUNDED)
		{
			goTransform.SetPos(VectorAdd(goTransform.GetPos(), {0, 0.2f, 0}));
			velocity = VectorSetY(velocity, 20000);
			state = PlayerMotionState::FALLING;
		}
		break;
	}
	case PlayerMotionState::FALLING:
	{
		acceleration += (gravityForce * mass);
		acceleration -= drag;
		velocity = VectorSetY(velocity, VectorY(velocity) - acceleration);

		goTransform.SetPos(goTransform.GetPos() + velocity * (Locator::GetTimer()->DeltaTime()));
		break;
	}
	}

}

PlayerMotionState Player::GetState()
{
	return state;
}

void Player::SetState(PlayerMotionState _state)
{
	state = _state;
}
